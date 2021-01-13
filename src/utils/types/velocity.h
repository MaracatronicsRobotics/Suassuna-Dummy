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

#include <src/utils/types/angle.h>
#include <src/utils/types/typesNamespace.h>

using namespace soccertypes;

class soccertypes::Velocity{
    public:
        Velocity();
        Velocity(bool known, float x, float y);
        Velocity(bool known, float abs, const Angle& arg);

    private:
        // Velocity components
        float _x;
        float _y;
        float _abs;
        Angle _arg;

        // Info flags
        bool _unknown;
        bool _valid;

    public:
        Velocity& operator =(const Velocity& other);
        const Angle& arg() const;

        void setVelocity(float x, float y);
        void setVelocity(float abs, const Angle& arg);
        float x() const;
        float y() const;
        float abs() const;

        bool isUnknown() const;
        bool isValid() const;
        void setUnknown();
        void setInvalid();

    private:
        void setCartesianComponents();
        void setPolarComponents();
};

#endif // VELOCITY_H
