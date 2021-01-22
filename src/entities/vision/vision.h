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

#ifndef VISION_H
#define VISION_H

#include <QUdpSocket>

#include <src/entities/entity.h>
#include <src/constants/constants.h>
#include <src/utils/types/color/color.h>
#include <src/utils/types/object/object.h>
#include <include/messages_robocup_ssl_wrapper.pb.h>
#include <include/messages_robocup_ssl_detection.pb.h>
#include <include/messages_robocup_ssl_robot_status.pb.h>

class Vision : public Entity
{
    Q_OBJECT
public:
    Vision(Constants *constants);
    ~Vision();

private:
    // Entity inherited methods
    void initialization();
    void loop();
    void finalization();

    // Constants
    Constants *_constants;
    Constants* getConstants();

    // Socket for receive vision data
    QUdpSocket *_visionClient;
    void bindAndConnect();

    // Network
    QString _visionAddress;
    quint16 _visionPort;

    // Objects control
    QMap<Colors::Color, QMap<quint8, Object*>*> _playerObjects;
    Object _ballObject;
    void updatePlayer(Colors::Color teamColor, quint8 playerId, SSL_DetectionRobot player);
    void updateBall(SSL_DetectionBall ball);

    // Vision reached control
    bool *_blueControl;
    bool *_yellowControl;
    bool _ballControl;
    void clearControls();

signals:
    void sendPlayer(Colors::Color teamColor, quint8 playerId, Object playerObject);
    void sendBall(Object ballObject);
    void sendGeometryData(SSL_GeometryData geometData);
};

#endif // VISION_H
