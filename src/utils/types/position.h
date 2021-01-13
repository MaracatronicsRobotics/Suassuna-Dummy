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

#ifndef POSITION_H
#define POSITION_H

#include <src/utils/types/typesNamespace.h>

class soccertypes::Position{
    public:
        Position();
        Position(bool known, float x, float y, float z);

    private:
        // Position coordinates
        float _x;
        float _y;
        float _z;

        // Info flags
        bool _unknown;
        bool _valid;

    public:
        Position& operator =(const Position& other);

        void setPosition(float x, float y, float z);
        float x() const;
        float y() const;
        float z() const;

        bool isUnknown() const;
        bool isValid() const;
        void setUnknown();
        void setInvalid();

};

#endif // POSITION_H
