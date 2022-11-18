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

#include "skill_idle.h"

#include <src/entities/player/player.h>

Skill_Idle::Skill_Idle() {

}

void Skill_Idle::configure() {

}

void Skill_Idle::run() {
    Armorial::Velocity velocity; velocity.set_vx(0.0); velocity.set_vy(0.0);
    Armorial::AngularSpeed angularSpeed; angularSpeed.set_vw(0.0);
    Armorial::KickSpeed kickSpeed; kickSpeed.set_chipangle(0.0); kickSpeed.set_kickangle(0.0); kickSpeed.set_kickspeed(0.0);

    setLinearSpeed(velocity);
    setAngularSpeed(angularSpeed);
    setKick(kickSpeed);
    setDribble(false);
}
