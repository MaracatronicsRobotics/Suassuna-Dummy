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

#include "angularspeed.h"

AngularSpeed::AngularSpeed() {
    setInvalid();
}

AngularSpeed::AngularSpeed(bool known, float theValue) {
    (known == true) ? setValue(theValue) : setUnknown();
}

AngularSpeed& AngularSpeed::operator =(const AngularSpeed& other) {
    // Valid speed
    if (other.isValid()) {
        // Unknown speed
        if (other.isUnknown()) {
            setUnknown();
        }
        // Known speed
        else {
            setValue(other.value());
        }
    }
    // Invalid speed
    else {
        setInvalid();
    }

    // Returns this speed
    return(*this);
}

AngularSpeed& AngularSpeed::operator =(const float theValue) {
    // Sets the speed value
    setValue(theValue);

    // Returns this speed
    return(*this);
}


// Set/get functions
float AngularSpeed::value() const {
    return(_value);
}

void  AngularSpeed::setValue(float theValue) {
    // Sets the speed
    _value = theValue;

    // Sets as a valid known speed
    _valid   = true;
    _unknown = false;
}

// Info functions
bool AngularSpeed::isUnknown() const {
    return(_unknown);
}

bool AngularSpeed::isValid() const {
    return(_valid);
}

void AngularSpeed::setInvalid() {
    _valid = false;
}

void AngularSpeed::setUnknown() {
    _unknown = true;
    _valid   = true;
}
