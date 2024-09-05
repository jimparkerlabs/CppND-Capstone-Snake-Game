//
// Created by Jim Parker on 9/5/24.
//

#include "food.h"

Food::Food(int x, int y) : x(x), y(y), type(REGULAR), engine(dev()), random_type(0, static_cast<int>(4)) { }

Food::Food(const Food& other) : x(other.x), y(other.y), type(other.type), engine(other.engine), random_type(0, static_cast<int>(4)) { }

Food &Food::operator=(const Food &other) {
    x = other.x;
    y = other.y;
    type = other.type;
    engine = other.engine;
    random_type = other.random_type;
    return *this;
}
