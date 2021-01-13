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

#include "team.h"

// Selects namespace
using namespace soccertypes;

Team::Team() {
    // Sets as invalid
    setInvalid();

    // Creates invalid types
    _invalidPosition     = new Position();
    _invalidAngle        = new Angle();
    _invalidVelocity     = new Velocity();
    _invalidAngularSpeed = new AngularSpeed();

    // Initializes the players
    _nPlayers = 0;
    _validPlayers.clear();
    _playersPositions.clear();
    _playersOrientations.clear();
    _playersVelocities.clear();
    _playersAngularSpeeds.clear();
    _ballPossessions.clear();
}

Team::Team(uint8 teamNumber, QString teamName) {
    // Sets team info
    _number = teamNumber;
    _name   = teamName;
    _valid  = true;

    // Creates invalid types
    _invalidPosition     = new Position();
    _invalidAngle        = new Angle();
    _invalidVelocity     = new Velocity();
    _invalidAngularSpeed = new AngularSpeed();

    // Initializes the players
    _nPlayers = 0;
    _validPlayers.clear();
    _playersPositions.clear();
    _playersOrientations.clear();
    _playersVelocities.clear();
    _playersAngularSpeeds.clear();
    _ballPossessions.clear();
    _kickEnabled.clear();
    _dribbleEnabled.clear();
    _batteryCharge.clear();
    _capacitorCharge.clear();
}

void Team::addPlayer(uint8 playerNum) {
    // Adds the player
    (void) _validPlayers.insert(playerNum, true);
    (void) _playersPositions.insert(playerNum, new Position(false,0,0,0));
    (void) _playersOrientations.insert(playerNum, new Angle(false,0));
    (void) _playersVelocities.insert(playerNum, new Velocity(false,0,0));
    (void) _playersAngularSpeeds.insert(playerNum, new AngularSpeed(false,0));
    (void) _kickEnabled.insert(playerNum, false);
    (void) _dribbleEnabled.insert(playerNum, false);
    (void) _batteryCharge.insert(playerNum, 0);
    (void) _capacitorCharge.insert(playerNum, 0);
    (void) _ballPossessions.insert(playerNum, false);
    _nPlayers++;
}

void Team::delPlayer(uint8 playerNum) {
    // Deletes the player
    (void) _validPlayers.remove(playerNum);
    (void) delete(_playersPositions[playerNum]);
    (void) delete(_playersOrientations[playerNum]);
    (void) delete(_playersVelocities[playerNum]);
    (void) delete(_playersAngularSpeeds[playerNum]);
    (void) _playersPositions.remove(playerNum);
    (void) _playersOrientations.remove(playerNum);
    (void) _playersVelocities.remove(playerNum);
    (void) _playersAngularSpeeds.remove(playerNum);
    (void) _ballPossessions.remove(playerNum);
    (void) _kickEnabled.remove(playerNum);
    (void) _dribbleEnabled.remove(playerNum);
    (void) _batteryCharge.remove(playerNum);
    (void) _capacitorCharge.remove(playerNum);
    _nPlayers--;
}

QList<uint8> Team::players() const {
    // Adds the players to the list
    QList<uint8> playersList;

    QHashIterator<uint8,Position*> it(_playersPositions);
    while (it.hasNext()) {
        playersList.append(it.next().key());
    }

    // Returns the list
    return(playersList);
}

const QString& Team::name() const {
    return(_name);
}

uint8 Team::number() const {
    return(_number);
}

void  Team::setName(const QString& teamName) {
    _name = teamName;
}

void  Team::setNumber(uint8 teamNumber) {
    _valid  = true;
    _number = teamNumber;
}

void Team::setPosition(uint8 playerNum, const Position& thePosition) {
    // Sets the player position
    if (_validPlayers.value(playerNum)) {
        (void) _playersPositions.value(playerNum)->operator =(thePosition);
    }
}

void Team::setOrientation(uint8 playerNum, const Angle& theOrientation) {
    // Sets the player orientation
    if (_validPlayers.value(playerNum)) {
        (void) _playersOrientations.value(playerNum)->operator =(theOrientation);
    }
}

