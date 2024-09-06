#ifndef SNAKE_H
#define SNAKE_H

#include "WorldObject.h"
#include <vector>

class Snake : public WorldObject {
public:
    Snake(int grid_width, int grid_height)
            : WorldObject(grid_width, grid_height) {
        heading = coordinate{0.0f, -1.0f};
        speed = 1.0f;
        turnSpeed = M_PI / 18.0f;
    }

    // overrides of inherited attributes
    void Update() override;
    bool isOccupying(const coordinate &point) const override;

    // snake-specific functionality
    void GrowBody();
    int numSegments() const {return body.size() + 1;};

    const std::size_t segment_size = 10;
    const std::size_t head_size = 12;
    const std::size_t segment_separation = segment_size;

    bool alive{true};

    std::vector<coordinate> body;

private:

    void UpdateHead();
    void UpdateBody();

//    void move() override;
    coordinate moveBody(const coordinate &point, const coordinate &toward);

    void addBodySegment(const coordinate &ref1, const coordinate &ref2);
    void addBodySegment(const coordinate &ref, float bearing_x, float bearing_y);

    bool growing{false};

};

#endif