#include "display.h"

static Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void initDisplay(uint8_t warningLed){
  if (!display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDRESS)) {
    digitalWrite(warningLed, HIGH);
    Serial.println(F("Error al inicializar la pantalla"));
    while (true); //stop program
  }
  
  display.setTextSize(1);

  showTextOnScreen("Iniciando...");
}

void clearScreen(){
  display.clearDisplay();
}

void clearScreenText(uint16_t x_pos, uint16_t y_pos, uint16_t characterNum){
  char blankText[characterNum];
  for (int i=0; i<characterNum; i++)
    blankText[i] = ' ';

  display.setCursor(x_pos, y_pos);
  display.setTextColor(SSD1306_WHITE, SSD1306_BLACK);
  display.print(blankText);
  display.display();
}

void showMainScreen(uint16_t secondsCountdown, uint32_t seconds, uint8_t day, uint8_t week){
  char buffer[50];
  uint8_t hours = seconds / 3600;
  uint8_t minutes = (seconds % 3600) / 60;
  uint8_t remainingSeconds = seconds % 60;
  bool pm = (hours >= 12) ? true : false;

  hours = pm ? hours-12 : hours;

  if (secondsCountdown < 0) secondsCountdown = 0;

  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);
  
  switch(day){
    case MONDAY: 
      display.setCursor(LETTER_LEN*8, ROW_HIGHT*0);
      break;
    case TUESDAY:
    case THURSDAY:
    case SATURDAY: 
      display.setCursor(LETTER_LEN*7.5, ROW_HIGHT*0);
      break;
    case WEDNESDAY:
      display.setCursor(LETTER_LEN*6, ROW_HIGHT*0);
      break;
    case FRIDAY:
    case SUNDAY: 
      display.setCursor(LETTER_LEN*7, ROW_HIGHT*0);
      break;
  }
  display.print(daysOfWeek[day]);


  sprintf(buffer, "%02d:%02d:%02d", hours, minutes, remainingSeconds);
  if (pm)
    strcat(buffer, " PM");
  else
    strcat(buffer, " AM");
  display.setCursor(LETTER_LEN*5, ROW_HIGHT*1);
  display.print(buffer);
  
  display.setCursor(LETTER_LEN*6.5, ROW_HIGHT*2);
  display.print("Semana:");
  week++;
  display.print(week);


  uint8_t hoursCountdown = secondsCountdown / 3600;
  uint8_t minutesCountdown = (secondsCountdown % 3600) / 60;
  uint8_t remainingSecondsCountdown = secondsCountdown % 60;

  sprintf(buffer, "Envio en: %02d:%02d:%02d", hoursCountdown, minutesCountdown, remainingSecondsCountdown);
  display.setCursor(LETTER_LEN*1.5, ROW_HIGHT*4);
  display.print(buffer);

  display.drawLine(40, 50, 87, 50, SSD1306_WHITE);
  display.drawLine(87, 50, 87, 64, SSD1306_WHITE);
  display.drawLine(40, 50, 40, 64, SSD1306_WHITE);
  display.setCursor(LETTER_LEN*8.5, ROW_HIGHT*7);
  display.print("Menu");
  display.display();
}

void showButtonsOnScreen(){
  display.setTextColor(SSD1306_WHITE);
  
  display.drawLine(0, 50, 28, 50, SSD1306_WHITE);
  display.drawLine(28, 50, 28, 64, SSD1306_WHITE);
  display.drawLine(0, 50, 0, 64, SSD1306_WHITE);
  display.setCursor(5, ROW_HIGHT*7);
  display.print("<--");

  display.drawLine(40, 50, 87, 50, SSD1306_WHITE);
  display.drawLine(87, 50, 87, 64, SSD1306_WHITE);
  display.drawLine(40, 50, 40, 64, SSD1306_WHITE);
  display.setCursor(LETTER_LEN*8, ROW_HIGHT*7);
  display.print("Elegir");

  display.drawLine(100, 50, 127, 50, SSD1306_WHITE);
  display.drawLine(127, 50, 127, 64, SSD1306_WHITE);
  display.drawLine(100, 50, 100, 64, SSD1306_WHITE);
  display.setCursor((LETTER_LEN*18)-2, ROW_HIGHT*7);
  display.print("-->");

  display.display();
}

void showTextOnScreen(char *str){
  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE, SSD1306_BLACK);
  display.setCursor(0, 0);
  display.print(str);
  display.display();
}

void showTextOnScreenParams(char *str, bool clearScreen, uint8_t color, uint16_t x_pos, uint16_t y_pos){
  if(clearScreen)
    display.clearDisplay();
  if (color == TEXT_WHITE)
    display.setTextColor(SSD1306_WHITE, SSD1306_BLACK);
  else if (color == TEXT_HIGHLIGHTED)
    display.setTextColor(SSD1306_BLACK, SSD1306_WHITE);
  display.setCursor(x_pos, y_pos);
  display.print(str);
  display.display();
}