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

#ifndef TYPES_H
#define TYPES_H

// Includes Qt library
#include <QtCore/QtCore>


// Elementary types
#define int8   qint8
#define int16  qint16
#define int32  qint32
#define uint8  quint8
#define uint16 quint16
#define uint32 quint32

#include <src/utils/types/angle.h>
#include <src/utils/types/position.h>
#include <src/utils/types/velocity.h>
#include <src/utils/types/angularspeed.h>
#include <src/utils/types/team.h>

#endif // TYPES_H
