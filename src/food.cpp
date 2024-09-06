//
// Created by Jim Parker on 9/5/24.
//

#include "food.h"
#include <iostream>

Food::Food(int x, int y) : x(x), y(y) {
    std::random_device dev;
    std::mt19937 engine(dev());
    std::uniform_int_distribution<int> random_type(0, 3);

    _type = static_cast<Type>( random_type(engine));
}

Food::Food(int x, int y, Type type) : x(x), y(y), _type(type) { }

Food::Food(const Food& other) : x(other.x), y(other.y) { }

Food &Food::operator=(const Food &other) {
    x = other.x;
    y = other.y;
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
