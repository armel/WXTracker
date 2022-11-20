// Copyright (c) F4HWN Armel. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <M5Unified.h>
#include "M5_ENV.h"
#include <Adafruit_BMP280.h>
#include "Adafruit_Sensor.h"

#define NUMBER_OF_TYPES 3
#define NUMBER_OF_RANGES 6
#define NUMBER_OF_MEASURES 240

M5GFX &display(M5.Lcd);

DHT12 dht12;
Adafruit_BMP280 bme;

uint16_t TFT_BACK   = 0x0000;
uint16_t TFT_FRONT  = 0xffff;

int8_t btnA, btnB;

const char *types[] = {"TEMPERATURE", "HUMIDITY", "PRESSURE"};
const char *periodicity_name[] = {"1s-4m", "15s-1h", "30s-2h", "1m-4h", "2m-8h", "6m-8h"};
uint16_t periodicity_time[] = {1, 15, 30, 60, 120, 240};

uint16_t indice[NUMBER_OF_TYPES][NUMBER_OF_RANGES] = { 0 };

float data[NUMBER_OF_TYPES] = { 0 };
float measures[NUMBER_OF_TYPES][NUMBER_OF_RANGES][NUMBER_OF_MEASURES] = { 0 };
float measures_min[NUMBER_OF_TYPES][NUMBER_OF_RANGES] = { 1000000 };
float measures_max[NUMBER_OF_TYPES][NUMBER_OF_RANGES] = { 0 };
