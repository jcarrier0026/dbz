#include "graphics.h"

#include "constants.h"

// Graphics-related constants.
constexpr char kGameTitle[] = "DBZ";

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

  SDL_RenderClear(renderer_);
}

void Graphics::AddSprite(const Sprite& sprite, const SDL_Rect& destination) {
  // Get a texture from the surface.
  SDL_Texture* texture =
      SDL_CreateTextureFromSurface(renderer_, sprite.GetSpriteSheet());

  // Draw this sprite on the screen.
  SDL_Rect source = sprite.GetSourceLocation();
  SDL_RenderCopy(renderer_, texture, &source, &destination);
}
