#ifndef MENU_h
#define MENU_H

#include "display.h"
#include "buttons.h"
#include "local_time.h"
#include "string.h"


enum exitFlags{
  NO_CHANGE,
  UPDATED_SCREEN,
  EXIT_SEND_SIGNAL,
  EXIT_COUNTDOWN,
};

enum menuLayers{
  LAYER_1,
  LAYER_2,
  LAYER_3,
};

enum menuIds{
  MENU_1,
  MENU_2,
  MENU_3,
  MENU_4,
  MENU_1_1,
  MENU_2_1,
  MENU_2_2,
  MENU_3_1,
};

uint8_t updateMenu(bool middleBtn, bool leftBtn, bool rightBtn);
void showChild(uint8_t childId);
void restartMenu();

#endif