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

#include "suassuna.h"

Suassuna::Suassuna(Constants *constants) {
    // Setting up constants
    _constants = constants;

    // Creating world
    _world = new World(getConstants());
}

void Suassuna::start() {
    // Creating World Map
    _worldMap = new WorldMap();

    // Creating and adding vision to world
    _vision = new Vision(getConstants());
    _world->addEntity(_vision, 0);

    // Vision-WorldMap connection
    QObject::connect(_vision, SIGNAL(sendDetectData(SSL_DetectionFrame)), _worldMap, SLOT(receiveDetectionData(SSL_DetectionFrame)), Qt::DirectConnection);
    QObject::connect(_vision, SIGNAL(sendGeometData(SSL_GeometryData)), _worldMap, SLOT(receiveGeometryData(SSL_GeometryData)), Qt::DirectConnection);

    // Creating and adding actuator to world
    _simActuator = new SimActuator(getConstants());
    _world->addEntity(_simActuator, 1);

    // Starting world
    _world->start();
}

void Suassuna::stop() {
    // Stopping and waiting world
    _world->stopEntity();
    _world->wait();

    // Deleting world (it also delete all other entities added to it)
    delete _world;
}

Constants* Suassuna::getConstants() {
    if(_constants == nullptr) {
        std::cout << Text::red("[ERROR] ", true) << Text::bold("Constants with nullptr value at Suassuna") << '\n';
    }
    else {
        return _constants;
    }

    return nullptr;
}
