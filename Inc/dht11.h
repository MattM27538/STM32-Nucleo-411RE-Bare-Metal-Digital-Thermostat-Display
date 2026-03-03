#include "stdint.h"

#ifndef DHT11_H_
#define DHT11_H_

typedef enum{
	dht11StartSuccess = 0,
	dht11StartError = 1
} DHT11Response;

void enablePinA8ForDHT11();

void dht11Start();

DHT11Response getDHT11StartResponse();

void getDHTData(float *temperature, float *relativeHumidity);

#endif
