//
// Created by Jim Parker on 9/10/24.
//

#ifndef SDL2TEST_SNAKEPART_H
#define SDL2TEST_SNAKEPART_H


#include "WorldObject.h"

class SnakePart : public WorldObject {
public:
    SnakePart(float x, float y) : WorldObject(x, y) {
        _size = 3;
        _speed = 0;
        _energy = 1;
    }

    void Update() override;
};


#endif //SDL2TEST_SNAKEPART_H
