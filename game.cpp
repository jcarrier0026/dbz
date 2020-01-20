#include "game.h"

#include <SDL2/SDL.h>

#include <iostream>

constexpr int kFps = 50;
constexpr int kMaxFrameTimeMs = 1000 / kFps;

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

  int last_update_time_ms = SDL_GetTicks();
  // The game loop.
  while (true) {
    // Clear out old keyup/keydown events.
    input_.BeginNewFrame();

    if (SDL_PollEvent(&event)) {
      switch (event.type) {
        case SDL_QUIT:
          return true;
          break;
        case SDL_KEYDOWN:
          if (event.key.repeat == 0) {
            input_.KeyDownEvent(event);
          }
          break;
        case SDL_KEYUP:
          input_.KeyUpEvent(event);
          break;
        default:
          // do nothing
          break;
      }
    }
    if (input_.WasKeyPressed(SDL_SCANCODE_ESCAPE)) {
      return true;
    }

    if (input_.WasKeyPressed(SDL_SCANCODE_A)) {
      graphics_.ChangeWindowColor();
    }

    // Cap the framerate at 50 FPS.
    const int current_time_ms = SDL_GetTicks();
    int elapsed_time_ms = current_time_ms - last_update_time_ms;
    int frame_time_ms = std::min(elapsed_time_ms, kMaxFrameTimeMs);
    // TODO: Update the frame here.

    last_update_time_ms = current_time_ms;
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
