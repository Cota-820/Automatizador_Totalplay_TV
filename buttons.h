#ifndef BUTTONS_H
#define BUTTONS_H

#include <Arduino.h>
#include "config.h"

struct Button {
  uint8_t pin;
  bool currentState;
  bool lastState;
};

extern Button btnSend;
extern Button btnMiddle;
extern Button btnLeft;
extern Button btnRight;

void initButtonPins();
void updateButtons();
bool wasPressed(const Button &btn);

#endif