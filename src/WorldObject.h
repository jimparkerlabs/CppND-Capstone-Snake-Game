//
// Created by Jim Parker on 9/6/24.
//

#include <cmath>

#ifndef SDL2TEST_WORLDOBJECT_H
#define SDL2TEST_WORLDOBJECT_H


class WorldObject {
public:
    struct coordinate {
        float x;
        float y;
    };

    WorldObject(int grid_width, int grid_height)
            : grid_width(grid_width),
              grid_height(grid_height),
              x(grid_width / 2),
              y(grid_height / 2) {}

    coordinate heading {0.0f, 0.0f};
    float speed{1.0f};
    float turnSpeed{M_PI / 180.0f};

    virtual void move();

    virtual bool isOccupying(const coordinate &point) const = 0;
    virtual void Update() = 0;

    float x;
    float y;

protected:
    static std::pair<float, float> getBearing(const coordinate &from, const coordinate &to);

    int grid_width;
    int grid_height;

};


#endif //SDL2TEST_WORLDOBJECT_H
