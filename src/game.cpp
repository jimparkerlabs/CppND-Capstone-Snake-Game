#include "game.h"
#include <iostream>
#include "SDL.h"

Game::Game(std::size_t grid_width, std::size_t grid_height)
    : engine(dev()),
      random_w(0, static_cast<int>(grid_width - 1)),
      random_h(0, static_cast<int>(grid_height - 1)),
      grid_width(grid_width),
      grid_height(grid_height) {

    gameObjects.emplace_back(std::make_unique<Snake>(grid_width / 2.0f, grid_height / 2.0f));
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
  Snake &player = *dynamic_cast<Snake*>(gameObjects[0].get());  // should check to make sure !gameObjects.empty()

  while (running) {
    frame_start = SDL_GetTicks();

    // Input, Update, Render - the main game loop.
    controller.HandleInput(running, player);
    Update();
//    renderer.Render(player, food);
      renderer.Render(gameObjects);

    frame_end = SDL_GetTicks();

    // Keep track of how long each loop through the input/update/render cycle
    // takes.
    frame_count++;
    frame_duration = frame_end - frame_start;

    // After every second, update the window title.
    if (frame_end - title_timestamp >= 1000) {
      renderer.UpdateWindowTitle(score, frame_count, player.energy());
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
    const Snake &player = *dynamic_cast<Snake*>(gameObjects[0].get());
    float x, y;

    while (filter<Food>(gameObjects).size() < numFoodToPlace) {
        x = random_w(engine);
        y = random_h(engine);
        // Check that the location is not occupied by a player item before placing Food.
        if (!player.isOccupying(WorldObject::coordinate {x, y})) {
            gameObjects.emplace_back(std::make_unique<Food>(x, y));
        }
    }
}

void Game::Update() {
    Snake &player = *dynamic_cast<Snake*>(gameObjects[0].get());

    if (player.energy() <= 0.0f) player.alive = false;

    if (!player.alive) return;

    for (auto &obj : gameObjects) {
        obj->Update();

        // bounce gameObjects that ran off the screen
        if (obj->position().x > 100) {
            // bounce left
        } else if (obj->position().x < 0) {
            // bounce right
        } else if (obj->position().y < 0) {
            // bounce down
        } else if (obj->position().y > 100) {
            // bounce up
        }
    }


    auto food = filter<Food>(gameObjects);
    auto snakes = filter<Snake>(gameObjects);
    auto snakeParts = filter<SnakePart>(gameObjects);

    // Check if any snakes got any food
    for (auto snake : snakes) {
        for (auto fd: food) {
            if (gotFood(snake, fd)) {
                score += static_cast<int>(fd->energy());
                snake->eat(fd);
                break;  // can only be one Food item here
            }
        }
    }

    // Check if any snakes got any snake parts
    for (auto snake : snakes) {
        for (auto fd: snakeParts) {
            if (gotFood(snake, fd)) {
                score += static_cast<int>(fd->energy());
                snake->eat(fd);
                break;  // can only be one Food item here
            }
        }
    }

    // Check if any snakes got "got"
    for (auto snake1 : snakes) {
        for (auto snake2 : snakes) {
            if (size_t index = snake2->bodyShot(snake1->position())) {
                // snake1 got snake2
                std::cout << "index: " << index << std::endl;
                snake1->eat(snake2);
                // cut snake2
                auto coords = snake2->truncateAt(index - 1);
                std::cout << coords.size() << std::endl;
                for (auto coord: coords) {
                    gameObjects.emplace_back(std::make_unique<SnakePart>(coord.x, coord.y));
                }
            }
        }
    }

    // Check if anything went off screen and handle
    for (auto &obj: gameObjects) {
        if (obj->position().x < 0 || obj->position().x > grid_width || obj->position().y < 0 ||
            obj->position().y > grid_height) {
            obj->alive = false;
        }
    }

    // TODO: remove "dead" food and objects off the screen and handle dead snakes
    gameObjects.erase(
            std::remove_if(gameObjects.begin() + 1, gameObjects.end(), [this](const std::unique_ptr<WorldObject> &obj) {
                return (!obj->alive || !visible(obj.get()));
            }), gameObjects.end());

    PlaceFood();
}

bool Game::gotFood(const Snake *snake, const WorldObject *const fd) const {
//    const Snake &player = *dynamic_cast<Snake*>(gameObjects[0].get());
    return snake->headShot(fd->position()) || fd->isOccupying(snake->position());
}

bool Game::visible(const WorldObject* const obj) {
    return true;
}

int Game::GetScore() const { return score; }
int Game::GetSize() const { return (*dynamic_cast<Snake*>(gameObjects[0].get())).numSegments(); }

template <typename T>
std::vector<T*> Game::filter(const std::vector<std::unique_ptr<WorldObject>>& objects) {
    std::vector<T*> result;
    for(const std::unique_ptr<WorldObject>& obj : objects) {
        if(auto* subClassObj = dynamic_cast<T*>(obj.get())) {
            result.push_back(subClassObj);
        }
    }
    return result;
}
