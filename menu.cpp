#include "menu.h"

MenuItem menuError = {MENU_ERROR, 0, 0, 0, {0}, {0}, NULL, NULL, NULL};
MenuItem menuDayHour_1 = {MENU_1, LAYER_1, 0, 0, {0}, {0}, NULL, NULL, NULL, NULL};
MenuItem menuChannel_2 = {MENU_2, LAYER_1, 0, 0, {0}, {0}, NULL, NULL, NULL, NULL};
MenuItem menuSendTime_3 = {MENU_3, LAYER_1, 0, 0, {0}, {0}, NULL, NULL, NULL, NULL};
MenuItem menuReset_4 = {MENU_4, LAYER_1, 0, 0, {0}, {0}, NULL, NULL, NULL, NULL};
MenuItem menuExit_5 = {MENU_5, LAYER_1, 0, 0, {0}, {0}, NULL, NULL, NULL, NULL};
MenuItem menuDayHour_1_1 = {MENU_1_1, LAYER_2, 0, 0, {0}, {0}, NULL, NULL, NULL, NULL};
MenuItem menuChannel_2_1 = {MENU_2_1, LAYER_2, 0, 0, {0}, {0}, NULL, NULL, NULL, NULL};
MenuItem menuChannel_2_2 = {MENU_2_2, LAYER_3, 0, 0, {0}, {0}, NULL, NULL, NULL, NULL};
MenuItem menuSendTime_3_1 = {MENU_3_1, LAYER_2, 0, 0, {0}, {0}, NULL, NULL, NULL, NULL};

MenuPositions menu_1_1_positions[] = {{LETTER_LEN*2, ROW_HIGHT*0}, 
                                      {LETTER_LEN*5, ROW_HIGHT*0}, 
                                      {LETTER_LEN*8, ROW_HIGHT*0}, 
                                      {LETTER_LEN*12, ROW_HIGHT*0},
                                      {LETTER_LEN*7, ROW_HIGHT*2},
                                      {LETTER_LEN*2, ROW_HIGHT*3},
                                      {LETTER_LEN*7, ROW_HIGHT*4}};

static MenuItem* currentMenu = NULL;
static bool menuShowed = false, itemHighlighted = false;
static unsigned long lastMillisHighlight = 0;
static uint8_t localDay = 0;
static uint32_t localSeconds = 0;
static char items[ITEMS_AMOUNT][ITEMS_SIZE] = {0};

void initMenu(){
  menuDayHour_1.leftMenu = &menuExit_5;
  menuDayHour_1.rightMenu = &menuChannel_2;
  menuDayHour_1.childrenMenu = &menuDayHour_1_1;

  menuChannel_2.leftMenu = &menuDayHour_1;
  menuChannel_2.rightMenu = &menuSendTime_3;
  menuChannel_2.childrenMenu = &menuChannel_2_1;

  menuSendTime_3.leftMenu = &menuChannel_2;
  menuSendTime_3.rightMenu = &menuReset_4;
  menuSendTime_3.childrenMenu = &menuSendTime_3_1;

  menuReset_4.leftMenu = &menuSendTime_3;
  menuReset_4.rightMenu = &menuExit_5;

  menuExit_5.leftMenu = &menuReset_4;
  menuExit_5.rightMenu = &menuDayHour_1;

  menuDayHour_1_1.parentMenu = &menuDayHour_1;

  menuChannel_2_1.parentMenu = &menuChannel_2;
  menuChannel_2_1.childrenMenu = &menuChannel_2_2;

  menuChannel_2_2.parentMenu = &menuChannel_2_1;

  menuSendTime_3_1.parentMenu = &menuSendTime_3;

  size_t menu_size;

  menu_size = sizeof(menu_1_1_positions) / sizeof(menu_1_1_positions[0]);
  for(int i=0; i<menu_size; i++){
    menuDayHour_1_1.itemXPos[i] = menu_1_1_positions[i].xPos;
    menuDayHour_1_1.itemYPos[i] = menu_1_1_positions[i].yPos;
  }  
  menuDayHour_1_1.maxItems = menu_size-1;
}

