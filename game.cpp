#include "game.h"

#include <SDL2/SDL.h>

#include <iostream>

Game::Game() {}

Game::~Game() {}

bool Game::Run() {
  if (!InitSdl()) {
    return false;
  }

  // Initialize the game window.
  graphics_.CreateWindow();

  // Event struct to grab input events from SDL
  SDL_Event event;

  // The game loop.
  while (true) {
    if (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT) {
        return true;
      }
    }
  }
}

bool Game::InitSdl() {
  if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
    std::cout << "SDL Failed to initialize. Error: " << SDL_GetError()
              << std::endl;
    return false;
  }
  return true;
}
