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

#include "locations.h"

#define MM2METER 1.0/1000.0

Locations::Locations(FieldSide ourSide, Field *field) {
    _field = field;
    _ourSide = ourSide;

    // Load default dimensions based on defaultField
    const float fieldX = _field->maxX();
    const float fieldY = _field->maxY();
    const float goalY = _field->goalWidth()/2;
    const float penaltyDist = _field->defenseRadius();

    // Set constant positions
    _fieldCenter = Position(true, 0.0, 0.0);

    // Update field corners
    _fieldBottomLeftCorner  = Position(true, -fieldX, -fieldY);
    _fieldBottomRightCorner = Position(true, fieldX, -fieldY);
    _fieldTopLeftCorner     = Position(true, -fieldX, fieldY);
    _fieldTopRightCorner    = Position(true, fieldX, fieldY);

    // Update goal/posts positions
    _rightGoalLeftPost = Position(true, fieldX, -goalY);
    _rightGoalRightPost = Position(true, fieldX, goalY);
    _leftGoalLeftPost = Position(true, -fieldX, goalY);
    _leftGoalRightPost = Position(true, -fieldX, -goalY);

    // Penalty marks
    _rightPenaltyMark = Position(true, (fieldX/2.0 - penaltyDist), 0.0);
    _leftPenaltyMark = Position(true, (-fieldX/2.0 + penaltyDist), 0.0);
}

Locations::~Locations() {
    delete _field;
}

FieldSide Locations::ourSide() {
    return _ourSide;
}

FieldSide Locations::theirSide() {
    return (_ourSide.isRight() ? Sides::LEFT : Sides::RIGHT);
}

Position Locations::fieldCenter() {
    _mutex.lockForRead();
    Position fieldCenter = _fieldCenter;
    _mutex.unlock();

    return fieldCenter;
}

float Locations::fieldMinX()  {
    _mutex.lockForRead();
    float fMinX = -fabs(ourFieldTopCorner().x());
    _mutex.unlock();

    return fMinX;
}

float Locations::fieldMaxX()  {
    _mutex.lockForRead();
    float fMaxX = fabs(ourFieldTopCorner().x());
    _mutex.unlock();

    return fMaxX;
}

float Locations::fieldMinY()  {
    _mutex.lockForRead();
    float fMinY = -fabs(ourFieldTopCorner().y());
    _mutex.unlock();

    return fMinY;
}

float Locations::fieldMaxY()  {
    _mutex.lockForRead();
    float fMaxY = fabs(ourFieldTopCorner().y());
    _mutex.unlock();

    return fMaxY;
}

float Locations::fieldLength()  {
    _mutex.lockForRead();
    float fLength = 2*fieldMaxX();
    _mutex.unlock();

    return fLength;
}

float Locations::fieldWidth()  {
    _mutex.lockForRead();
    float fWidth = 2*fieldMaxY();
    _mutex.unlock();

    return fWidth;
}

Position Locations::fieldRightTopCorner() {
    _mutex.lockForRead();
    Position fRightTopCorner = Position(true, this->fieldMaxX(), this->fieldMaxY());
    _mutex.unlock();

    return fRightTopCorner;
}

Position Locations::fieldRightBottomCorner() {
    _mutex.lockForRead();
    Position fRightBottomCorner = Position(true, this->fieldMaxX(), this->fieldMinY());
    _mutex.unlock();

    return fRightBottomCorner;
}

Position Locations::fieldLeftTopCorner() {
    _mutex.lockForRead();
    Position fLeftTopCorner = Position(true, this->fieldMinX(), this->fieldMaxY());
    _mutex.unlock();

    return fLeftTopCorner;
}

Position Locations::fieldLeftBottomCorner() {
    _mutex.lockForRead();
    Position fLeftBottomCorner = Position(true, this->fieldMinX(), this->fieldMinY());
    _mutex.unlock();

    return fLeftBottomCorner;
}

Position Locations::ourFieldTopCorner() {
    _mutex.lockForRead();
    Position ourFTopCorner = (ourSide().isRight() ? _fieldTopRightCorner : _fieldTopLeftCorner);
    _mutex.unlock();

    return ourFTopCorner;
}

Position Locations::ourFieldBottomCorner() {
    _mutex.lockForRead();
    Position ourFBottomCorner = (ourSide().isRight() ? _fieldBottomRightCorner : _fieldBottomLeftCorner);
    _mutex.unlock();

    return ourFBottomCorner;
}

Position Locations::ourGoal() {
    _mutex.lockForRead();
    Position ourG = Position(true, (ourSide().isRight() ? _rightGoalLeftPost : _leftGoalLeftPost).x(), 0.0);
    _mutex.unlock();

    return ourG;
}

