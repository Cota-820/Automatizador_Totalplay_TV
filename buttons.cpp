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
  updateButton(btnSend);
  updateButton(btnMiddle);
  updateButton(btnLeft);
  updateButton(btnRight);

  vTaskDelay(pdMS_TO_TICKS(25)); // antirrebote
}

void updateButton(Button &btn) {
  btn.lastState = btn.currentState;
  btn.currentState = digitalRead(btn.pin);

  if (btn.currentState == LOW && btn.lastState == HIGH) {
    btn.pressStartTime = millis();
    btn.lastRepeatTime = millis();
    btn.longPressActive = false;
  }
  else if (btn.currentState == HIGH && btn.lastState == LOW) {
    btn.longPressActive = false;
  }
}

bool wasPressed(Button &btn) {
  if (btn.currentState == LOW && btn.lastState == HIGH) {
    return true;
  }

  if (btn.currentState == LOW) {
    unsigned long now = millis();

    if (!btn.longPressActive && (now - btn.pressStartTime >= 1000)) {
      btn.longPressActive = true; // quitar const
      btn.lastRepeatTime = now;
      return true;
    }

    if (btn.longPressActive && (now - btn.lastRepeatTime >= 200)) {
      btn.lastRepeatTime = now;
      return true;
    }
  }

  return false;
}