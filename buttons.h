#ifndef BUTTONS_H
#define BUTTONS_H

#include <Arduino.h>
#include "config.h"

struct Button {
  uint8_t pin;
  bool currentState;
  bool lastState;
  unsigned long pressStartTime;   // tiempo en que comenzó a presionarse
  unsigned long lastRepeatTime;   // última vez que devolvió true en modo repetición
  bool longPressActive;           // si ya está en modo repetición
};

extern Button btnSend;
extern Button btnMiddle;
extern Button btnLeft;
extern Button btnRight;

void initButtonPins();
void updateButtons();
bool wasPressed(Button &btn);

#endif