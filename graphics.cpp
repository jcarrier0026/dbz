#include "graphics.h"


bool Graphics::InitSdl() {
  if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
    std::cout << "SDL Failed to initialize. Error: " << SDL_GetError()
              << std::endl;
    return false; //failed to initialize
  }
  return true; //successfully initialized
 }


int Graphics::createWindow() {
  // If SDL can't initialize, exit
  if (!InitSdl()) {
    return 1;
  }

  SDL_Window* window;
  SDL_Renderer* renderer;

  // SDL method to create our window
  SDL_CreateWindowAndRenderer(kWindowWidth, kWindowHeight, 0, &window,
                              &renderer);
  SDL_SetWindowTitle(window, kGameTitle);

  // Changes background to blue
  SDL_SetRenderDrawColor(renderer, BackgroundColor.red, BackgroundColor.green,
                         BackgroundColor.blue, BackgroundColor.alpha);

  // Clear the screen, putting our background color in every pixel
  SDL_RenderClear(renderer);

  // displays our screen in the window
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

