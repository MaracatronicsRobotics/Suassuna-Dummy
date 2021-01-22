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

class Position
{
public:
    Position();
    Position(bool isValid, float x, float y);

    // Setters
    void setPosition(bool isValid, float x, float y);
    void setInvalid();

    // Getterrs
    bool isInvalid() const;
    float x() const;
    float y() const;

private:
    // Params
    bool _isValid;
    float _x;
    float _y;
};

#endif // POSITION_H
