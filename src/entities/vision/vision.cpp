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

#include "vision.h"
#include <src/utils/text/text.h>

Vision::Vision(Constants *constants) : Entity(ENT_VISION) {
    // Taking constants
    _constants = constants;

    // Taking network data from constants
    _visionAddress = getConstants()->visionAddress();
    _visionPort = getConstants()->visionPort();

    // Allocating memory to control vectors
    _blueControl = (bool *) malloc(getConstants()->qtPlayers() * sizeof(bool));
    _yellowControl = (bool *) malloc(getConstants()->qtPlayers() * sizeof(bool));
}

Vision::~Vision() {
    // Closing socket
    if(_visionClient->isOpen()) {
        _visionClient->close();
    }

    // Deleting vision client
    delete _visionClient;

    // Delete controls
    free(_blueControl);
    free(_yellowControl);

    // Get teams list
    QList<Colors::Color> teamList = _playerObjects.keys();

    // For each team
    for(QList<Colors::Color>::iterator it = teamList.begin(); it != teamList.end(); it++) {
        // Take team associated objects
        QMap<quint8, Object*> *teamObjects = _playerObjects.value((*it));
        QList<Object*> objects = teamObjects->values();

        // For each object, delete it
        for(QList<Object*>::iterator it2 = objects.begin(); it2 != objects.end(); it2++) {
            delete (*it2);
        }

        // Clear team association
        teamObjects->clear();

        // Delete pointer
        delete teamObjects;
    }

    // Clear teams
    _playerObjects.clear();
}

void Vision::initialization() {
    // Bind and connect socket in network
    bindAndConnect();

    std::cout << Text::cyan("[VISION] ", true) + Text::bold("Started at address '" + _visionAddress.toStdString() + "' and port '" + std::to_string(_visionPort) + "'.") + '\n';
}

void Vision::loop() {
    while(_visionClient->hasPendingDatagrams()) {
        // Creating auxiliary vars
        SSL_WrapperPacket wrapperData;
        QNetworkDatagram datagram;

        // Receiving datagram
        datagram = _visionClient->receiveDatagram();

        // Check if it is valid
        if(!datagram.isValid()) {
            continue;
        }

        // Parse to protobuf
        if(wrapperData.ParseFromArray(datagram.data().data(), datagram.data().size()) == false) {
            std::cout << Text::cyan("[VISION] ", true) << Text::red("Wrapper packet parsing error.", true) + '\n';
            continue;
        }

        // Debug vision frame
        if(wrapperData.has_detection()) {
            SSL_DetectionFrame visionFrame = wrapperData.detection();

            // Clear vision controls
            clearControls();

            // For ball (always take first)
            if(visionFrame.balls_size() > 0) {
                _ballControl = true;
                updateBall(visionFrame.balls(0));
            }

            // For blue team
            for(int i = 0; i < visionFrame.robots_blue_size(); i++) {
                // Mark as reached
                _blueControl[visionFrame.robots_blue(i).robot_id()] = true;

                // Take player and update
                SSL_DetectionRobot robot = visionFrame.robots_blue(i);
                updatePlayer(Colors::Color::BLUE, robot.robot_id(), robot);
            }

            // For yellow team
            for(int i = 0; i < visionFrame.robots_yellow_size(); i++) {
                // Mark as reached
                _yellowControl[visionFrame.robots_yellow(i).robot_id()] = true;

                // Take player and update
                SSL_DetectionRobot robot = visionFrame.robots_yellow(i);
                updatePlayer(Colors::Color::YELLOW, robot.robot_id(), robot);
            }

            // Updating filters for players that don't appeared
            for(int i = 0; i < getConstants()->qtPlayers(); i++) {
                // Blue
                if(_blueControl[i] == false) {
                    // Check if team is registered in map
                    if(!_playerObjects.contains(Colors::Color::BLUE)) {
                        _playerObjects.insert(Colors::Color::BLUE, new QMap<quint8, Object*>());
                    }

                    // Take team map
                    QMap<quint8, Object*> *teamMap = _playerObjects.value(Colors::Color::BLUE);

                    // Check if teamMap has the required player
                    if(!teamMap->contains(i)) {
                        teamMap->insert(i, new Object());
                    }

                    // Take object
                    Object* bluePlayerObject = teamMap->value(i);
                    bluePlayerObject->updateObject(0.0f, Position(false, 0.0f, 0.0f));
                    emit sendPlayer(Colors::Color::BLUE, i, *bluePlayerObject);
                }

                // Yellow
                if(_yellowControl[i] == false) {
                    // Check if team is registered in map
                    if(!_playerObjects.contains(Colors::Color::YELLOW)) {
                        _playerObjects.insert(Colors::Color::YELLOW, new QMap<quint8, Object*>());
                    }

                    // Take team map
                    QMap<quint8, Object*> *teamMap = _playerObjects.value(Colors::Color::YELLOW);

                    // Check if teamMap has the required player
                    if(!teamMap->contains(i)) {
                        teamMap->insert(i, new Object());
                    }

                    // Take object
                    Object* yellowPlayerObject = teamMap->value(i);

                    yellowPlayerObject->updateObject(0.0f, Position(false, 0.0, 0.0));
                    emit sendPlayer(Colors::Color::YELLOW, i, *yellowPlayerObject);
                }

                // Ball
                if(_ballControl == false) {
                    _ballObject.updateObject(0.0f, Position(false, 0.0, 0.0));
                    emit sendBall(_ballObject);
                }
            }
        }
        // Debug geometry data
        if(wrapperData.has_geometry() && getConstants()->useGeometryFromCamera()) {
            SSL_GeometryData geomData = wrapperData.geometry();
            emit sendGeometryData(geomData);
        }
    }
}

