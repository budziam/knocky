#include <Arduino.h>
#include "accelerometer.h"
#include "knock_detector.h"

void setup()
{
  Serial.begin(9600);
  
  setupAccelerometer();
}

void loop()
{
  analyzeAcceleratorValues();
}

void analyzeAcceleratorValues()
{
  static uint32_t previousMillis = millis();
  
  if (millis() - previousMillis < 10) {
    return;
  }
  
  int x, y, z;

  getAxesValues(x, y, z);
  knockDetectorPushValues(millis(), x, y, z);
  
  printAxis(x, y, z, false);
  
  previousMillis = millis();
}

void printAxis(int x, int y, int z, bool jsonFormat)
{
  if (jsonFormat) {
    Serial.print("{'x': ");
    Serial.print(x, DEC);
    Serial.print(", 'y': ");
    Serial.print(y, DEC);
    Serial.print(", 'z': ");
    Serial.print(z, DEC);
    Serial.print("},");
  } 
  else {
    Serial.print(x, DEC);
    Serial.print("\t\t");
    Serial.print(y, DEC);
    Serial.print("\t\t");
    Serial.print(z, DEC);
  }

  Serial.println();
}

