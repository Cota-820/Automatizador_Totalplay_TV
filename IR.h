#ifndef IR_H
#define IR_H

#include <Arduino.h>
#include <Preferences.h>
#include "display.h"
#include "local_time.h"
#include "config.h"

#define ADDRESS 0x3383

#define OK_CMMD 0x41 
#define OK_CMMD_NAME "OK" 
#define BACK_CMMD 0x95
#define BACK_CMMD_NAME "REGRESAR"

#define NUM_0_CMD 0x60
#define NUM_1_CMD 0x61
#define NUM_2_CMD 0x62
#define NUM_3_CMD 0x63
#define NUM_4_CMD 0x64
#define NUM_5_CMD 0x65
#define NUM_6_CMD 0x66
#define NUM_7_CMD 0x67
#define NUM_8_CMD 0x68
#define NUM_9_CMD 0x69

#define MAX_CHANNELS 7
#define WEEKS 4

void initChannels();
void saveChannels(uint8_t week, uint16_t channels_array[]);
void stopSuspension();
uint8_t getNumCommd(uint8_t digit);
void sendSignal(uint16_t address, uint8_t command, char *signalName, int msToWait);

#endif