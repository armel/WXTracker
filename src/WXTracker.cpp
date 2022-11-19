// Copyright (c) F4HWN Armel. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <WXTracker.h>
#include "font.h"
#include "functions.h"

void setup() {
    // Init M5
    auto cfg = M5.config();
    M5.begin(cfg);

    // Wire
    Wire.begin(32, 33);  // Wire init, adding the I2C bus.

    // Init Display
    display.begin();
    display.clear();
    display.setRotation(3);  // Rotate the screen. 
    display.setFont(&YELLOWCRE8pt7b);

    // Draw Line
    display.drawLine(0, 40, 240, 40, WHITE);  // Fill the screen with black (to clear the screen). 
}

void loop() {
    static uint16_t iteration = 0;
    static uint8_t alternance = 0;
    float data[3] = { 0 };

    while (!bme.begin(0x76)) {
        Serial.println("Could not find a valid BMP280 sensor, check wiring!");
    }
    data[0] = dht12.readTemperature();    // Store the temperature obtained from dht12.
    data[1] = dht12.readHumidity();       // Store the humidity obtained from dht12.
    data[2] = bme.readPressure();    // Stores the pressure gained by BMP.

    //display.setCursor(0, 0);
    //display.printf("ENV (DHT12 / BMP280)\n\n\n\nTEMPERATURE: %2.1f  \n\nHUMIDITE: %2.0f %%  \n\nPRESSION: %2.0f", tmp, hum, pressure);

    if(iteration % 15 == 0)          // 1 hour 
    {
        Serial.printf("%d %d\n", iteration, 15);
        shift(measure_t[0], data[0], indice[0]);
        shift(measure_h[0], data[1], indice[0]);
        shift(measure_p[0], data[2], indice[0]);

        if(indice[0] < NUMBER_OF_MEASURE)
        {
            indice[0]++;
        }
    }
    /*
    if(iteration % 30 == 0)     // 2 hours 
    {
        Serial.printf("%d %d\n", iteration, 30);
        shift(measure_t[1], data[0], indice[1]);
        shift(measure_h[1], data[1], indice[1]);
        shift(measure_p[1], data[2], indice[1]);

        if(indice[1] < NUMBER_OF_MEASURE)
        {
            indice[1]++;
        }
    }
    if(iteration % 60 == 0)     // 4 hours
    {
        Serial.printf("%d %d\n", iteration, 60);
        shift(measure_t[2], data[0], indice[2]);
        shift(measure_h[2], data[1], indice[2]);
        shift(measure_p[2], data[2], indice[2]);

        if(indice[2] < NUMBER_OF_MEASURE)
        {
            indice[2]++;
        }
    }
    if(iteration % 120 == 0)    // 8 hours
    {
        Serial.printf("%d %d\n", iteration, 120);

        shift(measure_t[3], data[0], indice[3]);
        shift(measure_h[3], data[1], indice[3]);
        shift(measure_p[3], data[2], indice[3]);

        if(indice[3] < NUMBER_OF_MEASURE)
        {
            indice[3]++;
        }
    }
    if(iteration % 360 == 0)    // 24 hours
    {
        Serial.printf("%d %d\n", iteration, 360);

        shift(measure_t[4], data[0], indice[4]);
        shift(measure_h[4], data[1], indice[4]);
        shift(measure_p[4], data[2], indice[4]);

        if(indice[4] < NUMBER_OF_MEASURE)
        {
            indice[4]++;
        }
    }
    */

    iteration++;
    if(iteration == 15 * 4 * 60 * 24)
    {
        iteration = 0;
    }

    // Value
    display.setTextColor(TFT_FRONT, TFT_BACK);
    display.setFont(&YELLOWCRE8pt7b);

    display.setTextPadding(240);
    display.setTextDatum(TL_DATUM);
    display.drawString(measures[alternance], 0, 6);
    
    display.setTextPadding(0);
    display.setTextDatum(TR_DATUM);
    display.drawFloat(data[alternance], 1, 240, 6);

    // Min and Max

    display.setTextColor(TFT_FRONT, TFT_BACK);
    display.setFont(&YELLOWCRE8pt7b);

    display.setTextPadding(240);
    display.setTextDatum(TR_DATUM);
    switch(alternance)
    {
        case 0:
            display.drawString(extrem(measure_t[0]), 240, 22);
            break;
        case 1:
            display.drawString(extrem(measure_h[0]), 240, 22);
            break;
        case 2:
            display.drawString(extrem(measure_p[0]), 240, 22);
            break;
    }

    alternance++;
    if(alternance == 3)
    {
        alternance = 0;
    }

    delay(1000);
}
