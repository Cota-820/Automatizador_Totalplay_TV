#include "display.h"
#include "string.h" 

void showTimeOnScreen(Adafruit_SSD1306& display, uint16_t segundos){
  if (segundos < 0) segundos = 0;

  uint8_t horas = segundos / 3600;
  uint8_t minutos = (segundos % 3600) / 60;
  uint8_t segundos_restantes = segundos % 60;

  display.clearDisplay();
  display.setCursor(0, 0);
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.println("Tiempo para siguiente\nenvio:\n");
  display.print("Hrs:");
  display.print(horas);
  display.print(" Min:");
  display.print(minutos);
  display.print(" Sec:");
  display.println(segundos_restantes);
  display.display();
}

void showTextOnScreen(Adafruit_SSD1306& display, char *str, int size){
  display.clearDisplay();
  display.setCursor(0, 0);
  display.setTextSize(size);
  display.setTextColor(SSD1306_WHITE);
  display.print(str);
  display.display();
}