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
    std::cout << heading.x << " " << heading.y << std::endl;
    x += (speed * heading.x);
    y += (speed * heading.y);
}

