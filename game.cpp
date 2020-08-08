#include "game.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <iostream>

#include "constants.h"
#include "perf.h"

Game::Game() {}

Game::~Game() {}

bool Game::Run() {
  if (!InitSdl()) {
    return false;
  }

  // Initialize the game window.
  graphics_.CreateWindow();

  // Event struct to grab input events from SDL.
  SDL_Event event;

  // DELETE THIS EVENTUALLY
  int goku_location = 50;

  // Create a perf object.
  Perf perf(true, constants::kFramesPerFpsCheck);

  SDL_Rect start_destination = {.x = 50, .y = 30, .w = 58, .h = 90};

  AnimatedSprite sprite("goku_sprite_sheet(in_progress)",
                        {.x = 0, .y = 0, .w = 29, .h = 45},
                        graphics_.GetRenderer(), 200, start_destination);
  // The game loop.
  while (true) {
    frame_start_time_ms = SDL_GetTicks();
    perf.StartTimer("game_loop");
    perf.StartTimer("input");

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

    if (input_.WasKeyPressed(SDL_SCANCODE_D) ||
        input_.IsKeyHeld(SDL_SCANCODE_D)) {
      graphics_.PlayAnimation("RunRight", sprite, &perf, false);
    } else {
      graphics_.PlayAnimation("Idle", sprite, &perf, false);
    }

    if (input_.WasKeyPressed(SDL_SCANCODE_A) ||
        input_.IsKeyHeld(SDL_SCANCODE_A)) {
      goku_location -= 4;
    }
    perf.StopTimer("input");

    perf.StartTimer("create_sprite");
    perf.StopTimer("create_sprite");

    perf.StartTimer("add_sprite");
    perf.StopTimer("add_sprite");

    perf.StartTimer("draw");
    graphics_.DrawNextFrame();
    perf.StopTimer("draw");

    LimitFrameRate();
    perf.StopTimer("game_loop");
    perf.ReportResults();
  }
}

void Game::LimitFrameRate() {
  int current_time_ms = SDL_GetTicks();
  int elapsed_time_ms = current_time_ms - frame_start_time_ms;
  if (elapsed_time_ms < constants::kMaxFrameTimeMs) {
    SDL_Delay(constants::kMaxFrameTimeMs - elapsed_time_ms);
  }
}

bool Game::InitSdl() {
  if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
    std::cout << "SDL Failed to initialize. Error: " << SDL_GetError()
              << std::endl;
    return false;
  }
  IMG_Init(IMG_INIT_PNG);
  return true;
}
