#include <Arduino.h>
#include "accelerometer.h"
#include "knock_detector.h"
#include "knock_listener.h"

#define KNOCK_SIZE 10

KnockDetector *detectorX = 0;
KnockDetector *detectorY = 0;
KnockDetector *detectorZ = 0;

void setup()
{
  Serial.begin(9600);
  
  detectorX = new KnockDetector('X');
  detectorY = new KnockDetector('Y');
  detectorZ = new KnockDetector('Z');
  
  setupAccelerometer();
  setupActions();
}

void loop()
{
  analyzeAcceleratorValues();
  knockListenerLoop();
}

void analyzeAcceleratorValues()
{
  static uint32_t previousMillis = millis();
  
  if (millis() - previousMillis < 5) {
    return;
  }
  
  int x, y, z;
  getAxesValues(x, y, z);
  
  if (isKnock(x, y, z)) {
    onKnock();
  }
  
  //printAxis(x, y, z, true);
  
  previousMillis = millis();
}

boolean isKnock(int x, int y, int z)
{
  static uint32_t knock_index = 0;
  static uint32_t last_knock = 0;
  
  knock_index += 1;
  boolean xKnock = detectorX->push(x);
  boolean yKnock = detectorY->push(y);
  boolean zKnock = detectorZ->push(z);
  
  if (knock_index - last_knock < KNOCK_SIZE) {
    return false;
  }
  
  if (!xKnock && !yKnock && !zKnock) {
    return false;
  }
  
  last_knock = knock_index;
  
  return true;
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

