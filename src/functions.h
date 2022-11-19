// Copyright (c) F4HWN Armel. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

void shift(float *measure, float measure_new, uint16_t indice)
{
    if(indice < NUMBER_OF_MEASURE)
    {
        measure[indice] = measure_new;
    }
    else
    {    
        for(uint16_t i = 0; i < NUMBER_OF_MEASURE - 1; i++)
        {  
            measure[i] = measure[i + 1];  
        }
        measure[NUMBER_OF_MEASURE - 1] = measure_new;
    }

    for(uint16_t i = 0; i <= NUMBER_OF_MEASURE - 1; i++)
    {
        Serial.printf("%d %2.0f\n", i, measure[i]);
    }
    Serial.println("-----");
}

String extrem(float *measure)
{
    char str_min[10];
    char str_max[10];

    float min = 1000000;
    float max = 0;

    for(uint16_t i = 0; i <= NUMBER_OF_MEASURE - 1; i++)
    {
        if(measure[i] < min)
        {
            min = measure[i];
        }
        else if(measure[i] > max)
        {
            max = measure[i];
        }
    }

    sprintf(str_min, "%2.1f", min);
    sprintf(str_max, "%2.1f", max);

    return String(str_min) + " - " + String(str_max);
}