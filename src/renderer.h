#ifndef RENDERER_H
#define RENDERER_H

#include <vector>
#include "SDL.h"
#include "snake.h"
#include "food.h"

class Renderer {
 public:
    Renderer(const std::size_t screen_width, const std::size_t screen_height,
             const std::size_t grid_width, const std::size_t grid_height);
    ~Renderer();

    void Render(Snake const &snake, std::vector<Food> &food);
    void UpdateWindowTitle(int score, int fps);

 private:
    SDL_Window *sdl_window;
    SDL_Renderer *sdl_renderer;

    const std::size_t screen_width;
    const std::size_t screen_height;
    const std::size_t grid_width;
    const std::size_t grid_height;

    int gridToScreen_x(float x) { return static_cast<int>(x / grid_width * screen_width); }
    int gridToScreen_y(float y) { return static_cast<int>(y / grid_height * screen_height); }

//    SDL_Point render_coordinates(std::size_t grid_x, std::size_t grid_y);
    SDL_Point render_coordinates(float grid_x, float grid_y);
    SDL_Point render_coordinates(Snake::coordinate point);

    void fillCircle(SDL_Renderer* renderer, SDL_Point center, int32_t radius);
    void fillRect(SDL_Renderer* renderer, SDL_Point center, int32_t width, int32_t height);
    void drawRect(SDL_Renderer* renderer, SDL_Point center, int32_t width, int32_t height);
//    void fillRect(SDL_Renderer* renderer, SDL_Rect &glyph);
};

#endif