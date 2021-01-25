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

#include "playbook_default2.h"

Playbook_Default2::Playbook_Default2() {

}

QString Playbook_Default2::name() {
    return "Playbook_Default2";
}

void Playbook_Default2::configure(int numPlayers) {
    // Cleaning vector (roles pointers are already stored to further delete when configure is called)
    _roles_default.clear();

    // For each player, register an role and call usesRole() to register it in the table
    for(int i = 0; i < numPlayers; i++) {
        _roles_default.push_back(new Role_Default());
        usesRole(_roles_default.at(i));
    }
}

void Playbook_Default2::run(int numPlayers) {
    // Get players ids list
    QList<quint8> players = getPlayers();

    // For each player, set its associated role
    for(int i = 0; i < numPlayers; i++) {
        // Take locations of our penalty mark
        Position goToPosition = getWorldMap()->getLocations()->ourPenaltyMark();
        goToPosition = Position(true, goToPosition.x(), -1.0 + (i * (2.0 / numPlayers)));
        Position lookToPosition = getWorldMap()->getLocations()->fieldCenter();

        // Set to align in the front of opposite goal
        _roles_default.at(i)->setPositionToGo(goToPosition);
        _roles_default.at(i)->setPositionToLook(lookToPosition);

        setPlayerRole(players.at(i), _roles_default.at(i));
    }
}
