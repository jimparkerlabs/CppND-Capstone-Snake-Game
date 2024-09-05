#include "game.h"
#include <iostream>
#include "SDL.h"

Game::Game(std::size_t grid_width, std::size_t grid_height)
    : snake(grid_width, grid_height),
      engine(dev()),
      random_w(0, static_cast<int>(grid_width - 1)),
      random_h(0, static_cast<int>(grid_height - 1)) {
  PlaceFood();
}

void Game::Run(Controller const &controller, Renderer &renderer,
               std::size_t target_frame_duration) {
  Uint32 title_timestamp = SDL_GetTicks();
  Uint32 frame_start;
  Uint32 frame_end;
  Uint32 frame_duration;
  int frame_count = 0;
  bool running = true;

  while (running) {
    frame_start = SDL_GetTicks();

    // Input, Update, Render - the main game loop.
    controller.HandleInput(running, snake);
    Update();
    renderer.Render(snake, food);

    frame_end = SDL_GetTicks();

    // Keep track of how long each loop through the input/update/render cycle
    // takes.
    frame_count++;
    frame_duration = frame_end - frame_start;

    // After every second, update the window title.
    if (frame_end - title_timestamp >= 1000) {
      renderer.UpdateWindowTitle(score, frame_count);
      frame_count = 0;
      title_timestamp = frame_end;
    }

    // If the time for this frame is too small (i.e. frame_duration is
    // smaller than the target ms_per_frame), delay the loop to
    // achieve the correct frame rate.
    if (frame_duration < target_frame_duration) {
      SDL_Delay(target_frame_duration - frame_duration);
    }
  }
}

void Game::PlaceFood() {
  int x, y;
  while (food.size() < numFoodToPlace) {
    x = random_w(engine);
    y = random_h(engine);
    // Check that the location is not occupied by a snake item before placing
    // Food.
    if (!snake.SnakeCell(x, y)) {
//      Food.x = x;
//      Food.y = y;
      food.emplace_back(Food {x, y});
    }
  }
}

void Game::Update() {
    if (!snake.alive) return;

    snake.Update();

    int new_x = static_cast<int>(snake.head_x);
    int new_y = static_cast<int>(snake.head_y);

    // Check if there's Food over here
    for (size_t i = 0; i < food.size(); ++i) {
        if (gotFood(food[i])) {
            score++;
            food.erase(food.begin() + i);
            // Grow snake and increase speed.
            snake.GrowBody();
            snake.speed *= 1.05;
            PlaceFood();
            break;  // can only be one Food item here
        }
    }
}

bool Game::gotFood(Food food) {
    // retrun true if Food x and y are inside the rectangle centered at snake.head_x and snake.head_y with sides = snake.head_size
    return (food.x >= snake.head_x - snake.head_size / 2 && food.x <= snake.head_x + snake.head_size / 2 &&
            food.y >= snake.head_y - snake.head_size / 2 && food.y <= snake.head_y + snake.head_size / 2);
}

int Game::GetScore() const { return score; }
int Game::GetSize() const { return snake.size(); }