/*****************************************************************************
  Author
  ------
    Stephane Camberlin <stephane.camberlin@gmail.com> - 2018 (c)
    Freely inspired from ej's o2 oled analyzer - v0.21 - http://ejlabs.net/arduino-oled-nitrox-analyzer
    
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
#include <EEPROM.h>
#include <Adafruit_ADS1015.h>

#include "O2Sensor.h"
#include "RunningAverage.h"

Adafruit_ADS1115 _ads(ADS_ADDRESS); // construct an ads1115 at address 0x48

#define RA_SIZE 20
RunningAverage _adc(RA_SIZE);

#ifndef O2_DEFAULT
#define O2_DEFAULT 20.95
#endif

O2Sensor::O2Sensor(void)
{
  /*
   * init ads1115: 16x gain (1 bit = 0.0078125mV)
   */
  _ads.setGain(GAIN_SIXTEEN);
  _ads.begin();
  byte lowByte = EEPROM.read(p_address);
  byte highByte = EEPROM.read(p_address + 1);
  _cal_adc = ((lowByte << 0) & 0xFF) + ((highByte << 8) & 0xFF00);
  if (_cal_adc < 1000) {
    _nDevices = scan_i2c_bus();
    _cal_adc = calibrate();
  }
}

O2Sensor::~O2Sensor() {}

boolean O2Sensor::error() { return _error; }
String O2Sensor::errorStr() { return _errorStr; }

int O2Sensor::scan_i2c_bus() {
  byte error, address;
  int nDevices = 0;
  static size_t arrayIndex = 0;  
  Wire.begin();
  Serial.println("Scanning i2c bus for Adafruit ADS1115.");
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
      if (address != 0)
        _ads1115[ arrayIndex++ ] = (byte) address;
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


/*
 *  read o2 sensor and add value in RunningAverage o2
 */
int16_t O2Sensor::readADC() {
  int adc = _ads.readADC_Differential_0_1();
  _adc.addValue(adc);
  return adc;
}


/*
 *  calibrate O2 sensor
 */
int O2Sensor::calibrate() {
  for (int cx = 1; cx <= RA_SIZE; cx++) {
    readADC();
    delay(100);
  }
  int p_value = abs(_adc.getAverage());
  byte lowByte = ((p_value >> 0) & 0xFF);
  byte highByte = ((p_value >> 8) & 0xFF);
  EEPROM.write(p_address, lowByte);
  EEPROM.write(p_address + 1, highByte);
  return p_value;
}

float O2Sensor::calMv() { 
  return (_cal_adc * _gain); 
}

float O2Sensor::avgTension() {
  readADC();
  return (float) abs(_adc.getAverage() * _gain);
}

float O2Sensor::currentTension() {
  return (float) abs(readADC() * _gain);
}

float O2Sensor::currentFo2(float mv) {
  float fo2 = (abs(mv) / (_cal_adc * _gain)) * O2_DEFAULT;
  if (abs(mv) <= 0.1) fo2 = 0;
  if (fo2 > 99.9) fo2 = 99.9;
  return (fo2);
}
