#include "local_time.h"

TaskHandle_t timerTaskHandle = NULL;
SemaphoreHandle_t secondsMutex;

char daysOfWeek[7] = {"Lnues", "Martes", "Miercoles", "Jueves", "Viernes", "Sabado", "Domingo"};

static uint8_t day = MONDAY; //WIP
static uint32_t seconds = 0; //WIP
static uint16_t secondsCountdown = 14400; //WIP
static uint16_t maxCountdown = 14400; //WIP

void initTime(){
  secondsMutex = xSemaphoreCreateMutex();

  xTaskCreatePinnedToCore(
      timerTask, "TimerTask", 2048, NULL, 1, &timerTaskHandle, 1                
    );
}

void timerTask(void *parameter) {
  while(1){
    vTaskDelay(pdMS_TO_TICKS(1000));

    if (xSemaphoreTake(secondsMutex, portMAX_DELAY) == pdTRUE) {
      if (seconds < MAX_SECONDS)
        seconds++;
      else{
        seconds = 0; 

        if(day != SUNDAY)
          day++;
        else
          day == MONDAY;
      }

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

void setSeconds(uint32_t new_seconds){
  if (xSemaphoreTake(secondsMutex, portMAX_DELAY) == pdTRUE) {
    seconds = new_seconds;
    xSemaphoreGive(secondsMutex);
  }
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
}

uint16_t getSecondsCountdown(){
  uint16_t temp;

  if (xSemaphoreTake(secondsMutex, portMAX_DELAY) == pdTRUE) {
    temp = secondsCountdown;
    xSemaphoreGive(secondsMutex);
  }

  return temp;
}

void resetCountdown(){
  if (xSemaphoreTake(secondsMutex, portMAX_DELAY) == pdTRUE) {
    secondsCountdown = maxCountdown;
    xSemaphoreGive(secondsMutex);
  }
}