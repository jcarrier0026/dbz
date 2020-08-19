#include "graphics.h"

#include <iostream>

#include "constants.h"
#include "location.h"

// Graphics-related constants.
constexpr char kGameTitle[] = "DBZ";
constexpr float kMsPerSecond = 1000.0;

Graphics::Graphics() {}

Graphics::~Graphics() {
  // Destroy the window.
  SDL_DestroyWindow(window_);

  // Quit SDL gracefully.
  SDL_Quit();
}

void Graphics::CreateWindow() {
  // SDL method to create our window.
  SDL_CreateWindowAndRenderer(constants::kWindowWidth, constants::kWindowHeight,
                              0, &window_, &renderer_);
  SDL_SetWindowTitle(window_, kGameTitle);

  // Clear the screen, putting our background color in every pixel.
  SDL_RenderClear(renderer_);

  // Displays our screen in the window.
  SDL_RenderPresent(renderer_);
}

void Graphics::DrawNextFrame() {
  // Draw the next frame to the screen.
  SDL_RenderPresent(renderer_);
  // Reset the renderer to prepare for the following frame.
  SDL_RenderClear(renderer_);
}

void Graphics::AddSprite(const Sprite& sprite, const SDL_Rect& destination,
                         Perf* perf) {
  // Draw this sprite on the screen.
  AnimationFrame frame = sprite.GetSourceAnimationFrame();
  perf->StartTimer("render_copy");
  SDL_RenderCopy(renderer_, sprite.GetSpriteTexture(), &frame.source,
                 &destination);
  perf->StopTimer("render_copy");
}

void Graphics::AddSprite(const Sprite& sprite, Location location, Perf* perf) {
  AnimationFrame frame = sprite.GetSourceAnimationFrame();
  SDL_Rect destination = {
      .x = static_cast<int>(location.x + (frame.offset.x * sprite.GetScale())),
      .y = static_cast<int>(location.y + (frame.offset.y * sprite.GetScale())),
      .w = static_cast<int>(frame.source.w * sprite.GetScale()),
      .h = static_cast<int>(frame.source.h * sprite.GetScale())};
  // Draw this sprite on the screen.
  perf->StartTimer("render_copy");
  SDL_RenderCopy(renderer_, sprite.GetSpriteTexture(), &frame.source,
                 &destination);
  perf->StopTimer("render_copy");
}
