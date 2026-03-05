#include "stdint.h"

#ifndef DHT11_H_
#define DHT11_H_

typedef enum{
	dht11StartSuccess = 0,
	dht11StartError = 1
} DHT11Response;

typedef struct{
	float temperature;
	float humidity;	
} DHT11Data;

void runDHT11();

void enablePinA8ForDHT11();

void dht11Start();

DHT11Response getDHT11StartResponse();

void getDHTData(float *temperature, float *relativeHumidity);

#endif
