#ifndef GRAPHICS_H
#define GRAPHICS_H
#include <SDL2/SDL.h>

// Graphics-related constants.
constexpr int kWindowWidth = 640;
constexpr int kWindowHeight = 480;
constexpr char kGameTitle[] = "DBZ";

// Structure to hold the RGB values of the background color.
struct {
  char red = 0x0;
  char green = 0x0;
  char blue = 0xFF;
  char alpha = 0XFF;
} background_color;

class Graphics {
 public:
  Graphics();
  ~Graphics();

  void ChangeWindowColor();

  // Attempts to create the game window.
  void CreateWindow();

 private:
  SDL_Window* window_;
  SDL_Renderer* renderer_;
};

#endif  // GRAPHICS_H
