#include "local_time.h"

TaskHandle_t timerTaskHandle = NULL;
SemaphoreHandle_t secondsMutex;

char* daysOfWeek[] = {"Lunes", "Martes", "Miercoles", "Jueves", "Viernes", "Sabado", "Domingo"};

static uint8_t day;
static uint32_t seconds;
static uint16_t secondsCountdown; 
static uint16_t maxCountdown;

static Preferences preferences;

void initTime(){
  secondsMutex = xSemaphoreCreateMutex();

  preferences.begin("day", false);
  preferences.begin("sec", false);
  preferences.begin("secCount", false);
  preferences.begin("maxSecCount", false);

  day = preferences.getUInt("day", MONDAY);
  seconds = preferences.getUInt("sec", 0);
  secondsCountdown = preferences.getUInt("secCount", FOUR_HOURS_TO_SEC);
  maxCountdown = preferences.getUInt("maxSecCount", FOUR_HOURS_TO_SEC);

  xTaskCreatePinnedToCore(
      timerTask, "TimerTask", 2048, NULL, 1, &timerTaskHandle, 1                
    );
}

void timerTask(void *parameter) {
  while(1){
    vTaskDelay(pdMS_TO_TICKS(1000));

    if (xSemaphoreTake(secondsMutex, portMAX_DELAY) == pdTRUE) {
      if (seconds < DAY_SECONDS)
        seconds++;
      else{
        seconds = 0; 

        if(day != SUNDAY)
          day++;
        else
          day == MONDAY;

        preferences.putUInt("day", day);
      }

      if(seconds % ONE_HOURS_TO_SEC == 0)
        preferences.putUInt("sec", seconds);

      if(secondsCountdown != 0)
        secondsCountdown--;

      xSemaphoreGive(secondsMutex);
    }
  }
}

uint32_t getSeconds(){
  uint32_t temp;

  if (xSemaphoreTake(secondsMutex, portMAX_DELAY) == pdTRUE) {
    temp = seconds;
    xSemaphoreGive(secondsMutex);
  }

  return temp;
}

void setSeconds(uint32_t newSeconds){
  if (xSemaphoreTake(secondsMutex, portMAX_DELAY) == pdTRUE) {
    seconds = newSeconds;
    xSemaphoreGive(secondsMutex);
  }
  preferences.putUInt("sec", seconds - (seconds % ONE_HOURS_TO_SEC));
}

uint8_t getDay(){
  uint8_t temp;

  if (xSemaphoreTake(secondsMutex, portMAX_DELAY) == pdTRUE) {
    temp = day;
    xSemaphoreGive(secondsMutex);
  }

  return temp;
}

void setDay(uint8_t new_day){
  if (xSemaphoreTake(secondsMutex, portMAX_DELAY) == pdTRUE) {
    day = new_day;
    xSemaphoreGive(secondsMutex);
  }
  preferences.putUInt("day", day);
}

uint16_t getSecondsCountdown(){
  uint16_t temp;

  if (xSemaphoreTake(secondsMutex, portMAX_DELAY) == pdTRUE) {
    temp = secondsCountdown;
    xSemaphoreGive(secondsMutex);
  }

  return temp;
}

void setMaxSecondsCountdown(uint16_t newSeconds){
  maxCountdown == newSeconds;
}

void resetCountdown(){
  if (xSemaphoreTake(secondsMutex, portMAX_DELAY) == pdTRUE) {
    secondsCountdown = maxCountdown;
    xSemaphoreGive(secondsMutex);
  }
}