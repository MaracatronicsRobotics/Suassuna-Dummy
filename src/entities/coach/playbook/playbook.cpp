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

#include "playbook.h"

#include <src/entities/coach/player/player.h>
#include <src/entities/coach/role/role.h>

Playbook::Playbook() {
    _initialized = false;
    _configured = false;
    _lastNumPlayers = 0;
}

Playbook::~Playbook() {
    setCurrRolesToOld();
    clearOldRoles();
}

WorldMap* Playbook::getWorldMap() {
    if(_worldMap == nullptr) {
        std::cout << Text::red("[ERROR] ", true) << Text::bold("WorldMap with nullptr value at " + this->name().toStdString()) + '\n';
    }
    else {
        return _worldMap;
    }

    return nullptr;
}

Constants* Playbook::getConstants() {
    if(_constants == nullptr) {
        std::cout << Text::red("[ERROR] ", true) << Text::bold("Constants with nullptr value at " + this->name().toStdString()) + '\n';
    }
    else {
        return _constants;
    }

    return nullptr;
}

bool Playbook::isInitialized() {
    return _initialized;
}

void Playbook::initialize(Constants *constants, WorldMap *worldMap) {
    _constants = constants;
    _worldMap = worldMap;
    _initialized = true;
}

void Playbook::resetPlaybook() {
    setCurrRolesToOld();
    clearPlayers();
    _configured = false;
}

void Playbook::runPlaybook() {
    // Check if has players
    if(_players.size() == 0) {
        std::cout << Text::red("[ERROR] ", true) << Text::bold(name().toStdString() + " has no players set!") + '\n';
        return ;
    }

    // Run configure and set curr roles to old if num of players in this playbook has changed
    if(_lastNumPlayers != _players.size() || !_configured) {
        _lastNumPlayers = _players.size();
        setCurrRolesToOld();
        configure(_lastNumPlayers);
        _configured = true;
    }

    // Ensure that only players in this playbook are assigned
    QList<quint8> playerIds = _assignmentTable.keys();
    QList<quint8>::iterator it;
    for(it = playerIds.begin(); it != playerIds.end(); it++) {
        quint8 id = (*it);
        if(!_players.contains(id)) {
            _assignmentTable.remove(id);
        }
    }

    // Ensure that players in this playbook exists in the assignment table
    for(it = _players.begin(); it != _players.end(); it++) {
        quint8 id = (*it);
        if(!_assignmentTable.contains(id)) {
            _assignmentTable.insert(id, nullptr);
        }
    }

    // Run playbook (this will update the assignment table)
    run(_lastNumPlayers);

    // Now use the assignment table and set players roles properly
    updatePlayersRoles();

    // Clear old roles
    clearOldRoles();
}

void Playbook::addPlayer(quint8 id) {
    // Check if player id is available on wm
    if(getWorldMap()->getPlayer(getConstants()->teamColor(), id).getPosition().isInvalid()) {
        std::cout << Text::red("[ERROR] ", true) << Text::bold(name().toStdString() + " -> ::addPlayer(" + std::to_string(id) + "), player " + std::to_string(id) + " does not exist in WorldMap.") + '\n';
        return ;
    }

    // Add player id to this playbook
    if(!_players.contains(id)) {
        _players.push_back(id);
    }
}

void Playbook::addPlayers(const QList<quint8> &ids) {
    // Check if list is empty
    if(ids.empty()) {
        return ;
    }

    // Add list
    QList<quint8>::const_iterator it;
    for(it = ids.constBegin(); it != ids.constEnd(); it++) {
        const quint8 id = (*it);
        addPlayer(id);
    }
}

void Playbook::clearPlayers() {
    _players.clear();
}

int Playbook::numPlayers() {
    return _players.size();
}

QList<quint8> Playbook::getPlayers() {
    return _players;
}

void Playbook::updatePlayersRoles() {
    QMap<quint8, Role*>::const_iterator it;
    for(it = _assignmentTable.constBegin(); it != _assignmentTable.constEnd(); it++) {
        // Take id and role to be assigned
        quint8 id = it.key();
        Role *role = it.value();

        // Get player pointer and set its role
        Player *player = getWorldMap()->getPlayerPointer(id);
        player->setRole(role);

        // Warning if the role is nullptr
        if(role == nullptr) {
            std::cout << Text::red("[WARNING] ", true) << Text::bold(name().toStdString() + " -> Player " + std::to_string(id) + " has no role assigned.") + '\n';
        }
    }
}

void Playbook::setCurrRolesToOld() {
    while(!_rolesList.isEmpty()) {
        Role *role = _rolesList.takeFirst();
        _oldRolesList.push_back(role);
    }
}

void Playbook::clearOldRoles() {
    while(!_oldRolesList.isEmpty()) {
        Role *role = _oldRolesList.takeFirst();
        if(role != nullptr) {
            delete role;
        }
    }

    _oldRolesList.clear();
}

bool Playbook::hasPlayer(quint8 id) {
    return _players.contains(id);
}

void Playbook::setPlayerRole(quint8 id, Role *role) {
    // Check pointer
    if(role == nullptr) {
        std::cout << Text::red("[ERROR] ", true) << Text::bold(name().toStdString() + " -> ::setPlayerRole(" + std::to_string(id) + ", NULL), role is null!") + '\n';
        return ;
    }

    // Check if player is on this playbook
    if(!hasPlayer(id)) {
        std::cout << Text::red("[ERROR] ", true) << Text::bold(name().toStdString() + " -> ::setPlayerRole(" + std::to_string(id) + ", " + role->name().toStdString() + "), player " + std::to_string(id) + " does not exist in this playbook.") + '\n';
        return ;
    }

    // Check if role is on this playbook
    if(!_rolesList.contains(role)) {
        std::cout << Text::red("[ERROR] ", true) << Text::bold(name().toStdString() + " -> ::setPlayerRole(" + std::to_string(id) + ", " + role->name().toStdString() + "), role " + role->name().toStdString() + " does not exist in this playbook.") + '\n';
        return ;
    }

    // Check if old player still has the role
    if(_assignmentTable.values().contains(role)) {
        quint8 oldID = _assignmentTable.key(role);
        if(_players.contains(oldID)) {
            _assignmentTable.insert(oldID, NULL);
        }
    }

    // Assign role properly
    _assignmentTable.insert(id, role);
}

void Playbook::usesRole(Role *role) {
    // Check pointer
    if(role == nullptr) {
        std::cout << Text::red("[ERROR] ", true) << Text::bold(name().toStdString() + " -> ::usesRole(NULL), role is null!") + '\n';
        return ;
    }

    // Add role
    if(!_rolesList.contains(role)) {
        _rolesList.push_back(role);
    }
}