Position Locations::ourGoalRightPost() {
    _mutex.lockForRead();
    Position ourGRightPost = (ourSide().isRight() ? _rightGoalRightPost : _leftGoalRightPost);
    _mutex.unlock();

    return ourGRightPost;
}

Position Locations::ourGoalLeftPost() {
    _mutex.lockForRead();
    Position ourGLeftPost = (ourSide().isRight() ? _rightGoalLeftPost : _leftGoalLeftPost);
    _mutex.unlock();

    return ourGLeftPost;
}

Position Locations::ourPenaltyMark() {
    _mutex.lockForRead();
    Position ourPMark = (ourSide().isRight() ? _rightPenaltyMark : _leftPenaltyMark);
    _mutex.unlock();

    return ourPMark;
}

Position Locations::theirFieldTopCorner() {
    _mutex.lockForRead();
    Position theirFTopCorner = theirSide().isRight() ? _fieldTopRightCorner : _fieldTopLeftCorner;
    _mutex.unlock();

    return theirFTopCorner;
}

Position Locations::theirFieldBottomCorner() {
    _mutex.lockForRead();
    Position theirFBottomCorner = (theirSide().isRight() ? _fieldBottomRightCorner : _fieldBottomLeftCorner);
    _mutex.unlock();

    return theirFBottomCorner;
}

Position Locations::theirGoal() {
    _mutex.lockForRead();
    Position theirG =Position(true, (theirSide().isRight() ? _rightGoalLeftPost : _leftGoalLeftPost).x(), 0.0);
    _mutex.unlock();

    return theirG;
}

Position Locations::theirGoalRightPost() {
    _mutex.lockForRead();
    Position theirGRightPost =(theirSide().isRight() ? _rightGoalRightPost : _leftGoalRightPost);
    _mutex.unlock();

    return theirGRightPost;
}

Position Locations::theirGoalLeftPost() {
    _mutex.lockForRead();
    Position theirGLeftPost = (theirSide().isRight() ? _rightGoalLeftPost : _leftGoalLeftPost);
    _mutex.unlock();

    return theirGLeftPost;
}

Position Locations::theirPenaltyMark() {
    _mutex.lockForRead();
    Position theirPMark = (theirSide().isRight() ? _rightPenaltyMark : _leftPenaltyMark);
    _mutex.unlock();

    return theirPMark;
}

float Locations::fieldCenterRadius() {
    _mutex.lockForRead();
    float fCenterRadius = _fieldCenterRadius;
    _mutex.unlock();

    return fCenterRadius;
}

float Locations::fieldDefenseLength() {
    _mutex.lockForRead();
    float fDefenseLength = _goalLength;
    _mutex.unlock();

    return fDefenseLength;
}

float Locations::fieldDefenseWidth() {
    _mutex.lockForRead();
    float fDefenseWidth = _goalWidth;
    _mutex.unlock();

    return fDefenseWidth;
}

float Locations::fieldGoalDepth() {
    _mutex.lockForRead();
    float fGoalDepth = _goalDepth;
    _mutex.unlock();

    return fGoalDepth;
}

bool Locations::isInsideOurField(const Position &pos) {
    return ((ourSide().isRight() && pos.x()>=0) || (ourSide().isLeft() && pos.x()<=0));
}

bool Locations::isInsideTheirField(const Position &pos) {
    return (isInsideOurField(pos)==false);
}

bool Locations::isInsideOurArea(const Position &pos, float factor) {
    double y_offset = ourSide().isLeft() ? 0.5 : -0.5;
    Position test(true, ourGoalLeftPost().x(), ourGoalLeftPost().y() - y_offset);

    double x_offset;
    x_offset = ourSide().isLeft() ? 1.0 : -1.0;
    Position ourGoalRightDeslocatedPost(true, ourGoalRightPost().x() + x_offset, ourGoalRightPost().y() + y_offset);

    return _isInsideArea(pos, factor, test, ourGoalRightDeslocatedPost);
}

bool Locations::isInsideTheirArea(const Position &pos, float factor) {
    double y_offset = theirSide().isLeft() ? 0.5 : -0.5;
    Position test(true, theirGoalLeftPost().x(), theirGoalLeftPost().y() - y_offset);

    double x_offset;
    x_offset = theirSide().isLeft() ? 1.0 : -1.0;
    Position theirGoalRightDeslocatedPost(true, theirGoalRightPost().x() + x_offset, theirGoalRightPost().y() + y_offset);

    return _isInsideArea(pos, factor, test, theirGoalRightDeslocatedPost);
}

