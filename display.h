#ifndef DISPLAY_H
#define DISPLAY_H

#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "string.h" 
#include "local_time.h"

#define TEXT_WHITE 0
#define TEXT_HIGHLIGHTED 1

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_ADDRESS 0x3C

#define ROW_HIGHT 8
#define LETTER_LEN 6


void initDisplay(uint8_t warningLed);
void clearScreen();
void clearScreenText(uint16_t x_pos, uint16_t y_pos, uint16_t characterNum);
void showMainScreen(uint16_t secondsCountdown, uint32_t seconds, uint8_t day, uint8_t week);
void showButtonsOnScreen();
void showTextOnScreen(char *str);
void showTextOnScreenParams(char *str, bool clearScreen, uint8_t color, uint16_t x_pos, uint16_t y_pos);

#endif