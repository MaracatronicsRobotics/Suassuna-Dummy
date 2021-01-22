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

#include "behavior_gotolookto.h"

Behavior_GoToLookTo::Behavior_GoToLookTo() {
    _positionToGo = Position(false, 0.0, 0.0);
    _positionToLook = Position(false, 0.0, 0.0);
}

QString Behavior_GoToLookTo::name() {
    return "Behavior_GoToLookTo";
}

void Behavior_GoToLookTo::setPositionToGo(Position &positionToGo) {
    _positionToGo = positionToGo;
}

void Behavior_GoToLookTo::setPositionToLook(Position &positionToLook) {
    _positionToLook = positionToLook;
}

void Behavior_GoToLookTo::configure() {
    // Starting skills
    _skill_goTo = new Skill_GoTo();
    _skill_rotateTo = new Skill_RotateTo();

    // Adding to behavior skill list
    addSkill(SKILL_GOTO, _skill_goTo);
    addSkill(SKILL_ROTATETO, _skill_rotateTo);
}

void Behavior_GoToLookTo::run() {
    // Check if the player is at a minimum distance to the desired point and if this point is valid
    if(!_positionToGo.isInvalid() && player()->getPlayerDistanceTo(_positionToGo) > player()->getLinearError()) {
        _skill_goTo->setTargetPosition(_positionToGo);
        setSkill(SKILL_GOTO);
    }

    // Check if the player is at a minimum angle difference to the desired point and if this point is valid
    if(!_positionToLook.isInvalid() && fabs(player()->getPlayerRotateAngleTo(_positionToLook, _positionToGo)) > player()->getAngularError()) {
        _skill_rotateTo->setReferencePosition(_positionToGo);
        _skill_rotateTo->setTargetPosition(_positionToLook);
        setSkill(SKILL_ROTATETO);
    }
}
