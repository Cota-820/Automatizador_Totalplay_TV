#ifndef DISPLAY_H
#define DISPLAY_H

#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "string.h" 
#include "local_time.h"

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_ADDRESS 0x3C

#define ROW_1 0
#define ROW_2 8
#define ROW_3 16
#define ROW_4 24
#define ROW_5 32
#define ROW_6 40
#define ROW_7 48
#define ROW_8 56

void initDisplay(uint8_t warningLed);
void showTimeOnScreen(uint16_t secondsCountdown, uint32_t seconds, uint8_t day);
void showButtonsOnScreen();
void showTextOnScreen(char *str);

#endif