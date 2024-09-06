//
// Created by Jim Parker on 9/5/24.
//

#ifndef SDL2TEST_FOOD_H
#define SDL2TEST_FOOD_H

#include <random>

class Food {
public:
    enum class Type { REGULAR, SPECIAL, BIG, SMALL };

    Food(int x, int y);
    Food(int x, int y, Type type);

    Food(const Food& other);
    Food& operator=(const Food & other);

    int x;
    int y;

    Type type() const {return _type;};
    float energy() const;
    float size() const;

private:
    Type _type {Type::REGULAR};
};

#endif //SDL2TEST_FOOD_H
