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


#ifndef PLAYBOOK_DEFAULT2_H
#define PLAYBOOK_DEFAULT2_H

#include <src/entities/coach/playbook/playbook.h>
#include <src/entities/coach/role/roles.h>

class Playbook_Default2 : public Playbook
{
public:
    Playbook_Default2();
    QString name();

private:
    // Playbook inherited methods
    void configure(int numPlayers);
    void run(int numPlayers);

    // Role pointer vector
    QList<Role_Default*> _roles_default;
};

#endif // PLAYBOOK_DEFAULT2_H
