/***
 * Maracatronics Robotics
 * Federal University of Pernambuco (UFPE) at Recife
 * http://www.maracatronics.com/
 *
 * This file is part of Armorial project.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 ***/

#include "angle.h"
#include <cmath>

using namespace soccertypes;

Angle::Angle() {
    setInvalid();
}

Angle::Angle(bool known, float theValue) {
    (known == true) ? setValue(theValue) : setUnknown();
}

float Angle::toRadians(float angle) {
    // Returns the converted value
    return(angle*toRad);
}

float Angle::toDegrees(const Angle& angle) {
    // Returns the converted value
    return(angle.value()*toDeg);
}

float Angle::toDegrees(float angle) {
    // Returns the converted value
    return(angle*toDeg);
}

float Angle::difference(const Angle& a, const Angle& b) {
    // Calculates the difference
    float difference = a.value()-b.value();

    // Verifies if the difference is the absolute smallest
    if (difference > Angle::pi) {
        difference -= Angle::twoPi;
    }
    else if (difference < -Angle::pi) {
        difference += Angle::twoPi;
    }

    // Returns the difference
    return(difference);
}

Angle& Angle::operator =(const Angle& other) {
    // Valid angle
    if (other.isValid()) {
        // Unknown angle
        if (other.isUnknown()) {
            setUnknown();
        }
        // Known angle
        else {
            setValue(other.value());
        }
    }
    // Invalid angle
    else {
        setInvalid();
    }

    // Returns this angle
    return(*this);
}

Angle& Angle::operator =(const float theValue) {
    // Sets the angle value
    setValue(theValue);

    // Returns this angle
    return(*this);
}

// Set/get functions
float Angle::value() const {
    return(_value);
}

void  Angle::setValue(float theValue) {
    // Sets the angle in the range 0 <= angle < 2*Pi
    _value = fmod(theValue, Angle::twoPi);
    if (_value < 0.0f) {
        _value += Angle::twoPi;
    }

    // Sets as a valid known angle
    _valid   = true;
    _unknown = false;
}

// Info functions
bool Angle::isUnknown() const {
    return(_unknown);
}

bool Angle::isValid() const {
    return(_valid);
}

void Angle::setInvalid() {
    _valid = false;
}

void Angle::setUnknown() {
    _unknown = true;
    _valid   = true;
}

