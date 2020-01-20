#include "graphics.h"
#include <iostream>

Graphics::Graphics() { CreateWindow(); }

Graphics::~Graphics() {
  // Quit SDL gracefully.
  SDL_Quit();
}

bool Graphics::InitSdl() {
  if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
    std::cout << "SDL Failed to initialize. Error: " << SDL_GetError()
              << std::endl;
    return false;
  }
  return true;
}

void Graphics::CreateWindow() {
  // If SDL can't initialize, exit.
  if (!InitSdl()) {
    window_created_ = false;
    return;
  }
  window_created_ = true;
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
  return;
}
