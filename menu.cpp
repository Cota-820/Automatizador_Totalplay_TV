#include "menu.h"

typedef struct MenuItem {
    char* title;
    const uint8_t id;
    const uint8_t layer;
    uint8_t selectedItem;
    struct MenuItem* parentMenu;
    struct MenuItem* childrenMenu;
    struct MenuItem* leftMenu;
    struct MenuItem* rightMenu;
} MenuItem;

MenuItem menuDayHour_1 = {"\n\n1. Cambiar dia y hora", MENU_1, LAYER_1, 0, NULL, NULL, NULL, NULL};
MenuItem menuChannel_2 = {"\n\n2. Cambiar canales", MENU_2, LAYER_1, 0, NULL, NULL, NULL, NULL};
MenuItem menuSendTime_3 = {"\n\n3. Cambiar tiempo de envio", MENU_3, LAYER_1, 0, NULL, NULL, NULL, NULL};
MenuItem menuExit_4 = {"\n\n4. Salir", MENU_4, LAYER_1, 0, NULL, NULL, NULL, NULL};
MenuItem menuDayHour_1_1 = {NULL, MENU_1_1, LAYER_2, 0, NULL, NULL, NULL, NULL};
MenuItem menuChannel_2_1 = {NULL, MENU_2_1, LAYER_2, 0, NULL, NULL, NULL, NULL};
MenuItem menuChannel_2_2 = {NULL, MENU_2_2, LAYER_3, 0, NULL, NULL, NULL, NULL};
MenuItem menuSendTime_3_1 = {NULL, MENU_3_1, LAYER_2, 0, NULL, NULL, NULL, NULL};

MenuItem* currentMenu = NULL;
static bool menuShowed = false, optionSelected = false;
static unsigned long lastMillis = 0;
uint8_t localDay;
uint32_t localSeconds;

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
}

uint8_t updateMenu(bool middleBtn, bool leftBtn, bool rightBtn){
  //mostrar menu si fue reiniciado
  if(currentMenu == NULL){
    currentMenu = &menuDayHour_1;
    showTextOnScreen(currentMenu->title);
    showButtonsOnScreen();
    return UPDATED_SCREEN;
  }

  if(!middleBtn && !leftBtn && !rightBtn)
    return NO_CHANGE;

  uint8_t currentLayer = currentMenu->layer;

  switch(currentLayer){
    case LAYER_1:
      if (wasPressed(btnLeft)){
        currentMenu = currentMenu->leftMenu;
        showTextOnScreen(currentMenu->title);
        showButtonsOnScreen();
        return UPDATED_SCREEN;
      }

      else if (wasPressed(btnRight)){
        currentMenu = currentMenu->rightMenu;
        showTextOnScreen(currentMenu->title);
        showButtonsOnScreen();
        return UPDATED_SCREEN;
      }

      else if (wasPressed(btnMiddle)){
        if (currentMenu->id == MENU_4)
          return EXIT_COUNTDOWN;

        currentMenu = currentMenu->childrenMenu;
        currentMenu->selectedItem = 0;
        showChild(currentMenu->id);

        lastMillis = millis();
        return UPDATED_SCREEN;
      }
      break;
    
    case LAYER_2:
      if (wasPressed(btnMiddle)){
        return EXIT_COUNTDOWN;
      }
      /*
      else if (wasPressed(btnLeft)){
        //
      }

      else if (wasPressed(btnRight)){
        //
      }
      */
      break;
  }
}

void showChild(uint8_t childId){
  switch(childId){
    case MENU_1_1:{
      localDay = getDay();
      localSeconds = getSeconds();

      uint8_t hours = localSeconds / 3600;
      uint8_t minutes = (localSeconds % 3600) / 60;
      uint8_t remainingSeconds = localSeconds % 60;

      char buffer[50], temp[20];

      sprintf(buffer, "\n\n\n   ");

      if(hours <= 9)
        sprintf(temp, "0%d:", hours);
      else 
        sprintf(temp, "%d:", hours);
      strcat(buffer, temp);

      if(minutes <= 9)
        sprintf(temp, "0%d:", minutes);
      else 
        sprintf(temp, "%d:", minutes);
      strcat(buffer, temp);

      if(remainingSeconds <= 9)
        sprintf(temp, "0%d  %s", remainingSeconds, daysOfWeek[localDay]);
      else 
        sprintf(temp, "%d  %s", remainingSeconds, daysOfWeek[localDay]);
      strcat(buffer, temp);


      showTextOnScreen(buffer);
      showButtonsOnScreen();
      break;
    }
    default:
      showTextOnScreen("error: invalid");
  }
}

void restartMenu(){
  currentMenu = NULL;
}