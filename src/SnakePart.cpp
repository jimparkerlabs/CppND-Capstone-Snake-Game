//
// Created by Jim Parker on 9/10/24.
//

#include "SnakePart.h"

void SnakePart::Update() {
    WorldObject::Update();
    _energy -= 1 / 150.0f;
    if (_energy <= 0.0f) alive = false;
}
