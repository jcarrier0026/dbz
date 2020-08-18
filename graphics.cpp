#include "graphics.h"

#include <iostream>

#include "constants.h"
#include "location.h"
#include "perf.h"

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

void Graphics::AddSprite(const Sprite& sprite, const SDL_Rect& destination) {
  // Draw this sprite on the screen.
  SDL_Rect source = sprite.GetSourceLocation();
  Perf::GetPerf()->StartTimer("render_copy");
  SDL_RenderCopy(renderer_, sprite.GetSpriteTexture(), &source, &destination);
  Perf::GetPerf()->StopTimer("render_copy");
}

void Graphics::AddSprite(const Sprite& sprite, Location location) {
  SDL_Rect source = sprite.GetSourceLocation();
  SDL_Rect destination = {.x = location.x,
                          .y = location.y,
                          .w = static_cast<int>(source.w * sprite.GetScale()),
                          .h = static_cast<int>(source.h * sprite.GetScale())};
  // Draw this sprite on the screen.
  Perf::GetPerf()->StartTimer("render_copy");
  SDL_RenderCopy(renderer_, sprite.GetSpriteTexture(), &source, &destination);
  Perf::GetPerf()->StopTimer("render_copy");
}
