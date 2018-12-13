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

#include "MixedGaz.h"
#include "O2Sensor.h"
#include "EnvSensor.h"
#include "AlambicLcdDisplay.h"

#define _DEBUG_SERIAL 9600

AlambicLcdDisplay lcd = AlambicLcdDisplay();

void setup() {
  String Alambic_s = String(ALAMBIC_STRING);
  Serial.begin(_DEBUG_SERIAL);
  while (!Serial); // wait for serial monitor on leonardo
  lcd.version();
  EnvSensor es = EnvSensor();
  if (es.error()) {
    lcd.environment_error();
  } else 
    lcd.environment(es.alt(), es.temp());
  lcd.calibrateStart();
  O2Sensor o2s = O2Sensor();
  for (int i=DEFAULT_ITERATION ; i>0; i--) {
    o2s.calibrate(); 
    lcd.calibrateIterate(i);
  }
  lcd.calibrateEnd();
}

void loop() {
  O2Sensor o2s = O2Sensor();    
  lcd.display_nitrox(o2s.currentFo2(o2s.avgTension()));
  lcd.display_mv(o2s.avgTension(), o2s.calMv());
  delay(DEFAULT_DELAY / 100);
}
