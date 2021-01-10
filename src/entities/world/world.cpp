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

#include "world.h"

#include <src/utils/text/text.h>

World::World() : Entity(ENT_WORLD){

}

World::~World() {

}

void World::addEntity(Entity *e, int priority) {
    // Insert entity in hash
    _moduleEntities.insert(priority, e);

    // Set entity priority
    e->setPriority(priority);
}

void World::initialization() {
    std::cout << Text::cyan("[WORLD] ", true) << Text::bold("Initializing modules.") << '\n';
    startEntities();
}

void World::loop() {
    // TODO
}

void World::finalization() {
    std::cout << Text::cyan("[WORLD] ", true) << Text::bold("Finishing modules.") << '\n';
    stopAndDeleteEntities();
}

void World::startEntities() {
    // Get priorities in hash
    QList<int> priorities = _moduleEntities.keys();

    // In each priority (decreasing, most priority first)
    const int prioritiesSize = priorities.size();
    for(int i = prioritiesSize - 1; i >= 0; i--) {
        const int priority = priorities.at(i);

        // Get associated entities
        const QList<Entity*> entities = _moduleEntities.values(priority);

        // Start those entities
        QList<Entity*>::const_iterator it;
        for(it = entities.constBegin(); it != entities.constEnd(); it++) {
            // Take entity
            Entity *entity = *it;

            // Start entity
            entity->start();
        }
    }
}

void World::stopAndDeleteEntities() {
    // Get priorities in hash
    QList<int> priorities = _moduleEntities.keys();

    // In each priority (increasing)
    const int prioritiesSize = priorities.size();
    for(int i = 0; i < prioritiesSize; i++) {
        const int priority = priorities.at(i);

        // Get associated entities
        const QList<Entity*> entities = _moduleEntities.values(priority);

        // Stop those entities
        QList<Entity*>::const_iterator it;
        for(it = entities.constBegin(); it != entities.constEnd(); it++) {
            // Take entity
            Entity *entity = *it;

            // Stop entity
            entity->stopEntity();

            // Wait entity
            entity->wait();
        }

        // Delete those entities
        for(it = entities.constBegin(); it != entities.constEnd(); it++) {
            // Take entity
            Entity *entity = *it;

            // Remove entity from hash
            _moduleEntities.values(priority).removeOne(entity);

            // Delete entity
            delete entity;
        }
    }
}