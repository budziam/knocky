#include <Wire.h>

byte DEVICE_ADDRESS = 0x53; //This address is fixed for the board we use because pin 12 is fixed to GND

byte DATA_FORMAT = 0x31;   //Data Format & Measurement Range Register
byte POWER_CTRL = 0x2D;    //Power Control Register
byte INT_ENABLE = 0x2E;    //Enable Data Ready Interrupt

byte DATAX0 = 0x32;        //X-Axis Data 0

byte values[6];

void setup()
{
  Wire.begin();    //Initiate the Wire library and join the I2C bus as a master. This is called only once.
  Serial.begin(9600);

  //Minimum initialization sequance according to the application note.
  writeRegister(DEVICE_ADDRESS, DATA_FORMAT, 0x0B); //Put the ADXL345 into Measurement Mode with full resolution (13-bit) and +/-16G range.
  writeRegister(DEVICE_ADDRESS, POWER_CTRL, 0x08); //Start Measurement.
  writeRegister(DEVICE_ADDRESS, INT_ENABLE, 0x80); //Enable Data Ready Interrupt.
}

void loop()
{
    int x, y, z;
    normalMode(x, y, z);

    Serial.print(x, DEC);
    Serial.print(", ");
    Serial.print(y, DEC);
    Serial.print(", ");
    Serial.print(z, DEC);
    Serial.println();
}

void normalMode(int &x, int &y, int &z)
{
  readRegister(DEVICE_ADDRESS, DATAX0, 6, values); 

  x = getAccelerationValue(values[0], values[1]);
  y = getAccelerationValue(values[2], values[3]);
  z = getAccelerationValue(values[4], values[5]);
  
  delay(15);
}

/**
 * The ADXL345 gives 10-bit or 13-bit acceleration values, but they are stored as bytes (8-bits).
 * To get the full value, two bytes must be combined for each axis.
 */
int getAccelerationValue(int youngerByte, int olderByte)
{
	return olderByte << 8 | youngerByte;
}

void writeRegister(byte device, byte registerAddress, byte value)
{
  Wire.beginTransmission(device);    //Start transmission to device
  Wire.write(registerAddress);       //Specify the address of the register to be written to
  Wire.write(value);                 //Send the value to be writen to the register
  Wire.endTransmission();            //End transmission 
}

void readRegister(byte device, byte registerAddress, int numBytes, byte *values)
{
  byte address = registerAddress;

  Wire.beginTransmission(device);
  Wire.write(address);
  Wire.endTransmission();

  Wire.beginTransmission(device);     
  Wire.requestFrom(device, numBytes);  //Request 6 bytes from device

  int i = 0;
  while (Wire.available() && i < numBytes) {        //Device may send less than requested
    values[i] = Wire.read();                        //Receive a byte from device and put it into the buffer
    i++;
  }
  
  Wire.endTransmission(); 
}
