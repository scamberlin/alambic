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

#include "Arduino.h"

#ifndef I2CBUS_h
#define I2CBUS_h
#define I2CBUS_LIB_VERSION "0.0.1"

/* Adafruit_ADS1115 ads(0x48);
 * 0x48 (1001000) ADR -> GND
 * 0x49 (1001001) ADR -> VDD
 * 0x4A (1001010) ADR -> SDA
 * 0x4B (1001011) ADR -> SCL
 */
#ifndef ADS_ADDRESS 
#define ADS_ADDRESS 0x48
#endif


class I2CBus
{
  
public:

  I2CBus(void);
  ~I2CBus();

  int scan_i2c_bus();
  boolean error();
  String errorStr();

protected:

  boolean _error = false;
  String _errorStr;
  
  int _nDevices;
  
  private:
    int p_address = 0;
};

#endif
