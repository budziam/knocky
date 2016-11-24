#ifndef REGISTER_H
#define REGISTER_H

#include <Arduino.h>

/**
 * Write data to a register
 */
void writeRegister(byte device, byte registerAddress, byte value);

/**
 * Read data from a register
 */
void readRegister(byte device, byte registerAddress, int numBytes, byte *values);

#endif
