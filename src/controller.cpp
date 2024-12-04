#include "controller.h"
#include <iostream>
#include "SDL.h"
#include "snake.h"

//void Controller::ChangeDirection(Snake &player, Snake::Direction input,
//                                 Snake::Direction opposite) const {
//  if (player.direction != opposite || player.numSegments() == 1) player.direction = input;
//  return;
//}

void Controller::HandleInput(bool &running, Snake &snake) const {
    SDL_Event e;
    while (SDL_PollEvent(&e)) {
        std::cout << e.type << std::endl;
        if (e.type == SDL_QUIT) {
            running = false;
        } else if (e.type == SDL_KEYDOWN) {
            switch (e.key.keysym.sym) {
                case SDLK_UP:
                case SDLK_w:
                    snake.adjustSpeed(snake.speed() * 0.05f);
                    break;

                case SDLK_DOWN:
                case SDLK_s:
                    snake.adjustSpeed(snake.speed() * -0.05f);
                    break;

                case SDLK_LEFT:
                case SDLK_a:
                    std::cout << "left" << std::endl;
                    ChangeHeading(snake, -M_PI / 18.0 * std::pow(1.05, snake.numSegments()));
                    break;

                case SDLK_RIGHT:
                case SDLK_d:
                    std::cout << "right" << std::endl;
                    ChangeHeading(snake, M_PI / 18.0 * std::pow(1.05, snake.numSegments()));
                    break;
                case SDLK_SPACE:
                    // TODO: change this to a pause
                    // snake.GrowBody();
                    break;

                case SDLK_ESCAPE:
                    running = false;
                    break;
            }
        }
    }
}

void Controller::ChangeHeading(Snake &snake, float radians) const {
//    float x = player._heading.x;
//    float _y = player._heading._y;
//    player._heading.x = x * std::cos(radians) - _y * std::sin(radians);
//    player._heading._y = x * std::sin(radians) + _y * std::cos(radians);
    snake.turn(radians);
}
