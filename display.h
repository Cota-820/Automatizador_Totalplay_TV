#ifndef DISPLAY_H
#define DISPLAY_H

#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_ADDRESS 0x3C


void showTimeOnScreen(Adafruit_SSD1306& display, uint16_t segundos);
void showTextOnScreen(Adafruit_SSD1306& display, char *str, int size);

#endif