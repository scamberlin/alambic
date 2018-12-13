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
#include <math.h>

#include "MixedGaz.h"

MixedGaz::MixedGaz(void)
{
  _fo2 = 0.00; 
  _fhe = 0.00;
}

MixedGaz::MixedGaz(float fo2)
{
  _fo2 = fo2;
  _fhe = 0.00;
}

MixedGaz::MixedGaz(float fo2, float fhe)
{
  _fo2 = fo2; 
  _fhe = fhe;
}

MixedGaz::~MixedGaz() {}

float MixedGaz::fo2() { return _fo2; }
void MixedGaz::fo2(float fo2) { _fo2 = fo2; }
  
float MixedGaz::fn2() { return _fn2; }
void MixedGaz::fn2(float fn2) { _fn2 = fn2; }

float MixedGaz::fhe() { return _fhe; }
void MixedGaz::fhe(float fhe) { _fhe = fhe; }

/*
 *  return maximum operating depth in meter
 */
float MixedGaz::maximumOperatingDepth () {
  return 10 * ( (MAX_PO2 / (_fo2 / 100)) - 1 );
}

float MixedGaz::maximumOperatingDepth (const float fo2) {
  return 10 * ( (MAX_PO2 / (fo2 / 100)) - 1 );
}

float MixedGaz::maximumOperatingDepth (const float fo2, const float max_po2) {
  return 10 * ( (max_po2 / (fo2 / 100)) - 1 );
}

/*
 *   return air equivalent narcotic depth
 */
float MixedGaz::equivalentNarcoticDepth (const float depth) {
  return ((depth + 10) * (1 - _fhe / 100)) - 10;
}

float MixedGaz::equivalentNarcoticDepth (const float depth, const float fhe) {
  return ((depth + 10) * (1 - fhe / 100)) - 10;
}
