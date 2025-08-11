#ifndef MENU_h
#define MENU_H

#include "display.h"
#include "buttons.h"
#include "local_time.h"
#include "string.h"

#define HIGHLIGHT_ON_MS 500
#define HIGHLIGHT_OFF_MS 200

#define ITEMS_AMOUNT 15
#define ITEMS_SIZE 25

#define ITEM_ARRAY_SIZE 15

enum exitFlags{
  NO_CHANGE,
  UPDATED_SCREEN,
  EXIT_SEND_SIGNAL,
  EXIT_COUNTDOWN,
};

#define MENU_1_TEXT  "\n\n1. Cambiar dia y hora"
#define MENU_2_TEXT  "\n\n2. Cambiar canales"
#define MENU_3_TEXT  "\n\n3. Cambiar tiempo de envio"
#define MENU_4_TEXT  "\n\n4. Salir"
#define MENU_DEFAULT_TEXT "N/A"
#define MENU_ERROR_TEXT "menu error: invalid pointer"

typedef struct{
  uint16_t xPos;
  uint16_t yPos;
}MenuPositions;

enum menu1_1_items{
  MENU_1_1_ITEM_1_INDEX,
  MENU_1_1_ITEM_2_INDEX,
  MENU_1_1_ITEM_3_INDEX,
  MENU_1_1_ITEM_4_INDEX,
  MENU_1_1_ITEM_5_INDEX,
  MENU_1_1_ITEM_6_INDEX,
  MENU_1_1_ITEM_7_INDEX,
};

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
  MENU_1_1,
  MENU_2_1,
  MENU_2_2,
  MENU_3_1,
};

typedef struct MenuItem {
    char* title;
    const uint8_t id;
    const uint8_t layer;
    uint8_t selectedItem;
    uint8_t maxItems;
    uint16_t itemXPos[ITEM_ARRAY_SIZE];
    uint16_t itemYPos[ITEM_ARRAY_SIZE];
    struct MenuItem* parentMenu;
    struct MenuItem* childrenMenu;
    struct MenuItem* leftMenu;
    struct MenuItem* rightMenu;
} MenuItem;

void initMenu();
uint8_t updateMenu(bool middleBtn, bool leftBtn, bool rightBtn);
void showChild();
void highlightMenuItem(bool highlight, char items[][ITEMS_SIZE], unsigned long *lastMilis);
uint8_t eventTimeMenu1_1(uint8_t selectedItem);
void updateTimeItem(uint16_t addSeconds, uint8_t index, int divisor);
void restartMenu();

#endif