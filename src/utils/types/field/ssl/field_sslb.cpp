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

#include "field_sslb.h"

Field_SSLB::Field_SSLB() {

}

QString Field_SSLB::name() const {
    return "Field_SSLB";
}

float Field_SSLB::length() const {
    return 9.00;
}

float Field_SSLB::width() const {
    return 6.00;
}

float Field_SSLB::goalWidth() const {
    return 1.00;
}

float Field_SSLB::goalDepth() const {
    return 0.20;
}

float Field_SSLB::goalAreaWidth() const {
    return 2.00;
}

float Field_SSLB::goalAreaDepth() const {
    return 1.00;
}

float Field_SSLB::centerRadius() const {
    return 0.50;
}

float Field_SSLB::defenseRadius() const {
    return 1.50;
}

float Field_SSLB::defenseStretch() const {
    return 0.50;
}
