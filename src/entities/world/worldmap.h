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
#include <QObject>
#include <src/utils/types/types.h>
#include <src/utils/types/typesNamespace.h>
#include <src/utils/color/color.h>
#include <include/messages_robocup_ssl_wrapper.pb.h>
#include <include/messages_robocup_ssl_detection.pb.h>

using namespace soccertypes;

class WorldMap : public QObject{
    Q_OBJECT
    public slots:
        void receiveDetectionData(SSL_DetectionFrame detectData);
        void receiveGeometryData(SSL_GeometryData geometData);

    public:
        WorldMap();
        ~WorldMap();

    private:
        mutable QReadWriteLock* _teamsLock;
        mutable QReadWriteLock* _ballsLock;
        mutable QMutex* _detectionMutex;

        // Teams info
        uint8 _nTeams;
        QHash<uint8,bool> _validTeams;
        QHash<uint8,Team> _teams;

        // Balls info
        uint8 _nBalls;
        QHash<uint8,bool>      _validBalls;
        QHash<uint8,Position*> _ballsPositions;
        QHash<uint8,Velocity*> _ballsVelocities;

        // Invalid types
        Angle        _invalidAngle;
        AngularSpeed _invalidAngularSpeed;
        Position     _invalidPosition;
        Velocity     _invalidVelocity;
        QString      _invalidName;
        static const uint8 _invalidNumber = -1;

        void updateBlueTeam(SSL_DetectionFrame* detectData);
        void updateYellowTeam(SSL_DetectionFrame* detectData);
        void deleteOldPlayers(QList<quint8>* recentPlayers, Colors::Color teamNum);

    public:
        void addTeam(uint8 teamNum, const QString& teamName);
        void delTeam(uint8 teamNum);
        QList<uint8> teams() const;
        const QString teamName(uint8 teamNum) const;
        uint8 teamNumber(const QString& name) const;

        void addBall(uint8 ballNum);
        void delBall(uint8 ballNum);
        QList<uint8> balls() const;
        const Position ballPosition(uint8 ballNum) const;
        const Velocity ballVelocity(uint8 ballNum) const;
        void setBallPosition(uint8 ballNum, const Position& position);
        void setBallVelocity(uint8 ballNum, const Velocity& velocity);

        void addPlayer(uint8 teamNum, uint8 playerNum);
        void delPlayer(uint8 teamNum, uint8 playerNum);

        QList<uint8> players(uint8 teamNum) const;
        const Position&     playerPosition(uint8 teamNum, uint8 playerNum)     const;
        const Angle&        playerOrientation(uint8 teamNum, uint8 playerNum)  const;
        const Velocity&     playerVelocity(uint8 teamNum, uint8 playerNum)     const;
        const AngularSpeed& playerAngularSpeed(uint8 teamNum, uint8 playerNum) const;

        bool                ballPossession(uint8 teamNum, uint8 playerNum)     const;
        bool                kickEnabled(uint8 teamNum, uint8 playerNum)        const;
        bool                dribbleEnabled(uint8 teamNum, uint8 playerNum)     const;

        unsigned char       batteryCharge(uint8 teamNum, uint8 playerNum)      const;
        unsigned char       capacitorCharge(uint8 teamNum, uint8 playerNum)    const;

        void setPlayerPosition(uint8 teamNum, uint8 playerNum, const Position& position);
        void setPlayerOrientation(uint8 teamNum, uint8 playerNum, const Angle& orientation);
        void setPlayerVelocity(uint8 teamNum, uint8 playerNum, const Velocity& velocity);
        void setPlayerAngularSpeed(uint8 teamNum, uint8 playerNum, const AngularSpeed& angularSpeed);
        void setBallPossession(uint8 teamNum, uint8 playerNum, bool possession);
        void setKickEnabled(uint8 teamNum, uint8 playerNum, bool status);
        void setDribbleEnabled(uint8 teamNum, uint8 playerNum, bool status);
        void setBatteryCharge(uint8 teamNum, uint8 playerNum, unsigned char charge);
        void setCapacitorCharge(uint8 teamNum, uint8 playerNum, unsigned char charge);
};

#endif // WORLDMAP_H
