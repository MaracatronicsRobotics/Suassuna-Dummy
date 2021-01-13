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

#include "worldmap.h"

// Includes Qt library
#include <QtCore/QtCore>

// Selects namespace
using namespace soccertypes;

WorldMap::WorldMap() {
    // Initializes the variables
    _nTeams = 0;
    _nBalls = 0;

    // Initialize empty hashes
    _validTeams.clear();
    _teams.clear();
    _validBalls.clear();
    _ballsPositions.clear();
    _ballsVelocities.clear();

    // Lockers
    _teamsLock = new QReadWriteLock();
    _ballsLock = new QReadWriteLock();
}

WorldMap::~WorldMap() {
    // Delete QReadWrite lockers
    delete _ballsLock;
    delete _teamsLock;
}

void WorldMap::receiveGeometryData(SSL_GeometryData geometData){
}

void WorldMap::receiveDetectionData(SSL_DetectionFrame detectData){
    updateBlueTeam(&detectData);
    updateYellowTeam(&detectData);
}

void WorldMap::updateBlueTeam(SSL_DetectionFrame* detectData){
    QList<quint8> recentPlayers;
    // Blue team
    if(!_validTeams.contains(Colors::BLUE)){
        addTeam(Colors::BLUE, "blue");
    }
    for(int i = 0; i < detectData->robots_blue_size(); i++){
        // Add/update player
        quint8 robotId = static_cast<quint8>(detectData->robots_blue(i).robot_id());
        addPlayer(Colors::BLUE, robotId);
        recentPlayers.append(robotId);

        // Checks if this robot has recent position data and update it
        if(detectData->robots_blue(i).has_x() && detectData->robots_blue(i).has_y()){
            Position robotPosition = Position(true, detectData->robots_blue(i).x(), detectData->robots_blue(i).y(), 0.0f);
            setPlayerPosition(Colors::BLUE, robotId, robotPosition);
        }

        // Checks if this robot has recent orientation data and update it
        if(detectData->robots_blue(i).has_orientation()){
            Angle robotOrientation = Angle(true, detectData->robots_blue(i).orientation());
            setPlayerOrientation(Colors::BLUE, robotId, robotOrientation);
        }
    }
    // Deletes players that weren't in the most recent detection packet
    deleteOldPlayers(&recentPlayers, Colors::BLUE);
}

void WorldMap::updateYellowTeam(SSL_DetectionFrame* detectData){
    QList<quint8> recentPlayers;
    // Yellow team
    if(!_validTeams.contains(Colors::YELLOW)){
        addTeam(Colors::YELLOW, "yellow");
    }
    for(int i = 0; i < detectData->robots_yellow_size(); i++){
        // Add/update player
        quint8 robotId = static_cast<quint8>(detectData->robots_yellow(i).robot_id());
        addPlayer(Colors::YELLOW, robotId);
        recentPlayers.append(robotId);

        // Checks if this robot has position data and update it in wm
        if(detectData->robots_yellow(i).has_x() && detectData->robots_yellow(i).has_y()){
            Position robotPosition = Position(true, detectData->robots_yellow(i).x(), detectData->robots_yellow(i).y(), 0.0f);
            setPlayerPosition(Colors::YELLOW, robotId, robotPosition);
        }

        // Checks if this robot has orientation data and update it in wm
        if(detectData->robots_yellow(i).has_orientation()){
            Angle robotOrientation = Angle(true, detectData->robots_yellow(i).orientation());
            setPlayerOrientation(Colors::YELLOW, robotId, robotOrientation);
        }
    }
    // Deletes players that weren't in the most recent detection packet
    deleteOldPlayers(&recentPlayers, Colors::YELLOW);
}

void WorldMap::deleteOldPlayers(QList<quint8>* recentPlayers, Colors::Color teamNum){
    QList<quint8> registeredPlayers = players(teamNum);
    QListIterator<quint8> it(registeredPlayers);
    while(it.hasNext()){
        quint8 next = it.next();
        if(!recentPlayers->contains(next)){
            delPlayer(teamNum, next);
        }
    }
}