void Vision::finalization() {
    std::cout << Text::cyan("[VISION] " , true) + Text::bold("Client finished.") + '\n';
}

void Vision::clearControls() {
    for(int i = 0; i < getConstants()->qtPlayers(); i++) {
        _blueControl[i] = false;
        _yellowControl[i] = false;
    }
    _ballControl = false;
}

void Vision::updatePlayer(Colors::Color teamColor, quint8 playerId, SSL_DetectionRobot player) {
    // Check if team is registered in map
    if(!_playerObjects.contains(teamColor)) {
        _playerObjects.insert(teamColor, new QMap<quint8, Object*>());
    }

    // Take team map
    QMap<quint8, Object*> *teamMap = _playerObjects.value(teamColor);

    // Check if teamMap has the required player
    if(!teamMap->contains(playerId)) {
        teamMap->insert(playerId, new Object());
    }

    // Take object
    Object* playerObject = teamMap->value(playerId);

    // Update
    playerObject->updateObject(player.confidence(), Position(true, player.x()/1000.0, player.y()/1000.0), Angle(true, player.orientation()));

    // Emit updated object
    emit sendPlayer(teamColor, playerId, *playerObject);
}

void Vision::updateBall(SSL_DetectionBall ball) {
    // Update
    _ballObject.updateObject(ball.confidence(), Position(true, ball.x()/1000.0, ball.y()/1000.0));

    // Emit updated object
    emit sendBall(_ballObject);
}

void Vision::bindAndConnect() {
    // Creating socket
    _visionClient = new QUdpSocket();

    // Binding in defined network
    if(_visionClient->bind(QHostAddress(_visionAddress), _visionPort, QUdpSocket::ShareAddress) == false) {
        std::cout << Text::cyan("[VISION] " , true) << Text::red("Error while binding socket.", true) + '\n';
        return ;
    }

    // Joining multicast group
    if(_visionClient->joinMulticastGroup(QHostAddress(_visionAddress)) == false) {
        std::cout << Text::cyan("[VISION] ", true) << Text::red("Error while joining multicast.", true) + '\n';
        return ;
    }
}

Constants* Vision::getConstants() {
    if(_constants == nullptr) {
        std::cout << Text::red("[ERROR] ", true) << Text::bold("Constants with nullptr value at Vision") + '\n';
    }
    else {
        return _constants;
    }

    return nullptr;
}
