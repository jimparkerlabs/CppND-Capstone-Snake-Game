#include "snake.h"
#include <cmath>
#include <iostream>
#include <cmath>

void Snake::Update() {
  SDL_Point prev_cell{
      static_cast<int>(head_x),
      static_cast<int>(
          head_y)};  // We first capture the head's cell before updating.
  UpdateHead();
  SDL_Point current_cell{
      static_cast<int>(head_x),
      static_cast<int>(head_y)};  // Capture the head's cell after updating.

  // Update all of the body vector items if the snake head has moved to a new
  // cell.
  if (current_cell.x != prev_cell.x || current_cell.y != prev_cell.y) {
    UpdateBody(current_cell, prev_cell);
  }
}

//void Snake::UpdateHead() {
//    switch (direction) {
//        case Direction::kUp:
//            head_y -= speed;
//            break;
//
//        case Direction::kDown:
//            head_y += speed;
//            break;
//
//        case Direction::kLeft:
//            head_x -= speed;
//            break;
//
//        case Direction::kRight:
//            head_x += speed;
//            break;
//    }
//
//    // Wrap the Snake around to the beginning if going off of the screen.
//    head_x = fmod(head_x + grid_width, grid_width);
//    head_y = fmod(head_y + grid_height, grid_height);
//}

void Snake::UpdateHead() {
    update_coordinates(head_x, head_y);

    // Wrap the Snake around to the beginning if going off of the screen.
    head_x = fmod(head_x + grid_width, grid_width);
    head_y = fmod(head_y + grid_height, grid_height);
}

//void Snake::UpdateBody(SDL_Point &current_head_cell, SDL_Point &prev_head_cell) {
//    // Add previous head location to vector
//    body.push_back(prev_head_cell);
//
//    if (!growing) {
//        // Remove the tail from the vector.
//        body.erase(body.begin());
//    } else {
//        growing = false;
//        size++;
//    }
//
//    // Check if the snake has died.
//    for (auto const &item : body) {
//        if (current_head_cell.x == item.x && current_head_cell.y == item.y) {
//            alive = false;
//        }
//    }
//}

void Snake::UpdateBody(SDL_Point &current_head_cell, SDL_Point &prev_head_cell) {
    const size_t segment_separation = 2;

    // iterate through each body segment and update points based on speed and direction to prior segment
    if (body.empty())  {
        if (growing) {
            growing = false;

            // add new segment in opposite direction of heading;
            body.push_back(SDL_Point{static_cast<int>(head_x - heading.x * segment_separation),
                                     static_cast<int>(head_y - heading.y * segment_separation)});
            size++;
        }
        return;
    }
    else if (body.size() == 1) {
        // move first body segment
        update_point(body[0], current_head_cell);
        if (growing) {
            growing = false;

            // add new segment in opposite direction of bearing from body segment to head;
            SDL_Point new_heading = getBearing(body.back(), SDL_Point {static_cast<int>(head_x), static_cast<int>(head_y)});
            body.push_back(SDL_Point{static_cast<int>(body.back().x - new_heading.x * segment_separation),
                                     static_cast<int>(body.back().y - new_heading.y * segment_separation)});
            size++;
        }
    } else {
        for (std::size_t i = 1; i < body.size(); ++i) {
            update_point(body[i], body[i - 1]);
        }

        if (growing) {
            // don't grow any more
            growing = false;

            // add new segment in opposite direction of bearing from last to next-to-last segments;
            SDL_Point new_heading = getBearing(body.back(), body[body.size() - 2]);
            body.push_back(SDL_Point{static_cast<int>(body.back().x - new_heading.x * segment_separation),
                                     static_cast<int>(body.back().y - new_heading.y * segment_separation)});
            size++;
        }
        // Check if the snake has died.
        for (auto const &item : body) {
            if (current_head_cell.x == item.x && current_head_cell.y == item.y) {
                alive = false;
            }
        }
    }
}

void Snake::GrowBody() { growing = true; }

// Inefficient method to check if cell is occupied by snake.
bool Snake::SnakeCell(int x, int y) {
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

void Snake::update_point(SDL_Point &point) {
    point.x += static_cast<int>(speed * heading.x);
    point.y += static_cast<int>(speed * heading.y);
}

void Snake::update_coordinates(float &x, float &y) {
    x += speed * heading.x;
    y += speed * heading.y;
}

void Snake::update_point(SDL_Point &point, const SDL_Point &toward) {
    SDL_Point to_heading =getBearing(point, toward);
    point.x += static_cast<int>(speed * to_heading.x);
    point.y += static_cast<int>(speed * to_heading.y);
}

SDL_Point Snake::getBearing(const SDL_Point &from, const SDL_Point &to) {
    float x = to.x - from.x;
    float y = to.y - from.y;
    float len = std::sqrt(x*x + y*y);
    if (len > 0) {
        return SDL_Point {static_cast<int>(x / len), static_cast<int>(y / len)};
    }
    return SDL_Point {static_cast<int>(x), static_cast<int>(y)};
}
