#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "snake.h"

class Controller {
 public:
    void HandleInput(bool &running, Snake &snake) const;
//    void HandleInput(bool &running, std::unique_ptr<Snake> &snake) const;

 private:
//    void ChangeDirection(Snake &player, Snake::Direction input,
//                         Snake::Direction opposite) const;
    void ChangeHeading(Snake &snake, float radians) const;
};

#endif