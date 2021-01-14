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

#ifndef SUASSUNA_H
#define SUASSUNA_H

#include <src/entities/vision/vision.h>
#include <src/entities/world/world.h>
#include <src/entities/actuator/simulator/simactuator.h>
#include <src/entities/world/worldmap.h>
#include <src/constants/constants.h>

class Suassuna
{
public:
    Suassuna(Constants *constants);

    // Internal management
    void start();
    void stop();

private:
    // Constants
    Constants *_constants;
    Constants* getConstants();

    // Modules
    Vision *_vision;
    SimActuator *_simActuator;

    // World
    World *_world;

    // World Map
    WorldMap *_worldMap;
};

#endif // SUASSUNA_H
