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

#include "position.h"

using namespace soccertypes;

Position::Position() {
    setInvalid();
}

Position::Position(bool known, float newX, float newY, float newZ) {
    (known == true) ? setPosition(newX, newY, newZ) : setUnknown();
}

Position& Position::operator =(const Position& other) {
    // Valid position
    if (other.isValid()) {
        // Unknown position
        if (other.isUnknown()) {
            setUnknown();
        }
        // Known position
        else {
            setPosition(other.x(), other.y(), other.z());
        }
    }
    // Invalid position
    else {
        setInvalid();
    }

    // Returns this position
    return(*this);
}

// Set/get functions
float Position::x() const {
    return(_x);
}

float Position::y() const {
    return(_y);
}

float Position::z() const {
    return(_z);
}

void  Position::setPosition(float newX, float newY, float newZ) {
    // Sets the coordinates
    _x = newX;
    _y = newY;
    _z = newZ;

    // Sets as a valid known position
    _valid   = true;
    _unknown = false;
}

// Info functions
bool Position::isUnknown() const {
    return(_unknown);
}

bool Position::isValid() const {
    return(_valid);
}

void Position::setInvalid() {
    _valid = false;
}

void Position::setUnknown() {
    _unknown = true;
    _valid   = true;
}
