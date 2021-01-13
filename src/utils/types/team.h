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

#ifndef TEAM_H
#define TEAM_H

#include <src/utils/types/types.h>
#include <src/utils/types/typesNamespace.h>

// Includes Qt library
#include <QtCore/QtCore>

using namespace soccertypes;

class soccertypes::Team{
public:
    Team();
    Team(uint8 number, QString name);

private:
    // Team info
    uint8   _number;
    QString _name;

    // Team players
    uint8 _nPlayers;
    QHash<uint8,bool> _validPlayers;
    QHash<uint8,Position*> _playersPositions;
    QHash<uint8,Angle*> _playersOrientations;
    QHash<uint8,Velocity*> _playersVelocities;
    QHash<uint8,AngularSpeed*> _playersAngularSpeeds;
    QHash<uint8,bool> _ballPossessions;
    QHash<uint8,bool> _dribbleEnabled;
    QHash<uint8,bool> _kickEnabled;
    QHash<uint8,unsigned char> _batteryCharge;
    QHash<uint8,unsigned char> _capacitorCharge;

    // Info flag
    bool _valid;

    // Invalid types
    Angle*        _invalidAngle;
    AngularSpeed* _invalidAngularSpeed;
    Position*     _invalidPosition;
    Velocity*     _invalidVelocity;

public:
    void addPlayer(uint8 playerNum);
    void delPlayer(uint8 playerNum);
    QList<uint8> players() const;

    const QString& name() const;
    uint8 number() const;
    void  setName(const QString& name);
    void  setNumber(uint8 number);

    void setPlayerBatteryCharge(uint8 playerNum, unsigned char charge);
    void setPlayerCapacitorCharge(uint8 playerNum, unsigned char charge);
    void setPlayerDribbleStatus(uint8 playerNum, bool status);
    void setPlayerKickStatus(uint8 playerNum, bool status);

    const Position*     position(uint8 playerNum)        const;
    const Angle*        orientation(uint8 playerNum)     const;
    const Velocity*     velocity(uint8 playerNum)        const;
    const AngularSpeed* angularSpeed(uint8 playerNum)    const;
    bool                ballPossession(uint8 playerNum)  const;
    unsigned char       batteryCharge(uint8 playerNum)   const;
    unsigned char       capacitorCharge(uint8 playerNum) const;
    bool                kickEnabled(uint8 playerNum)     const;
    bool                dribbleEnabled(uint8 playerNum)  const;

    void setPosition(uint8 playerNum, const Position& position);
    void setOrientation(uint8 playerNum, const Angle& orientation);
    void setVelocity(uint8 playerNum, const Velocity& velocity);
    void setAngularSpeed(uint8 playerNum, const AngularSpeed& angularSpeed);
    void setBallPossession(uint8 playerNum, bool possession);

    bool isValid() const;
    void setInvalid();
};

#endif // TEAM_H
