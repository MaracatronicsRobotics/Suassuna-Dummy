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

#include <src/entities/coach/team/team.h>
#include <src/entities/player/player.h>

Suassuna::Suassuna() {
    // Set GUI as nullptr by default
    _gui = nullptr;

    // Start entity manager
    _entityManager = new Threaded::EntityManager();
}

Suassuna::~Suassuna() {
    // If GUI is not null, hide and delete
    if(_gui != nullptr) {
        _gui->hide();
        delete _gui;
    }

    // Delete all entities in EntityManager
    delete _entityManager;
}

bool Suassuna::start(bool useGUI) {
    // If useGUI is set, create and show the GUI
    if(useGUI) {
        _gui = new GUI();
        _gui->show();
    }

    // Start worldmap
    _worldMap = new WorldMap(Constants::visionServiceAddress(), Constants::visionServicePort());
    _entityManager->addEntity(_worldMap);

    // Start controller
    _controller = new Controller(Constants::actuatorServiceAddress(), Constants::actuatorServicePort());
    _entityManager->addEntity(_controller);

    // Start teams
    magic_enum::enum_for_each<Common::Enums::Color>([this] (auto color) {
        if(color != Common::Enums::Color::UNDEFINED) {
            _teams.insert(color, new Team(color));

            for(int i = 0; i < Constants::maxNumPlayers(); i++) {
                Player *player = new Player(i, color, ((color == Constants::teamColor()) ? _controller : nullptr), _worldMap);
                _teams[color]->addPlayer(player);

                if(color == Constants::teamColor()) {
                    _entityManager->addEntity(player);
                }
            }
        }
    });

    // Setup teams in WorldMap
    _worldMap->setupTeams(_teams);

    // Start all entities
    _entityManager->startEntities();

    return true;
}

bool Suassuna::stop() {
    // Stop entities registered in EntityManager (this also waits for them to stop)
    _entityManager->disableEntities();

    return true;
}
