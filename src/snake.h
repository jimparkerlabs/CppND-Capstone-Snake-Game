#ifndef SNAKE_H
#define SNAKE_H

#include <vector>
//#include "SDL.h"

class Snake {
 public:
//  enum class Direction { kUp, kDown, kLeft, kRight };
  struct coordinate {
      float x;
      float y;
  };

  Snake(int grid_width, int grid_height)
      : grid_width(grid_width),
        grid_height(grid_height),
        head_x(grid_width / 2),
        head_y(grid_height / 2) {}

  void Update();

  void GrowBody();
  bool isOccupying(int x, int y);

//  Direction direction = Direction::kUp;
  float heading_x {0.0f};
  float heading_y {-1.0f};

  float speed{1.0f};
  float turnSpeed{M_PI / 18.0f};

  const std::size_t segment_size = 10;
  const std::size_t head_size = 12;
  const std::size_t segment_separation = segment_size;

  int size() const {return body.size() + 1;};
  bool alive{true};
  float head_x;
  float head_y;
  std::vector<coordinate> body;

 private:
    static std::pair<float, float> getBearing(const coordinate &from, const coordinate &to);

    void UpdateHead();
    void UpdateBody();

    void move(coordinate &point);
    coordinate moveBody(const coordinate &point, const coordinate &toward);
    void move(float &x, float &y);

    void addBodySegment(const coordinate &ref1, const coordinate &ref2);
    void addBodySegment(const coordinate &ref, float bearing_x, float bearing_y);

    bool growing{false};

    int grid_width;
    int grid_height;
};

#endif