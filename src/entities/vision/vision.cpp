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

#include <include/messages_robocup_ssl_wrapper.pb.h>
#include <include/messages_robocup_ssl_detection.pb.h>
#include <src/utils/text/text.h>

Vision::Vision(QString visionAddress, quint16 visionPort) : Entity(ENT_VISION) {
    // Creating socket and setting network data
    _visionClient = new QUdpSocket(this);
    _visionAddress = visionAddress;
    _visionPort = visionPort;

    // Bind and connect socket in network
    bindAndConnect();
}

Vision::~Vision() {
    // Closing and deleting socket
    if(_visionClient->isOpen()) {
        _visionClient->close();
    }

    delete _visionClient;
}

void Vision::initialization() {
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
    if(_visionClient->bind(QHostAddress(_visionAddress), _visionPort, QUdpSocket::ShareAddress) == false) {
        std::cout << Text::cyan("[VISION] " , true) << Text::red("Error while binding socket.", true) << '\n';
        return ;
    }

    if(_visionClient->joinMulticastGroup(QHostAddress(_visionAddress)) == false) {
        std::cout << Text::cyan("[VISION] ", true) << Text::red("Error while joining multicast.", true) << '\n';
        return ;
    }
}
