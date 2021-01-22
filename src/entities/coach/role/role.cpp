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

#include "role.h"

#include <src/entities/coach/player/player.h>
#include <src/entities/coach/behavior/behavior.h>

Role::Role() {
    _player = nullptr;
    _constants = nullptr;
    _actualBehavior = nullptr;
    _initialized = false;
}

Role::~Role() {
    // Deleting skills
    QList<Behavior*> behaviorList = _behaviorList.values();
    QList<Behavior*>::iterator it;

    for(it = behaviorList.begin(); it != behaviorList.end(); it++) {
        delete *it;
    }

    // Cleaning map
    _behaviorList.clear();
}

bool Role::isInitialized() {
    return _initialized;
}

void Role::initialize(Constants *constants) {
    _constants = constants;
    configure();
    _initialized = true;
}

void Role::setPlayer(Player *player) {
    _player = player;
}

void Role::runRole() {
    // Check if behavior have at least one skill
    if(_behaviorList.size() == 0) {
        std::cout << Text::red("[ERROR] ", true) + Text::bold(this->name().toStdString() + ":Has no behaviors set!.") + '\n';
        return ;
    }

    // Run behavior (implemented by child inherited method)
    run();

    // Check if initialized
    if(!_actualBehavior->isInitialized()) {
        _actualBehavior->initialize(getConstants());
    }

    // Run skill
    _actualBehavior->setPlayer(player());
    _actualBehavior->runBehavior();
}

void Role::addBehavior(int id, Behavior *behavior) {
    if(_behaviorList.contains(id)) {
        std::cout << Text::red("[ERROR] ", true) + Text::bold(this->name().toStdString() + ":Trying to add a behavior with an id already associated.") + '\n';
        return ;
    }

    // If is the first skill added, set it as actualSkill
    if(_actualBehavior == nullptr) {
        _actualBehavior = behavior;
    }

    _behaviorList.insert(id, behavior);
}

void Role::setBehavior(int id) {
    if(!_behaviorList.contains(id)) {
        std::cout << Text::red("[ERROR] ", true) + Text::bold(this->name().toStdString() + ":Trying to set an behavior that has not added previously.") + '\n';
        return ;
    }

    _actualBehavior = _behaviorList.value(id);
}

Player* Role::player() {
    return _player;
}

Constants* Role::getConstants() {
    if(_constants == nullptr) {
        std::cout << Text::red("[ERROR] ", true) + Text::bold("Constants with nullptr value at " + this->name().toStdString()) + '\n';
    }
    else {
        return _constants;
    }

    return nullptr;
}
