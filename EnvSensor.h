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

#ifndef ENVSENSOR_h
#define ENVSENSOR_h
#define ENVSENSOR_LIB_VERSION "0.0.1"

class EnvSensor
{  
public:
  EnvSensor(void);
  ~EnvSensor();
  float alt();
  void alt(float);
  float temp();
  void temp(float);
  boolean error();
  String errorStr();

protected:
  boolean _error = false;
  String _errorStr;
  float _alt = 0.0;
  float _temp = 0.0;
  float _po2[10][3] = {
    {0,    0.21, 0.99},
    {327,  0.20, 0.96},
    {818,  0.19, 0.90},
    {1272, 0.18, 0.86},
    {1727, 0.17, 0.81},
    {2181, 0.16, 0.76},
    {2727, 0.15, 0.71},
    {3242, 0.14, 0.67},
    {3848, 0.13, 0.62},
    {4454, 0.12, 0.57}
  };
};

#endif
