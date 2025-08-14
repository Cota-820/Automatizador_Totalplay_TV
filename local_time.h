#ifndef LOCAL_TIME_H
#define LOCAL_TIME_H

#include <Arduino.h>
#include <Preferences.h>

#define DAY_SECONDS 86400 //24 horas

#define ONE_HOURS_TO_SEC 3600
#define TWO_HOURS_TO_SEC 7200
#define THREE_HOURS_TO_SEC 10800
#define FOUR_HOURS_TO_SEC 14400

#define MAX_WEEK 3

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

extern char* daysOfWeek[];

void initTime();
void timerTask(void *parameter);
uint32_t getSeconds();
void setSeconds(uint32_t new_seconds);
uint8_t getDay();
void setDay(uint8_t new_day);
uint8_t getWeek();
void setWeek(uint8_t new_week);
uint16_t getSecondsCountdown();
void setMaxSecondsCountdown(uint16_t newSeconds);
void resetCountdown();

#endif