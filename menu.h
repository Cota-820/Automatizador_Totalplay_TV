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

#define ITEM_ARRAY_SIZE 10

#define MENU_1_1_ITEM_1_X_POS (LETTER_LENGHT*3)
#define MENU_1_1_ITEM_1_Y_POS (ROW_HIGHT*3)
#define MENU_1_1_ITEM_2_X_POS (LETTER_LENGHT*6)
#define MENU_1_1_ITEM_2_Y_POS (ROW_HIGHT*3)
#define MENU_1_1_ITEM_3_X_POS (LETTER_LENGHT*9)
#define MENU_1_1_ITEM_3_Y_POS (ROW_HIGHT*3)
#define MENU_1_1_ITEM_4_X_POS (LETTER_LENGHT*13)
#define MENU_1_1_ITEM_4_Y_POS (ROW_HIGHT*3)

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
void showChild(uint8_t childId);
void highlightMenuItem(bool highlight, MenuItem* currentMenu, char items[][ITEMS_SIZE]);
void restartMenu();

#endif