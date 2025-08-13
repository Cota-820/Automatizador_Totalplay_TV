#include "IR.h"
#include "local_time.h"

char screenText[128] = {0}; 
static uint16_t channels[MAX_CHANNELS] = {DEFAULT_CHNNL_MON, 
                                          DEFAULT_CHNNL_THUS,
                                          DEFAULT_CHNNL_WEND,
                                          DEFAULT_CHNNL_THURS,
                                          DEFAULT_CHNNL_FRYD,
                                          DEFAULT_CHNNL_SAT,
                                          DEFAULT_CHNNL_SUN,};


static Preferences preferences;

void initChannels(){
  preferences.begin("channels", false);

  if (preferences.getBytesLength("channels") != 0) {
    preferences.getBytes("channels", channels, sizeof(channels));
  }
}

void stopSuspension(){
  uint8_t day = getDay();

  uint8_t digit1 = channels[day] / 100;        
  uint8_t digit2 = (channels[day] / 10) % 10;  
  uint8_t digit3 = channels[day] % 10; 

  char digit1_str[5];
  char digit2_str[5];
  char digit3_str[5];

  sprintf(digit1_str, "%u", digit1);
  sprintf(digit2_str, "%u", digit2);
  sprintf(digit3_str, "%u", digit3);

  for(int i=0; i<2 ; i++){ 
    sendSignal(ADDRESS, BACK_CMMD, BACK_CMMD_NAME, 1000);
    sendSignal(ADDRESS, getNumCommd(digit1), digit1_str, 1000);
    sendSignal(ADDRESS, getNumCommd(digit1), digit2_str, 1000);
    sendSignal(ADDRESS, getNumCommd(digit1), digit3_str, 1500);
  }
}

uint8_t getNumCommd(uint8_t digit){
  static const uint8_t num_cmds[] = {
    NUM_0_CMD, NUM_1_CMD, NUM_2_CMD, NUM_3_CMD, NUM_4_CMD,
    NUM_5_CMD, NUM_6_CMD, NUM_7_CMD, NUM_8_CMD, NUM_9_CMD
  };

  if (digit <= 9)
    return num_cmds[digit];
  else 
    return NUM_0_CMD; //invalid digit
  
}

void sendSignal(uint16_t address, uint8_t command, char *signalName, int msToWait){
  sprintf(screenText, "Enviado, espera... \n\nBoton: %s", signalName);
  showTextOnScreen(screenText);
  IrSender.sendNEC(address, command, 0);
  vTaskDelay(pdMS_TO_TICKS(msToWait));
}