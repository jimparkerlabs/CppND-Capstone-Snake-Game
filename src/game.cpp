#include "game.h"
#include <iostream>
#include <thread>
#include <future>

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
    Snake* player = dynamic_cast<Snake*>(gameObjects[0].get());

    if (player->energy() <= 0.0f) player->alive = false;

    if (!player->alive) return;

    // update all gameObjects in parallel
    std::vector<std::thread> threads;

    for (auto &obj : gameObjects) {
        threads.emplace_back([&obj]() { obj->Update(); });
    }

    // wait for all the updates to complete
    for (auto& t : threads) {
        if (t.joinable()) {
            t.join();
        }
    }

    auto foods = filter<Food>(gameObjects);
    auto snakes = filter<Snake>(gameObjects);
    auto snakeParts = filter<SnakePart>(gameObjects);

    // see if any snakes got anything
    for (auto snake : snakes) {
        // Check if snake got any foods
        for (auto food: foods) {
            if (gotFood(snake, food)) {
                if (snake == player) {
                    score += static_cast<int>(food->energy());
                }
                snake->eat(food);
                break;  // can only be one Food item here
            }
        }

        // Check if snake got any snake parts
        for (auto snakePart: snakeParts) {
            if (gotFood(snake, snakePart)) {
                if (snake == player) {
                    score += static_cast<int>(snakePart->energy());
                }
                snake->eat(snakePart);
                break;  // can only be one snakePart here
            }
        }

        // Check if snake got another snake
        // otherSnake->bodyShot is potentially expensive; run them all in parallel and return results as a vector of futures
        std::vector<std::promise<size_t>> promises;
        std::vector<std::thread> bodyShotThreads;

        for (auto otherSnake : snakes) {
            promises.emplace_back();  // create a promise for the returned value
            std::promise<size_t>& prms = promises.back();  // get a reference to the promise just created
            bodyShotThreads.emplace_back([&prms, &otherSnake, &snake]() {
                prms.set_value(otherSnake->bodyShot(snake->position()));
            });
        }

        // wait for all the bodyShotThreads to complete
        for (auto& t : bodyShotThreads) {
            if (t.joinable()) {
                t.join();
            }
        }

        for (size_t i=0; i < promises.size(); ++i) {
            if (size_t index = promises[i].get_future().get()) {
                Snake* otherSnake = snakes[i];
                // snake got otherSnake
                snake->eat(otherSnake);
                std::cout << "ate a snake ";
                // cut otherSnake
                auto coords = otherSnake->truncateAt(index - 1);
                std::cout << "cut a snake ";

                // turn otherSnake's tail into snake parts
                for (auto coord: coords) {
                    gameObjects.emplace_back(std::make_unique<SnakePart>(coord.x, coord.y));
                }
                std::cout << "snake food!" << std::endl;

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

    // remove "dead" foods and objects off the screen and handle dead snakes
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