void WorldMap::addTeam(uint8 teamNum, const QString& name) {
    _teamsLock->lockForWrite();
    // Adds the team
    (void) _teams.remove(teamNum);
    (void) _validTeams.insert(teamNum, true);
    _teams[teamNum] = Team(teamNum, name);
    _nTeams++;
    _teamsLock->unlock();
}

void WorldMap::delTeam(uint8 teamNum) {
    _teamsLock->lockForWrite();
    // Deletes the team
    (void) _validTeams.remove(teamNum);
    (void) _teams.remove(teamNum);
    _nTeams--;
    _teamsLock->unlock();
}

QList<uint8> WorldMap::teams() const {
    _teamsLock->lockForRead();
    // Adds the teams to the list
    QList<uint8> teamsList;
    QHashIterator<uint8,Team> it(_teams);
    while (it.hasNext()) {
        teamsList.append(it.next().key());
    }
    _teamsLock->unlock();

    // Returns the list
    return(teamsList);
}

const QString WorldMap::teamName(uint8 teamNum) const {
    _teamsLock->lockForRead();
    // Returns the team name
    if (_validTeams.value(teamNum)) {
        QString teamName = _teams[teamNum].name();
        _teamsLock->unlock();
        return(teamName);
    }
    _teamsLock->unlock();

    // Returns an invalid name
    return(_invalidName);
}

uint8 WorldMap::teamNumber(const QString& name) const {
    _teamsLock->lockForRead();
    // Runs the teams searching for the wanted name
    QHashIterator<uint8,Team> it(_teams);
    while (it.hasNext()) {
        it.next();
        if (it.value().name() == name) {
            uint8 teamNumber = it.value().number();
            _teamsLock->unlock();
            return(teamNumber);
        }
    }
    _teamsLock->unlock();

    // Returns an invalid number
    return(_invalidNumber);
}

void WorldMap::addBall(uint8 ballNum) {
    _ballsLock->lockForWrite();
    // Adds the ball
    (void) _validBalls.insert(ballNum, true);
    (void) _ballsPositions.insert(ballNum, new Position(false,0,0,0));
    (void) _ballsVelocities.insert(ballNum, new Velocity(false,0,0));
    _ballsLock->unlock();
}

void WorldMap::delBall(uint8 ballNum) {
    _ballsLock->lockForWrite();
    // Deletes the ball
    (void) _validBalls.remove(ballNum);
    (void) _ballsPositions.remove(ballNum);
    (void) _ballsVelocities.remove(ballNum);
    _ballsLock->unlock();
}

QList<uint8> WorldMap::balls() const {
    _ballsLock->lockForRead();
    // Adds the balls to the list
    QList<uint8> ballsList;
    QHashIterator<uint8,Position*> it(_ballsPositions);
    while (it.hasNext()) {
        ballsList.append(it.next().key());
    }
    _ballsLock->unlock();

    // Returns the list
    return(ballsList);
}

const Position WorldMap::ballPosition(uint8 ballNum) const {
    _ballsLock->lockForRead();
    // Returns the ball position
    if (_validBalls.value(ballNum)) {
        Position ballPosition = *(_ballsPositions[ballNum]);
        _ballsLock->unlock();
        return(ballPosition);
    }
    _ballsLock->unlock();

    // Returns an invalid position
    return(_invalidPosition);
}

const Velocity WorldMap::ballVelocity(uint8 ballNum) const {
    _ballsLock->lockForRead();
    // Returns the ball velocity
    if (_validBalls.value(ballNum)) {
        Velocity ballVelocity = *(_ballsVelocities[ballNum]);
        _ballsLock->unlock();
        return(ballVelocity);
    }
    _ballsLock->unlock();

    // Returns an invalid velocity
    return(_invalidVelocity);
}

void WorldMap::setBallPosition(uint8 ballNum, const Position& position) {
    _ballsLock->lockForWrite();
    // Sets the ball position
    if (_validBalls.value(ballNum)) {
        (void) _ballsPositions.value(ballNum)->operator =(position);
    }
    _ballsLock->unlock();
}

