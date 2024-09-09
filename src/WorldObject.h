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

    WorldObject(int grid_width, int grid_height) :
//              grid_width(grid_width),
//              grid_height(grid_height),
            _position({grid_width / 2.0f, grid_height / 2.0f}) {}

    WorldObject(float x, float y) :
            _position({x, y}) {}

    virtual coordinate position() const {return _position;}

    virtual float energy() const {return _energy;}
    virtual void adjustEnergy(float deltaEnergy);

    virtual float speed() const {return _speed;}
    virtual void adjustSpeed(float deltaSpeed);

    virtual coordinate heading() const {return _heading;}
    virtual void turn(float radians);

    virtual float size() const {return _size;}
    virtual bool isOccupying(const coordinate &point) const;

    virtual void move();
    virtual void Update() = 0;

protected:
    coordinate _position;
    coordinate _heading {0.0f, 0.0f};
    float _speed{1.0f};
    float _energy{0.0f};
    float _size{1.0f};

    float _maximumSpeed{100.0f};
    float _maximumTurn{M_PI / 18.0};

    static std::pair<float, float> getBearing(const coordinate &from, const coordinate &to);

//    int grid_width;
//    int grid_height;
};


#endif //SDL2TEST_WORLDOBJECT_H
