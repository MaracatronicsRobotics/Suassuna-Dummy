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

#ifndef ROLE_H
#define ROLE_H

#include <QObject>

#include <src/entities/coach/basecoach.h>
#include <src/constants/constants.h>

class Role : public QObject
{
    Q_OBJECT
public:
    Role();
    virtual ~Role();

    // Role name (for debug)
    virtual QString name() = 0;

    // Init role control
    bool isInitialized();
    void initialize(Constants *constants);
    void setPlayer(Player *player);

    // Method to run in playbook
    void runRole();

protected:
    // Role control methods
    void addBehavior(int id, Behavior *behavior);
    void setBehavior(int id);

    // Player and constants getters
    Player* player();
    Constants* getConstants();

private:
    // Virtual implementation in inherited classes
    virtual void configure() = 0;
    virtual void run() = 0;

    // Player access
    Player *_player;

    // Constants
    Constants *_constants;

    // Behavior list
    QMap<int, Behavior*> _behaviorList;
    Behavior *_actualBehavior;

    // Initialize control
    bool _initialized;
};

#endif // ROLE_H
