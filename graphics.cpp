#include "graphics.h"

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
  SDL_SetRenderDrawColor(renderer_, background_color.red, background_color.green,
                         background_color.blue, background_color.alpha);

  // Clear the screen, putting our background color in every pixel.
  SDL_RenderClear(renderer_);

  // Displays our screen in the window.
  SDL_RenderPresent(renderer_);
}


void Graphics::ChangeWindowColor() {
 background_color.red += 50;
 background_color.blue += 50;

 // Changes background.
  SDL_SetRenderDrawColor(renderer_, background_color.red, background_color.green,
                         background_color.blue, background_color.alpha);

  // Clear the screen, putting our background color in every pixel.
  SDL_RenderClear(renderer_);

  // Displays our screen in the window.
  SDL_RenderPresent(renderer_);
}
