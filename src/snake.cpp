#include "snake.h"
#include <cmath>
#include <iostream>
#include <algorithm>
#include "WorldObject.h"

void Snake::Update() {
    UpdateHead();
    UpdateBody();
    _energy -= 1.0 / 60.0f;  // TODO: some multiple of speed

    // wrap segments if necessary
//    x = fmod(x + grid_width, grid_width);
//    y = fmod(y + grid_height, grid_height);

    // iterate over body and do the same
    for (Snake::coordinate &point : body) {
//        point.x = fmod(point.x + grid_width, grid_width);
//        point.y = fmod(point.y + grid_height, grid_height);
    }
}

void Snake::UpdateHead() {
    move();
}

void Snake::UpdateBody() {
    if (growing) {
        if (body.empty()) {
            addBodySegment(_position, _heading);
            growing = false;
        } else if (body.size() == 1){
            addBodySegment(body[0], _position);
            growing = false;
        } else {
            addBodySegment(body.back(), body[body.size() - 2]);
            growing = false;
        }
    }

    if (!body.empty()) {
        // move first body segment
        body[0] = moveBody(body[0], _position);
    }

    for (std::size_t i = 1; i < body.size(); ++i) {
        body[i] = moveBody(body[i], body[i - 1]);
    }

    // Check if the player has died
    // TODO: change this to cut the player
    for (auto const &item : body) {
        if (_position.x == item.x && _position.y == item.y) {
            alive = false;
            std::cout << "You are dead!" << std::endl;
            alive = true;
        }
    }
}

void Snake::addBodySegment(const coordinate &ref1, const coordinate &ref2) {
    auto [newBearing_x, newBearing_y] = getBearing(ref1, ref2);
    addBodySegment(ref1, newBearing_x, newBearing_y);
}

void Snake::addBodySegment(const coordinate &ref, float bearing_x, float bearing_y) {
    body.push_back(coordinate {ref.x - bearing_x * segment_separation, ref.y - bearing_y * segment_separation});
    _maximumSpeed = _maximumSpeed * body.size() / (body.size() - 1);
}

void Snake::GrowBody() { growing = true; }

// Inefficient method to check if cell is occupied by player.
size_t Snake::bodyShot(const coordinate &point) const {
//    if (headShot(point)) return body.size() + 1;

    for (size_t i = 0; i < body.size(); i++) {
        const auto& item = body[i];
        if ((abs(point.x - item.x) < (segment_size / 2.0)) && (abs(point.y - item.y) < (segment_size / 2.0)))
            return i + 1;
    }
    return 0;
}

Snake::coordinate Snake::moveBody(const coordinate &point, const coordinate &toward) {
    auto [bearing_x, bearing_y]  = getBearing(point, toward);
    return coordinate {toward.x - (segment_separation * bearing_x), toward.y - (segment_separation * bearing_y)};
}

void Snake::eat(Food *obj) {
    obj->alive = false;

    if (alive) {
        adjustEnergy(obj->energy());
        GrowBody();
    }
}

void Snake::eat(Snake *obj) {
    std::cout << "snake-eating!" << std::endl;
    adjustEnergy(1);
}

void Snake::truncateAt(size_t index) {
    // remove all elements from body vector after index
    if (index < body.size())
        body.erase(body.begin() + index, body.end());
    // TODO: reduce energy
    _energy *= (index - 1.0f) / body.size();
}

