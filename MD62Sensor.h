/*****************************************************************************
  Author
  ------
    Stephane Camberlin <stephane.camberlin@gmail.com> - 2018 (c)
    Freely inspired from 
    
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

#ifndef MD62SENSOR_h
#define MD62SENSOR_h
#define MD62SENSOR_LIB_VERSION "0.0.1"

#ifndef HE_DEFAULT
#define HE_DEFAULT 0.00
#endif

#ifndef MD62_MAX_MV
#define MD62_MAX_MV 661.26
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
#define GAIN 0.03125
#endif

#ifndef RA_SIZE 
#define RA_SIZE 20
#endif

class MD62Sensor
{
  
public:

  MD62Sensor(void);
  ~MD62Sensor();

  int16_t readADC();
  int calibrate();
  float currentTension();
  float avgTension();
  float calMv();
  float currentFhe(float);

  boolean error();
  String errorStr();

protected:

  boolean _error = false;
  String _errorStr;
  
  int _cal_adc;
  float _gain = GAIN;
  float _result_max = MD62_MAX_MV;
  float _cal_wheatstone = 10;
  
  private:
    int p_address = 2;
    unsigned long time;

};

#endif
