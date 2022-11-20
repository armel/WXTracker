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
    display.drawLine(0, 85, 240, 85, WHITE);  // Fill the screen with black (to clear the screen). 
}

void loop() {
    boolean refresh = false;

    static uint16_t iteration = 0;
    static uint8_t range = 0;

    char str_min[10];
    char str_max[10];

    float min, max;

    getButton();

    if(btnA == 1)
    {
        range = (range++ < (NUMBER_OF_RANGES - 1)) ? range : 0;
        refresh = true;
    }

    while (!bme.begin(0x76)) {
        Serial.println("Could not find a valid BMP280 sensor, check wiring!");
    }
    data[0] = dht12.readTemperature();  // Store the temperature obtained from dht12.
    data[1] = dht12.readHumidity();     // Store the humidity obtained from dht12.
    data[2] = bme.readPressure() / 100; // Stores the pressure gained by BMP.

    //display.setCursor(0, 0);
    //display.printf("ENV (DHT12 / BMP280)\n\n\n\nTEMPERATURE: %2.1f  \n\nHUMIDITE: %2.0f %%  \n\nPRESSION: %2.0f", tmp, hum, pressure);

    for(uint8_t i = 0; i < NUMBER_OF_RANGES; i++)
    {
        if(iteration % periodicity_time[i] == 0)          // 1 hour 
        {
            Serial.printf("%d %d\n", iteration, periodicity_time[i]);
            save(i);
            if(range == i) refresh = true;
        }
    }

    //Serial.printf("--> %d %d %d %d\n", btnA, btnB, range, refresh);

    // Refresh
    if(refresh == true)
    {
        for(uint8_t i = 0; i < NUMBER_OF_TYPES; i++)
        {
            switch(i)
            {
                case 0:
                display.setTextColor(TFT_ORANGE, TFT_BLACK);
                break;

                case 1:
                display.setTextColor(TFT_SKYBLUE, TFT_BLACK);
                break;

                case 2:
                display.setTextColor(TFT_WHITE, TFT_BLACK);
                break;
            }

            // Value
            display.setFont(&YELLOWCRE8pt7b);

            display.setTextPadding(240);
            display.setTextDatum(TL_DATUM);
            display.drawString(types[i], 0, 6 + (45 * i));
            
            display.setTextPadding(0);
            display.setTextDatum(TR_DATUM);
            display.drawFloat(data[i], 1, 240, 6 + (45 * i));

            // Range
            display.setTextColor(TFT_LIGHTGREY, TFT_BLACK);
            display.setFont(&tahoma8pt7b);
            display.setTextPadding(240);
            display.setTextDatum(TL_DATUM);

            display.drawString(String(periodicity_name[range]) + " (" + String(indice[i][range]) + ")", 0, 22 + (45 * i));

            // Min and Max
            display.setTextPadding(0);
            display.setTextDatum(TR_DATUM);

            min = measures_min[i][range];
            max = measures_max[i][range];
            sprintf(str_min, "%2.1f", min);
            sprintf(str_max, "%2.1f", max);

            display.drawString(String(str_min) + " - " + String(str_max), 240, 22 + (45 * i));
        }
        refresh = false;
    }

    iteration++;
    if(iteration == 15 * 4 * 60 * 24)
    {
        iteration = 0;
    }

    delay(1000);
}
