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

#ifndef PLAYBOOK_H
#define PLAYBOOK_H

#include <src/constants/constants.h>
#include <src/entities/world/worldmap.h>
#include <src/entities/coach/basecoach.h>

class Playbook
{
public:
    Playbook();
    virtual ~Playbook();

    // Playbook name (for debug)
    virtual QString name() = 0;

    // Init playbook control
    bool isInitialized();
    void initialize(Constants *constants, WorldMap *worldMap);

    // Playbook management
    void resetPlaybook();

    // Method to run in coach
    void runPlaybook();

    // Players control
    void addPlayer(quint8 id);
    void addPlayers(const QList<quint8> &ids);
    void clearPlayers();
    void updatePlayersRoles();
    int numPlayers();
    QList<quint8> getPlayers();

protected:
    // Players control
    bool hasPlayer(quint8 id);
    void setPlayerRole(quint8 id, Role *role);

    // Role management
    void usesRole(Role *role);

    // Constants and WorldMap access
    Constants* getConstants();
    WorldMap* getWorldMap();

private:
    // Virtual implementation in inherited classes
    virtual void configure(int numPlayers) = 0;
    virtual void run(int numPlayers) = 0;

    // Roles management
    void clearOldRoles();
    void setCurrRolesToOld();

    // Constants and worldmap vars
    Constants *_constants;
    WorldMap *_worldMap;

    // Players in this playbook list
    QList<quint8> _players;
    QMap<quint8, Role*> _assignmentTable;
    QList<Role*> _rolesList;
    QList<Role*> _oldRolesList;
    int _lastNumPlayers;

    // Initialize and configure control
    bool _initialized;
    bool _configured;
};

#endif // PLAYBOOK_H
