#include "config.h"
#include "IR.h"
#include "display.h"
#include "local_time.h"
#include <IRremote.h>
#include "string.h"

enum state{
  STATE_COUNTDOWN,
  STATE_SEND,
  STATE_MENU_START,
  STATE_MENU,
};

enum menuOptions{
  DAY_HOUR,
  CHANNEL,
  SEND_TIME,
  EXIT,
  MENU_COUNT,
};

char* menuTextArray[] = {"Cambiar dia y hora", "Cambiar canales", "Cambiar tiempo de envio", "Salir"};

uint32_t seconds;
uint16_t secondsCountdown;
uint8_t sendBttState, sendOldBttState = HIGH, 
  middleBttState, middleOldBttState = HIGH,
  leftBttState, leftOldBttState = HIGH,
  rightBttState, rightOldBttState = HIGH;
uint8_t state = STATE_COUNTDOWN, menuOption, day, lastDay;
//bool menuDisplayed = false;
unsigned long currentMillis, lastMillisCountdown = 0, lastMillisMenu = 0;
char screenText[128] = {0}; 

void setup() {
  Serial.begin(115200);

  initTime();

  pinMode(BUILD_IN_LED, OUTPUT);
  pinMode(LED_IR_PIN, OUTPUT);
  pinMode(BUTTON_SEND_PIN, INPUT_PULLUP);
  pinMode(BUTTON_MIDDLE_PIN, INPUT_PULLUP);
  pinMode(BUTTON_LEFT_PIN, INPUT_PULLUP);
  pinMode(BUTTON_RIGHT_PIN, INPUT_PULLUP);

  initDisplay(BUILD_IN_LED);  

  IrSender.begin(LED_IR_PIN);

  state = STATE_SEND;

  delay(1000); //TEMP
}

void loop() {
  currentMillis = millis();

  sendBttState = digitalRead(BUTTON_SEND_PIN);
  middleBttState = digitalRead(BUTTON_MIDDLE_PIN);
  leftBttState = digitalRead(BUTTON_LEFT_PIN);
  rightBttState = digitalRead(BUTTON_RIGHT_PIN);

  if (sendBttState == LOW && sendOldBttState == HIGH)
    state = STATE_SEND;

  switch(state){
    case STATE_COUNTDOWN:
      //cambiar a menu si se presiono boton
      if (middleBttState == LOW && middleOldBttState == HIGH)
        state = STATE_MENU_START;

      //actualizar pantalla cada segundo
      if (currentMillis - lastMillisCountdown >= 1000) {
        lastMillisCountdown = currentMillis;

        secondsCountdown = getSecondsCountdown();
        seconds = getSeconds();
        day = getDay();
        
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
    case STATE_MENU_START:
      menuOption = DAY_HOUR;
      showMenuOnScreen(menuTextArray[menuOption]);
      state = STATE_MENU;
      break;
    case STATE_MENU:
      if (middleBttState == LOW && middleOldBttState == HIGH)
        state = STATE_COUNTDOWN;
      else if (leftBttState == LOW && leftOldBttState == HIGH) {
        menuOption = (menuOption - 1 + MENU_COUNT) % MENU_COUNT;
        showMenuOnScreen(menuTextArray[menuOption]);
      }
      else if (rightBttState == LOW && rightOldBttState == HIGH){
        menuOption = (menuOption + 1) % MENU_COUNT;
        showMenuOnScreen(menuTextArray[menuOption]);
      }
      break;
  }

  sendOldBttState = sendBttState;
  middleOldBttState = middleBttState;
  leftBttState = leftOldBttState;
  rightBttState = rightOldBttState;
  
  //evitar rebote de boton
  vTaskDelay(pdMS_TO_TICKS(25));
}

void stopSuspension(){
  for(int i=0; i<2 ; i++){ //WIP change ok for channel num 
    sendSignal(ADDRESS, BACK_CMMD, BACK_CMMD_NAME, 1000);
    sendSignal(ADDRESS, OK_CMMD, OK_CMMD_NAME, 1000);
  }
}

void sendSignal(uint16_t address, uint8_t command, char *signalName, int msToWait){
  sprintf(screenText, "Enviado, espera... \n\nBoton: %s", signalName);
  showTextOnScreen(screenText, 1);
  IrSender.sendNEC(ADDRESS, OK_CMMD, 0);
  vTaskDelay(pdMS_TO_TICKS(msToWait));
}
