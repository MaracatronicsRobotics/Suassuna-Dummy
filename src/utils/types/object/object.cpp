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

#include "object.h"

Object::Object() {
    setInvalid();
}

Object::~Object() {

}

Position Object::getPosition() {
    Position retn = _position;

    return retn;
}

Velocity Object::getVelocity() {
    Velocity retn = _velocity;

    return retn;
}

Angle Object::getOrientation() {
    Angle retn = _orientation;

    return retn;
}

bool Object::isObjectLoss() {
    return _lossFilter.checkLoss();
}

bool Object::isObjectSafe() {
    return _noiseFilter.checkNoise();
}

void Object::updateObject(float confidence, Position pos, Angle orientation) {
    // Update confidence
    _confidence = confidence;

    // If pos is invalid (robot is not visible in frame)
    if(pos.isInvalid()) {
        // If loss filter is not initialized
        if(!_lossFilter.isInitialized()) {
            // Just start loss
            _lossFilter.startLoss();
        }
        // If loss filter is already initialized
        else {
            // If object is really lost
            if(isObjectLoss()) {
                // Reset noise and set invalid
                _noiseFilter.startNoise();
                setInvalid();
            }
            // If object is not lost already and is safe
            else if(!isObjectLoss() && isObjectSafe()){
                // Predict with Kalman
                _kalmanFilter.predict();
                _position = _kalmanFilter.getPosition();
                _velocity = _kalmanFilter.getVelocity();
            }
        }
    }
    // If pos is valid (robot was saw in frame)
    else {
        // If noise filter is not initialized
        if(!_noiseFilter.isInitialized()) {
            // Init noise
            _noiseFilter.startNoise();
            // Set invalid
            setInvalid();
        }
        // If noise filter is already initialized
        else {
            // If object is safe (survived at noise filter)
            if(isObjectSafe()) {
                // Reset loss filter
                _lossFilter.startLoss();

                // Iterate in kalman filter
                _kalmanFilter.iterate(pos);

                // Update positions, orientations, velocity and confidence
                _position.setPosition(true, _kalmanFilter.getPosition().x(), _kalmanFilter.getPosition().y());
                _velocity = _kalmanFilter.getVelocity();
                _orientation = orientation;
            }
            // If object is unsafe yet (noise is running)
            else {
                // Set invalid
                setInvalid();

                // Reset loss
                _lossFilter.startLoss();
            }
        }
    }
}

void Object::setInvalid() {
    _position.setInvalid();
    _velocity.setInvalid();
    _orientation.setInvalid();
    _confidence = 0.0;
}
