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

#include "coach.h"

#include <src/entities/coach/coordinator/coordinator.h>
#include <src/entities/world/worldmap.h>

Coach::Coach(Constants *constants, WorldMap *worldMap) : Entity(ENT_COACH) {
    _constants = constants;
    _worldMap = worldMap;
    _coordinator = nullptr;
}

Coach::~Coach() {
    delete _coordinator;
}

void Coach::setCoordinator(Coordinator *coordinator) {
    _coordinator = coordinator;
}

void Coach::initialization() {
    std::cout << Text::cyan("[COACH] ", true) + Text::bold("Thread started.") + '\n';
}

void Coach::loop() {
    // Check if coordinator has set
    if(_coordinator == nullptr) {
        std::cout << Text::red("[ERROR] ", true) + Text::bold("No coordinator has been set in Coach.") + '\n';
        return ;
    }

    // Check if coordinator is initialized and initialize if neccessary
    if(!_coordinator->isInitialized()) {
        _coordinator->initialize(getConstants(), getWorldMap());
    }

    // Run coordinator
    _coordinator->runCoordinator();
}

void Coach::finalization() {
    std::cout << Text::cyan("[COACH] ", true) + Text::bold("Thread ended.") + '\n';
}

WorldMap* Coach::getWorldMap() {
    if(_worldMap == nullptr) {
        std::cout << Text::red("[ERROR] ", true) << Text::bold("WorldMap with nullptr value at Coach") + '\n';
    }
    else {
        return _worldMap;
    }

    return nullptr;
}

Constants* Coach::getConstants() {
    if(_constants == nullptr) {
        std::cout << Text::red("[ERROR] ", true) << Text::bold("Constants with nullptr value at Coach") + '\n';
    }
    else {
        return _constants;
    }

    return nullptr;
}
