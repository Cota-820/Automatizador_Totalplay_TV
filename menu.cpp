#include "menu.h"

MenuStruct menuError = {MENU_ERROR, 0, 0, 0, 0, {0}, {0}, NULL, NULL, NULL};
MenuStruct menuDayHour_1 = {MENU_1, LAYER_1, 0, 0, 0, {0}, {0}, NULL, NULL, NULL, NULL};
MenuStruct menuChannel_2 = {MENU_2, LAYER_1, 0, 0, 0, {0}, {0}, NULL, NULL, NULL, NULL};
MenuStruct menuSendTime_3 = {MENU_3, LAYER_1, 0, 0, 0, {0}, {0}, NULL, NULL, NULL, NULL};
MenuStruct menuReset_4 = {MENU_4, LAYER_1, 0, 0, 0, {0}, {0}, NULL, NULL, NULL, NULL};
MenuStruct menuExit_5 = {MENU_5, LAYER_1, 0, 0, 0, {0}, {0}, NULL, NULL, NULL, NULL};
MenuStruct menuDayHour_1_1 = {MENU_1_1, LAYER_2, 0, 0, 0, {0}, {0}, NULL, NULL, NULL, NULL};
MenuStruct menuChannel_2_1 = {MENU_2_1, LAYER_2, 0, 0, 0, {0}, {0}, NULL, NULL, NULL, NULL};
MenuStruct menuChannel_2_2 = {MENU_2_2, LAYER_3, 0, 0, 0, {0}, {0}, NULL, NULL, NULL, NULL};
MenuStruct menuSendTime_3_1 = {MENU_3_1, LAYER_2, 0, 0, 0, {0}, {0}, NULL, NULL, NULL, NULL};
MenuStruct menuReset_4_1 = {MENU_4_1, LAYER_3, 0, 0, 0, {0}, {0}, NULL, NULL, NULL, NULL};

MenuPositions menu_1_1_positions[] = {{LETTER_LEN*2, ROW_HIGHT*0}, 
                                      {LETTER_LEN*5, ROW_HIGHT*0}, 
                                      {LETTER_LEN*8, ROW_HIGHT*0}, 
                                      {LETTER_LEN*12, ROW_HIGHT*0},
                                      {(LETTER_LEN*13)+3, ROW_HIGHT*1},
                                      {LETTER_LEN*7, ROW_HIGHT*3},
                                      {(LETTER_LEN*6)+3, ROW_HIGHT*4}};

MenuPositions menu_2_1_positions[] = {{LETTER_LEN*0, ROW_HIGHT*1},
                                      {LETTER_LEN*7, ROW_HIGHT*1},
                                      {LETTER_LEN*14, ROW_HIGHT*1},
                                      {LETTER_LEN*4, ROW_HIGHT*2},
                                      {LETTER_LEN*13, ROW_HIGHT*2},
                                      {LETTER_LEN*4, ROW_HIGHT*3},
                                      {LETTER_LEN*13, ROW_HIGHT*3},
                                      {LETTER_LEN*6, ROW_HIGHT*5}};

MenuPositions menu_2_2_positions[] = {{LETTER_LEN*10, ROW_HIGHT*1},
                                      {LETTER_LEN*11, ROW_HIGHT*1},
                                      {LETTER_LEN*12, ROW_HIGHT*1},
                                      {LETTER_LEN*10, ROW_HIGHT*2},
                                      {LETTER_LEN*11, ROW_HIGHT*2},
                                      {LETTER_LEN*12, ROW_HIGHT*2},
                                      {LETTER_LEN*10, ROW_HIGHT*3},
                                      {LETTER_LEN*11, ROW_HIGHT*3},
                                      {LETTER_LEN*12, ROW_HIGHT*3},
                                      {LETTER_LEN*10, ROW_HIGHT*4},
                                      {LETTER_LEN*11, ROW_HIGHT*4},
                                      {LETTER_LEN*12, ROW_HIGHT*4},
                                      {LETTER_LEN*2, ROW_HIGHT*5},
                                      {LETTER_LEN*12, ROW_HIGHT*5},};

MenuPositions menu_3_1_positions[] = {{LETTER_LEN*8, ROW_HIGHT*1},
                                      {LETTER_LEN*8, ROW_HIGHT*2},
                                      {LETTER_LEN*8, ROW_HIGHT*3},
                                      {LETTER_LEN*6, ROW_HIGHT*5}};

MenuPositions menu_4_1_positions[] = {{LETTER_LEN*6, ROW_HIGHT*3},
                                      {LETTER_LEN*14, ROW_HIGHT*3}};

