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

#include "entity.h"

Entity::Entity(EntityType type) {
    _entityType = type;
    _entityPriority = 0; // default priority is 0
    _loopFrequency = 60; // default loop frequency is 60
    _isEnabled = true;   // enabling by default
}

void Entity::run(){
    initialization();

    while(isEnabled()) {
        startTimer();
        if(isEnabled()) {
            loop();
        }
        stopTimer();

        long rest = getRemainingTime();
        if(rest >= 0) {
            msleep(rest);
        }
    }

    finalization();
}

void Entity::setLoopFrequency(int hz) {
    _mutexLoopTime.lock();
    _loopFrequency = hz;
    _mutexLoopTime.unlock();
}

void Entity::setPriority(int priority) {
    _mutexPriority.lock();
    _entityPriority = priority;
    _mutexPriority.unlock();
}

void Entity::enableEntity() {
    _mutexEnabled.lock();
    _isEnabled = true;
    _mutexEnabled.unlock();
}

void Entity::stopEntity() {
    _mutexEnabled.lock();
    _isEnabled = false;
    _mutexEnabled.unlock();
}

int Entity::loopFrequency() {
    _mutexLoopTime.lock();
    int loopFrequency = _loopFrequency;
    _mutexLoopTime.unlock();

    return loopFrequency;
}

int Entity::entityPriority() {
    _mutexPriority.lock();
    int entityPriority = _entityPriority;
    _mutexPriority.unlock();

    return entityPriority;
}

bool Entity::isEnabled() {
    _mutexEnabled.lock();
    bool isEnabled = _isEnabled;
    _mutexEnabled.unlock();

    return isEnabled;
}

EntityType Entity::entityType() {
    return _entityType;
}

void Entity::startTimer() {
    _entityTimer.start();
}

void Entity::stopTimer() {
    _entityTimer.stop();
}

long Entity::getRemainingTime() {
    long remainingTime = (1000 / _loopFrequency) - _entityTimer.getMiliSeconds();

    return remainingTime;
}
