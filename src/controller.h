#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "snake.h"

class Controller {
 public:
    void HandleInput(bool &running, Snake &snake) const;

 private:
    void ChangeHeading(Snake &snake, float radians) const;
};

#endif