void WorldMap::setBallVelocity(uint8 ballNum, const Velocity& velocity) {
    _ballsLock->lockForWrite();
    // Sets the ball velocity
    if (_validBalls.value(ballNum)) {
        (void) _ballsVelocities.value(ballNum)->operator =(velocity);
    }
    _ballsLock->unlock();
}

void WorldMap::addPlayer(uint8 teamNum, uint8 playerNum) {
    _teamsLock->lockForWrite();
    // Adds the player
    if (_validTeams.value(teamNum)) {
        _teams[teamNum].addPlayer(playerNum);
    }
    _teamsLock->unlock();
}

void WorldMap::delPlayer(uint8 teamNum, uint8 playerNum) {
    _teamsLock->lockForWrite();
    // Deletes the player
    if (_validTeams.value(teamNum)) {
        _teams[teamNum].delPlayer(playerNum);
    }
    _teamsLock->unlock();
}

QList<uint8> WorldMap::players(uint8 teamNum) const {
    _teamsLock->lockForRead();
    // Returns the players list
    if (_validTeams.value(teamNum)) {
        QList<uint8> playersList = _teams[teamNum].players();
        _teamsLock->unlock();
        return(playersList);
    }
    _teamsLock->unlock();

    // Returns an empty list
    return(QList<uint8>());
}

const Position& WorldMap::playerPosition(uint8 teamNum, uint8 playerNum) const {
    _teamsLock->lockForRead();
    // Returns an invalid position
    if (!_validTeams.value(teamNum)) {
        _teamsLock->unlock();
        return(_invalidPosition);
    }
    _teamsLock->unlock();

    // Returns the player position
    return(*(_teams[teamNum].position(playerNum)));
}

const Angle& WorldMap::playerOrientation(uint8 teamNum, uint8 playerNum) const {
    _teamsLock->lockForRead();
    // Returns an invalid orientation
    if (!_validTeams.value(teamNum)) {
        _teamsLock->unlock();
        return(_invalidAngle);
    }
    _teamsLock->unlock();

    // Returns the player orientation
    return(*(_teams[teamNum].orientation(playerNum)));
}

const Velocity& WorldMap::playerVelocity(uint8 teamNum, uint8 playerNum) const {
    _teamsLock->lockForRead();
    // Returns an invalid velocity
    if (!_validTeams.value(teamNum)) {
        _teamsLock->unlock();
        return(_invalidVelocity);
    }
    _teamsLock->unlock();

    // Returns the player velocity
    return(*(_teams[teamNum].velocity(playerNum)));
}

const AngularSpeed& WorldMap::playerAngularSpeed(uint8 teamNum, uint8 playerNum) const {
    _teamsLock->lockForRead();
    // Returns an invalid speed
    if (!_validTeams.value(teamNum)) {
        _teamsLock->unlock();
        return(_invalidAngularSpeed);
    }
    _teamsLock->unlock();

    // Returns the player angular speed
    return(*(_teams[teamNum].angularSpeed(playerNum)));
}

bool WorldMap::ballPossession(uint8 teamNum, uint8 playerNum) const {
    _teamsLock->lockForRead();
    // Returns the flag
    if (!_validTeams.value(teamNum)) {
        _teamsLock->unlock();
        return(false);
    }
    bool ballPossesion = _teams[teamNum].ballPossession(playerNum);
    _teamsLock->unlock();

    // Returns the flag
    return(ballPossesion);
}

bool WorldMap::kickEnabled(quint8 teamNum, quint8 playerNum) const {
    _teamsLock->lockForRead();
    // Returns the flag
    if (!_validTeams.value(teamNum)) {
        _teamsLock->unlock();
        return(false);
    }
    bool kickEnabled = _teams[teamNum].kickEnabled(playerNum);
    _teamsLock->unlock();

    // Returns the flag
    return(kickEnabled);
}

bool WorldMap::dribbleEnabled(quint8 teamNum, quint8 playerNum) const {
    _teamsLock->lockForRead();
    // Returns the flag
    if (!_validTeams.value(teamNum)) {
        _teamsLock->unlock();
        return(false);
    }
    bool dribbleEnabled = _teams[teamNum].dribbleEnabled(playerNum);
    _teamsLock->unlock();

    // Returns the flag
    return(dribbleEnabled);
}

