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

#ifndef ANGULARSPEED_H
#define ANGULARSPEED_H

#include <src/utils/types/typesNamespace.h>

class soccertypes::AngularSpeed{
public:
    AngularSpeed();
    AngularSpeed(bool known, float value);

private:
    // Angle value
    float _value;

    // Info flags
    bool _unknown;
    bool _valid;

public:
    AngularSpeed& operator =(const AngularSpeed& other);
    AngularSpeed& operator =(const float value);

    void setValue(float value);
    float value() const;
    bool isUnknown() const;
    bool isValid() const;
    void setUnknown();
    void setInvalid();
};

#endif // ANGULARSPEED_H
