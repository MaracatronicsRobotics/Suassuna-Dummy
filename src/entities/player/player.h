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

#include <src/entities/basesuassuna.h>

class Player : public Common::Types::Object, public Threaded::Entity
{
public:
    Player(const quint8& playerId, const Common::Enums::Color& teamColor, Controller* controller, WorldMap *worldMap);

    /*!
     * \brief Player params getters
     */
    Common::Enums::Color teamColor();
    quint8 playerId();

    // Role management
    QString roleName();
    QString behaviorName();

protected:
    // Friend classes for update and internal control of the player
    friend class Team;
    friend class Skill;
    friend class Behavior;
    friend class Role;

    /*!
     * \brief Update this Player class with a given Common::Types::Object containing
     * the data.
     * \param playerData The given data to update this Player instance.
     */
    void updatePlayer(Common::Types::Object playerData);

    /*!
     * \brief Mark player as idle, setting its speeds to zero.
     */
    void idle();

    /*!
     * \return The Controller pointer of this player instance.
     */
    Controller* controller();

    /*!
     * \brief setRole
     * \param role
     */
    void setRole(Role* role);

private:
    // Entity inherited methods
    void initialization();
    void loop();
    void finalization();

    // Internal objects
    quint8 _playerId;
    Common::Enums::Color _teamColor;

    // Role management
    Role *_playerRole;
    QMutex _mutexRole;

    // Modules
    Controller *_controller;
    WorldMap *_worldMap;

    // Idle control
    Utils::Timer _idleTimer;
    bool _firstIt;
};

#endif // PLAYER_H
