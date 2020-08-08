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

  // Create a perf object.
  Perf perf(true, constants::kFramesPerFpsCheck);

  // Create background.
  Sprite background("Namek Background", {132, 0, 500, 298},
                    graphics_.GetRenderer());

  // Create an animated sprite object.
  perf.StartTimer("create_sprite");
  AnimatedSprite sprite("goku_sprite_sheet(in_progress)",
                        {.x = 0, .y = 0, .w = 29, .h = 45},
                        graphics_.GetRenderer(), 200, {50, 500, 58, 90});
  perf.StopTimer("create_sprite");

  // The game loop.
  while (true) {
    graphics_.AddSprite(background, {0, 0, 1000, 596}, &perf);
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

    perf.StopTimer("input");

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
