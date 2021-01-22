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

#ifndef ANGLE_H
#define ANGLE_H

class Angle
{
public:
    // Pi constants
    static constexpr float pi    = 3.14159265358979323846;
    static constexpr float twoPi = 6.28318530717958647692;

private:
    // Conversion constants
    static constexpr float toRad =  0.01745329251994329577;
    static constexpr float toDeg = 57.29577951308232087680;

// Params
private:
    // Angle value
    float _value;

    // Info flags
    bool _unknown;
    bool _valid;

// Conversions
public:
    static float toRadians(float angle);
    static float toDegrees(const Angle& angle);
    static float toDegrees(float angle);
    static float difference(const Angle& a, const Angle& b);

// Constructors
public:
    Angle();
    Angle(bool known, float value);

// Setters
public:
    void setValue(float value);
    float value() const;

public:
    bool isValid() const;
    void setInvalid();
};

#endif // ANGLE_H
