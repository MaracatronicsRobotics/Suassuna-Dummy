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

#include <src/utils/types/typesNamespace.h>

class soccertypes::Angle {
    public:
        // Constructors
        Angle();
        Angle(bool known, float value);

        // Pi constants
        static constexpr float pi    = 3.14159265358979323846f;
        static constexpr float twoPi = 6.28318530717958647692f;

    private:
        // Conversion constants
        static constexpr float toRad =  0.01745329251994329577f;
        static constexpr float toDeg = 57.29577951308232087680f;

        // Angle value
        float _value;

        // Info flags
        bool _unknown;
        bool _valid;

    public:
        static float toRadians(float angle);
        static float toDegrees(const Angle& angle);
        static float toDegrees(float angle);
        static float difference(const Angle& a, const Angle& b); // Returns a positive or negative difference

        Angle& operator =(const Angle& other);
        Angle& operator =(const float value);

        void setValue(float value);
        float value() const;
        bool isUnknown() const;
        bool isValid() const;
        void setUnknown();
        void setInvalid();
};

#endif // ANGLE_H
