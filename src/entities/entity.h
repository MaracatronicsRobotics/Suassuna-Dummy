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

#ifndef ENTITY_H
#define ENTITY_H

#include <QThread>
#include <QMutex>

#include <src/utils/timer/timer.h>

enum EntityType {
    ENT_PLAYER,
    ENT_COACH,
    ENT_VISION,
    ENT_ACTUATOR,
    ENT_WORLD
};

class Entity : public QThread
{
public:
    Entity(EntityType type);

    // Setters
    void setLoopFrequency(int hz);
    void setPriority(int priority);
    void enableEntity();
    void stopEntity();

    // Getters
    int loopFrequency();
    int entityPriority();
    bool isEnabled();
    EntityType entityType();

private:
    // Main run method
    void run();

    // Virtual methods
    virtual void initialization() = 0;
    virtual void loop() = 0;
    virtual void finalization() = 0;

    // Entity info
    int _loopFrequency;
    int _entityPriority;
    bool _isEnabled;
    EntityType _entityType;

    // Entity timer
    Timer _entityTimer;
    void startTimer();
    void stopTimer();
    long getRemainingTime();

    // Entity mutexes
    QMutex _mutexRunning;
    QMutex _mutexEnabled;
    QMutex _mutexPriority;
    QMutex _mutexLoopTime;
};

#endif // ENTITY_H
