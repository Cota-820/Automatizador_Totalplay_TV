#ifndef LOCAL_TIME_H
#define LOCAL_TIME_H

#include <Arduino.h>

#define MAX_SECONDS 86400

enum day{
  MONDAY,
  TUESDAY,
  WEDNESDAY,
  THURSDAY,
  FRIDAY,
  SATURDAY,
  SUNDAY
};

extern TaskHandle_t timerTaskHandle;
extern SemaphoreHandle_t timerMutex;

void initTime();
void timerTask(void *parameter);
uint32_t getSeconds();
void setSeconds(uint32_t new_seconds);
uint8_t getDay();
void setDay(uint8_t new_day);
uint16_t getSecondsCountdown();
void resetCountdown();

#endif