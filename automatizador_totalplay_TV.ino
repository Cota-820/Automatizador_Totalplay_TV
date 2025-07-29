#include "config.h"
#include "IR.h"
#include "display.h"
#include "local_time.h"
#include <IRremote.h>
#include "string.h"

enum estado{
  STATE_COUNTDOWN,
  STATE_SEND,
};

uint32_t seconds;
uint16_t secondsCountdown;
uint8_t currentButtonState, lastButtonState = HIGH, state = STATE_COUNTDOWN, day, lastDay;
unsigned long currentMillis, lastMillis = 0;
char screenText[128] = {0}; 

void setup() {
  Serial.begin(115200);

  initTime();

  pinMode(BUILD_IN_LED, OUTPUT);
  pinMode(LED_IR_PIN, OUTPUT);
  pinMode(BUTTON_SEND_PIN, INPUT_PULLUP);

  initDisplay(BUILD_IN_LED);  

  IrSender.begin(LED_IR_PIN);

  state = STATE_SEND;

  delay(1000); //TEMP
}

void loop() {
  currentMillis = millis();
  currentButtonState = digitalRead(BUTTON_SEND_PIN);

  //revisar boton
  if (currentButtonState == LOW && lastButtonState == HIGH)
    state = STATE_SEND;

  switch(state){
    case STATE_COUNTDOWN:
      //actualizar pantalla cada segundo
      if (currentMillis - lastMillis >= 1000) {
        lastMillis = currentMillis;

        secondsCountdown = getSecondsCountdown();
        seconds = getSeconds();
        day = getDay();
        
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
  }

  lastButtonState = currentButtonState;
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
