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
}

Vision::~Vision() {
    // Closing and deleting socket
    if(_visionClient->isOpen()) {
        _visionClient->close();
    }

    delete _visionClient;
}

void Vision::initialization() {
    // Bind and connect socket in network
    bindAndConnect();

    std::cout << Text::cyan("[VISION] ", true) << Text::bold("Started at address '" + _visionAddress.toStdString() + "' and port '" + std::to_string(_visionPort) + "'.") << '\n';
}

void Vision::loop() {
    while(_visionClient->hasPendingDatagrams()) {
        // Creating auxiliary vars
        SSL_WrapperPacket wrapperData;
        char *buffer = new char[65535];
        long long int packetLength = 0;

        // Reading upcoming packet and parsing it to protobuf
        packetLength = _visionClient->readDatagram(buffer, 65535);
        if(wrapperData.ParseFromArray(buffer, int(packetLength)) == false) {
            std::cout << Text::cyan("[VISION] ", true) << Text::red("Wrapper packet parsing error.", true) << '\n';
            continue;
        }

        // Debug vision frame
        if(wrapperData.has_detection()) {
            SSL_DetectionFrame visionFrame = wrapperData.detection();
            emit sendDetectData(visionFrame);

            std::cout << "CAMERA " << visionFrame.camera_id() << '\n';
            std::cout << "======================= " << '\n';
            std::cout << "BLUE TEAM" << '\n';
            for(int i = 0; i < visionFrame.robots_blue_size(); i++) {
                std::cout << "BLUE " << visionFrame.robots_blue(i).robot_id() << '\n';
                std::cout << "x: " << visionFrame.robots_blue(i).x() << " / y: " << visionFrame.robots_blue(i).y() << '\n';
                std::cout << "ori: " << visionFrame.robots_blue(i).orientation() << '\n';
            }
            std::cout << "======================= " << '\n';
            std::cout << "YELLOW TEAM" << '\n';
            for(int i = 0; i < visionFrame.robots_yellow_size(); i++) {
                std::cout << "YELLOW " << visionFrame.robots_yellow(i).robot_id() << '\n';
                std::cout << "x: " << visionFrame.robots_yellow(i).x() << " / y: " << visionFrame.robots_yellow(i).y() << '\n';
                std::cout << "ori: " << visionFrame.robots_yellow(i).orientation() << '\n';
            }
            std::cout << "======================= " << '\n';
        }

        // Debug geometry data
        if(wrapperData.has_geometry()) {
            SSL_GeometryData geomData = wrapperData.geometry();
            //emit sendGeometData(geomData);

            std::cout << "GEOMETRY" << '\n';
            std::cout << "======================= " << '\n';
            std::cout << "FIELD DIMENSIONS" << '\n';
            std::cout << "field_length: " << geomData.field().field_length() << '\n';
            std::cout << "field_width: " << geomData.field().field_width() << '\n';
            std::cout << "boundary_width: " << geomData.field().boundary_width() << '\n';
            std::cout << "goal_width: " << geomData.field().goal_width() << '\n';
            std::cout << "goal_depth: " << geomData.field().goal_depth() << '\n';
            std::cout << "field_lines_size: " << geomData.field().field_lines_size() << '\n';
            std::cout << "field_arcs_size: " << geomData.field().field_arcs_size() << '\n';
            std::cout << "======================= " << '\n';
        }
        delete[] buffer;
    }
}

void Vision::finalization() {
    std::cout << Text::cyan("[VISION] " , true) << Text::bold("Client finished.") << '\n';
}

void Vision::bindAndConnect() {
    // Creating socket
    _visionClient = new QUdpSocket();

    // Binding in defined network
    if(_visionClient->bind(QHostAddress(_visionAddress), _visionPort, QUdpSocket::ShareAddress) == false) {
        std::cout << Text::cyan("[VISION] " , true) << Text::red("Error while binding socket.", true) << '\n';
        return ;
    }

    // Joining multicast group
    if(_visionClient->joinMulticastGroup(QHostAddress(_visionAddress)) == false) {
        std::cout << Text::cyan("[VISION] ", true) << Text::red("Error while joining multicast.", true) << '\n';
        return ;
    }
}

Constants* Vision::getConstants() {
    if(_constants == nullptr) {
        std::cout << Text::red("[ERROR] ", true) << Text::bold("Constants with nullptr value at Vision") << '\n';
    }
    else {
        return _constants;
    }

    return nullptr;
}
