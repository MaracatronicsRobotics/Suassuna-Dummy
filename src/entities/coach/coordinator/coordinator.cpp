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


#include "coordinator.h"

Coordinator::Coordinator() {
    _initialized = false;
    _actualQtPlayers = 0;
    _actualPlaybook = nullptr;
    _actualPlaybookId = -1;
    _configured = false;
}

Coordinator::~Coordinator() {
    // Delete all playbooks
    QMap<int, Playbook*>::iterator it;
    for(it = _playbookList.begin(); it != _playbookList.end(); it++) {
        Playbook *pb = it.value();
        delete pb;
    }
}

bool Coordinator::isInitialized() {
    return _initialized;
}

void Coordinator::initialize(Constants *constants, WorldMap *worldMap) {
    _constants = constants;
    _worldMap = worldMap;
    _initialized = true;
}

WorldMap* Coordinator::getWorldMap() {
    if(_worldMap == nullptr) {
        std::cout << Text::red("[ERROR] ", true) << Text::bold("WorldMap with nullptr value at " + this->name().toStdString()) + '\n';
    }
    else {
        return _worldMap;
    }

    return nullptr;
}

Constants* Coordinator::getConstants() {
    if(_constants == nullptr) {
        std::cout << Text::red("[ERROR] ", true) << Text::bold("Constants with nullptr value at " + this->name().toStdString()) + '\n';
    }
    else {
        return _constants;
    }

    return nullptr;
}

void Coordinator::addPlaybook(int id, Playbook *playbook) {
    // Check if id was already registered
    if(_playbookList.contains(id)) {
        std::cout << Text::red("[ERROR] ", true) + Text::bold("Trying to add an playbook in an already occupied position.") + '\n';
        return ;
    }

    // Check if playbook was already registered
    if(_playbookList.values().contains(playbook)) {
        std::cout << Text::red("[ERROR] ", true) + Text::bold("Trying to add an playbook that was already added.") + '\n';
        return ;
    }

    // Insert playbook
    _playbookList.insert(id, playbook);

    // If actual playbook is nullptr, set it as actual playbook
    if(_actualPlaybook == nullptr) {
        _actualPlaybook = playbook;
    }
}

void Coordinator::setPlaybook(int id) {
    // Check if id was registered
    if(!_playbookList.contains(id)) {
        std::cout << Text::red("[ERROR] ", true) + Text::bold("Trying to use an playbook id that was not registered.") + '\n';
        return ;
    }

    // Check if this id is the same as the last id
    if(_actualPlaybookId == id) {
        return ;
    }

    // Reset old playbook
    resetPlaybook(_actualPlaybook);

    // Check if playbook is initialized and initialize if necessary
    if(!_playbookList.value(id)->isInitialized()) {
        _playbookList.value(id)->initialize(getConstants(), getWorldMap());
    }

    // Set actual playbook and id
    _actualPlaybookId = id;
    _actualPlaybook = _playbookList.value(id);

    // Reset new playbook
    resetPlaybook(_actualPlaybook);

    // Set players to new playbook
    _actualPlaybook->addPlayers(getWorldMap()->getAvailablePlayers(getConstants()->teamColor()));
}

void Coordinator::resetPlaybook(Playbook *playbook) {
    // Reset playbook
    playbook->resetPlaybook();
}

void Coordinator::runCoordinator() {
    // If not configured yet, call configure method
    if(!_configured) {
        configure();
        _configured = true;
    }

    // Check if have any playbooks
    if(_playbookList.size() == 0) {
        std::cout << Text::red("[ERROR] ", true) + Text::bold("No playbooks have been registered.") + '\n';
        return ;
    }

    // Check if have available players
    QList<quint8> availablePlayers = getWorldMap()->getAvailablePlayers(getConstants()->teamColor());
    if(availablePlayers.size() == 0) {
        return ;
    }

    // Call run virtual method (will choose what playbook to use)
    run();

    // Check if actual playbook is initialized
    if(!_actualPlaybook->isInitialized()) {
        _actualPlaybook->initialize(getConstants(), getWorldMap());
    }

    // Check if qt players changed
    if(availablePlayers.size() != _actualQtPlayers) {
        // Update actualQtPlayers
        _actualQtPlayers = availablePlayers.size();

        // Clear and set players in playbook
        _actualPlaybook->clearPlayers();
        _actualPlaybook->addPlayers(availablePlayers);
    }

    // Run actual playbook
    _actualPlaybook->runPlaybook();
}