uint8_t updateMenu(bool pressedMiddleBtn, bool pressedLeftBtn, bool pressedRightBtn){
  //mostrar menu si fue reiniciado
  if(currentMenu == NULL){
    currentMenu = &menuDayHour_1;
    showMenu();
    return UPDATED_SCREEN;
  }

  uint8_t currentLayer = currentMenu->layer;

  switch(currentLayer){
    case LAYER_1:
      if (pressedLeftBtn || pressedRightBtn){
        currentMenu = pressedLeftBtn ? currentMenu->leftMenu : currentMenu->rightMenu;

        if (currentMenu == NULL)
          currentMenu = &menuError;
        
        showMenu();
        return UPDATED_SCREEN;
      }

      else if (pressedMiddleBtn){
        if (currentMenu->id == MENU_1 || currentMenu->id == MENU_2 || currentMenu->id == MENU_3) {
          currentMenu = currentMenu->childrenMenu;
          currentMenu->selectedItem = 0;
          showMenu();
          itemHighlighted = false;
          return UPDATED_SCREEN;
        }
        else
          return EXIT_COUNTDOWN;
      }
      break;
    
    case LAYER_2:
      unsigned long interval = itemHighlighted ? HIGHLIGHT_ON_MS : HIGHLIGHT_OFF_MS;

      if (millis() - lastMillisHighlight > interval) {
          itemHighlighted = !itemHighlighted;
          highlightMenuItem(itemHighlighted, items, &lastMillisHighlight);
      }

      if (pressedMiddleBtn){
        if (currentMenu->id == MENU_1_1){
          return eventTimeMenu1_1(currentMenu->selectedItem);
        }
        return EXIT_COUNTDOWN; //temp
      }
      
      else if (pressedLeftBtn || pressedRightBtn){
        highlightMenuItem(false, items, &lastMillisHighlight);
        if(pressedLeftBtn)
          if (currentMenu->selectedItem != 0)
            currentMenu->selectedItem--;
          else
            currentMenu->selectedItem = currentMenu->maxItems;
        else {
          currentMenu->selectedItem++;
          currentMenu->selectedItem %= currentMenu->maxItems+1;
        }
        highlightMenuItem(true, items, &lastMillisHighlight);
        itemHighlighted = true;
        return UPDATED_SCREEN;
      }
      //Serial.println(currentMenu->selectedItem);
      break;
  }
  
  return NO_CHANGE;
}

