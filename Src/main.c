#include "oled.h"
#include "dht11.h"
#include "delay.h"
#include <stdbool.h>

int main(){
	SSD1306DisplayInit();

	const int oledBufferForDisplay1Size = 20;
	
	OLEDBuffer oledBufferForDisplay1 = oledBufferCreate(oledBufferForDisplay1Size);

	static DHT11Data temperatureAndHumidityData = {0.0, 0.0};

	runDHT11(&temperatureAndHumidityData, &oledBufferForDisplay1);
}


