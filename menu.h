#ifndef MENU_h
#define MENU_H

#include "display.h"
#include "buttons.h"
#include "local_time.h"
#include "string.h"

#define HIGHLIGHT_ON_MS 500
#define HIGHLIGHT_OFF_MS 200

#define ITEMS_AMOUNT 5
#define ITEMS_SIZE 20

#define MENU_1_1_ITEM_1_X_POS (LETTER_LENGHT*3)
#define MENU_1_1_ITEM_1_Y_POS (ROW_HIGHT*3)

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

void initMenu();
uint8_t updateMenu(bool middleBtn, bool leftBtn, bool rightBtn);
void showChild(uint8_t childId);
void restartMenu();

#endif