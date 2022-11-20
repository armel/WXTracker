// Copyright (c) F4HWN Armel. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

void shift(float *measure, float measure_new, uint16_t indice)
{
    if(indice < NUMBER_OF_MEASURES)
    {
        measure[indice] = measure_new;
    }
    else
    {    
        for(uint16_t i = 0; i < NUMBER_OF_MEASURES - 1; i++)
        {  
            measure[i] = measure[i + 1];  
        }
        measure[NUMBER_OF_MEASURES - 1] = measure_new;
    }

    /*
    for(uint16_t i = 0; i <= NUMBER_OF_MEASURES - 1; i++)
    {
        Serial.printf("%d %2.0f\n", i, measure[i]);
    }
    Serial.println("-----");
    */
}

// Manage map float
float mapFloat(float x, float in_min, float in_max, float out_min, float out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

float getMin(float *measure, uint16_t indice)
{
    float min = 1000000;

    for(uint16_t i = 0; i <= indice - 1; i++)
    {
        if(measure[i] <= min)
        {
            min = measure[i];
        }
    }
    return min;
}

float getMax(float *measure, uint16_t indice)
{
    float max = 0;

    for(uint16_t i = 0; i <= indice - 1; i++)
    {
        if(measure[i] >= max)
        {
            max = measure[i];
        }
    }
    return max;
}

void save(uint8_t range)
{
    for(uint8_t i = 0; i < NUMBER_OF_TYPES; i++)
    {
        shift(measures[i][range], data[i], indice[i][range]);

        if(indice[i][range] < NUMBER_OF_MEASURES)
        {
            indice[i][range]++;
        }

        measures_min[i][range] = getMin(measures[i][range], indice[i][range]);
        measures_max[i][range] = getMax(measures[i][range], indice[i][range]);

        if(measures_min[i][range] == 0) measures_min[i][range] = measures_max[i][range];

        //Serial.printf("%d, %2.1f, %2.1f\n", i, measures_min[i][range], measures_max[i][range]);
    }

}

void getButton()
{
    M5.update();
    btnA = M5.BtnA.isPressed();
    btnB = M5.BtnB.isPressed();
}