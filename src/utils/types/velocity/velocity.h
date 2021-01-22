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

#ifndef VELOCITY_H
#define VELOCITY_H

#include <math.h>

class Velocity
{
public:
    Velocity();
    Velocity(bool isValid, float vx, float vy);

    // Setters
    void setVelocity(bool isValid, float vx, float vy);
    void setInvalid();

    // Getterrs
    bool isInvalid();
    float vx() const;
    float vy() const;
    float abs() const;
    float arg() const;

private:
    // Params
    bool _isValid;
    float _vx;
    float _vy;
};

#endif // VELOCITY_H
