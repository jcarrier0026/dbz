#ifndef GRAPHICS_H
#define GRAPHICS_H
#include <SDL2/SDL.h>

#include "animated_sprite.h"
#include "location.h"
#include "sprite.h"

class Graphics {
 public:
  Graphics();
  ~Graphics();

  // Attempts to create the game window.
  void CreateWindow();

  // Draw the next frame and clear the renderer.
  void DrawNextFrame();

  // Add this sprite to the renderer for the next frame, scaled to fit the
  // provided destination rectangle.
  void AddSprite(const Sprite& sprite, const SDL_Rect& destination);

  // Add a sprite to the renderer at the specified location, scaled by the
  // sprite scale value.
  void AddSprite(const Sprite& sprite, Location location);

  // This returns a pointer to the renderer struct.
  // Exposing this is unfortunate but the Sprite needs access to it to create
  // textures.
  // This method should be used with caution.
  // The graphics class still owns the renderer.
  SDL_Renderer* GetRenderer() { return renderer_; }

 private:
  SDL_Window* window_;
  SDL_Renderer* renderer_;
};

#endif  // GRAPHICS_H
