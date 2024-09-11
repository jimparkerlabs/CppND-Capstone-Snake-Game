#ifndef GAME_H
#define GAME_H

#include <random>
#include "SDL.h"
#include "controller.h"
#include "renderer.h"
#include "snake.h"
#include "food.h"
#include "WorldObject.h"

class Game {
public:
    Game(std::size_t grid_width, std::size_t grid_height);
    void Run(Controller const &controller, Renderer &renderer,
             std::size_t target_frame_duration);
    int GetScore() const;
    int GetSize() const;

private:
    // TODO: vector of gameObjects
    std::vector<std::unique_ptr<WorldObject>> gameObjects;

    std::random_device dev;
    std::mt19937 engine;
    std::uniform_real_distribution<float> random_w;
    std::uniform_real_distribution<float> random_h;
//    std::uniform_int_distribution<int> random_w;
//    std::uniform_int_distribution<int> random_h;

    const int numFoodToPlace = 6;
    int score{0};

    bool gotFood(const Snake *snake, const WorldObject *fd) const;
    bool visible(const WorldObject* const obj);

    void PlaceFood();
    void Update();

    size_t grid_width;
    size_t grid_height;

    template <typename T>
    std::vector<T*> filter(const std::vector<std::unique_ptr<WorldObject>>& objects);
};

#endif