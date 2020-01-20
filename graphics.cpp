#include "graphics.h"

#include <iostream>

Graphics::Graphics() {}

Graphics::~Graphics() {
  // Quit SDL gracefully.
  SDL_Quit();
}

void Graphics::CreateWindow() {
  // SDL method to create our window.
  SDL_CreateWindowAndRenderer(kWindowWidth, kWindowHeight, 0, &window_,
                              &renderer_);
  SDL_SetWindowTitle(window_, kGameTitle);

  // Changes background.
  SDL_SetRenderDrawColor(renderer_, BackgroundColor.red, BackgroundColor.green,
                         BackgroundColor.blue, BackgroundColor.alpha);

  // Clear the screen, putting our background color in every pixel.
  SDL_RenderClear(renderer_);

  // Displays our screen in the window.
  SDL_RenderPresent(renderer_);
}