bool Locations::isOutsideField(const Position &pos, float factor) {
    return _isOutsideField(pos, factor*fieldMaxX(), factor*fieldMaxY());
}

bool Locations::isOutsideField(const Position &pos, const float dx, const float dy) {
    return _isOutsideField(pos, fieldMaxX()+dx, fieldMaxY()+dy);
}

bool Locations::isInsideField(const Position &pos, float factor) {
    return (!isOutsideField(pos, factor));
}

bool Locations::isInsideField(const Position &pos, float dx, float dy) {
    return (!isOutsideField(pos, dx, dy));
}

bool Locations::_isInsideArea(const Position &pos, float factor, const Position &goalLeftPost, const Position &goalRightDeslocatedPost) {
    // rectangle
    return( (pos.x() <= std::max(goalLeftPost.x() * factor, goalRightDeslocatedPost.x() * factor)) && (pos.x() >= std::min(goalLeftPost.x() * factor, goalRightDeslocatedPost.x() * factor)) &&
                (pos.y() <= std::max(goalLeftPost.y() * factor, goalRightDeslocatedPost.y() * factor)) && (pos.y() >= std::min(goalLeftPost.y() * factor, goalRightDeslocatedPost.y() * factor)) );

    return false;
}

bool Locations::_isOutsideField(const Position &pos, const float maxX, const float maxY) {
    if(fabs(pos.x()) > maxX)
        return true;
    if(fabs(pos.y()) > maxY)
        return true;
    return false;
}

void Locations::updateGeometryData(SSL_GeometryData geometryData) {
    _mutex.lockForWrite();

    _lastData = geometryData;

    SSL_GeometryFieldSize field = _lastData.field();

    // Calc centerRadius and areaRadius
    float centerRadius = 0.0;
    float areaRadius = 0.0;
    for(int i=0; i<field.field_arcs_size(); i++) {
        const SSL_FieldCicularArc arc = field.field_arcs(i);
        if(arc.name() == "CenterCircle")
            centerRadius = arc.radius() + arc.thickness()/2;
        if(arc.name() == "LeftFieldLeftPenaltyArc")
            areaRadius = arc.radius() + arc.thickness()/2;
    }

    // Calc areaWidth and areaStretch
    float areaWidth = 0.0;
    float areaStretch = 0.0;
    for(int i=0; i<field.field_lines_size(); i++) {
       const SSL_FieldLineSegment line = field.field_lines(i);

       // Defense width
       if(line.name() == "RightPenaltyStretch") {
           areaWidth = field.field_length()/2 - line.p1().x() - line.thickness()/2;
           areaStretch = 2*fabs(line.p1().y());
           break;
       }
    }

    // Calc goalDepth and areaLength
    float areaLength = areaStretch + 2*areaRadius;

    // Updating positions
    _fieldCenter = Position(true, 0.0, 0.0);
    _fieldTopRightCorner = Position(true, (field.field_length()/2.0)*MM2METER, (field.field_width()/2.0)*MM2METER);
    _fieldTopLeftCorner = Position(true, (-field.field_length()/2.0)*MM2METER, (field.field_width()/2.0)*MM2METER);
    _fieldBottomLeftCorner = Position(true, (-field.field_length()/2.0)*MM2METER, (-field.field_width()/2.0)*MM2METER);
    _fieldBottomRightCorner = Position(true, (field.field_length()/2.0)*MM2METER, (-field.field_width()/2.0)*MM2METER);
    _rightPenaltyMark = Position(true, (field.field_length()/2.0 - areaRadius)*MM2METER, 0.0);
    _leftPenaltyMark = Position(true, (-field.field_length()/2.0 + areaRadius)*MM2METER, 0.0);
    _leftGoalLeftPost = Position(true, (-field.field_length()/2.0)*MM2METER, (-field.goal_width()/2.0)*MM2METER);
    _leftGoalRightPost = Position(true, (-field.field_length()/2.0)*MM2METER, (field.goal_width()/2.0)*MM2METER);
    _rightGoalLeftPost = Position(true, (field.field_length()/2.0)*MM2METER, (field.goal_width()/2.0)*MM2METER);
    _rightGoalRightPost = Position(true, (field.field_length()/2.0)*MM2METER, (-field.goal_width()/2.0)*MM2METER);
    _fieldCenterRadius = centerRadius*MM2METER;
    _goalLength = areaLength*MM2METER;
    _goalWidth = areaWidth*MM2METER;
    _goalDepth = field.goal_depth()*MM2METER;

    _mutex.unlock();
}
