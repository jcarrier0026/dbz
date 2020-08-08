#ifndef GRAPHICS_H
#define GRAPHICS_H
#include <SDL2/SDL.h>

#include "animated_sprite.h"
#include "perf.h"
#include "sprite.h"

class Graphics {
 public:
  Graphics();
  ~Graphics();

  // Attempts to create the game window.
  void CreateWindow();

  // Draw the next frame and clear the renderer.
  void DrawNextFrame();

  // Add this sprite to the renderer for the next frame at the specified
  // location.
  void AddSprite(const Sprite& sprite, const SDL_Rect& destination, Perf* perf);

  // Adds the current frame in the animation to the renderer. It also adds the
  // offsets for the destination rectangle.
  void AddSprite(AnimatedSprite& sprite, Perf* perf, std::string animation);

  // Does the logic to figure out what frame of the animation we are on before
  // calling AddSprite(AnimatedSprite&, Perf*, std::string).
  void PlayAnimation(std::string animation, AnimatedSprite& sprite, Perf* perf,
                     bool once = false);

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
