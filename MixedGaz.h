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

#ifndef MIXEDGAZ_H
#define MIXEDGAZ_H
#define MIXEDGAZ_LIB_VERSION "0.0.1"

#ifndef MAX_PO2
#define MAX_PO2 1.4
#endif

class MixedGaz
{
  
public:

  MixedGaz(void);
  MixedGaz(float);
  MixedGaz(float, float);
  
  ~MixedGaz();

  float fo2();
  void fo2(float);
  
  float fn2();
  void fn2(float);

  float fhe();
  void fhe(float);

  // return maximum operating depth in meter
  float maximumOperatingDepth ();
  float maximumOperatingDepth (const float);
  float maximumOperatingDepth (const float, const float);

  // return air equivalent narcotic depth in meter
  float equivalentNarcoticDepth (const float);
  float equivalentNarcoticDepth (const float, const float);
  
protected:

  float _fo2;
  float _fhe;
  float _fn2;
  
};

#endif
