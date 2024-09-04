#ifndef RENDERER_H
#define RENDERER_H

#include <vector>
#include "SDL.h"
#include "snake.h"

class Renderer {
 public:
  Renderer(const std::size_t screen_width, const std::size_t screen_height,
           const std::size_t grid_width, const std::size_t grid_height);
  ~Renderer();

  void Render(Snake const snake, SDL_Point const &food);
  void UpdateWindowTitle(int score, int fps);

 private:
  SDL_Window *sdl_window;
  SDL_Renderer *sdl_renderer;

  const std::size_t screen_width;
  const std::size_t screen_height;
  const std::size_t grid_width;
  const std::size_t grid_height;

  SDL_Point render_coordinates(std::size_t grid_x, std::size_t grid_y);
  SDL_Point render_coordinates(SDL_Point point);

  void fillCircle(SDL_Renderer* renderer, SDL_Point center, int32_t radius);
    void fillRect(SDL_Renderer* renderer, SDL_Point center, int32_t width, int32_t height);
//    void fillRect(SDL_Renderer* renderer, SDL_Rect &glyph);
};

#endif