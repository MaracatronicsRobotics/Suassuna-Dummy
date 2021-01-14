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

#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <QJsonDocument>
#include <QJsonObject>
#include <QVariantMap>
#include <QString>
#include <QFile>
#include <src/utils/text/text.h>

class Constants
{
public:
    Constants(QString fileName);

    // Thread
    int threadFrequency();

    // Vision
    QString visionAddress();
    quint16 visionPort();

    // SimActuator
    QString simActuatorAddress();
    quint16 simActuatorPort();

protected:
    QVariantMap documentMap() { return _documentMap; }

private:
    // Internal file vars
    QString _fileName;
    QString _fileBuffer;
    QFile _file;

    // Internal json parse vars
    QJsonDocument _document;
    QVariantMap _documentMap;

    // Thread
    void readThreadConstants();
    int _threadFrequency;

    // Vision
    void readVisionConstants();
    QString _visionAddress;
    quint16 _visionPort;

    // SimActuator
    void readSimActuatorConstants();
    QString _simActuatorAddress;
    quint16 _simActuatorPort;
};

#endif // CONSTANTS_H
