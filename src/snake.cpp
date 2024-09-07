#include "snake.h"
#include <cmath>
#include <iostream>

void Snake::Update() {
    UpdateHead();
    UpdateBody();

    // wrap segments if necessary
    x = fmod(x + grid_width, grid_width);
    y = fmod(y + grid_height, grid_height);

    // iterate over body and do the same
    for (Snake::coordinate &point : body) {
        point.x = fmod(point.x + grid_width, grid_width);
        point.y = fmod(point.y + grid_height, grid_height);
    }
}

void Snake::UpdateHead() {
    move();
}

void Snake::UpdateBody() {
    if (growing) {
        if (body.empty()) {
            addBodySegment(coordinate{x, y}, heading.x, heading.y);
            growing = false;
        } else if (body.size() == 1){
            addBodySegment(body[0], coordinate {x, y});
            growing = false;
        } else {
            addBodySegment(body.back(), body[body.size() - 2]);
            growing = false;
        }
    }

    if (!body.empty()) {
        // move first body segment
        body[0] = moveBody(body[0], Snake::coordinate{x, y});
    }

    for (std::size_t i = 1; i < body.size(); ++i) {
        body[i] = moveBody(body[i], body[i - 1]);
    }

    // Check if the snake has died
    // TODO: change this to cut the snake
    for (auto const &item : body) {
        if (x == item.x && y == item.y) {
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
//                             static_cast<int>(body.back().y - new_bearing.y * segment_separation)});
    //numSegments++;
}

void Snake::addBodySegment(const coordinate &ref, float bearing_x, float bearing_y) {
    //std::cout << "new segment, size= " << size << "  body.size() = " << body.numSegments() << std::endl;
    body.push_back(coordinate {ref.x - bearing_x * segment_separation, ref.y - bearing_y * segment_separation});
}

void Snake::GrowBody() { growing = true; }

// Inefficient method to check if cell is occupied by snake.
bool Snake::isOccupying(const coordinate &point) const {
  if (point.x == x && point.y == y) {
    return true;
  }
  for (auto const &item : body) {
    if (point.x == item.x && point.y == item.y) {
      return true;
    }
  }
  return false;
}

//void Snake::move() {
//    x += (speed * std::pow(1.05, body.size()) * heading.x);
//    y += (speed * std::pow(1.05, body.size()) * heading.y);
//}

//void Snake::move() {
//    x += (speed * heading.x);
//    y += (speed * heading.y);
//}

Snake::coordinate Snake::moveBody(const coordinate &point, const coordinate &toward) {
    auto [bearing_x, bearing_y]  = getBearing(point, toward);
    return coordinate {toward.x - (segment_separation * bearing_x), toward.y - (segment_separation * bearing_y)};
}

