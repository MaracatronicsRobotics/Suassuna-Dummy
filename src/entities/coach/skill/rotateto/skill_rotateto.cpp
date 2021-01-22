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

#include "skill_rotateto.h"

Skill_RotateTo::Skill_RotateTo() {
    _targetPosition = Position(false, 0.0, 0.0);
    _referencePosition = Position(false, 0.0, 0.0);
}

QString Skill_RotateTo::name() {
    return "Skill_RotateTo";
}

void Skill_RotateTo::setTargetPosition(Position &targetPosition) {
    _targetPosition = targetPosition;
}

void Skill_RotateTo::setReferencePosition(Position &referencePosition) {
    _referencePosition = referencePosition;
}

void Skill_RotateTo::configure() {

}

void Skill_RotateTo::run() {
    if(!_targetPosition.isInvalid()) {
        player()->rotateTo(_targetPosition, _referencePosition);
    }
}
