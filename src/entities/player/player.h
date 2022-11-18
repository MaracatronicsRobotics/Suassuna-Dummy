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

#include <Armorial/Common/Types/Object/Object.h>
#include <Armorial/Common/Enums/Color/Color.h>
#include <Armorial/Threaded/Entity/Entity.h>
#include <Armorial/Utils/Timer/Timer.h>

#include <src/entities/controller/controller.h>

class Player : public Common::Types::Object, public Threaded::Entity
{
public:
    Player(const quint8& playerId, const Common::Enums::Color& teamColor, Controller* controller);

    /*!
     * \brief Player params getters
     */
    Common::Enums::Color teamColor();
    quint8 playerId();

    /*!
     * \brief Mark player as idle, setting its speeds to zero.
     */
    void idle();

protected:
    friend class Team;

    /*!
     * \brief Update this Player class with a given Common::Types::Object containing
     * the data.
     * \param playerData The given data to update this Player instance.
     */
    void updatePlayer(Common::Types::Object playerData);

private:
    // Entity inherited methods
    void initialization();
    void loop();
    void finalization();

    // Internal objects
    quint8 _playerId;
    Common::Enums::Color _teamColor;

    // Modules
    Controller *_controller;

    // Idle control
    Utils::Timer _idleTimer;
    bool _firstIt;
};

#endif // PLAYER_H
