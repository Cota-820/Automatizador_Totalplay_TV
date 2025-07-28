#include "config.h"
#include "IR.h"
#include <IRremote.h>
#include "display.h"
#include "string.h"

#define LED_IR_PIN 15
#define BUTTON_PIN 0
#define BUILD_IN_LED 2

enum estado{
  STATE_COUNTDOWN,
  STATE_SEND,
};

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

int seconds;
uint8_t currentButtonState, lastButtonState = HIGH, state = 0;
unsigned long currentMillis, lastMillis = 0;
char screenText[128] = {0}; 

void setup() {
  Serial.begin(115200);

  pinMode(BUILD_IN_LED, OUTPUT);

  if (!display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDRESS)) {
    digitalWrite(BUILD_IN_LED, HIGH);
    Serial.println(F("Error al inicializar la pantalla"));
    while (true); //stop program
  }

  showTextOnScreen(display, "Iniciando...", 1);  

  pinMode(LED_IR_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);

  resetSeconds(&seconds);
  state = STATE_COUNTDOWN;

  IrSender.begin(LED_IR_PIN);

  delay(1000);
}

void loop() {
  currentMillis = millis();
  currentButtonState = digitalRead(BUTTON_PIN);


  //check button
  if (currentButtonState == LOW && lastButtonState == HIGH)
    state = STATE_SEND;

  switch(state){
    case STATE_COUNTDOWN:
      //show every second
      if (currentMillis - lastMillis >= 1000) {
        lastMillis = currentMillis;

        seconds--;

        
        if(seconds != 0)
          showTimeOnScreen(display, seconds);
        else
          state = STATE_SEND;
        
      }
      break;

    case STATE_SEND:
      stopSuspension();
      resetSeconds(&seconds);
      state = STATE_COUNTDOWN;
      break;
  }

  lastButtonState = currentButtonState;
  delay(10);
}

void stopSuspension(){
  for(int i=0; i<2 ; i++){
    sendSignal(ADDRESS, BACK_CMMD, BACK_CMMD_NAME, 1000);
    sendSignal(ADDRESS, OK_CMMD, OK_CMMD_NAME, 1000);
  }
}

void sendSignal(uint16_t address, uint8_t command, char *signalName, int timeToWait){
  sprintf(screenText, "Enviado, espera... \n\nBoton: %s", signalName);
  showTextOnScreen(display, screenText, 1);
  IrSender.sendNEC(ADDRESS, OK_CMMD, 0);
  delay(timeToWait);
}

void resetSeconds(int *seconds){
  *seconds = (HORAS_A_ENVIAR * 3600) + (MINUTOS_A_ENVIAR * 60) + SEGUNDOS_A_ENVIAR;
}
