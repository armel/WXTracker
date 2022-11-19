// Copyright (c) F4HWN Armel. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <M5Unified.h>
#include "M5_ENV.h"
#include <Adafruit_BMP280.h>
#include "Adafruit_Sensor.h"

#define NUMBER_OF_RANGE 5
#define NUMBER_OF_MEASURE 4

M5GFX &display(M5.Lcd);

DHT12 dht12;
Adafruit_BMP280 bme;

uint16_t TFT_BACK   = 0x0000;
uint16_t TFT_FRONT  = 0xffff;

const char *measures[] = {"TEMPERATURE", "HUMIDITY", "PRESSURE"};

uint16_t indice[NUMBER_OF_RANGE] = { 0 };

float measure_t[NUMBER_OF_RANGE][NUMBER_OF_MEASURE] = { 0 };
float measure_h[NUMBER_OF_RANGE][NUMBER_OF_MEASURE] = { 0 };
float measure_p[NUMBER_OF_RANGE][NUMBER_OF_MEASURE] = { 0 };
