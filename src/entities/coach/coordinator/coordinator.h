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

#ifndef COORDINATOR_H
#define COORDINATOR_H

#include <src/entities/coach/playbook/playbooks.h>

class Coordinator
{
public:
    Coordinator();
    virtual ~Coordinator();

    // Coordinator name (for debug)
    virtual QString name() = 0;

    // Init coordinator control
    bool isInitialized();
    void initialize(Constants *constants, WorldMap *worldMap);

    // Playbook management
    void addPlaybook(int id, Playbook *playbook);
    void setPlaybook(int id);
    void resetPlaybook(Playbook *playbook);

    // Run
    void runCoordinator();

protected:
    // Constants and WorldMap access
    Constants* getConstants();
    WorldMap* getWorldMap();

private:
    // Virtual implementation in inherited classes
    virtual void configure() = 0;
    virtual void run() = 0;

    // Constants and WorldMap pointers
    Constants *_constants;
    WorldMap *_worldMap;

    // Init control
    bool _initialized;
    bool _configured;

    // Playbooks list
    QMap<int, Playbook*> _playbookList;
    Playbook *_actualPlaybook;
    int _actualPlaybookId;

    // Players management
    int _actualQtPlayers;
};

#endif // COORDINATOR_H
