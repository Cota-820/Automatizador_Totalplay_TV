#ifndef MENU_H
#define MENU_H

#include "nvs_flash.h"
#include "esp_system.h"
#include "display.h"
#include "buttons.h"
#include "local_time.h"
#include "string.h"
#include "IR.h"

#define HIGHLIGHT_ON_MS 500
#define HIGHLIGHT_OFF_MS 200

#define ITEM_ARRAY_SIZE 20

//para array de items
#define ITEMS_AMOUNT ITEM_ARRAY_SIZE
#define ITEMS_SIZE 25

enum exitFlags{
  NO_CHANGE,
  UPDATED_SCREEN,
  EXIT_SEND_SIGNAL,
  EXIT_COUNTDOWN,
};

#define MENU_LAYER_1_X_POS (LETTER_LEN*0)
#define MENU_LAYER_1_Y_POS (ROW_HIGHT*2)

enum menuLayers{
  LAYER_1,
  LAYER_2,
  LAYER_3,
};

enum menuIds{
  MENU_ERROR,
  MENU_1,
  MENU_2,
  MENU_3,
  MENU_4,
  MENU_5,
  MENU_1_1,
  MENU_2_1,
  MENU_2_2,
  MENU_3_1,
  MENU_4_1,
};

typedef struct MenuStruct {
    const uint8_t id;
    const uint8_t layer;
    uint8_t selectedItem;
    uint8_t maxItems;
    uint16_t tempValue;
    uint16_t itemXPos[ITEM_ARRAY_SIZE];
    uint16_t itemYPos[ITEM_ARRAY_SIZE];
    struct MenuStruct* parentMenu;
    struct MenuStruct* childrenMenu;
    struct MenuStruct* leftMenu;
    struct MenuStruct* rightMenu;
} MenuStruct;

typedef struct MenuPositions{
  uint16_t xPos;
  uint16_t yPos;
}MenuPositions;


void initMenu();
void setMenuItemPositions(MenuStruct *menu, MenuPositions *positions, size_t count);
uint8_t updateMenu(bool middleBtn, bool leftBtn, bool rightBtn);
void showMenu();
void highlightMenuItem(bool highlight, char items[][ITEMS_SIZE], unsigned long *lastMilis);
uint8_t menuEvent();
uint8_t handleMenu1_1(uint8_t selectedItem);
uint8_t handleMenu2_2();
void updateTimeItem(uint16_t addSeconds, uint8_t index, int divisor);
void restartMenu();

#endif