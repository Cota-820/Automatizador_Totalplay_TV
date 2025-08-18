# Automatizador para decodificador Totalplay

## Programa para eliminar el modo reposo del decodificador Totalplay usando la placa ESP32 y señales IR

La empresa de Totalplay a inicios de año 2025, saco una actualización para su decodificador la cual activa el modo reposo después de 6 horas si no detecta actividad alguna, lo cual elimina la reproducción de lo que estaba mostrando.
Esto no es una opción que se puede cambiar en el dispositivo y tampoco algo que se puede solicitar. Para un usuario normal esto no es un gran problema, pero si eres parte de un negocio o empresa que usa este servicio para mostrarlo 24/7, tendrías que estar activando manualmente cada  ciertas horas.
Este programa automatiza el envío de señales infrarrojas, las mismas enviadas por el control remoto, para simular actividad hacia el decodificador.

# Hardware Utilizado
- ESP32-DevKitC (o placa generica)
- Led ir333-a
- Resistencia 100 Ω (220 Ω si no se utilizara Transistor)
- Transistor 2N2222
- Pantalla SSD1306 128x64px

# Características
El programa cuenta con varias funciones que pueden ser configuradas:
- Un botón para el envío manual de la señal y otros 3 para la manipulación de menú.
- Muestra el tiempo para el siguiente envío de señal.
- Muestra día y hora.
- Configuración para canales de cada día.
- Los datos se guardan en memoria no volátil(no se pierde al apagar el dispositivo), a excepción de minutos y segundos.

  # Cómo utilizar
Clona el proyecto y abrelo en el entorno de Arduino. 
Librerías requeridas:
- Adafruit-GFX-Library
- Adafruit_SSD1306
- IRremote. 

Se pueden cambiar las configuración por defecto del programa en el archivo "config.h".
El diagrama eléctrico se encuentra en "imagenes/diagrama.png". Es recomendable conectar el led al transistor y no directamente al GPIO, esto para tener una mayor corriente. Una vez armado y cargado es recomendable dejarlo enfrente del decodificador o en un lugar donde el receptor pueda leer las señales del LED.
