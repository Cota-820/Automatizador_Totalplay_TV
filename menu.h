#ifndef MENU_h
#define MENU_H

#include "display.h"
#include "buttons.h"
#include "local_time.h"
#include "string.h"

uint8_t updateMenu(bool middleBtn, bool leftBtn, bool rightBtn);
void restartMenu();

#endif