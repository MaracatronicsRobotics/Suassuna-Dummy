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

#ifndef COACH_H
#define COACH_H

#include <src/entities/entity.h>
#include <src/constants/constants.h>
#include <src/entities/coach/basecoach.h>

class Coach : public Entity
{
public:
    Coach(Constants *constants, WorldMap *worldMap);
    ~Coach();

    // Coordinator management
    void setCoordinator(Coordinator *coordinator);

private:
    // Entity inherited methods
    void initialization();
    void loop();
    void finalization();

    // Coordinator
    Coordinator *_coordinator;

    // Constants
    Constants* getConstants();
    Constants *_constants;

    // Worldmap
    WorldMap *_worldMap;
    WorldMap* getWorldMap();
};

#endif // COACH_H
