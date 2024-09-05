#include "renderer.h"
#include <iostream>
#include <string>

Renderer::Renderer(const std::size_t screen_width,
                   const std::size_t screen_height,
                   const std::size_t grid_width, const std::size_t grid_height)
    : screen_width(screen_width),
      screen_height(screen_height),
      grid_width(grid_width),
      grid_height(grid_height) {
  // Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cerr << "SDL could not initialize.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }

  // Create Window
  sdl_window = SDL_CreateWindow("Snake Game", SDL_WINDOWPOS_CENTERED,
                                SDL_WINDOWPOS_CENTERED, screen_width,
                                screen_height, SDL_WINDOW_SHOWN);

  if (nullptr == sdl_window) {
    std::cerr << "Window could not be created.\n";
    std::cerr << " SDL_Error: " << SDL_GetError() << "\n";
  }

  // Create renderer
  sdl_renderer = SDL_CreateRenderer(sdl_window, -1, SDL_RENDERER_ACCELERATED);
  if (nullptr == sdl_renderer) {
    std::cerr << "Renderer could not be created.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }
}

Renderer::~Renderer() {
  SDL_DestroyWindow(sdl_window);
  SDL_Quit();
}

void Renderer::Render(Snake const &snake, std::vector<Food> &food) {
    // Clear screen
    SDL_SetRenderDrawColor(sdl_renderer, 0x1E, 0x1E, 0x1E, 0xFF);
    SDL_RenderClear(sdl_renderer);

    // Render Food
    const std::size_t food_size = 10;

    {
        SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xCC, 0x00, 0xFF);

        for (Food const &fd: food) {
            auto center = render_coordinates(fd.x, fd.y);

//    fillRect(sdl_renderer, center, food_size, food_size);
            fillCircle(sdl_renderer, center, food_size / 2);
        }
    }

    // Render snake body
    // TODO: allow various head shapes, segment shapes, and segment separations
    {
//        int segmentRenderWidth = gridToScreen_x(snake.segment_size);
//        int segmentRenderHeight = gridToScreen_y(snake.segment_size);
        SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
        for (Snake::coordinate const &point: snake.body) {
            SDL_Point center = render_coordinates(point);
            fillCircle(sdl_renderer, center, gridToScreen_x(snake.segment_size / 2));
        }
    }

    // Render snake's head
    {
        if (snake.alive) {
            SDL_SetRenderDrawColor(sdl_renderer, 0x00, 0x7A, 0xCC, 0xFF);
        } else {
            SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0x00, 0x00, 0xFF);
        }

        SDL_Point render_point = render_coordinates(snake.head_x, snake.head_y);

        fillCircle(sdl_renderer, render_point, gridToScreen_x(snake.head_size / 2));
    }
    // Update Screen
    SDL_RenderPresent(sdl_renderer);
}

void Renderer::UpdateWindowTitle(int score, int fps) {
  std::string title{"Snake Score: " + std::to_string(score) + " FPS: " + std::to_string(fps)};
  SDL_SetWindowTitle(sdl_window, title.c_str());
}

//SDL_Point Renderer::render_coordinates(std::size_t grid_x, std::size_t grid_y) {
//    return SDL_Point {static_cast<int>(static_cast<double>(grid_x)  / grid_width * screen_width), static_cast<int>(static_cast<double>(grid_y) / grid_height * screen_height)};
//}

SDL_Point Renderer::render_coordinates(float grid_x, float grid_y) {
    return SDL_Point {static_cast<int>(grid_x  / grid_width * screen_width), static_cast<int>(grid_y / grid_height * screen_height)};
}

SDL_Point Renderer::render_coordinates(Snake::coordinate point) {
    return SDL_Point {static_cast<int>(point.x  / grid_width * screen_width), static_cast<int>(point.y / grid_height * screen_height)};
}

void Renderer::fillCircle(SDL_Renderer* renderer, SDL_Point center, int32_t radius)
{
    for(int y = -radius; y <= radius; y++)
    {
        for(int x = -radius; x <= radius; x++)
        {
            if(x * x + y * y <= radius * radius)
            {
                SDL_RenderDrawPoint(renderer, center.x + x, center.y + y);
            }
        }
    }
}

void Renderer::fillRect(SDL_Renderer *renderer, SDL_Point center, int32_t width, int32_t height) {
    SDL_Rect glyph {center.x - width / 2, center.y - height / 2, width, height};
    SDL_RenderFillRect(sdl_renderer, &glyph);
}

//void Renderer::fillRect(SDL_Renderer *renderer, SDL_Rect &glyph) {
//    SDL_RenderFillRect(sdl_renderer, &glyph);
//}
