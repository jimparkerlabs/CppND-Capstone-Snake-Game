//
// Created by Jim Parker on 9/5/24.
//

#include "WorldObject.h"

#ifndef SDL2TEST_FOOD_H
#define SDL2TEST_FOOD_H

#include <random>

class Food : public WorldObject {
public:
    enum class Type { REGULAR, SPECIAL, BIG, SMALL };

    Food(int x, int y);
    Food(int x, int y, Type type);

    Food(const Food& other);
    Food& operator=(const Food & other);

    float size()  const override;
    float energy() const override;
    bool isOccupying(const coordinate &point) const override {return false;};
    void Update() override {};

    Type type() const {return _type;};

private:
    Type _type {Type::REGULAR};
};

#endif //SDL2TEST_FOOD_H
