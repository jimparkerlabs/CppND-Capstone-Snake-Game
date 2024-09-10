#ifndef SNAKE_H
#define SNAKE_H

#include "WorldObject.h"
#include "food.h"
#include <vector>

class Snake : public WorldObject {
public:
    enum class Type { PLAYER, BLUE, RED };

    Snake(float x, float y)
            : WorldObject(x, x) {
        _heading = coordinate{0.0f, -1.0f};
        _speed = 1.0f;
        _energy = 100.0f,
        _size = 15;
    }

    // overrides of inherited attributes
    void Update() override;
    bool headShot(const coordinate &point) const { return WorldObject::isOccupying(point);}
    size_t bodyShot(const coordinate &point) const;

    void eat(WorldObject *obj);
    void eat(Snake *obj);

    std::vector<coordinate> truncateAt(size_t index);

    // player-specific functionality
    void GrowBody();
    int numSegments() const {return body.size() + 1;};

    const float segment_size = 10.0f;
    const float segment_separation = segment_size;

    std::vector<coordinate> body;

private:
    Type _type {Type::PLAYER};

    void UpdateHead();
    void UpdateBody();

//    void move() override;
    coordinate moveBody(const coordinate &point, const coordinate &toward);

    void addBodySegment(const coordinate &ref1, const coordinate &ref2);
    void addBodySegment(const coordinate &ref, float bearing_x, float bearing_y);

    bool growing{false};

};

#endif