#include "menu.h"

enum exitFlags{
  NO_CHANGE,
  UPDATED_SCREEN;
  EXIT_SEND_SIGNAL,
  EXIT_COUNTDOWN,
};

enum manuLayers{
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
  menuDayHour_1->leftMenu = menuExit_4;
  menuDayHour_1->rightMenu = menuChannel_2;
  menuDayHour_1->childrenMenu = menuDayHour_1_1;

  menuChannel_2->leftMenu = menuDayHour_1;
  menuChannel_2->rightMenu = menuSendTime_3;
  menuChannel_2->childrenMenu = menuChannel_2_1;

  menuSendTime_3->leftMenu = menuChannel_2;
  menuSendTime_3->rightMenu = menuExit_4;
  menuSendTime_3->childrenMenu = menuChannel_3;

  menuExit_4->leftMenu = menuSendTime_3;
  menuExit_4->rightMenu = menuDayHour_1;

  menuDayHour_1_1->parentMenu = menuDayHour_1;

  menuChannel_2_1->parentMenu = menuChannel_2;
  menuChannel_2_1->childrenMenu = menuChannel_2_2;

  menuChannel_2_2->parentMenu = menuChannel_2_1;

  menuChannel_3_1->parentMenu = menuSendTime_3;
}

uint8_t updateMenu(bool middleBtn, bool leftBtn, bool rightBtn){
  //mostrar menu si fue reiniciado
  if(currentMenu == NULL){
    currentMenu = menuDayHour_1;
    showTextOnScreen(currentMenu->title);
    return UPDATED_SCREEN;
  }

  if(!middleBtn && !leftBtn && !rightBtn)
    return NO_CHANGE;

  uint8_t currentLayer = currentMenu->layer;

  switch(currentLayer){
    case LAYER_1:
      if (wasPressed(btnLeft)){
        current_menu = current_menu->leftMenu;
        showTextOnScreen(currentMenu->title);
        return UPDATED_SCREEN;
      }

      else if (wasPressed(btnRight)){
        current_menu = current_menu->rightMenu;
        showTextOnScreen(currentMenu->title);
        return UPDATED_SCREEN;
      }

      else if (wasPressed(btnMiddle)){
        if (current_menu->id == MENU_4)
          return EXIT_COUNTDOWN;

        current_menu = current_menu->childrenMenu;
        current_menu->selectedItem = 0;
        showChild(current_menu->id);

        lastMillis = millis();
        return UPDATED_SCREEN;
      }
      break;
    
    case LAYER_2:
      if (millis() - lastMillis >= 500){
        //update selected item
      }

      if (wasPressed(btnMiddle)){
        //
      }

      else if (wasPressed(btnLeft)){
        //
      }

      else if (wasPressed(btnRight)){
        //
      }
      break;
  }
}

void showChild(uint8_t childId){
  //

  switch(childId){
    case MENU_1_1:
      localDay = getDay();
      localSeconds = getSeconds();

      uint8_t hours = localSeconds / 3600;
      uint8_t minutes = (localSeconds % 3600) / 60;
      uint8_t remainingSeconds = localSeconds % 60;

      char buffer[50], temp[20];

      sprintf(buffer, "   ");

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
        sprintf(temp, "0%d  %s", remainingSeconds);
      else 
        sprintf(temp, "%d  %s", remainingSeconds);
      strcat(buffer, temp);


      showTextOnScreen();

      break;
    default:
      showTextOnScreen("error: invalid");
  }
}

void restartMenu(){
  currentMenu = NULL;
  currentItem = 0;
}