#include <Arduino.h>
#include "accelerometer.h"
#include "knock_detector.h"
#include "knock_listener.h"

void setup()
{
  Serial.begin(9600);
  
  setupAccelerometer();
  setupKnockDetector();
  setupKnockListener();
}

void loop()
{
  analyzeAcceleratorValues();
}

void analyzeAcceleratorValues()
{
  static uint32_t previousMillis = millis();
  
  if (millis() - previousMillis < 5) {
    return;
  }
  
  int x, y, z;
  getAxesValues(x, y, z);
  
  knockDetectorPushValue(x, y, z);
  
  previousMillis = millis();
}

void printAxis(int x, int y, int z, bool csvFormat)
{
  if (csvFormat) {
    Serial.print(x, DEC);
    Serial.print(",");
    Serial.print(y, DEC);
    Serial.print(",");
    Serial.print(z, DEC);
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

