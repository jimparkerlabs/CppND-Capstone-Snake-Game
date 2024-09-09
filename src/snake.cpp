#include "snake.h"
#include <cmath>
#include <iostream>

void Snake::Update() {
    UpdateHead();
    UpdateBody();

    // wrap segments if necessary
//    _position.x = fmod(_position.x + grid_width, grid_width);
//    _position.y = fmod(_position.y + grid_height, grid_height);

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
            addBodySegment(_position, _heading.x, _heading.y);
            growing = false;
        } else if (body.size() == 1){
            addBodySegment(_position, body[0]);
            growing = false;
        } else {
            addBodySegment(body.back(), body[body.size() - 2]);
            growing = false;
        }
    }

    if (!body.empty()) {
        // move first body segment
        body[0] = moveBody(body[0], Snake::_position);
    }

    for (std::size_t i = 1; i < body.size(); ++i) {
        body[i] = moveBody(body[i], body[i - 1]);
    }

    // Check if the snake has died
    // TODO: change this to cut the snake
    for (auto const &item : body) {
        if (_position.x == item.x && _position.y == item.y) {
            alive = false;
            std::cout << "You are dead!" << std::endl;
            alive = true;
        }
    }
}

void Snake::addBodySegment(const coordinate &ref1, const coordinate &ref2) {
//    std::cout << "new segment, size= " << size << "  body.size() = " << body.numSegments() << std::endl;
    auto [newBearing_x, newBearing_y] = getBearing(ref1, ref2);
    addBodySegment(ref1, newBearing_x, newBearing_y);
//    body.push_back(SDL_Point{static_cast<int>(body.back().x - new_bearing.x * segment_separation),
//                             static_cast<int>(body.back()._y - new_bearing._y * segment_separation)});
    //numSegments++;
}

void Snake::addBodySegment(const coordinate &ref, float bearing_x, float bearing_y) {
    //std::cout << "new segment, size= " << size << "  body.size() = " << body.numSegments() << std::endl;
    body.push_back(coordinate {ref.x - bearing_x * segment_separation, ref.y - bearing_y * segment_separation});
}

void Snake::GrowBody() { growing = true; }

// Inefficient method to check if cell is occupied by snake.
bool Snake::isOccupying(const coordinate &point) const {
    if (WorldObject::isOccupying(point)) return true;

    // check for the body
    for (auto const &segment : body) {
        if (point.x == segment.x && point.y == segment.y) {
            return true;
        }
    }
    return false;
}

//void Snake::move() {
//    x += (_speed * std::pow(1.05, body.size()) * _heading.x);
//    _y += (_speed * std::pow(1.05, body.size()) * _heading._y);
//}

//void Snake::move() {
//    x += (_speed * _heading.x);
//    _y += (_speed * _heading._y);
//}

Snake::coordinate Snake::moveBody(const coordinate &point, const coordinate &toward) {
    auto [bearing_x, bearing_y]  = getBearing(point, toward);
    return coordinate {toward.x - (segment_separation * bearing_x), toward.y - (segment_separation * bearing_y)};
}

