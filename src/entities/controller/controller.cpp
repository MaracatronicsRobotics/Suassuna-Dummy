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

#include "controller.h"

#include <spdlog/spdlog.h>

#include <src/constants/constants.h>

Controller::Controller(QString serviceAddress, quint16 servicePort) : Base::GRPC::Client<Armorial::Actuator::ActuatorService>(serviceAddress, servicePort) {
    //
}

void Controller::setLinearSpeed(const quint8 &playerId, const Armorial::Velocity &linearSpeed) {
    if(!_controlPackets.contains(playerId)) setupDefaultPacket(playerId);

    _mutex.lock();
    Armorial::Velocity* velocity = new Armorial::Velocity(); velocity->CopyFrom(linearSpeed);
    _controlPackets[playerId].set_allocated_robotvelocity(velocity);
    _mutex.unlock();
}

void Controller::setAngularSpeed(const quint8& playerId, const Armorial::AngularSpeed& angularSpeed) {
    if(!_controlPackets.contains(playerId)) setupDefaultPacket(playerId);

    _mutex.lock();
    Armorial::AngularSpeed* angSpeed = new Armorial::AngularSpeed(); angSpeed->CopyFrom(angularSpeed);
    _controlPackets[playerId].set_allocated_robotangularspeed(angSpeed);
    _mutex.unlock();
}

void Controller::setKick(const quint8& playerId, const Armorial::KickSpeed& kickSpeed) {
    if(!_controlPackets.contains(playerId)) setupDefaultPacket(playerId);

    _mutex.lock();
    Armorial::KickSpeed* kickData = new Armorial::KickSpeed(); kickData->CopyFrom(kickSpeed);
    _controlPackets[playerId].set_allocated_robotkick(kickData);
    _mutex.unlock();
}

void Controller::setDribble(const quint8& playerId, const bool& dribbling) {
    if(!_controlPackets.contains(playerId)) setupDefaultPacket(playerId);

    _mutex.lock();
    _controlPackets[playerId].set_dribbling(dribbling);
    _mutex.unlock();
}

void Controller::setupDefaultPacket(const quint8 &playerId) {
    _mutex.lock();
    _controlPackets[playerId] = Armorial::ControlPacket();
    Armorial::Color *teamColor = new Armorial::Color(); teamColor->set_isblue(Constants::teamColor() == Common::Enums::Color::BLUE);
    Armorial::RobotIdentifier *robotIdentifier = new Armorial::RobotIdentifier(); robotIdentifier->set_allocated_robotcolor(teamColor); robotIdentifier->set_robotid(playerId);
    _controlPackets[playerId].set_allocated_robotidentifier(robotIdentifier);
    _mutex.unlock();
}

void Controller::initialization() {
    // Try to connect to server
    if(connectToServer(true)) {
        spdlog::info("[{}] Connected to actuator service at address '{}' and port '{}'.", clientName().toStdString(), getServiceAddress().toStdString(), getServicePort());
    }
    else {
        spdlog::error("[{}] Failed to connect to actuator service at address '{}' and port '{}'.", clientName().toStdString(), getServiceAddress().toStdString(), getServicePort());
        return ;
    }
}

void Controller::loop() {
    // Check if is disconnected from server and try to reconnect
    if(!isConnectedToServer()) {
        spdlog::warn("[{}] Disconnected from actuator service, trying to reconnect...", clientName().toStdString());
        bool couldReconnect = connectToServer(true);

        if(couldReconnect) {
            spdlog::info("[{}] Succesfully recconected to actuator service at address '{}' and port '{}'.", clientName().toStdString(), getServiceAddress().toStdString(), getServicePort());
        }
        else {
            spdlog::warn("[{}] Reconnection attempt to actuator service at address '{}' and port '{}' failed.", clientName().toStdString(), getServiceAddress().toStdString(), getServicePort());
            return ;
        }
    }

    // Loop over the packets and send them forward to actuator
    _mutex.lock();

    // Get updated players
    QList<quint8> updatedPlayers = _controlPackets.keys();

    // If list is not empty, it means that at least one player has sent new control packets... so send them through network
    if(!updatedPlayers.isEmpty()) {
        // Create default data transfer objects
        grpc::ClientContext context;
        google::protobuf::Empty request;
        std::unique_ptr<grpc::ClientWriter<Armorial::ControlPacket>> writer = getStub()->SetControls(&context, &request);

        // Send packet for updated players
        for(const auto& pkt : _controlPackets) {
            writer->Write(pkt);
        }
    }

    // Reset list of received packets
    _controlPackets.clear();

    _mutex.unlock();
}

void Controller::finalization() {
    spdlog::info("[{}] Disconnected from actuator service.", clientName().toStdString());
}
