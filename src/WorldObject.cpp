//
// Created by Jim Parker on 9/6/24.
//

#include "WorldObject.h"
#include <utility>
#include <iostream>

std::pair<float, float> WorldObject::getBearing(const coordinate &from, const coordinate &to) {
    float x = to.x - from.x;
    float y = to.y - from.y;
    float len = std::sqrt(x*x + y*y);
    if (len > 0) {
        return std::make_pair((x / len), (y / len));
    }
    return std::make_pair(x, y);
}

void WorldObject::move() {
//    std::cout << "heading: " << _heading.x << " " << _heading.y << "... speed " << _speed << " ...x, y " << _position.x << ", " << _position.y << std::endl;
    _position.x += (_speed * _heading.x);
    _position.y += (_speed * _heading.y);
//    std::cout << "-> x, y " << _position.x << ", " << _position.y << std::endl;
}

void WorldObject::Update() {
    move();
}

void WorldObject::turn(float radians) {
    float hx = _heading.x;
    float hy = _heading.y;

    float rads = (radians < -_maximumTurn || radians > _maximumTurn) ? _maximumTurn : abs(radians);
//    std::cout << rads << " | " << (radians > 0) - (radians < 0) << std::endl;
    rads *= static_cast<float>((radians > 0.0) - (radians < 0.0));

//    std::cout << rads << " " << radians << " " << hx << " " << hy << " " << std::cos(rads) << " " << std::sin(rads) << std::endl;

    _heading.x = hx * std::cos(rads) - hy * std::sin(rads);
    _heading.y = hx * std::sin(rads) + hy * std::cos(rads);
//    std::cout << _heading.x << " " << _heading.y << std::endl;

}

void WorldObject::adjustSpeed(float deltaSpeed) {
    float newSpeed = _speed + deltaSpeed;
    if (newSpeed < 0.0) _speed = 0.0;
    else if  (newSpeed > _maximumSpeed) _speed = _maximumSpeed;
    else _speed = newSpeed;
}

void WorldObject::adjustEnergy(float deltaEnergy) {
    if (_energy + deltaEnergy < 0) _energy = 0.0;
    else _energy += deltaEnergy;
}

bool WorldObject::isOccupying(const WorldObject::coordinate &point) const {
    // simple square "collision boundary"
    if ((abs(point.x - _position.x) < (_size / 2.0)) && (abs(point.y - _position.y) < (_size / 2.0))) return true;

    return false;
}

