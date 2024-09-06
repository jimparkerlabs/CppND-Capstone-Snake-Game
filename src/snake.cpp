#include "snake.h"
#include <cmath>
#include <iostream>
#include <cmath>

void Snake::Update() {
    UpdateHead();
    UpdateBody();

    // wrap segments if necessary
    head_x = fmod(head_x + grid_width, grid_width);
    head_y = fmod(head_y + grid_height, grid_height);

    // iterate over body and do the same
    for (Snake::coordinate &point : body) {
        point.x = fmod(point.x + grid_width, grid_width);
        point.y = fmod(point.y + grid_height, grid_height);
    }
}

void Snake::UpdateHead() {
    move(head_x, head_y);
}

void Snake::UpdateBody() {
    if (growing) {
        if (body.empty()) {
            addBodySegment(coordinate{ head_x, head_y}, heading_x, heading_y);
            growing = false;
        } else if (body.size() == 1){
            addBodySegment(coordinate {head_x, head_y}, body[0]);
            growing = false;
        } else {
            addBodySegment(body.back(), body[body.size() - 2]);
            growing = false;
        }
    }

    if (!body.empty()) {
        // move first body segment
        body[0] = moveBody(body[0], Snake::coordinate{head_x, head_y});
    }

    for (std::size_t i = 1; i < body.size(); ++i) {
        body[i] = moveBody(body[i], body[i - 1]);
    }

    // Check if the snake has died
    // TODO: change this to cut the snake
    for (auto const &item : body) {
        if (head_x == item.x && head_y == item.y) {
            alive = false;
            std::cout << "You are dead!" << std::endl;
            alive = true;
        }
    }
}

void Snake::addBodySegment(const coordinate &ref1, const coordinate &ref2) {
//    std::cout << "new segment, size= " << size << "  body.size() = " << body.size() << std::endl;
    auto [newBearing_x, newBearing_y] = getBearing(ref1, ref2);
    addBodySegment(ref1, newBearing_x, newBearing_y);
//    body.push_back(SDL_Point{static_cast<int>(body.back().x - new_bearing.x * segment_separation),
//                             static_cast<int>(body.back().y - new_bearing.y * segment_separation)});
    //size++;
}

void Snake::addBodySegment(const coordinate &ref, float bearing_x, float bearing_y) {
    //std::cout << "new segment, size= " << size << "  body.size() = " << body.size() << std::endl;
    body.push_back(coordinate {ref.x - bearing_x * segment_separation, ref.y - bearing_y * segment_separation});
}

void Snake::GrowBody() { growing = true; }

// Inefficient method to check if cell is occupied by snake.
bool Snake::isOccupying(int x, int y) {
  if (x == static_cast<int>(head_x) && y == static_cast<int>(head_y)) {
    return true;
  }
  for (auto const &item : body) {
    if (x == item.x && y == item.y) {
      return true;
    }
  }
  return false;
}

void Snake::move(coordinate &point) {
    point.x += (speed * std::pow(1.05, body.size()) * heading_x);
    point.y += (speed * std::pow(1.05, body.size()) * heading_y);
}

void Snake::move(float &x, float &y) {
    x += speed * std::pow(1.05, body.size()) * heading_x;
    y += speed * std::pow(1.05, body.size())  * heading_y;
}

Snake::coordinate Snake::moveBody(const coordinate &point, const coordinate &toward) {
    auto [bearing_x, bearing_y]  = getBearing(point, toward);
    return coordinate {toward.x - (segment_separation * bearing_x), toward.y - (segment_separation * bearing_y)};
}

std::pair<float, float> Snake::getBearing(const coordinate &from, const coordinate &to) {
    float x = to.x - from.x;
    float y = to.y - from.y;
    float len = std::sqrt(x*x + y*y);
    if (len > 0) {
        return std::make_pair((x / len), (y / len));
    }
    return std::make_pair(x, y);
}