void Team::setVelocity(uint8 playerNum, const Velocity& theVelocity) {
    // Sets the player velocity
    if (_validPlayers.value(playerNum)) {
        (void) _playersVelocities.value(playerNum)->operator =(theVelocity);
    }
}

void Team::setPlayerBatteryCharge(uint8 playerNum, unsigned char charge){
    // Sets the player speed
    if (_validPlayers.value(playerNum)) {
        (void) _batteryCharge.insert(playerNum, charge);
    }
}

void Team::setPlayerCapacitorCharge(uint8 playerNum, unsigned char charge){
    // Sets the player speed
    if (_validPlayers.value(playerNum)) {
        (void) _capacitorCharge.insert(playerNum, charge);
    }
}

void Team::setPlayerDribbleStatus(uint8 playerNum, bool status){
    // Sets the player speed
    if (_validPlayers.value(playerNum)) {
        (void) _dribbleEnabled.insert(playerNum, status);
    }
}

void Team::setPlayerKickStatus(uint8 playerNum, bool status){
    // Sets the player speed
    if (_validPlayers.value(playerNum)) {
        (void) _kickEnabled.insert(playerNum, status);
    }
}

void Team::setAngularSpeed(uint8 playerNum, const AngularSpeed& theAngularSpeed) {
    // Sets the player speed
    if (_validPlayers.value(playerNum)) {
        (void) _playersAngularSpeeds.value(playerNum)->operator =(theAngularSpeed);
    }
}

void Team::setBallPossession(uint8 playerNum, bool possession) {
    // Sets the flag
    if (_validPlayers.value(playerNum)) {
        (void) _ballPossessions.insert(playerNum, possession);
    }
}

const Position* Team::position(uint8 playerNum) const {
    // Returns the player position
    if (_validPlayers.value(playerNum)) {
        return(_playersPositions.value(playerNum));
    }
    // Returns an invalid position
    return(_invalidPosition);
}

const Angle* Team::orientation(uint8 playerNum) const {
    // Returns the player orientation
    if (_validPlayers.value(playerNum)) {
        return(_playersOrientations.value(playerNum));
    }
    // Returns an invalid angle
    return(_invalidAngle);
}

const Velocity* Team::velocity(uint8 playerNum) const {
    // Returns the player velocity
    if (_validPlayers.value(playerNum)) {
        return(_playersVelocities.value(playerNum));
    }
    // Returns an invalid velocity
    return(_invalidVelocity);
}

const AngularSpeed* Team::angularSpeed(uint8 playerNum) const {
    // Returns the player speed
    if (_validPlayers.value(playerNum)) {
        return(_playersAngularSpeeds.value(playerNum));
    }
    // Returns an invalid speed
    return(_invalidAngularSpeed);
}

bool Team::ballPossession(uint8 playerNum) const {
    // Returns the flag
    if (_validPlayers.value(playerNum)) {
        return(_ballPossessions.value(playerNum));
    }
    // Returns 'false'
    return(false);
}

bool Team::kickEnabled(quint8 playerNum) const{
    // Returns the flag
    if (_validPlayers.value(playerNum)) {
        return(_kickEnabled.value(playerNum));
    }
    // Returns 'false'
    return(false);
}

bool Team::dribbleEnabled(quint8 playerNum) const{
    // Returns the flag
    if (_validPlayers.value(playerNum)) {
        return(_dribbleEnabled.value(playerNum));
    }
    // Returns 'false'
    return(false);
}

unsigned char Team::batteryCharge(quint8 playerNum) const{
    // Returns the flag
    if (_validPlayers.value(playerNum)) {
        return(_batteryCharge.value(playerNum));
    }
    // Returns '0'
    return(0);
}

unsigned char Team::capacitorCharge(quint8 playerNum) const{
    // Returns the flag
    if (_validPlayers.value(playerNum)) {
        return(_capacitorCharge.value(playerNum));
    }
    // Returns '0'
    return(0);
}

bool Team::isValid() const {
    return(_valid);
}

void Team::setInvalid() {
    _valid = false;
    _validPlayers.clear();
}
