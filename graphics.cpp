#include "graphics.h"

#include <iostream>

#include "constants.h"

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
  SDL_Rect source = sprite.GetSourceLocation();
  perf->StartTimer("render_copy");
  SDL_RenderCopy(renderer_, sprite.GetSpriteTexture(), &source, &destination);
  perf->StopTimer("render_copy");
}

void Graphics::AddSprite(AnimatedSprite& sprite, Perf* perf,
                         std::string animation) {
  // Draw this sprite on the screen.
  int frame = sprite.GetFrameIndex();
  SDL_Rect source = sprite.GetSourceRect(animation, frame);
  SDL_Rect destination = sprite.GetDestinationRect();
  Vector2 offset = sprite.GetOffsets(animation);
  destination.x = (destination.x + offset.x) % (constants::kWindowWidth - 64);
  destination.y += offset.y;
  sprite.SetDestinationRect(destination);
  perf->StartTimer("render_copy");
  SDL_RenderCopy(renderer_, sprite.GetSpriteTexture(), &source, &destination);
  perf->StopTimer("render_copy");
}

void Graphics::PlayAnimation(std::string animation, AnimatedSprite& sprite,
                             Perf* perf, bool once) {
  sprite.SetCurrentAnimationOnce(once);
  if (sprite.GetCurrentAnimation() != animation) {
    std::cout << "starting animation" << std::endl;
    sprite.SetCurrentAnimation(animation);
    sprite.SetFrameIndex(0);
  } else {
    sprite.SetElapsedTime(SDL_GetTicks());
    sprite.TimeToUpdateFrame();
  }
  this->AddSprite(sprite, perf, animation);
}
