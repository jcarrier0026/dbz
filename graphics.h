#ifndef GRAPHICS_H
#define GRAPHICS_H
#include <SDL2/SDL.h>

#include "sprite.h"

// Structure to hold the RGB values of the background color.
struct {
  char red = 0x30;
  char green = 0x30;
  char blue = 0x30;
  char alpha = 0XFF;
} background_color;

class Graphics {
 public:
  Graphics();
  ~Graphics();

  void ChangeWindowColor();

  // Attempts to create the game window.
  void CreateWindow();

  // Draw the next frame and clear the renderer.
  void DrawNextFrame();

  // Add this sprite to the renderer for the next frame at the specified
  // location.
  void AddSprite(const Sprite& sprite, const SDL_Rect& destination);

 private:
  SDL_Window* window_;
  SDL_Renderer* renderer_;
};

#endif  // GRAPHICS_H
