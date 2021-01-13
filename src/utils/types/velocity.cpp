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

#include "velocity.h"
#include <cmath>

using namespace soccertypes;

Velocity::Velocity() {
    setInvalid();
}

Velocity::Velocity(bool known, float newX, float newY) {
    if(known == true){
        setVelocity(newX, newY);
    }else{
        setUnknown();
    }
}

Velocity::Velocity(bool known, float newAbs, const Angle& newArg) {
    if(known == true){
        setVelocity(newAbs, newArg);
    }else{
        setUnknown();
    }
}

Velocity& Velocity::operator =(const Velocity& other) {
    // Valid velocity
    if (other.isValid()) {
        // Unknown velocity
        if (other.isUnknown()) {
            setUnknown();
        }
        // Known velocity
        else {
            setVelocity(other.x(), other.y());
        }
    }
    // Invalid velocity
    else {
        setInvalid();
    }

    // Returns this velocity
    return(*this);
}


// Set/get functions
float Velocity::x() const {
    return(_x);
}

float Velocity::y() const {
    return(_y);
}

float Velocity::abs() const {
    return(_abs);
}

const Angle& Velocity::arg() const {
    return(_arg);
}

void Velocity::setVelocity(float newX, float newY) {
    // Sets the components
    _x = newX;
    _y = newY;

    // Calculates abs and arg
    setPolarComponents();

    // Sets as a valid known velocity
    _valid   = true;
    _unknown = false;
}

void Velocity::setVelocity(float newAbs, const Angle& newArg) {
    // Sets the values
    _abs = newAbs;
    _arg = newArg;

    // Calculates x and y
    setCartesianComponents();

    // Sets as a valid known velocity
    _valid   = true;
    _unknown = false;
}

bool Velocity::isUnknown() const {
    return(_unknown);
}

bool Velocity::isValid() const {
    return(_valid);
}

void Velocity::setInvalid() {
    _valid = false;
}

void Velocity::setUnknown() {
    _unknown = true;
    _valid   = true;
}

void Velocity::setCartesianComponents() {
    // Sets the components
    _x = _abs*cos(_arg.value());
    _y = _abs*sin(_arg.value());
}

void Velocity::setPolarComponents() {
    // Sets the components
    _abs = sqrt(pow(_x, 2) + pow(_y, 2));
    _arg = atan2(_y, _x);
}
