#include "config.h"
#include "IR.h"
#include "display.h"
#include "local_time.h"
#include "buttons.h"
#include "menu.h"
#include "string.h"

#define COUNTDOWN_MS_TO_WAIT 1000
#define MENU_MS_TO_WAIT 60000

enum state{
  STATE_COUNTDOWN,
  STATE_SEND,
  STATE_MENU,
};

uint8_t state = STATE_COUNTDOWN;
unsigned long currentMillis, lastMillisCountdown = 0, lastMillisMenu = 0;

void setup() {
  Serial.begin(115200);

  initTime();
  initMenu();
  initChannels();

  pinMode(BUILD_IN_LED, OUTPUT);
  pinMode(LED_IR_PIN, OUTPUT);
  
  initButtonPins();

  initDisplay(BUILD_IN_LED);  

  delay(1000);
}

void loop() {
  currentMillis = millis();

  if (wasPressed(btnSend))
    state = STATE_SEND;

  switch(state){
    case STATE_COUNTDOWN:
      //cambiar a menu si se presiono boton
      if (wasPressed(btnMiddle)){
        restartMenu();
        state = STATE_MENU;
      }

      //actualizar pantalla cada segundo
      if (currentMillis - lastMillisCountdown >= COUNTDOWN_MS_TO_WAIT) {
        lastMillisCountdown = currentMillis;

        uint16_t secondsCountdown = getSecondsCountdown();
        
        //si no acabo el tiempo, actualiza pantalla
        if(secondsCountdown != 0)
          showMainScreen(secondsCountdown, getSeconds(), getDay(), getWeek());
        else
          state = STATE_SEND;
      }
      break;

    case STATE_SEND:
      stopSuspension();
      resetCountdown();
      state = STATE_COUNTDOWN;
      break;
    case STATE_MENU:
      uint8_t menuExitFlag = updateMenu(wasPressed(btnMiddle), wasPressed(btnLeft), wasPressed(btnRight));

      //accion a realizar dependiendo de bandera de salida
      switch (menuExitFlag){
        case NO_CHANGE:
          if (currentMillis - lastMillisMenu >= MENU_MS_TO_WAIT)
            state = STATE_COUNTDOWN;
          break;
        case UPDATED_SCREEN:
          lastMillisMenu = currentMillis;
          break;
        case EXIT_SEND_SIGNAL:
          state = STATE_SEND;
          break;
        case EXIT_COUNTDOWN:
          state = STATE_COUNTDOWN;
          break;
      }

      break;
  }

  updateButtons();
}
