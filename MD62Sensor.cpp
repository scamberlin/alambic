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

#include "MD62Sensor.h"
#include "RunningAverage.h"

Adafruit_ADS1115 _ads_md62(ADS_ADDRESS); // construct an ads1115 at address 0x48

RunningAverage _adc_md62(RA_SIZE);


MD62Sensor::MD62Sensor(void)
{
  /*
   * init ads1115: 16x gain (1 bit = 0.0078125mV)
   */
  time = millis();
  _ads_md62.setGain(GAIN_FOUR);
  _ads_md62.begin();
  EEPROM.get(p_address, _cal_adc);
  Serial.println("MD62Sensor.MD62Sensor._cal_adc : " + String(_cal_adc));
  if (_cal_adc < 100) {
    _cal_adc = calibrate();
  }
}

MD62Sensor::~MD62Sensor() {}

boolean MD62Sensor::error() { return _error; }
String MD62Sensor::errorStr() { return _errorStr; }

/*
 *  read he sensor
 */
int16_t MD62Sensor::readADC() {
  int md62s = abs(_ads_md62.readADC_Differential_2_3());
  Serial.println("MD62Sensor.readADC.md62s : " + String(md62s));
  return md62s;
}

/*
 *  calibrate he sensor
 */
int MD62Sensor::calibrate() {
  int md62s = readADC();
  float mv = md62s * _gain;
  while(mv > 30) {
    md62s = readADC();
    Serial.println("MD62Sensor.calibrate.md62s : " + String(md62s));
    _adc_md62.addValue(md62s);
    mv = md62s * _gain;
    Serial.println("MD62Sensor.calibrate.mv : " + String(mv));
    delay(50);
  }
  int p_value = _adc_md62.getAverage();
  Serial.println("MD62Sensor.calibrate.p_value : " + String(p_value));
  EEPROM.put(p_address, p_value);
  return p_value;
}

float MD62Sensor::calMv() { 
  Serial.println("MD62Sensor.calMv.cal_mv : " + String(_cal_adc * _gain));
  return (_cal_adc * _gain); 
}

float MD62Sensor::avgTension() {
  readADC();
  Serial.println("MD62Sensor.avgTension.avg_mv : " + String(_adc_md62.getAverage() * _gain));
  return (float) (_adc_md62.getAverage() * _gain);
}

float MD62Sensor::currentTension() {
  Serial.println("MD62Sensor.currentTension.cur_mv : " + String(readADC() * _gain));
  return (float) (readADC() * _gain);
}

float MD62Sensor::currentFhe(float mv) {
  int corr;
  float fhe = 0.00;
  mv = mv - _cal_wheatstone;
  if (time < 480000) {  corr = 1  ; }
  if (time < 360000) {  corr = 2  ; }
  if (time < 300000) {  corr = 3  ; }
  if (time < 270000) {  corr = 4  ; }
  if (time < 240000) {  corr = 5  ; }
  if (time < 210000) {  corr = 6  ; }
  if (time < 180000) {  corr = 7  ; }
  if (time < 165000) {  corr = 8  ; }
  if (time < 150000) {  corr = 9  ; }
  if (time < 120000) {  corr = 10 ; }
  if (time < 105000) {  corr = 11 ; }
  if (time < 90000)  {  corr = 12 ; }
  if (time < 80000)  {  corr = 13 ; }
  if (time < 70000)  {  corr = 14 ; }
  if (time < 60000)  {  corr = 15 ; }
  if (time < 50000)  {  corr = 16 ; }
  if (time < 40000)  {  corr = 17 ; }
  if (time < 30000)  {  corr = 18 ; }
  mv = mv - corr;
  fhe = 100 * mv / _result_max;
  if (fhe > 50) {
    fhe = fhe * (1 + (fhe - 50) * 0.4 / 100);
  }
  if (fhe < 0.99)
    fhe = 0.00;
  Serial.println("MD62Sensor.currentFhe.fhe : " + String(fhe));
  return (fhe);
}
