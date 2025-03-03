// Libraries
#include "mbed.h"
#include "arm_book_lib.h"
#define NIGHT_LEVEL 35   // Car Detected
#define DAY_LEVEL 40     // No Car Detected
#define LIGHT_SENSOR_SAMPLES 10  // Number of samples to average

AnalogIn lightsens(A0);               // Light sensor (LDR)

bool Car_Detect = false;           
int accumulatedTimeDelay = 0;        // For tracking delay times
float lightReadingsArray[LIGHT_SENSOR_SAMPLES];  // Array to store light readings
static int lightSampleIndex = 0;                 // Index for current sample

bool carAtEntrance() 
{
    // Add new reading to array
    lightReadingsArray[lightSampleIndex] = lightsens.read();
    lightSampleIndex++;
    
    // Reset index if we reach the end of array
    if (lightSampleIndex >= LIGHT_SENSOR_SAMPLES) {
        lightSampleIndex = 0;
    }
    
    // Calculate average
    float lightReadingsSum = 0.0;
    for (int i = 0; i < LIGHT_SENSOR_SAMPLES; i++) {
        lightReadingsSum += lightReadingsArray[i];
    }
    
    // Scale to 0-100 (higher number means darker)
    float currentLightLevel = (1.0 - (lightReadingsSum / LIGHT_SENSOR_SAMPLES)) * 100;
    
    // Check if the light level indicates dusk or darker
    if (currentLightLevel >= NIGHT_LEVEL) {
        Car_Detect = true;  
    } else if (currentLightLevel < DAY_LEVEL) {
        Car_Detect = false; 
    }
    
    return Car_Detect;  // Return the state of Car_Detect
}
