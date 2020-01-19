#include <SDL2/SDL.h>

#include <iostream>

// Constants
// TODO(josh): Move these into a graphics class and use them there.
constexpr int kWindowWidth = 640;
constexpr int kWindowHeight = 480;
constexpr char kGameTitle[] = "DBZ";

// Structure to hold the RGB values of the background color.
constexpr struct {
  char red = 0x0;
  char green = 0x0;
  char blue = 0xFF;
  // Opaque is just 255 (0xFF), but let's use the provided SDL constant.
  char alpha = SDL_ALPHA_OPAQUE;
} BackgroundColor;

// Function to initialize the SDL library.
// Returns true if initialization succeeded.
bool InitSdl() {
  if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
    std::cout << "SDL Failed to initialize. Error: " << SDL_GetError()
              << std::endl;
    return false;
  }
  return true;
}

int main(int argc, char** argv) {
  // If SDL can't initialize, exit.
  if (!InitSdl()) {
    // Return nonzero values from main to indicate that something went wrong.
    return 1;
  }

  // Some SDL structures for the graphics stuff.
  SDL_Window* window;
  SDL_Renderer* renderer;

  // Magic SDL methods for creating the window.
  SDL_CreateWindowAndRenderer(kWindowWidth, kWindowHeight, 0, &window,
                              &renderer);
  SDL_SetWindowTitle(window, kGameTitle);

  // Change the window background to blue
  SDL_SetRenderDrawColor(renderer, BackgroundColor.red, BackgroundColor.green,
                         BackgroundColor.blue, BackgroundColor.alpha);

  // Clear the screen, putting our background color in every pixel.
  SDL_RenderClear(renderer);

  // Show our newly rendered screen on the window.
  SDL_RenderPresent(renderer);

  std::cout << "Press any key to exit" << std::endl;

  // Wait for user input before exiting.
  // If we didn't do this, the program would immediately terminate.
  // If we want to see the window, we need to make the program wait.
  std::cin.get();

  // Quit SDL gracefully
  SDL_Quit();

  // Returning 0 from main means that the program executed successfully.
  return 0;
}