void showMenu(){
  switch(currentMenu->id){
    case MENU_1:
      showTextOnScreenParams("1. Cambiar dia y hora", true, TEXT_WHITE, MENU_LAYER_1_X_POS, MENU_LAYER_1_Y_POS);
      showButtonsOnScreen(CHOOSE);
      break;
    case MENU_2:
      showTextOnScreenParams("2. Cambiar canales", true, TEXT_WHITE, MENU_LAYER_1_X_POS, MENU_LAYER_1_Y_POS);
      showButtonsOnScreen(CHOOSE);
      break;
    case MENU_3:
      showTextOnScreenParams("3. Cambiar tiempo de envio", true, TEXT_WHITE, MENU_LAYER_1_X_POS, MENU_LAYER_1_Y_POS);
      showButtonsOnScreen(CHOOSE);
      break;
    case MENU_4:
      showTextOnScreenParams("4. Restaurar valores predeterminados", true, TEXT_WHITE, MENU_LAYER_1_X_POS, MENU_LAYER_1_Y_POS);
      showButtonsOnScreen(CHOOSE);
      break;
    case MENU_5:
      showTextOnScreenParams("5. Salir", true, TEXT_WHITE, MENU_LAYER_1_X_POS, MENU_LAYER_1_Y_POS);
      showButtonsOnScreen(CHOOSE);
      break;
    case MENU_1_1:{
      localDay = getDay();
      localSeconds = getSeconds();

      uint8_t hours = localSeconds / 3600;
      uint8_t minutes = (localSeconds % 3600) / 60;
      uint8_t remainingSeconds = localSeconds % 60;

      uint8_t i = 0;

      char buffer[50];

      clearScreen();

      sprintf(items[i], "%02d", hours);
      sprintf(buffer, items[i]);
      strcat(buffer, ":");
      showTextOnScreenParams(buffer, false, TEXT_WHITE, currentMenu->itemXPos[i], currentMenu->itemYPos[i]);
      i++;
      
      sprintf(items[i], "%02d", minutes);
      sprintf(buffer, items[i]);
      strcat(buffer, ":");
      showTextOnScreenParams(buffer, false, TEXT_WHITE, currentMenu->itemXPos[i], currentMenu->itemYPos[i]);
      i++;

      sprintf(items[i], "%02d", remainingSeconds);
      sprintf(buffer, items[i]);
      showTextOnScreenParams(buffer, false, TEXT_WHITE, currentMenu->itemXPos[i], currentMenu->itemYPos[i]);
      i++;

      sprintf(items[i], "%s", daysOfWeek[localDay]);
      sprintf(buffer, items[i]);
      showTextOnScreenParams(buffer, false, TEXT_WHITE, currentMenu->itemXPos[i], currentMenu->itemYPos[i]);
      i++;

      sprintf(items[i], "Guardar");
      sprintf(buffer, items[i]);
      showTextOnScreenParams(buffer, false, TEXT_WHITE, currentMenu->itemXPos[i], currentMenu->itemYPos[i]);
      i++;

      sprintf(items[i], "Guardar y Enviar");
      sprintf(buffer, items[i]);
      showTextOnScreenParams(buffer, false, TEXT_WHITE, currentMenu->itemXPos[i], currentMenu->itemYPos[i]);
      i++;

      sprintf(items[i], "Salir");
      sprintf(buffer, items[i]);
      showTextOnScreenParams(buffer, false, TEXT_WHITE, currentMenu->itemXPos[i], currentMenu->itemYPos[i]);

      showButtonsOnScreen(CHOOSE);
      break;
    }
    default:
      showTextOnScreen("\n\nerror: invalid menu");
  }
}

void highlightMenuItem(bool highlight, char items[][ITEMS_SIZE], unsigned long *lastMilis){
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
    case MENU_1_1_ITEM_1_INDEX: //horas
      updateTimeItem(3600, MENU_1_1_ITEM_1_INDEX, 3600);
      return UPDATED_SCREEN;
      break;
    case MENU_1_1_ITEM_2_INDEX: //minutos
      updateTimeItem(60, MENU_1_1_ITEM_2_INDEX, 60);
      return UPDATED_SCREEN;
      break;
    case MENU_1_1_ITEM_3_INDEX: //sec
      updateTimeItem(1, MENU_1_1_ITEM_3_INDEX, 1);
      return UPDATED_SCREEN;
      break;
    case MENU_1_1_ITEM_4_INDEX: //day
      localDay++;
      localDay %= 7;
      sprintf(items[MENU_1_1_ITEM_4_INDEX], daysOfWeek[localDay]);
      clearScreenText(currentMenu->itemXPos[MENU_1_1_ITEM_4_INDEX], currentMenu->itemYPos[MENU_1_1_ITEM_4_INDEX], 11);
      highlightMenuItem(true, items, &lastMillisHighlight);
      return UPDATED_SCREEN;
      break;
    case MENU_1_1_ITEM_5_INDEX: //guardar
      setSeconds(localSeconds);
      setDay(localDay);
      return EXIT_COUNTDOWN;
      break;
    case MENU_1_1_ITEM_6_INDEX: //guardar y enviar
      setSeconds(localSeconds);
      setDay(localDay);
      return EXIT_SEND_SIGNAL;
      break;
    case MENU_1_1_ITEM_7_INDEX: //salir
      return EXIT_COUNTDOWN;
      break;
  }
  return NO_CHANGE;
}

void updateTimeItem(uint16_t addSeconds, uint8_t itemIndex, int divisor) {
    localSeconds += addSeconds;
    localSeconds %= 86400;

    uint8_t value = (localSeconds / divisor) % ((divisor == 3600) ? 24 : 60);

    sprintf(items[itemIndex], "%02d", value);

    highlightMenuItem(true, items, &lastMillisHighlight);
}

void restartMenu(){
  currentMenu = NULL;
}