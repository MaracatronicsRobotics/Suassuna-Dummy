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

#ifndef WORLDMAP_H
#define WORLDMAP_H

#include <QObject>
#include <QMap>

#include <src/constants/constants.h>
#include <src/entities/coach/basecoach.h>
#include <src/entities/world/locations/locations.h>
#include <src/utils/types/color/color.h>
#include <src/utils/types/object/object.h>
#include <include/messages_robocup_ssl_geometry.pb.h>

class WorldMap : public QObject
{
    Q_OBJECT
public:
    WorldMap(Constants *constants, FieldSide ourSide, Field *field);
    ~WorldMap();

    // Objects getter
    Object getPlayer(Colors::Color teamColor, quint8 playerId);
    Object getBall();

    // Player pointer management
    void addPlayer(quint8 playerId, Player *playerPointer);
    Player* getPlayerPointer(quint8 playerId);

    // Utilities
    QList<quint8> getAvailablePlayers(Colors::Color teamColor);

    // Locations getter
    Locations* getLocations();

private:
    // Objects internal vars
    QMap<Colors::Color, QMap<quint8, Object>*> _playerObjects;
    Object _ballObject;

    // Player internal pointers
    QMap<quint8, Player*> _playerPointers;

    // Constants
    Constants *_constants;
    Constants* getConstants();

    // Field locations
    Locations *_locations;

    // Mutexes for read/write control management
    QReadWriteLock _playerMutex;
    QReadWriteLock _ballMutex;

public slots:
    void updatePlayer(Colors::Color teamColor, quint8 playerId, Object playerObject);
    void updateBall(Object ballObject);
    void updateGeometry(SSL_GeometryData geometryData);
};

#endif // WORLDMAP_H
