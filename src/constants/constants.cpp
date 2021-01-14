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

#include "constants.h"

Constants::Constants(QString fileName) {
    _fileName = fileName;

    // Opening and reading file content in buffer
    _file.setFileName(_fileName);
    _file.open(QIODevice::ReadOnly | QIODevice::Text);
    _fileBuffer = _file.readAll();
    _file.close();

    // Parsing buffer to json objects
    _document = QJsonDocument::fromJson(_fileBuffer.toUtf8());
    _documentMap = _document.object().toVariantMap();

    // Read data
    readThreadConstants();
    readVisionConstants();
    readSimActuatorConstants();
}

void Constants::readThreadConstants() {
    // Taking thread mapping in json
    QVariantMap threadMap = documentMap()["Thread"].toMap();

    // Filling vars
    _threadFrequency = threadMap["threadFrequency"].toInt();
    std::cout << Text::purple("[CONSTANTS] ", true) << Text::bold("Loaded threadFrequency: " + std::to_string(_threadFrequency)) << '\n';
}

void Constants::readVisionConstants() {
    // Taking vision mapping in json
    QVariantMap visionMap = documentMap()["Vision"].toMap();

    // Filling vars
    _visionAddress = visionMap["visionAddress"].toString();
    std::cout << Text::purple("[CONSTANTS] ", true) << Text::bold("Loaded visionAddress: " + _visionAddress.toStdString()) << '\n';

    _visionPort = visionMap["visionPort"].toUInt();
    std::cout << Text::purple("[CONSTANTS] ", true) << Text::bold("Loaded visionPort: " + std::to_string(_visionPort)) << '\n';
}

void Constants::readSimActuatorConstants() {
    // Taking simActuator mapping in json
    QVariantMap visionMap = documentMap()["SimActuator"].toMap();

    // Filling vars
    _simActuatorAddress = visionMap["simActuatorAddress"].toString();
    std::cout << Text::purple("[CONSTANTS] ", true) << Text::bold("Loaded simActuatorAddress: " + _simActuatorAddress.toStdString()) << '\n';

    _simActuatorPort = visionMap["simActuatorPort"].toUInt();
    std::cout << Text::purple("[CONSTANTS] ", true) << Text::bold("Loaded simActuatorPort: " + std::to_string(_simActuatorPort)) << '\n';
}

int Constants::threadFrequency() {
    return _threadFrequency;
}

QString Constants::visionAddress() {
    return _visionAddress;
}

quint16 Constants::visionPort() {
    return _visionPort;
}

QString Constants::simActuatorAddress() {
    return _simActuatorAddress;
}

quint16 Constants::simActuatorPort() {
    return _simActuatorPort;
}
