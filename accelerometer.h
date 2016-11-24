#ifndef ACCELEROMETER_H
#define ACCELEROMETER_H

#include <Arduino.h>

// This address is fixed for the board we use because pin 12 is fixed to GND
byte DEVICE_ADDRESS = 0x53;

/**
 * Prepare everything to work properly
 */
void setupAccelerometer();

/**
 * Get acceleration values for each axis
 */
void getAxesValues(int &x, int &y, int &z);

/**
 * The ADXL345 gives 10-bit or 13-bit acceleration values, but they are stored
 * as bytes (8-bits).
 * To get the full value, two bytes must be combined for each axis.
 */
int calculateAxisValue(int youngerByte, int olderByte);

#endif
