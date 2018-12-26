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

#include "Arduino.h"

#ifndef Alambic_LCD_DISPLAY_H
#define Alambic_LCD_DISPLAY_H
#define Alambic_LCD_DISPLAY_LIB_VERSION "0.0.1"

#ifndef ALAMBIC_STRING
#define ALAMBIC_STRING "Alambic v0.1"
#endif


/* Custom are fonts added to library "TFT_eSPI\Fonts\Custom" folder
 * a #include must also be added to the "User_Custom_Fonts.h" file
 * in the "TFT_eSPI\User_Setups" folder. See example entries.
 */
#define FF18    &FreeSans12pt7b 
#define CF_OL24 &Orbitron_Light_24
#define CF_OL32 &Orbitron_Light_32
#define CF_RT24 &Roboto_Thin_24
#define CF_S24  &Satisfy_24
#define CF_Y32  &Yellowtail_32

#define GFXFF 1

#ifndef DEFAULT_DELAY
#define DEFAULT_DELAY 1000
#endif

#ifndef DEFAULT_ITERATION
#define DEFAULT_ITERATION 1
#endif

#define TFT_GREY 0x5AEB // New colour

class AlambicLcdDisplay
{
public:
  const float fhe = 0.00;
  AlambicLcdDisplay(void);
  ~AlambicLcdDisplay();
  void version();
  void environment(float, float);
  void environment_error(void);
  void calibrateStart();
  void calibrateIterate(int);
  void calibrateEnd();
  void clear();
  void display_fo2(float);
  void display_mix(float);
  void display_mod(float);
  void display_mv(float);
  void display_cal(float);
  void display_trimix(float, float);
  void debug_float(float);
  void debug_int(int);
  void debug_int16_t(int16_t);
};

#endif
