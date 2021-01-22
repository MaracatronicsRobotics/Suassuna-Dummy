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

#include "player.h"

#include <src/entities/coach/role/role.h>

Player::Player(quint8 playerId, Constants *constants, WorldMap *worldMap) : Entity(ENT_PLAYER) {
    _playerId = playerId;
    _constants = constants;
    _worldMap = worldMap;
    _playerRole = nullptr;
}

WorldMap* Player::getWorldMap() {
    if(_worldMap == nullptr) {
        std::cout << Text::red("[ERROR] ", true) << Text::bold("WorldMap with nullptr value at Player") + '\n';
    }
    else {
        return _worldMap;
    }

    return nullptr;
}

quint8 Player::playerId() {
    return _playerId;
}

Position Player::position() {
    Position playerPos = getWorldMap()->getPlayer(getConstants()->teamColor(), playerId()).getPosition();
    return playerPos;
}

Angle Player::orientation() {
    Angle playerAngle = getWorldMap()->getPlayer(getConstants()->teamColor(), playerId()).getOrientation();
    return playerAngle;
}

void Player::setRole(Role *role) {
    _mutexRole.lock();
    _playerRole = role;
    _mutexRole.unlock();
}

float Player::getPlayerRotateAngleTo(Position &targetPosition, Position &referencePosition) {
    float componentX = (targetPosition.x() - referencePosition.x());
    float componentY = (targetPosition.y() - referencePosition.y());
    float distToTarget = sqrt(pow(componentX, 2) + pow(componentY, 2));

    componentX = componentX / distToTarget;

    // Check possible divisions for 0
    if(isnanf(componentX)) {
        return 0.0f;
    }

    float angleOriginToTarget; // Angle from field origin to targetPosition
    float angleRobotToTarget;  // Angle from robot to targetPosition

    if(componentY < 0.0f) {
        angleOriginToTarget = 2*M_PI - acos(componentX); // Angle that the target make with x-axis to robot
    } else {
        angleOriginToTarget = acos(componentX); // Angle that the target make with x-axis to robot
    }

    angleRobotToTarget = angleOriginToTarget - orientation().value();

    // Adjusting to rotate the minimum possible
    if(angleRobotToTarget > M_PI) angleRobotToTarget -= 2.0 * M_PI;
    if(angleRobotToTarget < -M_PI) angleRobotToTarget += 2.0 * M_PI;

    return angleRobotToTarget;
}

float Player::getPlayerDistanceTo(Position &targetPosition) {
    return sqrt(pow(position().x() - targetPosition.x(), 2) + pow(position().y() - targetPosition.y(), 2));
}

float Player::getLinearError() {
    return 0.05f; // 5cm
}

float Player::getAngularError() {
    return 0.02f; // ~= 1.15 deg
}

void Player::goTo(Position &targetPosition) {
    Position playerPosition = position();

    float dx = (targetPosition.x() - playerPosition.x());
    float dy = (targetPosition.y() - playerPosition.y());
    float vxSaida = (dx * cos(orientation().value()) + dy * sin(orientation().value()));
    float vySaida = (dy * cos(orientation().value()) - dx * sin(orientation().value()));

    emit setLinearSpeed(getConstants()->teamColor(), playerId(), vxSaida, vySaida);
}

void Player::rotateTo(Position &targetPosition, Position referencePosition) {
    // If no reference position is defined, use the player position
    if(referencePosition.isInvalid()) {
        referencePosition = position();
    }

    float angleRobotToTarget = getPlayerRotateAngleTo(targetPosition, referencePosition);

    emit setAngularSpeed(getConstants()->teamColor(), playerId(), angleRobotToTarget);
}

void Player::idle() {
    emit setLinearSpeed(getConstants()->teamColor(), playerId(), 0.0, 0.0);
    emit setAngularSpeed(getConstants()->teamColor(), playerId(), 0.0);
}

void Player::initialization() {
    QString teamColorName = getConstants()->teamColorName().toUpper();
    std::cout << Text::cyan("[PLAYER " + teamColorName.toStdString() + ":" + std::to_string(playerId()) + "] ", true) + Text::bold("Thread started.") + '\n';
}

void Player::loop() {
    if(position().isInvalid()) {
        setRole(nullptr);
        idle();
    }
    else {
        _mutexRole.lock();
        if(_playerRole != nullptr) {
            if(!_playerRole->isInitialized()) {
                _playerRole->initialize(getConstants());
            }
            _playerRole->setPlayer(this);
            _playerRole->runRole();
        }
        _mutexRole.unlock();
    }
}

void Player::finalization() {
    QString teamColorName = getConstants()->teamColorName().toUpper();
    std::cout << Text::cyan("[PLAYER " + teamColorName.toStdString() + ":" + std::to_string(playerId()) + "] ", true) + Text::bold("Thread ended.") + '\n';
}

Constants* Player::getConstants() {
    if(_constants == nullptr) {
        std::cout << Text::red("[ERROR] ", true) << Text::bold("Constants with nullptr value at Player") + '\n';
    }
    else {
        return _constants;
    }

    return nullptr;
}
