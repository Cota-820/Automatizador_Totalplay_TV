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
  if (secondsCountdown < 0) secondsCountdown = 0;

  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);

  display.setCursor(0, ROW_HIGHT*0);
  display.print(daysOfWeek[day]);

  uint8_t hours = seconds / 3600;
  uint8_t minutes = (seconds % 3600) / 60;
  uint8_t remainingSeconds = seconds % 60;
  display.setCursor(LETTER_LEN*11, ROW_HIGHT*0);
  display.print(hours);
  display.print(":");
  display.print(minutes);
  display.print(":");
  display.print(remainingSeconds);

  display.setCursor(0, ROW_HIGHT*1);
  display.print("Semana:");
  week++;
  display.print(week);


  uint8_t hoursCountdown = secondsCountdown / 3600;
  uint8_t minutesCountdown = (secondsCountdown % 3600) / 60;
  uint8_t remainingSecondsCountdown = secondsCountdown % 60;

  display.setCursor(0, ROW_HIGHT*4);
  display.print("Envio en: ");
  display.print(hoursCountdown);
  display.print(":");
  display.print(minutesCountdown);
  display.print(":");
  display.print(remainingSecondsCountdown);

  display.setCursor((LETTER_LEN*8)+3, ROW_HIGHT*7);
  display.print("Menu");
  display.display();
}

void showButtonsOnScreen(uint8_t buttonText){
  display.setTextColor(SSD1306_WHITE);
  
  display.drawLine(0, 50, 25, 50, SSD1306_WHITE);
  display.drawLine(25, 50, 25, 64, SSD1306_WHITE);
  display.drawLine(0, 50, 0, 64, SSD1306_WHITE);
  display.setCursor(1, ROW_HIGHT*7);
  display.print("<--");

  
  display.setCursor(LETTER_LEN*7, ROW_HIGHT*7);
  if (buttonText == CHOOSE)
    display.print("Elegir");
  else if(buttonText == CHANGE)
    display.print("Cambiar");

  display.drawLine(100, 50, 127, 50, SSD1306_WHITE);
  display.drawLine(127, 50, 127, 64, SSD1306_WHITE);
  display.drawLine(100, 50, 100, 64, SSD1306_WHITE);
  display.setCursor((LETTER_LEN*18)-1, ROW_HIGHT*7);
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