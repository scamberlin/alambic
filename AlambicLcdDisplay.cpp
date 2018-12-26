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

/*
Tests string alignment

Normally strings are printed relative to the top left corner but this can be
changed with the setTextDatum() function. The library has #defines for:

TL_DATUM = Top left
TC_DATUM = Top centre
TR_DATUM = Top right
ML_DATUM = Middle left
MC_DATUM = Middle centre
MR_DATUM = Middle right
BL_DATUM = Bottom left
BC_DATUM = Bottom centre
BR_DATUM = Bottom right

 */

#include <stdlib.h>
#include <M5Stack.h>
//#include <SPI.h>

#include "AlambicLcdDisplay.h"
#include "MixedGaz.h"

AlambicLcdDisplay::AlambicLcdDisplay(void) {
  M5.begin();
  M5.Lcd.fillScreen(TFT_GREY);
  M5.Lcd.setTextPadding(40);
  M5.Lcd.setTextDatum(MC_DATUM);
  M5.Lcd.setTextColor(TFT_GREEN, TFT_GREY);
  M5.Lcd.setFreeFont(FF18);
}

AlambicLcdDisplay::~AlambicLcdDisplay() {}

void AlambicLcdDisplay::clear() {
  M5.Lcd.fillScreen(TFT_GREY);
}

void AlambicLcdDisplay::version() {
  M5.Lcd.setFreeFont(FF18);
  M5.Lcd.setTextPadding(40);
  M5.Lcd.setTextColor(TFT_RED, TFT_GREY);
  M5.Lcd.drawString(String(ALAMBIC_STRING), (int)(M5.Lcd.width()/2), 30, GFXFF);
  M5.Lcd.setTextPadding(0);
}

void AlambicLcdDisplay::environment(float alt, float temp) {
  String temp_s = String("temp: " + String(temp) + " cel");
  String alt_s = String("alt: " + String(alt) + " m");
}

void AlambicLcdDisplay::environment_error(void) {
  String temp_s = String("temp. :    error");
  String alt_s = String("alti. :    error");
}

void AlambicLcdDisplay::calibrateStart() {
  M5.Lcd.setFreeFont(FF18);
  M5.Lcd.setTextPadding(50);
  M5.Lcd.setTextColor(TFT_GREEN, TFT_GREY);
  M5.Lcd.drawString("calibrating...\n", 60, (int)(M5.Lcd.height()/2), GFXFF);
  delay(DEFAULT_DELAY / 3);
}

void AlambicLcdDisplay::calibrateIterate(int i) {
  char timer[16];
  sprintf(timer, "%.1ds remaining", i);
  M5.Lcd.setFreeFont(FF18);
  M5.Lcd.setTextColor(TFT_GREEN, TFT_GREY);
  M5.Lcd.drawString(timer, 60, (int)(M5.Lcd.height()/2), GFXFF);
  delay(DEFAULT_DELAY);
}

void AlambicLcdDisplay::calibrateEnd() {
  M5.Lcd.setFreeFont(FF18);
  M5.Lcd.setTextColor(TFT_GREEN, TFT_GREY);
  M5.Lcd.drawString("o2 sensor ok...\n", 60, (int)(M5.Lcd.height()/2), GFXFF);
  M5.Lcd.setTextPadding(0);
  delay(DEFAULT_DELAY / 3);
}

void AlambicLcdDisplay::display_mix(float fo2) {
  String mix = "unknown";
  M5.Lcd.setFreeFont(FF18);
  M5.Lcd.setTextColor(TFT_RED, TFT_GREY);
  if (fo2 >= 20.00 && fo2 < 21.90) {
    mix = String("air");
    M5.Lcd.setTextColor(TFT_GREEN, TFT_GREY);
  }
  if (fo2 <= 16.00 && fo2 > 1.00) {
    mix = String("hypoxic");
    M5.Lcd.setTextColor(TFT_RED, TFT_GREY);
  }
  if (fo2 > 21.90) {
    mix = String("nitrox");
    M5.Lcd.setTextColor(TFT_BLUE, TFT_GREY);
  }
  String mix_s = String("gaz: " + String(mix));
  M5.Lcd.setTextPadding(20);
  M5.Lcd.drawString(mix_s, 80, 20, GFXFF);
  M5.Lcd.setTextPadding(0);
}

void AlambicLcdDisplay::display_mod(float fo2) {
  float mod = MixedGaz().maximumOperatingDepth(fo2, MAX_PO2);
  String mod_s = String("mod: " + String(mod));
  M5.Lcd.setFreeFont(FF18);
  M5.Lcd.setTextColor(TFT_GREEN);
  M5.Lcd.setTextPadding(20);
  M5.Lcd.drawString(mod_s, 260, 20, GFXFF);
  M5.Lcd.setTextPadding(0);
}

void AlambicLcdDisplay::display_fo2(float fo2) {
  M5.Lcd.setTextColor(TFT_GREEN);
  M5.Lcd.setFreeFont(FF18);
  M5.Lcd.setTextPadding(40);
  String mod_s = String(String(fo2) + " / " + String(fhe));
  M5.Lcd.drawString(mod_s, 160, 120, GFXFF);
  M5.Lcd.setTextPadding(0);
}

void AlambicLcdDisplay::display_mv(float mv) {
  String mv_s = String("mv: " + String(mv));
  M5.Lcd.setFreeFont(FF18);
  M5.Lcd.setTextColor(TFT_GREEN);
  M5.Lcd.setTextPadding(20);
  M5.Lcd.drawString(mv_s, 50, 220, GFXFF);
  M5.Lcd.setTextPadding(0);
}

void AlambicLcdDisplay::display_cal(float cal_mv) {
  String cal_mv_s = String("cal: " + String(cal_mv));
  M5.Lcd.setFreeFont(FF18);
  M5.Lcd.setTextColor(TFT_GREEN);
  M5.Lcd.setTextPadding(20);
  M5.Lcd.drawString(cal_mv_s, 260, 220, GFXFF);
  M5.Lcd.setTextPadding(0);
}

void AlambicLcdDisplay::display_trimix(float fo2, float fhe) {
  static char outstr[15];
  float mod = MixedGaz().maximumOperatingDepth(fo2, MAX_PO2);
  float end = MixedGaz().equivalentNarcoticDepth(mod, fhe);
  M5.Lcd.clear(BLACK);
  delay(DEFAULT_DELAY);
}

void AlambicLcdDisplay::debug_int(int value) {
  M5.Lcd.clear(BLACK);
  delay(DEFAULT_DELAY);
}

void AlambicLcdDisplay::debug_int16_t(int16_t value) {
  M5.Lcd.clear(BLACK);
  delay(DEFAULT_DELAY);
}

void AlambicLcdDisplay::debug_float(float value) {
  M5.Lcd.clear(BLACK);
  delay(DEFAULT_DELAY);
}
