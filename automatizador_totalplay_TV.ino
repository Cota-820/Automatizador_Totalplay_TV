#include "config.h"
#include "IR.h"
#include "display.h"
#include "local_time.h"
#include "buttons.h"
#include "menu.h"
#include <IRremote.h>
#include "string.h"

#define COUNTDOWN_MS_TO_WAIT 1000
#define MENU_MS_TO_WAIT 30000

enum state{
  STATE_COUNTDOWN,
  STATE_SEND,
  STATE_MENU,
};

uint8_t state = STATE_COUNTDOWN, lastDay;
bool menuInitialized = false;
unsigned long currentMillis, lastMillisCountdown = 0, lastMillisMenu = 0;
char screenText[128] = {0}; 

void setup() {
  Serial.begin(115200);

  initTime();

  pinMode(BUILD_IN_LED, OUTPUT);
  pinMode(LED_IR_PIN, OUTPUT);
  
  initButtonPins();

  initDisplay(BUILD_IN_LED);  

  IrSender.begin(LED_IR_PIN);

  state = STATE_SEND;

  delay(1000); //TEMP
}

void loop() {
  currentMillis = millis();

  if (wasPressed(btnSend))
    state = STATE_SEND;
    menuInitialized = false;

  switch(state){
    case STATE_COUNTDOWN:
      //cambiar a menu si se presiono boton
      if (wasPressed(btnMiddle))
        state = STATE_MENU;

      //actualizar pantalla cada segundo
      if (currentMillis - lastMillisCountdown >= COUNTDOWN_MS_TO_WAIT) {
        lastMillisCountdown = currentMillis;

        uint16_t secondsCountdown = getSecondsCountdown();
        uint32_t seconds = getSeconds();
        uint8_t day = getDay();
        
        //si no acabo el tiempo, y no es otro dia, actualiza pantalla
        if(secondsCountdown != 0 && day==lastDay)
          showTimeOnScreen(secondsCountdown, seconds, day);
        else
          state = STATE_SEND;

        lastDay = day;
      }
      break;

    case STATE_SEND:
      stopSuspension();
      resetCountdown();
      state = STATE_COUNTDOWN;
      break;
    case STATE_MENU:
      if(!menuInitialized){
        restartMenu();
        menuInitialized = true;
      }

      uint8_t menuExitFlag = updateMenu(wasPressed(btnMiddle), wasPressed(btnLeft), wasPressed(btnRight));

      //accion a realizar dependiendo de bandera de salida
      switch (menuExitFlag){
        case NO_CHANGE:
          if (currentMillis - lastMillisMenu >= MENU_MS_TO_WAIT){
            menuInitialized = false;
            STATE = STATE_COUNTDOWN;
          }
          break;
        case UPDATED_SCREEN:
          lastMillisMenu = currentMillis;
          break;
        case EXIT_SEND_SIGNAL:
          menuInitialized = false;
          STATE = STATE_SEND;
          break;
        case EXIT_COUNTDOWN:
          menuInitialized = false;
          STATE = STATE_COUNTDOWN;
          break;
      }

      break;
  }

  updateButtons();
}

void stopSuspension(){
  for(int i=0; i<2 ; i++){ //WIP change ok for channel num 
    sendSignal(ADDRESS, BACK_CMMD, BACK_CMMD_NAME, 1000);
    sendSignal(ADDRESS, OK_CMMD, OK_CMMD_NAME, 1000);
  }
}

void sendSignal(uint16_t address, uint8_t command, char *signalName, int msToWait){
  sprintf(screenText, "Enviado, espera... \n\nBoton: %s", signalName);
  showTextOnScreen(screenText);
  IrSender.sendNEC(ADDRESS, OK_CMMD, 0);
  vTaskDelay(pdMS_TO_TICKS(msToWait));
}
