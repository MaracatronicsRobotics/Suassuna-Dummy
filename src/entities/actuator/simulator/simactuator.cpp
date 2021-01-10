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

#include "simactuator.h"

#include <math.h>
#include <src/utils/text/text.h>

SimActuator::SimActuator(QString actuatorAddress, quint16 actuatorPort) {
    _actuatorAddress = actuatorAddress;
    _actuatorPort = actuatorPort;
}

void SimActuator::initialization() {
    connectToNetwork();
    std::cout << Text::cyan("[ACTUATOR] ", true) << Text::bold("Started at address '" + _actuatorAddress.toStdString() + "' and port '" + std::to_string(_actuatorPort) + "'.") << '\n';
}

void SimActuator::loop() {
    for(int i = 0; i < QT_TEAMS; i++) {
        for(int j = 0; j < QT_PLAYERS; j++) {
            _dataMutex.lockForRead();
            if(!_robotData[i][j].isUpdated) {
                sendData(_robotData[i][j]);
                _robotData[i][j].isUpdated = true;
            }
            _dataMutex.unlock();
        }
    }
}

void SimActuator::finalization() {
    finishConnection();
    std::cout << Text::cyan("[ACTUATOR] " , true) << Text::bold("Client finished.") << '\n';
}

void SimActuator::connectToNetwork() {
    _actuatorClient = new QUdpSocket();

    if(_actuatorClient->isOpen()) {
        _actuatorClient->close();
    }

    _actuatorClient->connectToHost(_actuatorAddress, _actuatorPort, QIODevice::WriteOnly, QAbstractSocket::IPv4Protocol);
}

void SimActuator::finishConnection() {
    if(_actuatorClient->isOpen()) {
        _actuatorClient->close();
    }

    delete _actuatorClient;
}

void SimActuator::sendData(robotData data) {
    // Creating packet
    grSim_Packet packet;

    // Setting macro informations (team and timestamp)
    packet.mutable_commands()->set_isteamyellow(data.isYellow);
    packet.mutable_commands()->set_timestamp(0.0);

    // Creating robot commands (vel, kick, dribble)
    grSim_Robot_Command *command = packet.mutable_commands()->add_robot_commands();

    // Setting commands
    // Player id
    command->set_id(data.playerId);

    // Player velocity
    command->set_wheelsspeed(false);
    command->set_veltangent(data.vx);
    command->set_velnormal(data.vy);
    command->set_velangular(data.vw);

    // Player kick speed
    command->set_kickspeedx(data.kickPowerX);
    command->set_kickspeedz(data.kickPowerZ);

    // Player dribble
    command->set_spinner(data.dribbling);

    // Sending data to simulator
    std::string buffer;
    packet.SerializeToString(&buffer);
    if(_actuatorClient->write(buffer.c_str(), buffer.length()) == -1) {
        std::cout << Text::cyan("[ACTUATOR] " , true) << Text::red("Failed to write to socket: ", true) << Text::red(_actuatorClient->errorString().toStdString(), true) << '\n';
    }
}

void SimActuator::setSpeed(int teamId, int playerId, float vx, float vy, float vw) {
    _dataMutex.lockForWrite();
    _robotData[teamId][playerId].vx = vx;
    _robotData[teamId][playerId].vy = vy;
    _robotData[teamId][playerId].vw = vw;
    _robotData[teamId][playerId].isUpdated = false;
    _dataMutex.unlock();
}

void SimActuator::dribble(int teamId, int playerId, bool enable) {
    _dataMutex.lockForWrite();
    _robotData[teamId][playerId].dribbling = enable;
    _robotData[teamId][playerId].isUpdated = false;
    _dataMutex.unlock();
}

void SimActuator::kick(int teamId, int playerId, float power) {
    _dataMutex.lockForWrite();
    _robotData[teamId][playerId].kickPowerX = power;
    _robotData[teamId][playerId].isUpdated = false;
    _dataMutex.unlock();
}

void SimActuator::chipKick(int teamId, int playerId, float power) {
    _dataMutex.lockForWrite();
    _robotData[teamId][playerId].kickPowerX = power * cos(0.42262189947);
    _robotData[teamId][playerId].kickPowerZ = power * sin(0.42262189947);
    _robotData[teamId][playerId].isUpdated = false;
    _dataMutex.unlock();
}
