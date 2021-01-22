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

Velocity::Velocity(){
    setInvalid();
}

Velocity::Velocity(bool isValid, float vx, float vy){
    _isValid = isValid;
    _vx = vx;
    _vy = vy;
}

void Velocity::setVelocity(bool isValid, float vx, float vy){
    _isValid = isValid;
    _vx = vx;
    _vy = vy;
}

void Velocity::setInvalid(){
    _isValid = false;
    _vx = 0.0;
    _vy = 0.0;
}

bool Velocity::isInvalid(){
    return _isValid;
}

float Velocity::vx() const {
    return(_vx);
}

float Velocity::vy() const {
    return(_vy);
}

float Velocity::abs() const {
    return sqrt(pow(_vx, 2) + pow(_vy, 2));
}

float Velocity::arg() const {
    return atan2(_vy, _vx);
}

