#include "controller.h"
#include <iostream>
#include "SDL.h"
#include "snake.h"

//void Controller::ChangeDirection(Snake &snake, Snake::Direction input,
//                                 Snake::Direction opposite) const {
//  if (snake.direction != opposite || snake.numSegments() == 1) snake.direction = input;
//  return;
//}

void Controller::HandleInput(bool &running, Snake &snake) const {
  SDL_Event e;
  while (SDL_PollEvent(&e)) {
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
              ChangeHeading(snake, -M_PI / 18.0 * std::pow(1.05, snake.numSegments()));
          break;

        case SDLK_RIGHT:
        case SDLK_d:
              ChangeHeading(snake, M_PI / 18.0 * std::pow(1.05, snake.numSegments()));
          break;

          case SDLK_SPACE:
              snake.GrowBody();
      }
    }
  }
}

void Controller::ChangeHeading(Snake &snake, float radians) const {
//    float x = snake._heading.x;
//    float _y = snake._heading._y;
//    snake._heading.x = x * std::cos(radians) - _y * std::sin(radians);
//    snake._heading._y = x * std::sin(radians) + _y * std::cos(radians);
    snake.turn(radians);
}
