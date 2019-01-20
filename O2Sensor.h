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

#include "Arduino.h"

#ifndef O2SENSOR_h
#define O2SENSOR_h
#define O2SENSOR_LIB_VERSION "0.0.1"

#ifndef MIN_O2_SENSOR_MV 
#define MIN_O2_SENSOR_MV 0.9
#endif

#ifndef MAX_O2_SENSOR_MV 
#define MAX_O2_SENSOR_MV 13.0
#endif

#ifndef O2_DEFAULT
#define O2_DEFAULT 20.95
#endif

/* Adafruit_ADS1115 ads(0x48);
 * 0x48 (1001000) ADR -> GND
 * 0x49 (1001001) ADR -> VDD
 * 0x4A (1001010) ADR -> SDA
 * 0x4B (1001011) ADR -> SCL
 */
#ifndef ADS_ADDRESS 
#define ADS_ADDRESS 0x48
#endif

/*                                                            
 *                                                                ADS1015  ADS1115
 *                                                                -------  -------
 * ads.setGain(GAIN_TWOTHIRDS);  // 2/3x gain +/- 6.144V  1 bit = 3mV      0.1875mV (default)
 * ads.setGain(GAIN_ONE);        // 1x gain   +/- 4.096V  1 bit = 2mV      0.125mV
 * ads.setGain(GAIN_TWO);        // 2x gain   +/- 2.048V  1 bit = 1mV      0.0625mV
 * ads.setGain(GAIN_FOUR);       // 4x gain   +/- 1.024V  1 bit = 0.5mV    0.03125mV
 * ads.setGain(GAIN_EIGHT);      // 8x gain   +/- 0.512V  1 bit = 0.25mV   0.015625mV
 * ads.setGain(GAIN_SIXTEEN);    // 16x gain  +/- 0.256V  1 bit = 0.125mV  0.0078125mV
 * Be sure to update this value based on the IC and the gain settings! 
 * float   multiplier = 3.0F;   // ADS1015 @ +/- 6.144V gain (12-bit results) 
 * float multiplier = 0.1875F; // ADS1115  @ +/- 6.144V gain (16-bit results) 
 */
#ifndef GAIN 
#define GAIN 0.0078125
#endif

class O2Sensor
{
  
public:

  O2Sensor(void);
  ~O2Sensor();

  int16_t readADC();
  int calibrate();
  float currentTension();
  float avgTension();
  float calMv();
  float currentFo2(float);

  boolean error();
  String errorStr();

protected:

  boolean _error = false;
  String _errorStr;
  
  float _min_mv = MIN_O2_SENSOR_MV;
  float _max_mv = MAX_O2_SENSOR_MV;
  float _gain = GAIN;
  int p_address = 0;
  int _cal_adc;    

};

#endif
