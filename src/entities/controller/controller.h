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

#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <include/proto/actuatorservice.grpc.pb.h>

#include <src/entities/basesuassuna.h>

/*!
 * \brief The Controller class
 */
class Controller : public Threaded::Entity, public Base::GRPC::Client<Armorial::Actuator::ActuatorService>
{
public:
    /*!
     * \brief Controller
     */
    Controller(QString serviceAddress, quint16 servicePort);

protected:
    friend class Player;
    friend class Skill;

    /*!
     * \brief setWheelsSpeed
     * \param playerId
     * \param wheelLeft
     * \param wheelRight
     */
    void setLinearSpeed(const quint8& playerId, const Armorial::Velocity& linearSpeed);

    /*!
     * \brief Set angular speed for a given robot.
     * \param playerId The given robot.
     * \param angularSpeed The given liner speed.
     */
    void setAngularSpeed(const quint8& playerId, const Armorial::AngularSpeed& angularSpeed);

    /*!
     * \brief Set kick data for a given robot.
     * \param playerId The given robot.
     * \param kickSpeed, chipKickAngle, kickAngle The given kick data.
     */
    void setKick(const quint8& playerId, const Armorial::KickSpeed& kickSpeed);

    /*!
     * \brief Set dribbling for a given robot.
     * \param playerId The given robot.
     * \param dribbling The given dribbling status.
     */
    void setDribble(const quint8& playerId, const bool& dribbling);

    /*!
     * \brief Setup a default packet with the robot identifier at the index of the _controlPackets map.
     * \param playerId The given robot.
     */
    void setupDefaultPacket(const quint8& playerId);

private:
    // Entity inherited methods
    void initialization();
    void loop();
    void finalization();

    // Intenrnal objects
    QMap<quint8, Armorial::ControlPacket> _controlPackets;
    QMutex _mutex;
};

#endif // CONTROLLER_H
