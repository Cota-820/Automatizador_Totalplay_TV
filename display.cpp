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

void showTimeOnScreen(uint16_t secondsCountdown, uint32_t seconds, uint8_t day){
  if (secondsCountdown < 0) secondsCountdown = 0;

  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);

  display.setCursor(0, ROW_1);

  display.print(daysOfWeek[day]);

  uint8_t hours = seconds / 3600;
  uint8_t minutes = (seconds % 3600) / 60;
  uint8_t remainingSeconds = seconds % 60;
  display.setCursor(50, ROW_1);
  display.print(hours);
  display.print(":");
  display.print(minutes);
  display.print(":");
  display.print(remainingSeconds);

  uint8_t hoursCountdown = secondsCountdown / 3600;
  uint8_t minutesCountdown = (secondsCountdown % 3600) / 60;
  uint8_t remainingSecondsCountdown = secondsCountdown % 60;

  display.setCursor(0, ROW_3);
  display.print("Restante: ");
  display.print(hoursCountdown);
  display.print(":");
  display.print(minutesCountdown);
  display.print(":");
  display.print(remainingSecondsCountdown);

  display.setCursor(50, ROW_8);
  display.print("Menu");
  display.display();
}

void showButtonsOnScreen(){
  display.setTextColor(SSD1306_WHITE);
  
  display.drawLine(0, 50, 30, 50, SSD1306_WHITE);
  display.drawLine(30, 50, 30, 64, SSD1306_WHITE);

  display.setCursor(0, ROW_8);
  display.print("<--");

  display.setCursor(50, ROW_8);
  display.print("Elegir");

  display.setCursor(113, ROW_8);
  display.print("-->");

  display.display();
}

void showTextOnScreen(char *str){
  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.print(str);
  display.display();
}