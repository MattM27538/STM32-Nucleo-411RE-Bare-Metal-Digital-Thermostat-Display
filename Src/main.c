#include "oled.h"
#include "dht11.h"
#include "delay.h"
#include <stdbool.h>

int main(){
	SSD1306_Init();
	SSD1306_GotoXY (0,0);
	SSD1306_Puts ("DHT11 STM32", &Font_11x18, 1);
	SSD1306_UpdateScreen();
	
	OLEDBuffer oledBufferForDisplay1 = oledBufferCreate();

	DHT11Data temperatureAndHumidity = {0.0, 0.0}; 

	runDHT11(&temperatureAndHumidity, &oledBufferForDisplay1);
}


