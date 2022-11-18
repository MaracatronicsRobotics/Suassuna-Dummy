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

#include <spdlog/spdlog.h>
#include <spdlog/fmt/bundled/color.h>

#define MAX_TIME_TO_MARK_AS_IDLE 1.0 // 1 second

Player::Player(const quint8& playerId, const Common::Enums::Color& teamColor, Controller* controller) {
    // Setup internal objects and modules
    _playerId = playerId;
    _teamColor = teamColor;
    _controller = controller;

    // Setup idle control
    _firstIt = false;
    _idleTimer.start();
}

Common::Enums::Color Player::teamColor() {
    return _teamColor;
}

quint8 Player::playerId() {
    return _playerId;
}

void Player::updatePlayer(Common::Types::Object playerData) {
    setPosition(playerData.getPosition());
    setVelocity(playerData.getVelocity());
    setAcceleration(playerData.getAcceleration());
    setOrientation(playerData.getOrientation());
    setAngularSpeed(playerData.getAngularSpeed());

    _idleTimer.start();
}

void Player::idle() {
    Armorial::Velocity velocity; velocity.set_vx(0.0); velocity.set_vy(0.0);
    Armorial::AngularSpeed angularSpeed; angularSpeed.set_vw(0.0);
    Armorial::KickSpeed kickSpeed; kickSpeed.set_chipangle(0.0); kickSpeed.set_kickangle(0.0); kickSpeed.set_kickspeed(0.0);

    _controller->setLinearSpeed(playerId(), velocity);
    _controller->setAngularSpeed(playerId(), angularSpeed);
    _controller->setKick(playerId(), kickSpeed);
    _controller->setDribble(playerId(), false);
}

void Player::initialization() {
    spdlog::info("[{}] Thread started.", fmt::format(fmt::fg(teamColor() == Common::Enums::Color::BLUE ? fmt::terminal_color::blue : fmt::terminal_color::yellow) | fmt::emphasis::bold, entityName().toStdString() + " " + std::to_string(playerId())));
}

void Player::loop() {
    // Check if player is idle (not received updated data from him for a long time)
    if(_idleTimer.getSeconds() >= MAX_TIME_TO_MARK_AS_IDLE || _firstIt) {
        _firstIt = false;
        idle();
    }
    else {
        idle();
    }
}

void Player::finalization() {
    spdlog::info("[{}] Thread ended.", fmt::format(fmt::fg(teamColor() == Common::Enums::Color::BLUE ? fmt::terminal_color::blue : fmt::terminal_color::yellow) | fmt::emphasis::bold, entityName().toStdString() + " " + std::to_string(playerId())));
}
