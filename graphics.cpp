#include "graphics.h"

#include <iostream>

#include "constants.h"

// Graphics-related constants.
constexpr char kGameTitle[] = "DBZ";
// Check the FPS this often.
constexpr int kFramesPerFpsCheck = 100;
constexpr float kMsPerSecond = 1000.0;

Graphics::Graphics() : number_of_frames_drawn_(0), last_fps_check_time_ms_(0) {}

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

  // Changes background.
  SDL_SetRenderDrawColor(renderer_, background_color.red,
                         background_color.green, background_color.blue,
                         background_color.alpha);

  // Clear the screen, putting our background color in every pixel.
  SDL_RenderClear(renderer_);

  // Displays our screen in the window.
  SDL_RenderPresent(renderer_);
}

void Graphics::ChangeWindowColor() {
  background_color.red += 50;
  background_color.blue += 50;

  // Changes background.
  SDL_SetRenderDrawColor(renderer_, background_color.red,
                         background_color.green, background_color.blue,
                         background_color.alpha);

  // Clear the screen, putting our background color in every pixel.
  SDL_RenderClear(renderer_);

  // Displays our screen in the window.
  SDL_RenderPresent(renderer_);
}

void Graphics::DrawNextFrame() {
  // Draw the next frame to the screen.
  SDL_RenderPresent(renderer_);
  // Calculate the FPS and write it to the terminal.
  CalculateFps();
  // Reset the renderer to prepare for the following frame.
  SDL_RenderClear(renderer_);
}

void Graphics::CalculateFps() {
  if (number_of_frames_drawn_ % kFramesPerFpsCheck == 0 &&
      number_of_frames_drawn_ > 0) {
    int current_time = SDL_GetTicks();
    int elapsed_time = current_time - last_fps_check_time_ms_;
    float fps =
        static_cast<float>(kFramesPerFpsCheck) / (elapsed_time / kMsPerSecond);
    std::cout << "FPS: " << fps << std::endl;
    last_fps_check_time_ms_ = SDL_GetTicks();
  }
  number_of_frames_drawn_++;
}
void Graphics::AddSprite(const Sprite& sprite, const SDL_Rect& destination) {
  // Get a texture from the surface.
  SDL_Texture* texture =
      SDL_CreateTextureFromSurface(renderer_, sprite.GetSpriteSheet());

  // Draw this sprite on the screen.
  SDL_Rect source = sprite.GetSourceLocation();
  SDL_RenderCopy(renderer_, texture, &source, &destination);
}
