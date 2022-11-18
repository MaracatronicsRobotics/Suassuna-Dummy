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

#ifndef WORLDMAP_H
#define WORLDMAP_H

#include <include/proto/visionservice.grpc.pb.h>

#include <src/entities/basesuassuna.h>

class WorldMap : public Threaded::Entity, public Base::GRPC::Client<Armorial::Vision::VisionService>
{
public:
    /*!
     * \brief Constructor for the WorldMap class.
     * \param serviceAddress, servicePort The given parameters for the connection with the Vision Service.
     */
    WorldMap(QString serviceAddress, quint16 servicePort);

    /*!
     * \brief Setup the internal pointers for the teams. This method is called via the Suassuna core interface.
     * \param teams The given teams.
     */
    void setupTeams(QMap<Common::Enums::Color, Team*>& teams);

    // Getters for internal objects
    Common::Types::Field getField();
    Common::Types::Object getBall();
    // Common::Types::Object getPlayer(const Common::Enums::Color& teamColor, quint8 playerId);
    // QList<Common::Types::Object> getPlayersFromTeam(const Common::Enums::Color &teamColor);

protected:
    // Updaters for internal objects
    void updateField();
    void updateBall();
    void updatePlayers();

private:
    // Entity inherited methods
    void initialization();
    void loop();
    void finalization();

    // Internal objects
    QMap<Common::Enums::Color, Team*> _teams;
    Common::Types::Field _field;
    Common::Types::Object _ball;

    // Internal mutex for object management
    QReadWriteLock _mutex;
};

#endif // WORLDMAP_H
