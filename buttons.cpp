#include "buttons.h"

Button btnSend   = {BUTTON_SEND_PIN, HIGH, HIGH, false, 0, 0, false};
Button btnMiddle = {BUTTON_MIDDLE_PIN, HIGH, HIGH, true, 0, 0, false};
Button btnLeft   = {BUTTON_LEFT_PIN, HIGH, HIGH, true, 0, 0, false};
Button btnRight  = {BUTTON_RIGHT_PIN, HIGH, HIGH, true, 0, 0, false};

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

  if (btn.checkPresstime && btn.currentState == LOW && btn.lastState == HIGH) {
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

  if (btn.checkPresstime && btn.currentState == LOW) {
    unsigned long now = millis();

    if (!btn.longPressActive && (now - btn.pressStartTime >= 1000)) {
      btn.longPressActive = true;
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