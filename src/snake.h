#ifndef SNAKE_H
#define SNAKE_H

#include <vector>
#include "SDL.h"

class Snake {
 public:
  enum class Direction { kUp, kDown, kLeft, kRight };

  Snake(int grid_width, int grid_height)
      : grid_width(grid_width),
        grid_height(grid_height),
        head_x(grid_width / 2),
        head_y(grid_height / 2) {}

  void Update();

  void GrowBody();
  bool SnakeCell(int x, int y);

  Direction direction = Direction::kUp;
  SDL_Point heading {0, -1};

  float speed{0.5f};
  int size{1};
  bool alive{true};
  float head_x;
  float head_y;
  std::vector<SDL_Point> body;

 private:
    void UpdateHead();
    void UpdateBody(SDL_Point &current_cell, SDL_Point &prev_cell);

    void update_point(SDL_Point &point);
    void update_point(SDL_Point &point, const SDL_Point &to);
    void update_coordinates(float &x, float &y);

    SDL_Point getBearing(const SDL_Point &from, const SDL_Point &to);

    bool growing{false};

    int grid_width;
    int grid_height;
};

#endif