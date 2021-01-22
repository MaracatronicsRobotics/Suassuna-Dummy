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

Position::Position(){
    setInvalid();
}

Position::Position(bool isValid, float x, float y){
    _isValid = isValid;
    _x = x;
    _y = y;
}

void Position::setPosition(bool isValid, float x, float y){
    _isValid = isValid;
    _x = x;
    _y = y;
}

void Position::setInvalid(){
    _isValid = false;
    _x = 0.0;
    _y = 0.0;
}

bool Position::isInvalid() const{
    return !_isValid;
}

float Position::x() const {
    return(_x);
}

float Position::y() const {
    return(_y);
}
