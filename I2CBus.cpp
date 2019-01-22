/*****************************************************************************
  Author
  ------
    Stephane Camberlin <stephane.camberlin@gmail.com> (c) 2018
    
  License
  -------
    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

*****************************************************************************/


#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <Wire.h>

#include "I2CBus.h"

I2CBus::I2CBus(void) {}

I2CBus::~I2CBus() {}

boolean I2CBus::error() { return _error; }
String I2CBus::errorStr() { return _errorStr; }

int I2CBus::scan_i2c_bus() {
  byte error, address;
  int nDevices = 0;
  static size_t arrayIndex = 0;  
  Wire.begin();
  Serial.println("Scanning i2c bus for devices.");
  for(address = 1; address < 127; address++ ) {
    Wire.beginTransmission(address);
    error = Wire.endTransmission();
    if (error == 0) {
      Serial.print("I2C device found at address 0x");
      if (address<16) 
        Serial.print("0");
      Serial.print(address,HEX);
      Serial.print(".\n");
      nDevices++;
      // if (address != 0)
      //  _ads1115[ arrayIndex++ ] = (byte) address;
    } else if (error==4) {
      Serial.print("Unknown error at address 0x");
      if (address<16) 
        Serial.print("0");
      Serial.print(address,HEX);
      Serial.print(".\n");
      return 0;
    }
  }
  if (nDevices == 0) {
    Serial.println("No I2C devices found.\n");
    return 0;
  }
  return (int) nDevices;
}
