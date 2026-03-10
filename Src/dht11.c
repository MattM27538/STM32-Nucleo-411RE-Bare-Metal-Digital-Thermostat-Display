#include "dht11.h"
#include "stm32f4xx.h"
#include "delay.h"
#include <oled.h>
#include <stdbool.h>

void setPinPA8AsOutput(){
	GPIOA->MODER |= GPIO_MODER_MODE8_0;
	GPIOA->MODER &= ~GPIO_MODER_MODE8_1;
}

void setPinPA8Low(){
	GPIOA->BSRR = GPIO_BSRR_BR8;
}

void setPinPA8AsInput(){
	GPIOA->MODER &= ~GPIO_MODER_MODE8;
}

void dht11Start(){
	setPinPA8AsOutput();

	setPinPA8Low();

	delayMilliSeconds(18);

	setPinPA8AsInput();
}

void enablePinA8ForDHT11(){
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
}

void runDHT11(DHT11Data temperatureAndHumidity, char* oledBuffer){
	enablePinA8ForDHT11();

	while(true){
		dht11Start();

		if(getDHT11StartResponse() == dht11StartSuccess){
			getDHTData(&temperatureAndHumidity.temperature, &temperatureAndHumidity.humidity);

			sprintf(oledBuffer, "Temp = %0.1f", temperatureAndHumidity.temperature);

			SSD1306_GotoXY (0, 20);
			SSD1306_Puts(oledBuffer, &Font_11x18, 1);

			sprintf(oledBuffer, "Humi = %0.1f", temperatureAndHumidity.humidity);
			
			SSD1306_GotoXY (0, 40);
			SSD1306_Puts(oledBuffer, &Font_11x18, 1);

			SSD1306_UpdateScreen();
		}
		else{
			sprintf(oledBuffer,"DHT Error");
		}

		delayMilliSeconds(1000);
	}
}

bool pinPA8IsHigh(){
	return GPIOA->IDR & GPIO_IDR_ID8;
}

DHT11Response getDHT11StartResponse(){
	uint8_t DHT11Response = 0;
	
	delayMicroSeconds(40);

	if (!(pinPA8IsHigh())){
		delayMicroSeconds(80);

		if (pinPA8IsHigh()){
			DHT11Response = dht11StartSuccess;
		}
		else{
			DHT11Response = dht11StartError;
		}
	}
	while (pinPA8IsHigh()){};
	
	return DHT11Response;
}

static uint8_t dht11ReadData(){
	uint8_t byteFromDHT11 = 0;
	const uint8_t numberOfBitsDHT11Sends = 8;
	for (uint8_t j = 0; j < numberOfBitsDHT11Sends; ++j){
		while (!pinPA8IsHigh()){}
		
		delayMicroSeconds (40);

		const int bitPositionToWriteTo = numberOfBitsDHT11Sends - j - 1;

		if (!pinPA8IsHigh()) {
			byteFromDHT11 &= ~(1 << bitPositionToWriteTo);
		}
		else {
			byteFromDHT11 |= (1 << bitPositionToWriteTo);
		};  

		while (!pinPA8IsHigh()){}
	}

	return byteFromDHT11;
}

void getDHTData(float *temperature, float *relativeHumidity){
	const uint8_t relativeHumidityIntegerComponent = dht11ReadData();

	//TODO: Remove storage of decimal components?
	const uint8_t relativeHumidityDecimalComponent = dht11ReadData();

	const uint8_t temperatureIntegerComponent = dht11ReadData();

	const uint8_t temperatureDecimalComponent = dht11ReadData();

	const uint8_t dataCheckSum = dht11ReadData();
	
	//TODO: checkSum (does Last 8 bits of (Byte 1 + Byte 2 + Byte 3 + Byte 4) = byte5?)

	*relativeHumidity = (float)relativeHumidityIntegerComponent;
	*temperature = (float)temperatureIntegerComponent;
}