unsigned char WorldMap::batteryCharge(quint8 teamNum, quint8 playerNum) const {
    _teamsLock->lockForRead();
    // Returns the flag
    if (!_validTeams.value(teamNum)) {
        _teamsLock->unlock();
        return(false);
    }
    unsigned char batteryCharge = _teams[teamNum].batteryCharge(playerNum);
    _teamsLock->unlock();

    // Returns the flag
    return(batteryCharge);
}

unsigned char WorldMap::capacitorCharge(quint8 teamNum, quint8 playerNum) const {
    _teamsLock->lockForRead();
    // Returns the flag
    if (!_validTeams.value(teamNum)) {
        _teamsLock->unlock();
        return(false);
    }
    unsigned char capacitorCharge = _teams[teamNum].capacitorCharge(playerNum);
    _teamsLock->unlock();

    // Returns the flag
    return(capacitorCharge);
}

void WorldMap::setPlayerPosition(uint8 teamNum, uint8 playerNum, const Position& position) {
    _teamsLock->lockForWrite();
    // Sets the player position
    if (_validTeams.value(teamNum)) {
        _teams[teamNum].setPosition(playerNum, position);
    }
    _teamsLock->unlock();
}

void WorldMap::setPlayerOrientation(uint8 teamNum, uint8 playerNum, const Angle& orientation) {
    _teamsLock->lockForWrite();
    // Sets the player orientation
    if (_validTeams.value(teamNum)) {
        _teams[teamNum].setOrientation(playerNum, orientation);
    }
    _teamsLock->unlock();
}

void WorldMap::setPlayerVelocity(uint8 teamNum, uint8 playerNum, const Velocity& velocity) {
    _teamsLock->lockForWrite();
    // Sets the player velocity
    if (_validTeams.value(teamNum)) {
        _teams[teamNum].setVelocity(playerNum, velocity);
    }
    _teamsLock->unlock();
}

void WorldMap::setPlayerAngularSpeed(uint8 teamNum, uint8 playerNum, const AngularSpeed& angularSpeed) {
    _teamsLock->lockForWrite();
    // Sets the player angular speed
    if (_validTeams.value(teamNum)) {
        _teams[teamNum].setAngularSpeed(playerNum, angularSpeed);
    }
    _teamsLock->unlock();
}

void WorldMap::setBallPossession(uint8 teamNum, uint8 playerNum, bool possession) {
    _teamsLock->lockForWrite();
    // Sets the flag
    if (_validTeams.value(teamNum)) {
        _teams[teamNum].setBallPossession(playerNum, possession);
    }
    _teamsLock->unlock();
}

void WorldMap::setKickEnabled(uint8 teamNum, uint8 playerNum, bool status){
    _teamsLock->lockForWrite();
    // Sets the flag
    if (_validTeams.value(teamNum)) {
        _teams[teamNum].setPlayerKickStatus(playerNum, status);
    }
    _teamsLock->unlock();
}

void WorldMap::setDribbleEnabled(uint8 teamNum, uint8 playerNum, bool status){
    _teamsLock->lockForWrite();
    // Sets the flag
    if (_validTeams.value(teamNum)) {
        _teams[teamNum].setPlayerDribbleStatus(playerNum, status);
    }
    _teamsLock->unlock();
}

void WorldMap::setBatteryCharge(uint8 teamNum, uint8 playerNum, unsigned char charge){
    _teamsLock->lockForWrite();
    // Sets the flag
    if (_validTeams.value(teamNum)) {
        _teams[teamNum].setPlayerBatteryCharge(playerNum, charge);
    }
    _teamsLock->unlock();
}

void WorldMap::setCapacitorCharge(uint8 teamNum, uint8 playerNum, unsigned char charge){
    _teamsLock->lockForWrite();
    // Sets the flag
    if (_validTeams.value(teamNum)) {
        _teams[teamNum].setPlayerCapacitorCharge(playerNum, charge);
    }
    _teamsLock->unlock();
}
