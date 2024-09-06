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
//          ChangeDirection(snake, Snake::Direction::kUp,
//                          Snake::Direction::kDown);
//          snake.speed *= 1.05;
//          snake.turnSpeed *= 1.05;
          break;

        case SDLK_DOWN:
        case SDLK_s:
//          ChangeDirection(snake, Snake::Direction::kDown,
//                          Snake::Direction::kUp);
//              snake.speed /= 1.05;
//              snake.turnSpeed /= 1.05;
          break;

        case SDLK_LEFT:
        case SDLK_a:
//              ChangeDirection(snake, Snake::Direction::kLeft,
//                            Snake::Direction::kRight);
              ChangeHeading(snake, -snake.turnSpeed * std::pow(1.05, snake.numSegments()));
          break;

        case SDLK_RIGHT:
        case SDLK_d:
//            ChangeDirection(snake, Snake::Direction::kRight,
//                          Snake::Direction::kLeft);
              ChangeHeading(snake, snake.turnSpeed * std::pow(1.05, snake.numSegments()));
          break;

          case SDLK_SPACE:
              snake.GrowBody();
      }
    }
  }
}

void Controller::ChangeHeading(Snake &snake, float radians) const {
    float x = snake.heading.x;
    float y = snake.heading.y;
    snake.heading.x = x * std::cos(radians) - y * std::sin(radians);
    snake.heading.y = x * std::sin(radians) + y * std::cos(radians);
}
