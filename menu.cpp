#include "menu.h"

MenuItem menuError = {MENU_ERROR, 0, 0, 0, 0, {0}, {0}, NULL, NULL, NULL};
MenuItem menuDayHour_1 = {MENU_1_TEXT, MENU_1, LAYER_1, 0, 0, {0}, {0}, NULL, NULL, NULL, NULL};
MenuItem menuChannel_2 = {MENU_2_TEXT, MENU_2, LAYER_1, 0, 0, {0}, {0}, NULL, NULL, NULL, NULL};
MenuItem menuSendTime_3 = {MENU_3_TEXT, MENU_3, LAYER_1, 0, 0, {0}, {0}, NULL, NULL, NULL, NULL};
MenuItem menuExit_4 = {MENU_4_TEXT, MENU_4, LAYER_1, 0, 0, {0}, {0}, NULL, NULL, NULL, NULL};
MenuItem menuDayHour_1_1 = {MENU_DEFAULT_TEXT, MENU_1_1, LAYER_2, 0, 0, {0}, {0}, NULL, NULL, NULL, NULL};
MenuItem menuChannel_2_1 = {MENU_DEFAULT_TEXT, MENU_2_1, LAYER_2, 0, 0, {0}, {0}, NULL, NULL, NULL, NULL};
MenuItem menuChannel_2_2 = {MENU_DEFAULT_TEXT, MENU_2_2, LAYER_3, 0, 0, {0}, {0}, NULL, NULL, NULL, NULL};
MenuItem menuSendTime_3_1 = {MENU_DEFAULT_TEXT, MENU_3_1, LAYER_2, 0, 0, {0}, {0}, NULL, NULL, NULL, NULL};

MenuItem* currentMenu = NULL;
static bool menuShowed = false, itemHighlighted = false;
static unsigned long lastMillisHighlight = 0;
static uint8_t localDay = 0;
static uint32_t localSeconds = 0;
static char items[ITEMS_AMOUNT][ITEMS_SIZE] = {0};

void initMenu(){
  menuDayHour_1.leftMenu = &menuExit_4;
  menuDayHour_1.rightMenu = &menuChannel_2;
  menuDayHour_1.childrenMenu = &menuDayHour_1_1;

  menuChannel_2.leftMenu = &menuDayHour_1;
  menuChannel_2.rightMenu = &menuSendTime_3;
  menuChannel_2.childrenMenu = &menuChannel_2_1;

  menuSendTime_3.leftMenu = &menuChannel_2;
  menuSendTime_3.rightMenu = &menuExit_4;
  menuSendTime_3.childrenMenu = &menuSendTime_3_1;

  menuExit_4.leftMenu = &menuSendTime_3;
  menuExit_4.rightMenu = &menuDayHour_1;

  menuDayHour_1_1.parentMenu = &menuDayHour_1;

  menuChannel_2_1.parentMenu = &menuChannel_2;
  menuChannel_2_1.childrenMenu = &menuChannel_2_2;

  menuChannel_2_2.parentMenu = &menuChannel_2_1;

  menuSendTime_3_1.parentMenu = &menuSendTime_3;

  uint8_t i=0;
  menuDayHour_1_1.itemXPos[i] = MENU_1_1_ITEM_1_X_POS;
  menuDayHour_1_1.itemYPos[i++] = MENU_1_1_ITEM_1_Y_POS;
  menuDayHour_1_1.itemXPos[i] = MENU_1_1_ITEM_2_X_POS;
  menuDayHour_1_1.itemYPos[i++] = MENU_1_1_ITEM_2_Y_POS;
  menuDayHour_1_1.itemXPos[i] = MENU_1_1_ITEM_3_X_POS;
  menuDayHour_1_1.itemYPos[i++] = MENU_1_1_ITEM_3_Y_POS;
  menuDayHour_1_1.itemXPos[i] = MENU_1_1_ITEM_4_X_POS;
  menuDayHour_1_1.itemYPos[i++] = MENU_1_1_ITEM_4_Y_POS;
  menuDayHour_1_1.maxItems = i-1;
}

