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

#ifndef BEHAVIOR_DEFAULT_H
#define BEHAVIOR_DEFAULT_H

#include <src/entities/player/behaviors/behavior.h>
#include <src/entities/player/skills/skills.h>

class Behavior_Default : public Behavior
{
public:
    Behavior_Default();

private:
    // Behavior inherited methods
    void configure();
    void run();

    // Skills enum
    enum {
        SKILL_IDLE
    };

    // Skills pointers
    Skill_Idle *_skill_idle;
};

#endif // BEHAVIOR_DEFAULT_H
