//
// Created by Jim Parker on 9/5/24.
//

#ifndef SDL2TEST_FOOD_H
#define SDL2TEST_FOOD_H

#include <random>

class Food {
public:
    Food(int x, int y);
    Food(const Food& other);
    Food& operator=(const Food & other);

    enum Type {
        REGULAR,
        SPECIAL,
        BIG,
        FAST
    };

    int x;
    int y;
    Type type;

private:
    std::random_device dev;
    std::mt19937 engine;
    std::uniform_int_distribution<int> random_type;

};

#endif //SDL2TEST_FOOD_H
