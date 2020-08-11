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

  // DELETE.
  SDL_Rect source_rect = {.x = 132, .y = 0, .w = 500, .h = 298};
  // Create background.
  Sprite background("Namek Background", source_rect, graphics_.GetRenderer());

  // Create an animated sprite object.
  // DELETE.
  source_rect = {0, 0, 30, 45};
  int time_between_frames = 200;
  SDL_Rect destination_rect = {50, 500, 58, 90};
  perf.StartTimer("create_sprite");
  bool play_animation_once;
  AnimatedSprite sprite("goku_sprite_sheet(in_progress)", source_rect,
                        graphics_.GetRenderer(), time_between_frames,
                        destination_rect);
  perf.StopTimer("create_sprite");

  // The game loop.
  while (true) {
    frame_start_time_ms = SDL_GetTicks();
    destination_rect = {0, 0, 1000, 596};
    graphics_.AddSprite(background, destination_rect, &perf);
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
    // DELETE.
    if (input_.WasKeyPressed(SDL_SCANCODE_D) ||
        input_.IsKeyHeld(SDL_SCANCODE_D)) {
      play_animation_once = false;
      sprite.PlayAnimation(AnimationType::kRunRight, &perf,
                           play_animation_once);
    }
    // DELETE.
    if (input_.WasKeyPressed(SDL_SCANCODE_A) ||
        input_.IsKeyHeld(SDL_SCANCODE_A)) {
      play_animation_once = false;
      sprite.PlayAnimation(AnimationType::kRunLeft, &perf, play_animation_once);
    }
    // DELETE.
    else {
      play_animation_once = false;
      sprite.PlayAnimation(AnimationType::kIdle, &perf, play_animation_once);
    }

    perf.StopTimer("input");

    graphics_.AddSprite(sprite, &perf);
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
