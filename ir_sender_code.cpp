//not used, only for copying logic

//For esp32 nodemcu
/*
#include "config.h"
#include "IR.h"
#include <IRremote.h>

#define LED_IR_PIN 15
#define BUTTON_PIN 19

#define LED_CONT_1 32
#define LED_CONT_2 33
#define LED_CONT_3 15
#define LED_CONT_4 26

enum estado{
  STATE_TURN_ON_LEDS,
  STATE_UPDATE_COUNTDOWN_LEDS,
  STATE_SEND
};

int minutes, maxMinutes;
uint8_t currentButtonState, lastButtonState = HIGH, state = 0;
unsigned long currentMillis, lastMillis;

void setup() {
  Serial.begin(115200);

  pinMode(LED_IR_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);

  pinMode(LED_CONT_1, OUTPUT);
  pinMode(LED_CONT_2, OUTPUT);
  pinMode(LED_CONT_3, OUTPUT);
  pinMode(LED_CONT_4, OUTPUT);

  IrSender.begin(LED_IR_PIN);

  maxMinutes = (HORAS_A_ENVIAR * 60) + MINUTOS_A_ENVIAR;
  Serial.print("T maximo:");
  Serial.println(maxMinutes);
  resetMinutes(&minutes);
  state = STATE_SEND;
}

void loop() {
  currentMillis = millis();
  currentButtonState = digitalRead(BUTTON_PIN);

  //check button
  if (currentButtonState == LOW && lastButtonState == HIGH)
    state = STATE_SEND;

  switch(state){
    case STATE_TURN_ON_LEDS:
      updateLeds(HIGH, HIGH, HIGH, HIGH);
      
      lastMillis = millis();
      resetMinutes(&minutes);
      state = STATE_UPDATE_COUNTDOWN_LEDS;
      break;
    case STATE_UPDATE_COUNTDOWN_LEDS:
      //update every 60 seconds
      if (currentMillis - lastMillis >= 60000) {
        lastMillis = currentMillis;

        minutes--;
        Serial.print("current t: ");
        Serial.println(minutes);

        if(minutes != 0){
          float percentage = (minutes * 100.0f) / maxMinutes;
          Serial.print("percentage: ");
          Serial.println(percentage);

          if (percentage >= 75 && percentage <= 100) {
            updateLeds(HIGH, HIGH, HIGH, HIGH);
          } else if (percentage >= 50 && percentage < 75) {
            updateLeds(HIGH, HIGH, HIGH, LOW);
          } else if (percentage >= 25 && percentage < 50) {
            updateLeds(HIGH, HIGH, LOW, LOW);
          } else if (percentage >= 5 && percentage < 25) {
            updateLeds(HIGH, LOW, LOW, LOW);
          } else if (percentage >= 0 && percentage < 5) {
            updateLeds(LOW, LOW, LOW, LOW);
          }
        }
        else
          state = STATE_SEND;
      }
      break;

    case STATE_SEND:
      stopSuspension();
      state = STATE_TURN_ON_LEDS;
      break;
  }

  lastButtonState = currentButtonState;
  delay(10);
}

void stopSuspension(){
  for(int i=0; i<2 ; i++){
    IrSender.sendNEC(ADDRESS, OK_CMMD, 0);
    updateLeds(HIGH, HIGH, HIGH, HIGH);
    delay(200);
    updateLeds(LOW, LOW, LOW, LOW);
    delay(700);
    IrSender.sendNEC(ADDRESS, BACK_CMMD, 0);
    updateLeds(HIGH, HIGH, HIGH, HIGH);
    delay(200);
    updateLeds(LOW, LOW, LOW, LOW);
    delay(700);
  }
}

void updateLeds(uint8_t led1, uint8_t led2, uint8_t led3, uint8_t led4){
  digitalWrite(LED_CONT_1, led1); 
  digitalWrite(LED_CONT_2, led2); 
  digitalWrite(LED_CONT_3, led3); 
  digitalWrite(LED_CONT_4, led4); 
}

void resetMinutes(int *minutes){
  *minutes = (HORAS_A_ENVIAR * 60) + MINUTOS_A_ENVIAR;
}
*/
