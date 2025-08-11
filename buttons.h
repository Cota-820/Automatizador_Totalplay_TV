#ifndef BUTTONS_H
#define BUTTONS_H

#include <Arduino.h>
#include "config.h"

struct Button {
  uint8_t pin;
  bool currentState;
  bool lastState;
  bool checkPresstime;
  unsigned long pressStartTime;   
  unsigned long lastRepeatTime;   
  bool longPressActive;           
};

extern Button btnSend;
extern Button btnMiddle;
extern Button btnLeft;
extern Button btnRight;

void initButtonPins();
void updateButtons();
void updateButton(Button &btn);
bool wasPressed(Button &btn);

#endif