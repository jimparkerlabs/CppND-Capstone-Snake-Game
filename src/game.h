#ifndef GAME_H
#define GAME_H

#include <random>
#include "SDL.h"
#include "controller.h"
#include "renderer.h"
#include "snake.h"
#include "food.h"

class Game {
public:
    Game(std::size_t grid_width, std::size_t grid_height);
    void Run(Controller const &controller, Renderer &renderer,
             std::size_t target_frame_duration);
    int GetScore() const;
    int GetSize() const;

private:
    // TODO: vector of gameObjects
    Snake snake;
    std::vector<Food> food;

    std::random_device dev;
    std::mt19937 engine;
    std::uniform_real_distribution<float> random_w;
    std::uniform_real_distribution<float> random_h;
//    std::uniform_int_distribution<int> random_w;
//    std::uniform_int_distribution<int> random_h;

    const int numFoodToPlace = 6;
    int score{0};

    bool gotFood(Food &fd) const;

    void PlaceFood();
    void Update();
};

#endif