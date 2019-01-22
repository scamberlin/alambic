/*****************************************************************************
  Author
  ------
    Stephane Camberlin <stephane.camberlin@gmail.com> - 2018 
    
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

#include <Wire.h>
#include <M5ez.h>
#include <ezTime.h>

#include "MixedGaz.h"
#include "O2Sensor.h"
#include "MD62Sensor.h"
#include "EnvSensor.h"
#include "AlambicLcdDisplay.h"

#define _DEBUG_SERIAL 9600
#define MAIN_DECLARED

AlambicLcdDisplay lcd = AlambicLcdDisplay();


void setup() {
  String Alambic_s = String(ALAMBIC_STRING);
  Serial.begin(_DEBUG_SERIAL);
  while (!Serial); // wait for serial 
  lcd.version();
  // EnvSensor es = EnvSensor();
  // if (es.error()) {
  //  lcd.environment_error();
  // } else 
  //  lcd.environment(es.alt(), es.temp());
  lcd.calibrateStart();
  O2Sensor o2s = O2Sensor();
  MD62Sensor md62s = MD62Sensor();
  for (int i=DEFAULT_ITERATION ; i>0; i--) {
    o2s.calibrate(); 
    md62s.calibrate();
    lcd.calibrateIterate(i);
  }
  lcd.calibrateEnd();
  lcd.clear(); 
}

void loop() {
  O2Sensor o2s = O2Sensor();
  MD62Sensor md62s = MD62Sensor();
  lcd.clear();
  float fo2 = (float) o2s.currentFo2(o2s.currentTension());
  float fhe = (float) md62s.currentFhe(md62s.currentTension());
  lcd.display_trimix(fo2, fhe);
  lcd.display_mix(fo2);
  lcd.display_mod(fo2);
  lcd.display_mv(o2s.currentTension());
  lcd.display_cal(o2s.calMv());
  delay(DEFAULT_DELAY);
}
