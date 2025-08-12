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

  for(int i=0; i<2 ; i++){ 
    sendSignal(ADDRESS, BACK_CMMD, BACK_CMMD_NAME, 1000);
    sendSignal(ADDRESS, getNumCommd, OK_CMMD_NAME, 1000);
  }
}

uint8_t getNumCommd(uint8_t digit){
  switch (digit){
    case 1:
      return NUM_1_CMD;
      break;
    case 2:
      return NUM_2_CMD;
      break;
    case 3:
      return NUM_3_CMD;
      break;
    case 4:
      return NUM_4_CMD;
      break;
    case 5:
      return NUM_5_CMD;
      break;
    case 6:
      return NUM_6_CMD;
      break;
    case 7:
      return NUM_7_CMD;
      break;
    case 8:
      return NUM_8_CMD;
      break;
    case 9:
      return NUM_9_CMD;
      break;
    default: //0 or invalid digit
      return NUM_0_CMD
  }
}

void sendSignal(uint16_t address, uint8_t command, char *signalName, int msToWait){
  sprintf(screenText, "Enviado, espera... \n\nBoton: %s", signalName);
  showTextOnScreen(screenText);
  IrSender.sendNEC(address, command, 0);
  vTaskDelay(pdMS_TO_TICKS(msToWait));
}