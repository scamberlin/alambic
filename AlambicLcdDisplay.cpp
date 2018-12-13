/*****************************************************************************
  Author
  ------
    Stephane Camberlin <stephane.camberlin@gmail.com> - 2018 (c)
    
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
#include <LiquidCrystal.h>
#include <SPI.h>

#include "AlambicLcdDisplay.h"
#include "MixedGaz.h"

/* initialize the LC library
 * with the LCD display
 * const int rs = 8,  en = 9,  d4 = 4, d5 = 5, d6 = 6, d7 = 7;
 */
int rs = 8,  en = 9,  d4 = 4, d5 = 5, d6 = 6, d7 = 7;
LiquidCrystal lc(rs, en, d4, d5, d6, d7);

AlambicLcdDisplay::AlambicLcdDisplay(void) {
  lc.begin(NUM_ROWS, NUM_COLS);
}

AlambicLcdDisplay::~AlambicLcdDisplay() {}

void AlambicLcdDisplay::version() {  
  lc.begin(NUM_ROWS, NUM_COLS);
  lc.clear();
  lc.setCursor(0, 0);
  lc.print(ALAMBIC_STRING);
  lc.setCursor(0, 1);
  lc.print("initializing...");
  delay(DEFAULT_DELAY * 2);
}

void AlambicLcdDisplay::environment(float alt,float temp) {
  String temp_s = String("temp: " + String(temp) + " cel");
  String alt_s = String("alt: " + String(alt) + " m");
  lc.begin(NUM_ROWS, NUM_COLS);
  lc.clear();
  lc.setCursor(0, 0);
  lc.print(temp_s);
  lc.setCursor(0, 1);
  lc.print(alt_s);
  delay(DEFAULT_DELAY * 2);
}

void AlambicLcdDisplay::environment_error(void) {
  String temp_s = String("temp. :    error");
  String alt_s = String("alti. :    error");
  lc.begin(NUM_ROWS, NUM_COLS);
  lc.clear();
  lc.setCursor(0, 0);
  lc.print(temp_s);
  lc.setCursor(0, 1);
  lc.print(alt_s);
  delay(DEFAULT_DELAY * 2);
}

void AlambicLcdDisplay::calibrateStart() {
  lc.begin(NUM_ROWS, NUM_COLS);
  lc.clear();
  lc.setCursor(0, 0);
  lc.print("calibrating...");
}

void AlambicLcdDisplay::calibrateIterate(int i) {
  char timer[16];
  sprintf(timer,"%0.1ds remaining", i);
  lc.setCursor(0, 1);
  lc.print(timer); 
  delay(DEFAULT_DELAY);
}

void AlambicLcdDisplay::calibrateEnd() {
  lc.setCursor(0, 1);
  lc.print("                ");
  lc.setCursor(0, 1);
  lc.print("o2 sensor ok...");
  delay(DEFAULT_DELAY);
  lc.clear();
}

void AlambicLcdDisplay::display_nitrox(float fo2) {
  static char outstr[15];
  float mod = MixedGaz().maximumOperatingDepth(fo2, MAX_PO2);
  lc.setCursor(0, 0);
  lc.print("O2 ");
  lc.setCursor(2, 0);
  dtostrf(fo2, 5, 1, outstr);
  lc.print(outstr);
  lc.setCursor(8, 0);
  lc.print("MOD ");
  lc.setCursor(11, 0);
  dtostrf(mod, 5, 1, outstr);
  lc.print(outstr);
}

void AlambicLcdDisplay::display_mv(float mv, float cal_mv) {
  static char outstr[15];
  lc.setCursor(0, 1);
  lc.print("MV ");
  lc.setCursor(2, 1);
  dtostrf(mv, 5, 2, outstr);
  lc.print(outstr); 
  lc.setCursor(8, 1);
  lc.print("CAL ");
  lc.setCursor(11, 1);
  dtostrf(cal_mv, 5, 2, outstr);
  lc.print(outstr);
}

void AlambicLcdDisplay::display_trimix(float fo2, float fhe) {
  static char outstr[15];
  float mod = MixedGaz().maximumOperatingDepth(fo2, MAX_PO2);
  float end = MixedGaz().equivalentNarcoticDepth(mod, fhe);
  lc.setCursor(0, 0);
  lc.print("O2 ");
  lc.setCursor(2, 0);
  dtostrf(fo2, 5, 1, outstr);
  lc.print(outstr);
  lc.setCursor(8, 0);
  lc.print("MOD ");
  lc.setCursor(11, 0);
  dtostrf(mod, 5, 1, outstr);
  lc.print(outstr); 
  lc.setCursor(0, 1);
  lc.print("HE ");
  lc.setCursor(2, 1);
  dtostrf(fhe, 5, 1, outstr);
  lc.print(outstr); 
  lc.setCursor(8, 1);
  lc.print("END ");
  lc.setCursor(11, 1);
  dtostrf(end, 5, 1, outstr);
  lc.print(outstr);
  delay(DEFAULT_DELAY);
}

void AlambicLcdDisplay::debug_int(int value) {
  lc.begin(NUM_ROWS, NUM_COLS);
  lc.clear();
  lc.setCursor(0, 0);
  lc.print("value: ");
  lc.setCursor(8, 0);
  lc.print(value);
  delay(DEFAULT_DELAY);
}

void AlambicLcdDisplay::debug_int16_t(int16_t value) {
  lc.begin(NUM_ROWS, NUM_COLS);
  lc.clear();
  lc.setCursor(0, 0);
  lc.print("value: ");
  lc.setCursor(8, 0);
  lc.print(value);
  delay(DEFAULT_DELAY);
}

void AlambicLcdDisplay::debug_float(float value) {
  lc.begin(NUM_ROWS, NUM_COLS);
  lc.clear();
  lc.setCursor(0, 0);
  lc.print("value: ");
  lc.setCursor(8, 0);
  lc.print(value);
  delay(DEFAULT_DELAY);
}
