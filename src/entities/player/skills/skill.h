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

#ifndef SKILL_H
#define SKILL_H

#include <src/entities/basesuassuna.h>

class Skill
{
public:
    Skill();
    virtual ~Skill() = default;

    // Name
    virtual inline QString name() {
        return NAMEOF_TYPE_RTTI(*this).data();
    }

    // Init skill control
    bool isInitialized();
    void initialize(WorldMap* worldMap);
    void setPlayer(Player *player);

    // Run
    void runSkill();

protected:
    // Player and worldmap getters
    WorldMap* getWorldMap();
    Player* player();

    // Controller interface
    void setLinearSpeed(const Armorial::Velocity& linearSpeed);
    void setAngularSpeed(const Armorial::AngularSpeed& angularSpeed);
    void setKick(const Armorial::KickSpeed& kickSpeed);
    void setDribble(const bool& dribbling);

private:
    // Virtual implementation in inherited classes
    virtual void configure() = 0;
    virtual void run() = 0;

    // Player access
    Player *_player;

    // WorldMap
    WorldMap *_worldMap;

    // Internal control
    bool _initialized;
};

#endif // SKILL_H
