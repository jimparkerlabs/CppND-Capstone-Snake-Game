//
// Created by Jim Parker on 9/5/24.
//

#include "food.h"
#include <iostream>

Food::Food(int x, int y) : WorldObject(x, y)/*, WorldObject(grid_width, grid_height)*/ {
    std::random_device dev;
    std::mt19937 engine(dev());
    std::uniform_int_distribution<int> random_type(0, 3);

    int rando = random_type(engine);
    std::cout << rando << std::endl;

    _type = static_cast<Type>(rando);
}

Food::Food(int x, int y, Type type) : WorldObject(x, y), _type(type)/*, WorldObject(grid_width, grid_height)*/ { }

Food::Food(const Food& other) : WorldObject(other.position().x, other.position().y), _type(other._type)/*, WorldObject(grid_width, grid_height)*/ { }

Food &Food::operator=(const Food &other) {
    _position.x = other.position().x;
    _position.y = other.position().y;
    _type = other._type;
    return *this;
}

float Food::energy() const {
    switch (_type) {
        case Type::REGULAR:
            return 1;
        case Type::SPECIAL:
            return 5;
        case Type::SMALL:
            return 1;
        case Type::BIG:
            return 0;
    }
}

float Food::size() const {
    switch (_type) {
        case Type::REGULAR:
            return 10;
        case Type::SPECIAL:
            return 5;
        case Type::SMALL:
            return 1;
        case Type::BIG:
            return 15;
    }
}
