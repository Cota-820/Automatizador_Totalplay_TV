#include "display.h"

static Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void initDisplay(uint8_t warningLed){
  if (!display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDRESS)) {
    digitalWrite(warningLed, HIGH);
    Serial.println(F("Error al inicializar la pantalla"));
    while (true); //stop program
  }

  showTextOnScreen("Iniciando...", 1);
}

void showTimeOnScreen(uint16_t secondsCountdown, uint32_t seconds, uint8_t day){
  if (secondsCountdown < 0) secondsCountdown = 0;

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);

  display.setCursor(0, ROW_1);
  switch(day){
    case MONDAY:
      display.print("Lunes");
      break;
    case TUESDAY:
      display.print("Martes");
      break;
    case WEDNESDAY:
      display.print("Miercoles");
      break;
    case THURSDAY:
      display.print("Jueves");
      break;
    case FRIDAY:
      display.print("Viernes");
      break;
    case SATURDAY:
      display.print("Sabado");
      break;
    case SUNDAY:
      display.print("Domingo");
      break;
  }
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

void showTextOnScreen(char *str, int size){
  display.clearDisplay();
  display.setCursor(0, 0);
  display.setTextSize(size);
  display.setTextColor(SSD1306_WHITE);
  display.print(str);
  display.display();
}