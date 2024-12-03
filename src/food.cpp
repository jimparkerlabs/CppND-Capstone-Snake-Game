//
// Created by Jim Parker on 9/5/24.
//

#include "food.h"
#include <iostream>
#include <cmath>

Food::Food(float x, float y) : WorldObject(x, y) {
    std::random_device dev;
    std::mt19937 engine(dev());
    std::uniform_int_distribution<int> random_type(0, 3);

    int rando = random_type(engine);
    _type = static_cast<Type>(rando);

    setUpType();
}

Food::Food(float x, float y, Type type) : WorldObject(x, y), _type(type) {
    setUpType();
}

Food::Food(const Food& other) : WorldObject(other.position().x, other.position().y), _type(other._type) {
    setUpType();
}

Food &Food::operator=(const Food &other) {
    _position.x = other.position().x;
    _position.y = other.position().y;
    _type = other._type;
    setUpType();
    return *this;
}

void Food::setUpType() {
    std::random_device dev;
    std::mt19937 engine(dev());
    std::uniform_real_distribution<> dist(0.0, 2.0 * M_PI);

    float angle = dist(engine);

    switch (_type) {
        case Type::REGULAR:
            _energy = 1;
            _size = 10;
            _speed = 0;
            _heading = coordinate{0, 0};
            break;
        case Type::SPECIAL:
            _energy = 5;
            _size = 5;
            _speed = 1;
            _heading = coordinate{std::cos(angle), std::sin(angle)};
            break;
        case Type::SMALL:
            _energy = 10;
            _size = 1;
            _speed = 5;
            _heading = coordinate{std::cos(angle), std::sin(angle)};
            break;
        case Type::BIG:
            _energy = 5;
            _size = 15;
            _speed = 3;
            _heading = coordinate{std::cos(angle), std::sin(angle)};
            break;
    }
}
