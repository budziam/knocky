#include <Wire.h>

// This address is fixed for the board we use because pin 12 is fixed to GND
byte DEVICE_ADDRESS = 0x53;

byte DATA_FORMAT = 0x31;
byte POWER_CTRL = 0x2D;
byte INT_ENABLE = 0x2E;

// Beginning of accelerate values data block as they are stored on 6 bytes
byte ACCELERATION_DATA = 0x32;

void setup()
{
    // Initiate the Wire library and join the I2C bus as a master.
    Wire.begin();
    Serial.begin(9600);

    // Minimum initialization sequance according to the application note.
    // Put the ADXL345 into Measurement Mode
    // with full resolution (13-bit) and +/-16G range.
    writeRegister(DEVICE_ADDRESS, DATA_FORMAT, 0x0B);
    
    // Start measurement
    writeRegister(DEVICE_ADDRESS, POWER_CTRL, 0x08);

    // Enable data ready interrupt
    writeRegister(DEVICE_ADDRESS, INT_ENABLE, 0x80);
}

void loop()
{
    printAxis(false);
}

void printAxis(bool jsonFormat)
{
    int x, y, z;
    
    getAxesValues(x, y, z);
    
    if (jsonFormat) {
        Serial.print("{'x': ");
        Serial.print(x, DEC);
        Serial.print(", 'y': ");
        Serial.print(y, DEC);
        Serial.print(", 'z': ");
        Serial.print(z, DEC);
        Serial.print("},");
    } else {
        Serial.print(x, DEC);
        Serial.print("\t\t");
        Serial.print(y, DEC);
        Serial.print("\t\t");
        Serial.print(z, DEC);
    }
    
    Serial.println();
}

/**
 * Get acceleration values for each axis
 */
void getAxesValues(int &x, int &y, int &z)
{
    byte values[6];
    readRegister(DEVICE_ADDRESS, ACCELERATION_DATA, 6, values); 

    x = calculateAxisValue(values[0], values[1]);
    y = calculateAxisValue(values[2], values[3]);
    z = calculateAxisValue(values[4], values[5]);
    
    delay(15);
}

/**
 * The ADXL345 gives 10-bit or 13-bit acceleration values, but they are stored
 * as bytes (8-bits).
 * To get the full value, two bytes must be combined for each axis.
 */
int calculateAxisValue(int youngerByte, int olderByte)
{
	return olderByte << 8 | youngerByte;
}

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
    Wire.requestFrom(device, numBytes); // Request numBytes bytes from device
    
    for(int i = 0; Wire.available() && i < numBytes; ++i) {
        values[i] = Wire.read();
    }
  
    Wire.endTransmission(); 
}
