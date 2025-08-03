#include "buttons.h"

Button btnSend   = {BUTTON_SEND_PIN, HIGH, HIGH};
Button btnMiddle = {BUTTON_MIDDLE_PIN, HIGH, HIGH};
Button btnLeft   = {BUTTON_LEFT_PIN, HIGH, HIGH};
Button btnRight  = {BUTTON_RIGHT_PIN, HIGH, HIGH};

void initButtonPins(){
  pinMode(btnSend.pin, INPUT_PULLUP);
  pinMode(btnMiddle.pin, INPUT_PULLUP);
  pinMode(btnLeft.pin, INPUT_PULLUP);
  pinMode(btnRight.pin, INPUT_PULLUP);
}

void updateButtons() {
  btnSend.lastState = btnSend.currentState;
  btnSend.currentState = digitalRead(btnSend.pin);
  
  btnMiddle.lastState = btnMiddle.currentState;
  btnMiddle.currentState = digitalRead(btnMiddle.pin);
  
  btnLeft.lastState = btnLeft.currentState;
  btnLeft.currentState = digitalRead(btnLeft.pin);
  
  btnRight.lastState = btnRight.currentState;
  btnRight.currentState = digitalRead(btnRight.pin);

  //evitar rebote de boton
  vTaskDelay(pdMS_TO_TICKS(25));
}

bool wasPressed(const Button &btn) {
  return (btn.currentState == LOW && btn.lastState == HIGH);
}