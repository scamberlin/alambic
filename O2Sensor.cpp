/*****************************************************************************
  Author
  ------
    Stephane Camberlin <stephane.camberlin@gmail.com> (c) 2018
    Freely inspired from ej's o2 oled analyzer - v0.21
    http://ejlabs.net/arduino-oled-nitrox-analyzer
    
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

O2Sensor::O2Sensor(void)
{
  /*
   * init ads1115: 16x gain (1 bit = 0.0078125mV)
   */
  _ads.setGain(GAIN_SIXTEEN);
  _ads.begin();
  EEPROM.get(p_address, _cal_adc);
  //Serial.println("o2_cal_val : " + String(_cal_adc));
  Serial.println("O2Sensor.O2Sensor._cal_adc : " + String(_cal_adc));
  if (_cal_adc < 100) {
    _cal_adc = calibrate();
  }
}

O2Sensor::~O2Sensor() {}

boolean O2Sensor::error() { return _error; }
String O2Sensor::errorStr() { return _errorStr; }


/*
 *  read o2 sensor and add value in RunningAverage o2
 */
int16_t O2Sensor::readADC() {
  int16_t o2s = abs(_ads.readADC_Differential_0_1());
  Serial.println("O2Sensor.readADC.o2s : " + String(o2s));
  return o2s;
}

/*
 *  calibrate O2 sensor
 */
int O2Sensor::calibrate() {
  for (int cx = 1; cx <= RA_SIZE; cx++) {
    _adc.addValue(readADC());
    delay(200);
  }
  int p_value = _adc.getAverage();
  Serial.println("O2Sensor.calibrate.p_value : " + String(p_value));
  EEPROM.put(p_address, p_value);
  return p_value;
}

float O2Sensor::calMv() { 
  Serial.println("O2Sensor.calMv.cal_mv : " + String(_cal_adc * _gain));
  return (_cal_adc * _gain); 
}

float O2Sensor::avgTension() {
  readADC();
  Serial.println("O2Sensor.avgTension.avg_mv : " + String(_adc.getAverage() * _gain));
  return (float) (_adc.getAverage() * _gain);
}

float O2Sensor::currentTension() {
  Serial.println("O2Sensor.currentTension.cur_mv : " + String(readADC() * _gain));
  return (float) (readADC() * _gain);
}

float O2Sensor::currentFo2(float mv) {
  float fo2 = (mv / (_cal_adc * _gain)) * O2_DEFAULT;
  if (mv <= 0.1) fo2 = 0;
  if (fo2 > 99.9) fo2 = 99.9;
  Serial.println("O2Sensor.currentFo2.fo2 : " + String(fo2));
  return (fo2);
}