static MenuStruct* currentMenu = NULL;
static bool menuShowed = false, itemHighlighted = false;
static unsigned long lastMillisHighlight = 0;
static uint8_t localDay = 0, localWeek = 0;
uint16_t localChannels[WEEKS][MAX_CHANNELS] = {0};
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
  menuReset_4.childrenMenu = &menuReset_4_1;

  menuExit_5.leftMenu = &menuReset_4;
  menuExit_5.rightMenu = &menuDayHour_1;

  menuDayHour_1_1.parentMenu = &menuDayHour_1;

  menuChannel_2_1.parentMenu = &menuChannel_2;
  menuChannel_2_1.childrenMenu = &menuChannel_2_2;

  menuChannel_2_2.parentMenu = &menuChannel_2_1;

  menuSendTime_3_1.parentMenu = &menuSendTime_3;

  menuReset_4_1.parentMenu = &menuReset_4;


  setMenuItemPositions(&menuDayHour_1_1, menu_1_1_positions, sizeof(menu_1_1_positions) / sizeof(menu_1_1_positions[0]));
  setMenuItemPositions(&menuChannel_2_1, menu_2_1_positions, sizeof(menu_2_1_positions) / sizeof(menu_2_1_positions[0]));
  setMenuItemPositions(&menuChannel_2_2, menu_2_2_positions, sizeof(menu_2_2_positions) / sizeof(menu_2_2_positions[0]));
  setMenuItemPositions(&menuSendTime_3_1, menu_3_1_positions, sizeof(menu_3_1_positions) / sizeof(menu_3_1_positions[0]));
  setMenuItemPositions(&menuReset_4_1, menu_4_1_positions, sizeof(menu_4_1_positions) / sizeof(menu_4_1_positions[0]));
}

void setMenuItemPositions(MenuStruct *menu, MenuPositions *positions, size_t count) {
  for (size_t i = 0; i < count; i++) {
      menu->itemXPos[i] = positions[i].xPos;
      menu->itemYPos[i] = positions[i].yPos;
  }
  menu->maxItems = count - 1;
}

uint8_t updateMenu(bool pressedMiddleBtn, bool pressedLeftBtn, bool pressedRightBtn){
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
        if (currentMenu->id == MENU_1 || currentMenu->id == MENU_2 || currentMenu->id == MENU_3 || currentMenu->id == MENU_4) {
          currentMenu = currentMenu->childrenMenu;
          showMenu();
          return UPDATED_SCREEN;
        }
        else
          return EXIT_COUNTDOWN;
      }
      break;
    
    case LAYER_2:
    case LAYER_3:
      unsigned long interval = itemHighlighted ? HIGHLIGHT_ON_MS : HIGHLIGHT_OFF_MS;

      if (millis() - lastMillisHighlight > interval) {
          itemHighlighted = !itemHighlighted;
          highlightMenuItem(itemHighlighted, items, &lastMillisHighlight);
      }

      if (pressedMiddleBtn)
        return menuEvent();
      
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
      break;
  }
  
  return NO_CHANGE;
}

