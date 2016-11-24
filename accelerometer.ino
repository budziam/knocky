#include <Wire.h>
#include "register.h"

byte DATA_FORMAT = 0x31;
byte POWER_CTRL = 0x2D;
byte INT_ENABLE = 0x2E;

// Beginning of accelerate values data block as they are stored on 6 bytes
byte ACCELERATION_DATA = 0x32;

void setupAccelerometer()
{
  // Initiate the Wire library and join the I2C bus as a master.
  Wire.begin();
  
  // Minimum initialization sequance according to the application note.
  // Put the ADXL345 into Measurement Mode with full resolution (13-bit) and +/-16G range.
  writeRegister(DEVICE_ADDRESS, DATA_FORMAT, 0x0B);

  // Start measurement
  writeRegister(DEVICE_ADDRESS, POWER_CTRL, 0x08);

  // Enable data ready interrupt
  writeRegister(DEVICE_ADDRESS, INT_ENABLE, 0x80);
}

void getAxesValues(int &x, int &y, int &z)
{
  byte values[6];
  readRegister(DEVICE_ADDRESS, ACCELERATION_DATA, 6, values); 

  x = calculateAxisValue(values[0], values[1]);
  y = calculateAxisValue(values[2], values[3]);
  z = calculateAxisValue(values[4], values[5]);
}

int calculateAxisValue(int youngerByte, int olderByte)
{
  return olderByte << 8 | youngerByte;
}