uint8_t updateMenu(bool pressedMiddleBtn, bool pressedLeftBtn, bool pressedRightBtn){
  //mostrar menu si fue reiniciado
  if(currentMenu == NULL){
    currentMenu = &menuDayHour_1;
    showTextOnScreen(currentMenu->title);
    showButtonsOnScreen(CHOOSE);
    return UPDATED_SCREEN;
  }

  uint8_t currentLayer = currentMenu->layer;

  switch(currentLayer){
    case LAYER_1:
      if (pressedLeftBtn || pressedRightBtn){
        if (pressedLeftBtn)
          currentMenu = currentMenu->leftMenu;
        else
          currentMenu = currentMenu->rightMenu;
        if (menu == NULL)
          currentMenu = menuError;
        showTextOnScreen(currentMenu->title);
        showButtonsOnScreen(CHOOSE);
        return UPDATED_SCREEN;
      }eturn UPDATED_SCREEN;
      }

      else if (pressedMiddleBtn){
        if (currentMenu->id == MENU_4)
          return EXIT_COUNTDOWN;

        currentMenu = currentMenu->childrenMenu;
        currentMenu->selectedItem = 0;
        showChild(currentMenu->id);

        itemHighlighted = false;
        //lastMillisHighlight = 0;
        return UPDATED_SCREEN;
      }
      break;
    
    case LAYER_2:
      //flasehar opcion actual
      unsigned long interval = itemHighlighted ? HIGHLIGHT_ON_MS : HIGHLIGHT_OFF_MS;

      if (millis() - lastMillisHighlight > interval) {
          itemHighlighted = !itemHighlighted;
          highlightMenuItem(itemHighlighted, currentMenu, items, &lastMillisHighlight);
      }

      if (pressedMiddleBtn){
        if (currentMenu == menuDayHour_1_1){
          eventTimeMenu1_1(currentMenu->selectedItem);

        }
        return EXIT_COUNTDOWN;
      }
      
      else if (pressedLeftBtn || pressedRightBtn){
        highlightMenuItem(false, currentMenu, items, &lastMillisHighlight);
        if(pressedLeftBtn)
          if (currentMenu->selectedItem != 0)
            currentMenu->selectedItem--;
          else
            currentMenu->selectedItem = currentMenu->maxItems;
        else
          if (currentMenu->selectedItem != currentMenu->maxItems)
            currentMenu->selectedItem++;
          else
            currentMenu->selectedItem = 0;
        highlightMenuItem(true, currentMenu, items, &lastMillisHighlight);
        itemHighlighted = true;
        return UPDATED_SCREEN;
      }
      //Serial.println(currentMenu->selectedItem);
      break;
  }

  //if(!pressedMiddleBtn && !pressedLeftBtn && !pressedRightBtn)
  //  return NO_CHANGE;
  
  return NO_CHANGE;
}

void showChild(uint8_t childId){
  switch(childId){
    case MENU_1_1:{
      localDay = getDay();
      localSeconds = getSeconds();

      uint8_t hours = localSeconds / 3600;
      uint8_t minutes = (localSeconds % 3600) / 60;
      uint8_t remainingSeconds = localSeconds % 60;

      uint8_t i = 0;

      char buffer[50], temp[20];

      sprintf(items[i++], "%02d", hours);
      strcat(buffer, items[i++]);
      strcat(buffer, ":");

      
      sprintf(items[i++], "%02d", minutes);
      strcat(buffer, items[i++]);
      strcat(buffer, ":");

      sprintf(items[i++], "%02d", remainingSeconds);
      strcat(buffer, items[i++]);
      strcat(buffer, "  ");

      sprintf(temp, "%s",daysOfWeek[localDay]);
      sprintf(items[i++], temp);
      strcat(buffer, temp);


      showTextOnScreenParams(buffer, true, TEXT_WHITE, MENU_1_1_ITEM_1_X_POS, MENU_1_1_ITEM_1_Y_POS);
      showButtonsOnScreen(CHANGE);
      break;
    }
    default:
      showTextOnScreen("error: invalid");
  }
}

void highlightMenuItem(bool highlight, MenuItem* currentMenu, char items[][ITEMS_SIZE], unsigned long *lastMilis){
  if (highlight)
    showTextOnScreenParams(items[currentMenu->selectedItem], false, TEXT_HIGHLIGHTED,
      currentMenu->itemXPos[currentMenu->selectedItem], currentMenu->itemYPos[currentMenu->selectedItem]);
  else
    showTextOnScreenParams(items[currentMenu->selectedItem], false, TEXT_WHITE,
      currentMenu->itemXPos[currentMenu->selectedItem], currentMenu->itemYPos[currentMenu->selectedItem]);
  
  *lastMilis = millis();
}

uint8_t eventTimeMenu1_1(uint8_t selectedItem){

  switch(selectedItem) {
    case 0: // hour
        updateTimeItem(3600, 0, 3600);
        break;
    case 1: // minutes
        updateTimeItem(60, 1, 60);
        break;
    case 2: // seconds
        updateTimeItem(1, 2, 1);
        break;
}

  }
}

void updateTimeItem(uint16_t addSeconds, uint8_t index, int divisor) {
    localSeconds += addSeconds;
    localSeconds %= 86400;

    uint8_t value = (localSeconds / divisor) % ((divisor == 3600) ? 24 : 60);

    sprintf(items[index], "%02d", value);

    highlightMenuItem(true, currentMenu, items, &lastMillisHighlight);
}

void restartMenu(){
  currentMenu = NULL;
}