void showMenu(){
  currentMenu->selectedItem = 0;
  itemHighlighted = false;

  switch(currentMenu->id){
    case MENU_1:
      showTextOnScreenParams("1. Cambiar dia y hora", true, TEXT_WHITE, MENU_LAYER_1_X_POS, MENU_LAYER_1_Y_POS);
      showButtonsOnScreen();
      break;
    case MENU_2:
      showTextOnScreenParams("2. Cambiar canales", true, TEXT_WHITE, MENU_LAYER_1_X_POS, MENU_LAYER_1_Y_POS);
      showButtonsOnScreen();
      break;
    case MENU_3:
      showTextOnScreenParams("3. Cambiar tiempo de envio", true, TEXT_WHITE, MENU_LAYER_1_X_POS, MENU_LAYER_1_Y_POS);
      showButtonsOnScreen();
      break;
    case MENU_4:
      showTextOnScreenParams("4. Restaurar valores predeterminados", true, TEXT_WHITE, MENU_LAYER_1_X_POS, MENU_LAYER_1_Y_POS);
      showButtonsOnScreen();
      break;
    case MENU_5:
      showTextOnScreenParams("5. Salir", true, TEXT_WHITE, MENU_LAYER_1_X_POS, MENU_LAYER_1_Y_POS);
      showButtonsOnScreen();
      break;
    case MENU_1_1:{
      localDay = getDay();

      localSeconds = getSeconds();
      localWeek = getWeek();

      uint8_t i = 0;

      char buffer[50];

      clearScreen();

      sprintf(items[i], "%02d", localSeconds / 3600);
      sprintf(buffer, items[i]);
      strcat(buffer, ":");
      showTextOnScreenParams(buffer, false, TEXT_WHITE, currentMenu->itemXPos[i], currentMenu->itemYPos[i]);
      i++;
      
      sprintf(items[i], "%02d", (localSeconds % 3600) / 60);
      sprintf(buffer, items[i]);
      strcat(buffer, ":");
      showTextOnScreenParams(buffer, false, TEXT_WHITE, currentMenu->itemXPos[i], currentMenu->itemYPos[i]);
      i++;

      sprintf(items[i], "%02d", localSeconds % 60);
      showTextOnScreenParams(items[i], false, TEXT_WHITE, currentMenu->itemXPos[i], currentMenu->itemYPos[i]);
      i++;

      sprintf(items[i], "%s", daysOfWeek[localDay]);
      showTextOnScreenParams(items[i], false, TEXT_WHITE, currentMenu->itemXPos[i], currentMenu->itemYPos[i]);
      i++;

      showTextOnScreenParams("Semana:", false, TEXT_WHITE, LETTER_LEN*6.5, ROW_HIGHT*1);
      sprintf(items[i], "%u", localWeek+1);
      showTextOnScreenParams(items[i], false, TEXT_WHITE, currentMenu->itemXPos[i], currentMenu->itemYPos[i]);
      i++;

      sprintf(items[i], "Guardar");
      showTextOnScreenParams(items[i], false, TEXT_WHITE, currentMenu->itemXPos[i], currentMenu->itemYPos[i]);
      i++;

      sprintf(items[i], "Regresar");
      showTextOnScreenParams(items[i], false, TEXT_WHITE, currentMenu->itemXPos[i], currentMenu->itemYPos[i]);

      showButtonsOnScreen();
      break;
    }
    case MENU_2_1:
      clearScreen();
      for(int i=0; i<=currentMenu->maxItems; i++){
        if(i != currentMenu->maxItems){
          sprintf(items[i], daysOfWeek[i]);
          showTextOnScreenParams(items[i], false, TEXT_WHITE, currentMenu->itemXPos[i], currentMenu->itemYPos[i]);
        }
        else{
          sprintf(items[i], "Regresar");
          showTextOnScreenParams(items[i], false, TEXT_WHITE, currentMenu->itemXPos[i], currentMenu->itemYPos[i]);
        }
      }
      showButtonsOnScreen();
      break;
    case MENU_2_2:{
      clearScreen();

      uint8_t i = 0, day=currentMenu->tempValue;
      day %= DAYS_IN_WEEK;
      char buffer[50];

      getChannels(localChannels);

      sprintf(buffer, "%s", daysOfWeek[day]);
      showTextOnScreenParams(buffer, false, TEXT_WHITE, LETTER_LEN*6, 0);

      showTextOnScreenParams("Semana 1:", false, TEXT_WHITE, 0, currentMenu->itemYPos[i]);
      sprintf(items[i], "%u", localChannels[0][day] / 100);
      showTextOnScreenParams(items[i], false, TEXT_WHITE, currentMenu->itemXPos[i], currentMenu->itemYPos[i]);
      i++;
      sprintf(items[i], "%u",(localChannels[0][day] / 10) % 10);
      showTextOnScreenParams(items[i], false, TEXT_WHITE, currentMenu->itemXPos[i], currentMenu->itemYPos[i]);
      i++;
      sprintf(items[i], "%u",localChannels[0][day] % 10);
      showTextOnScreenParams(items[i], false, TEXT_WHITE, currentMenu->itemXPos[i], currentMenu->itemYPos[i]);
      i++;

      showTextOnScreenParams("Semana 2:", false, TEXT_WHITE, 0, currentMenu->itemYPos[i]);
      sprintf(items[i], "%u", localChannels[1][day] / 100);
      showTextOnScreenParams(items[i], false, TEXT_WHITE, currentMenu->itemXPos[i], currentMenu->itemYPos[i]);
      i++;
      sprintf(items[i], "%u",(localChannels[1][day] / 10) % 10);
      showTextOnScreenParams(items[i], false, TEXT_WHITE, currentMenu->itemXPos[i], currentMenu->itemYPos[i]);
      i++;
      sprintf(items[i], "%u",localChannels[1][day] % 10);
      showTextOnScreenParams(items[i], false, TEXT_WHITE, currentMenu->itemXPos[i], currentMenu->itemYPos[i]);
      i++;

      showTextOnScreenParams("Semana 3:", false, TEXT_WHITE, 0, currentMenu->itemYPos[i]);
      sprintf(items[i], "%u", localChannels[2][day] / 100);
      showTextOnScreenParams(items[i], false, TEXT_WHITE, currentMenu->itemXPos[i], currentMenu->itemYPos[i]);
      i++;
      sprintf(items[i], "%u",(localChannels[2][day] / 10) % 10);
      showTextOnScreenParams(items[i], false, TEXT_WHITE, currentMenu->itemXPos[i], currentMenu->itemYPos[i]);
      i++;
      sprintf(items[i], "%u",localChannels[2][day] % 10);
      showTextOnScreenParams(items[i], false, TEXT_WHITE, currentMenu->itemXPos[i], currentMenu->itemYPos[i]);
      i++;

      showTextOnScreenParams("Semana 4:", false, TEXT_WHITE, 0, currentMenu->itemYPos[i]);
      sprintf(items[i], "%u", localChannels[3][day] / 100);
      showTextOnScreenParams(items[i], false, TEXT_WHITE, currentMenu->itemXPos[i], currentMenu->itemYPos[i]);
      i++;
      sprintf(items[i], "%u",(localChannels[3][day] / 10) % 10);
      showTextOnScreenParams(items[i], false, TEXT_WHITE, currentMenu->itemXPos[i], currentMenu->itemYPos[i]);
      i++;
      sprintf(items[i], "%u",localChannels[3][day] % 10);
      showTextOnScreenParams(items[i], false, TEXT_WHITE, currentMenu->itemXPos[i], currentMenu->itemYPos[i]);
      i++;

      sprintf(items[i], "Guardar");
      showTextOnScreenParams(items[i], false, TEXT_WHITE, currentMenu->itemXPos[i], currentMenu->itemYPos[i]);
      i++;

      sprintf(items[i], "Regresar");
      showTextOnScreenParams(items[i], false, TEXT_WHITE, currentMenu->itemXPos[i], currentMenu->itemYPos[i]);

      showButtonsOnScreen();

      break;
    }
    case MENU_3_1:{
      uint8_t i = 0;
      char buffer[50];

      clearScreen();

      sprintf(buffer, "Enviar cada:");
      showTextOnScreenParams(buffer, false, TEXT_WHITE, LETTER_LEN*5, ROW_HIGHT*0);

      sprintf(items[i], "2hrs");
      showTextOnScreenParams(items[i], false, TEXT_WHITE, currentMenu->itemXPos[i], currentMenu->itemYPos[i]);
      i++;

      sprintf(items[i], "3hrs");
      showTextOnScreenParams(items[i], false, TEXT_WHITE, currentMenu->itemXPos[i], currentMenu->itemYPos[i]);
      i++;

      sprintf(items[i], "4hrs");
      showTextOnScreenParams(items[i], false, TEXT_WHITE, currentMenu->itemXPos[i], currentMenu->itemYPos[i]);
      i++;

      sprintf(items[i], "Regresar");
      showTextOnScreenParams(items[i], false, TEXT_WHITE, currentMenu->itemXPos[i], currentMenu->itemYPos[i]);
      i++;

      showButtonsOnScreen();

      break;
    }
    case MENU_4_1:{
      uint8_t i = 0;
      char buffer[50];
      clearScreen();

      sprintf(buffer, "Confirmar reinicio?");
      showTextOnScreenParams(buffer, false, TEXT_WHITE, LETTER_LEN*1, ROW_HIGHT*0);

      sprintf(items[i], "NO");
      showTextOnScreenParams(items[i], false, TEXT_WHITE, currentMenu->itemXPos[i], currentMenu->itemYPos[i]);
      i++;

      sprintf(items[i], "SI");
      showTextOnScreenParams(items[i], false, TEXT_WHITE, currentMenu->itemXPos[i], currentMenu->itemYPos[i]);
      i++;

      showButtonsOnScreen();

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

uint8_t menuEvent() {
  switch (currentMenu->id) {
    case MENU_1_1:
      return handleMenu1_1(currentMenu->selectedItem);
    case MENU_2_1:
      if(currentMenu->selectedItem < DAYS_IN_WEEK){
        currentMenu->childrenMenu->tempValue = currentMenu->selectedItem;
        currentMenu = currentMenu->childrenMenu;
      }
      else
        currentMenu = currentMenu->parentMenu;

      showMenu();
      return UPDATED_SCREEN;
    case MENU_2_2:
      return handleMenu2_2();
    case MENU_3_1:
      switch (currentMenu->selectedItem){
        case 0:
          setMaxSecondsCountdown(TWO_HOURS_TO_SEC);
          return EXIT_COUNTDOWN;
        case 1:
          setMaxSecondsCountdown(THREE_HOURS_TO_SEC);
          return EXIT_COUNTDOWN;
        case 2:
          setMaxSecondsCountdown(FOUR_HOURS_TO_SEC);
          return EXIT_COUNTDOWN;
        case 3:
          currentMenu = currentMenu->parentMenu;
          showMenu();
          return UPDATED_SCREEN;
      }
    case MENU_4_1:
      switch (currentMenu->selectedItem){
        case 0:
          currentMenu = currentMenu->parentMenu;
          showMenu();
          return UPDATED_SCREEN;
        case 1:
          nvs_flash_erase();  
          nvs_flash_init();
          showTextOnScreenParams("Borando datos...", true, TEXT_WHITE, LETTER_LEN*0, ROW_HIGHT*3);
          delay(1000);
          ESP.restart();
          return UPDATED_SCREEN;
      }
    default:
      return EXIT_COUNTDOWN; //temp
  }
}

uint8_t handleMenu1_1(uint8_t selectedItem){
  switch(selectedItem) {
    case 0: //horas
      updateTimeItem(3600, 0, 3600);
      return UPDATED_SCREEN;
    case 1: //minutos
      updateTimeItem(60, 1, 60);
      return UPDATED_SCREEN;
    case 2: //sec
      updateTimeItem(1, 2, 1);
      return UPDATED_SCREEN;
    case 3: //day
      localDay++;
      localDay %= 7;
      sprintf(items[3], daysOfWeek[localDay]);
      clearScreenText(currentMenu->itemXPos[3], currentMenu->itemYPos[3], 11);
      highlightMenuItem(true, items, &lastMillisHighlight);
      return UPDATED_SCREEN;
    case 4: //week
      localWeek++;
      localWeek %= WEEK_LIMIT;
      sprintf(items[4], "%u", localWeek+1);
      highlightMenuItem(true, items, &lastMillisHighlight);
      return UPDATED_SCREEN;
    case 5: //guardar
      setSeconds(localSeconds);
      setDay(localDay);
      setWeek(localWeek);
      return EXIT_COUNTDOWN;
    case 6: //regresar
      currentMenu = currentMenu->parentMenu;
      showMenu();
      return UPDATED_SCREEN;
  }
}

uint8_t handleMenu2_2(){
  uint8_t localItem = currentMenu->selectedItem;
  uint8_t day = currentMenu->tempValue;
  
  if (localItem==0 || localItem==3 || localItem==6 || localItem == 9){ //centenas
    localChannels[localItem/3][day] += 100;
    localChannels[localItem/3][day] %= 1000;

    sprintf(items[localItem], "%u", localChannels[localItem/3][day] / 100);
    highlightMenuItem(true, items, &lastMillisHighlight);
    return UPDATED_SCREEN;
  }
  else if (localItem==1 || localItem==4 || localItem==7 || localItem == 10){ //decenas
    uint8_t digit = (localChannels[0][day] / 10) % 10;
    if(digit != 9)
      localChannels[(localItem-1)/3][day] += 10;
    else
      localChannels[(localItem-1)/3][day] -= 90;
      
    sprintf(items[localItem], "%u", (localChannels[(localItem-1)/3][day]/ 10) % 10);
    highlightMenuItem(true, items, &lastMillisHighlight);
    return UPDATED_SCREEN;
  }
  else if (localItem==2 || localItem==5 || localItem==8 || localItem == 11){ //unidades
    uint8_t digit = localChannels[(localItem-2)/3][day] % 10;
    if(digit != 9)
      localChannels[(localItem-2)/3][day] += 1;
    else
      localChannels[(localItem-2)/3][day] -= 9;
      
    sprintf(items[localItem], "%u", localChannels[(localItem-2)/3][day] % 10);
    highlightMenuItem(true, items, &lastMillisHighlight);
    return UPDATED_SCREEN;
  }
  else if(localItem == 12 || localItem == 13){ //guardar - regresar
    if(localItem == 12)
      saveChannels(localChannels);
    currentMenu = currentMenu->parentMenu;
    showMenu();
    return UPDATED_SCREEN;
  }
  else 
    return EXIT_COUNTDOWN;
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