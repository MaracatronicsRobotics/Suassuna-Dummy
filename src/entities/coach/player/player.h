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

#ifndef PLAYER_H
#define PLAYER_H

#include <src/entities/entity.h>
#include <src/constants/constants.h>
#include <src/entities/coach/basecoach.h>
#include <src/entities/world/worldmap.h>

class Player : public Entity
{
    Q_OBJECT
public:
    Player(quint8 playerId, Constants *constants, WorldMap *worldMap);

    // Worldmap getter
    WorldMap* getWorldMap();

    // Player internal getters
    quint8 playerId();
    Position position();
    Angle orientation();
    float getPlayerRotateAngleTo(Position &targetPosition, Position &referencePosition);
    float getPlayerDistanceTo(Position &targetPosition);

    // Player error
    float getLinearError();
    float getAngularError();

    // Role management
    void setRole(Role *role);

    // Skills
    void goTo(Position &targetPosition);
    void rotateTo(Position &targetPosition, Position referencePosition = Position(false, 0.0, 0.0));
    void idle();

private:
    // Entity inherited methods
    void initialization();
    void loop();
    void finalization();

    // Constants
    Constants* getConstants();
    Constants *_constants;

    // Worldmap
    WorldMap *_worldMap;

    // Player internal
    quint8 _playerId;

    // Role management
    Role *_playerRole;
    QMutex _mutexRole;

signals:
    void setLinearSpeed(int teamId, int playerId, float vx, float vy);
    void setAngularSpeed(int teamId, int playerId, float vw);
    void dribble(int teamId, int playerId, bool enable);
    void kick(int teamId, int playerId, float power);
    void chipKick(int teamId, int playerId, float power);
};

#endif // PLAYER_H
