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

#include "EnvSensor.h"

#include <stdlib.h>
#include <Adafruit_BMP085.h>


/* ==== Branchements du module BMP085 avec 4 fils :
 * GND sur la masse de l'Arduino
 * +3.3 sur le +3.3 de l'Arduino
 * SDA (=data) vers AnalogPin4
 * SCL (=clock) vers AnalogPin5
 *
 * Pas besoin de brancher CLR (reset) ni OEC (end of conversion)
 * Mais EOC peut servir si on cherche à accélérer son code Arduino 
 */
#ifndef DEFAULT_HPA
#define DEFAULT_HPA 101325
#endif

Adafruit_BMP085 _bmp;

EnvSensor::EnvSensor(void)
{
  if (!_bmp.begin()) {
    _errorStr = String("no BMP085 found");
    _error = true;
  }
  _alt = _bmp.readAltitude(DEFAULT_HPA);
  _temp = _bmp.readTemperature();
}

EnvSensor::~EnvSensor() {}
float EnvSensor::alt() { return _alt; }
float EnvSensor::temp() { return _temp; }
boolean EnvSensor::error() { return _error; }
String EnvSensor::errorStr() { return _errorStr; }
