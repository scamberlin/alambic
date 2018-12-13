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

#ifndef NUM_ROWS
#define NUM_ROWS 2
#endif

#ifndef NUM_COLS
#define NUM_COLS 16
#endif

#ifndef DEFAULT_DELAY
#define DEFAULT_DELAY 1000
#endif

#ifndef DEFAULT_ITERATION
#define DEFAULT_ITERATION 1
#endif

class AlambicLcdDisplay
{
public:
  AlambicLcdDisplay(void);
  ~AlambicLcdDisplay();
  void version();
  void environment(float, float);
  void environment_error(void);
  void calibrateStart();
  void calibrateIterate(int);
  void calibrateEnd();
  void display_nitrox(float);
  void display_mv(float, float);
  void display_trimix(float, float);
  void debug_float(float);
  void debug_int(int);
  void debug_int16_t(int);
};

#endif
