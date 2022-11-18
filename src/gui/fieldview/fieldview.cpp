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

#include "fieldview.h"

#include <spdlog/spdlog.h>

FieldView::FieldView(const Common::Types::Field& field, const QString& centralLogoPath, QWidget *parent) : Common::Widgets::FieldView(field, centralLogoPath, parent) {
    this->setupIdSize(60);
}

void FieldView::draw() {
    _drawMutex.lock();

    // Draw field lines
    drawFieldLines();

    // Draw received balls
    for(auto it = _balls.begin(); it != _balls.end(); it++) {
        if((*it).ballposition().isinvalid()) {
            continue;
        }

        drawBall((*it).ballposition());
    }

    // Draw received robots
    for(auto it = _robots.begin(); it != _robots.end(); it++) {
        if((*it).robotposition().isinvalid()) {
            continue;
        }

        const Common::Enums::Color robotTeamColor = ((*it).robotidentifier().robotcolor().isblue()) ? Common::Enums::BLUE : Common::Enums::YELLOW;
        const Armorial::Position robotPosition = (*it).robotposition();
        drawRobot(Geometry::Vector2D(robotPosition.x(), robotPosition.y()), (*it).robotorientation().value(), robotTeamColor, (*it).robotidentifier().robotid());
    }

    _drawMutex.unlock();
}

void FieldView::updateBalls(const QList<Armorial::Ball> &balls) {
    _drawMutex.lock();
    _balls = balls;
    _drawMutex.unlock();
}

void FieldView::updateRobots(const QList<Armorial::Robot> &robots) {
    _drawMutex.lock();
    _robots = robots;
    _drawMutex.unlock();
}

void FieldView::updateFieldGeometry(const Common::Types::Field &field) {
    _drawMutex.lock();
    setupFieldGeometry(field);
    resetView();
    _drawMutex.unlock();
}
