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

#include "worldmap.h"

#include <src/utils/text/text.h>

WorldMap::WorldMap(Constants *constants, FieldSide ourSide, Field *field) {
    // Taking constants
    _constants = constants;

    // Fill player objects
    for(int i = Colors::Color::YELLOW; i <= Colors::Color::BLUE; i++) {
        _playerObjects.insert(Colors::Color(i), new QMap<quint8, Object>());
        QMap<quint8, Object> *_teamObjects = _playerObjects.value(Colors::Color(i));
        for(int j = 0; j < getConstants()->qtPlayers(); j++) {
            _teamObjects->insert(j, Object());
        }
    }

    // Initializing locations
    _locations = new Locations(ourSide, field);
}

WorldMap::~WorldMap() {
    // Get teams list
    QList<Colors::Color> teamList = _playerObjects.keys();

    // For each team
    for(QList<Colors::Color>::iterator it = teamList.begin(); it != teamList.end(); it++) {
        // Take team associated objects
        QMap<quint8, Object> *teamObjects = _playerObjects.value((*it));

        // Clear team association
        teamObjects->clear();

        // Delete pointer
        delete teamObjects;
    }

    // Clear teams
    _playerObjects.clear();

    // Delete locations
    delete _locations;
}

Constants* WorldMap::getConstants() {
    if(_constants == nullptr) {
        std::cout << Text::red("[ERROR] ", true) << Text::bold("Constants with nullptr value at WorldMap") + '\n';
    }
    else {
        return _constants;
    }

    return nullptr;
}


Object WorldMap::getPlayer(Colors::Color teamColor, quint8 playerId) {
    _playerMutex.lockForRead();

    // Check if contains teamColor
    if(!_playerObjects.contains(teamColor)) {
        std::cout << Text::red("[ERROR] ", true) + Text::bold("WorldMap::getPlayer(" + std::to_string(teamColor) + ", quint8), teamColor " + std::to_string(teamColor) + " does not exists.") + '\n';
        return Object();
    }

    // Taking map for team
    QMap<quint8, Object> *_teamObjects = _playerObjects.value(teamColor);

    // Check if contains required player
    if(!_teamObjects->contains(playerId)) {
        std::cout << Text::red("[ERROR] ", true) + Text::bold("WorldMap::getPlayer(teamColor, " + std::to_string(playerId) + "), playerId " + std::to_string(playerId) + " does not exists.") + '\n';
        return Object();
    }

    // Take object
    Object requiredObject = _teamObjects->value(playerId);

    _playerMutex.unlock();

    return requiredObject;
}

Object WorldMap::getBall() {
    _ballMutex.lockForRead();
    Object ballObject = _ballObject;
    _ballMutex.unlock();

    return ballObject;
}

void WorldMap::addPlayer(quint8 playerId, Player *playerPointer) {
    _playerPointers.insert(playerId, playerPointer);
}

Player* WorldMap::getPlayerPointer(quint8 playerId) {
    if(!_playerPointers.contains(playerId)) {
        std::cout << Text::red("[ERROR] ", true) + Text::bold("WorldMap::getPlayerPointer(" + std::to_string(playerId) + "), playerId " + std::to_string(playerId) + " does not exists.") + '\n';
        return nullptr;
    }

    return _playerPointers.value(playerId);
}

QList<quint8> WorldMap::getAvailablePlayers(Colors::Color teamColor) {
    QList<quint8> playersList;
    if(!_playerObjects.contains(teamColor)) {
        std::cout << Text::red("[ERROR] ", true) + Text::bold("WorldMap::getAvailablePlayers(" + std::to_string(teamColor) + "), teamColor " + std::to_string(teamColor) + " does not exists.") + '\n';
        return playersList;
    }

    _playerMutex.lockForRead();
    // Take team players
    QMap<quint8, Object> *teamPlayers = _playerObjects.value(teamColor);
    QMap<quint8, Object>::iterator it;

    for(it = teamPlayers->begin(); it != teamPlayers->end(); it++) {
        // Take player id and object
        quint8 playerId = it.key();
        Object playerObject = it.value();

        // If position is not invalid (player exists in field) add to the playersList
        if(!playerObject.getPosition().isInvalid()) {
            playersList.push_back(playerId);
        }
    }
    _playerMutex.unlock();

    return playersList;
}

void WorldMap::updatePlayer(Colors::Color teamColor, quint8 playerId, Object playerObject) {
    _playerMutex.lockForWrite();

    // If !contains teamColor, create it
    if(!_playerObjects.contains(teamColor)) {
        _playerObjects.insert(teamColor, new QMap<quint8, Object>());
    }

    // Taking map for the required team
    QMap<quint8, Object> *_teamObjects = _playerObjects.value(teamColor);

    // If !contains a player with playerId, create it
    if(!_teamObjects->contains(playerId)) {
        _teamObjects->insert(playerId, Object());
    }

    // Updating required object
    _teamObjects->insert(playerId, playerObject);

    Object oj = _teamObjects->value(playerId);

    _playerMutex.unlock();
}
void WorldMap::updateBall(Object ballObject) {
    _ballMutex.lockForWrite();

    _ballObject = ballObject;

    _ballMutex.unlock();
}

void WorldMap::updateGeometry(SSL_GeometryData geometryData) {
    _locations->updateGeometryData(geometryData);
}

Locations* WorldMap::getLocations() {
    return _locations;
}
