#include <Wire.h>

void writeRegister(byte device, byte registerAddress, byte value)
{
  Wire.beginTransmission(device);

  // Specify the address of the register to be written to
  Wire.write(registerAddress);       

  // Send the value to be writen to the register
  Wire.write(value);

  Wire.endTransmission(); 
}

void readRegister(byte device, byte registerAddress, int numBytes, byte *values)
{
  Wire.beginTransmission(device);
  Wire.write(registerAddress);
  Wire.endTransmission();

  Wire.beginTransmission(device); 
  Wire.requestFrom(device, (uint8_t) numBytes); // Request numBytes bytes from device

  for(int i = 0; Wire.available() && i < numBytes; ++i) {
    values[i] = Wire.read();
  }

  Wire.endTransmission(); 
}
