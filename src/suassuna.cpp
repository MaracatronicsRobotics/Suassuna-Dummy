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

#include <src/entities/coach/player/player.h>
#include <src/entities/coach/role/default/role_default.h>
#include <src/utils/types/field/ssl/field_sslb.h>
#include <src/entities/coach/coordinator/ssl/coordinator_ssl.h>

Suassuna::Suassuna(Constants *constants) {
    // Setting up constants
    _constants = constants;

    // Creating world
    _world = new World(getConstants());
}

void Suassuna::start() {
    // Creating World Map (set here the map that u desire)
    _worldMap = new WorldMap(getConstants(), getConstants()->teamSide(), new Field_SSLB());

    // Creating and adding vision to world
    _vision = new Vision(getConstants());
    _world->addEntity(_vision, 0);

    // Vision-WorldMap connection
    qRegisterMetaType<Colors::Color>("Colors::Color");
    qRegisterMetaType<Object>("Object");
    QObject::connect(_vision, SIGNAL(sendPlayer(Colors::Color, quint8, Object)), _worldMap, SLOT(updatePlayer(Colors::Color, quint8, Object)), Qt::DirectConnection);
    QObject::connect(_vision, SIGNAL(sendBall(Object)), _worldMap, SLOT(updateBall(Object)), Qt::DirectConnection);
    QObject::connect(_vision, SIGNAL(sendGeometryData(SSL_GeometryData)), _worldMap, SLOT(updateGeometry(SSL_GeometryData)), Qt::DirectConnection);

    // Creating and adding actuator to world
    _simActuator = new SimActuator(getConstants());
    _world->addEntity(_simActuator, 1); // needs to be an higher priority than the last player priority

    // Adding players
    for(int i = 0; i < getConstants()->qtPlayers(); i++) {
        Player *player = new Player(i, getConstants(), _worldMap);
        QObject::connect(player, SIGNAL(setLinearSpeed(int, int, float, float)), _simActuator, SLOT(setLinearSpeed(int, int, float, float)));
        QObject::connect(player, SIGNAL(setAngularSpeed(int, int, float)), _simActuator, SLOT(setAngularSpeed(int, int, float)));
        QObject::connect(player, SIGNAL(dribble(int, int, bool)), _simActuator, SLOT(dribble(int, int, bool)));
        QObject::connect(player, SIGNAL(kick(int, int, float)), _simActuator, SLOT(kick(int, int, float)));
        QObject::connect(player, SIGNAL(chipKick(int, int, float)), _simActuator, SLOT(chipKick(int, int, float)));

        /// TODO: remove this (testing)
        Role_Default *rl = new Role_Default();
        player->setRole(rl);

        _worldMap->addPlayer(i, player);
        _world->addEntity(player, 2);
    }

    // Creating coach
    _coach = new Coach(getConstants(), _worldMap);
    _world->addEntity(_coach, 3);

    // Setting coordinator to coach
    _coach->setCoordinator(new Coordinator_SSL());

    // Starting world
    _world->start();

    // Disabling world thread (loop() won't run anymore)
    _world->disableLoop();
}

void Suassuna::stop() {
    // Stopping and waiting world
    _world->stopEntity();
    _world->wait();

    // Deleting world (it also delete all other entities added to it)
    delete _world;

    // Delete worldmap
    delete _worldMap;
}

Constants* Suassuna::getConstants() {
    if(_constants == nullptr) {
        std::cout << Text::red("[ERROR] ", true) << Text::bold("Constants with nullptr value at Suassuna") + '\n';
    }
    else {
        return _constants;
    }

    return nullptr;
}
