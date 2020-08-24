#include "game.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <iostream>

#include "animation_data.h"
#include "constants.h"
#include "location.h"
#include "perf.h"
#include "z_fighter.h"

using constants::kBackgroundScale;
using constants::kGokuScale;
using constants::kGokuSpeed;

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

  SDL_Rect background_source = {.x = 132, .y = 0, .w = 500, .h = 298};

  // Create background.
  Sprite background("Namek Background", background_source, kBackgroundScale,
                    graphics_.GetRenderer());

  Perf::GetPerf()->StartTimer("create_sprite");

  AnimatedSprite goku_animated_sprite("goku_sprite_sheet(in_progress)",
                                      graphics_.GetRenderer(), kGokuScale,
                                      GetGokuAnimations());
  Perf::GetPerf()->StopTimer("create_sprite");

  Location goku_location(50, 500);

  ZFighter goku(std::move(goku_animated_sprite), goku_location);

  // If goku is super saiyan.
  bool super_saiyan = false;

  std::cout << sizeof(AnimatedSprite) << std::endl;

  // The game loop.
  while (true) {
    frame_start_time_ms = SDL_GetTicks();

    // Add the background
    graphics_.AddSprite(background, Location(0, 0));
    Perf::GetPerf()->StartTimer("game_loop");
    Perf::GetPerf()->StartTimer("input");

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

    // This is the farthest goku can go to the right before hitting the edge.
    int goku_window_boundary =
        constants::kWindowWidth - goku.GetMutableSprite().GetWidth();

    // TODO: Move to player class.
    if (input_.WasKeyPressed(SDL_SCANCODE_D) ||
        input_.IsKeyHeld(SDL_SCANCODE_D)) {
      // Move goku to the right by his speed, wrapping at the window edge.
      goku.GetMutableLocation().x += kGokuSpeed;

      // If goku is super saiyan, he moves faster.
      goku.GetMutableLocation().x +=
          super_saiyan ? constants::kSsGokuSpeedMod : 0;

      if (goku.GetMutableLocation().x > goku_window_boundary) {
        goku.GetMutableLocation().x = 0;
      }

      super_saiyan
          ? goku.GetMutableSprite().PlayAnimation(AnimationType::kSsRunRight)
          : goku.GetMutableSprite().PlayAnimation(AnimationType::kRunRight);
    }

    if (input_.WasKeyPressed(SDL_SCANCODE_A) ||
        input_.IsKeyHeld(SDL_SCANCODE_A)) {
      goku.GetMutableLocation().x -= kGokuSpeed;

      // If goku is super saiyan, he moves faster.
      goku.GetMutableLocation().x -=
          super_saiyan ? constants::kSsGokuSpeedMod : 0;

      // If goku runs left far enough, let's wrap to the right side.
      if (goku.GetMutableLocation().x < 0) {
        goku.GetMutableLocation().x = goku_window_boundary;
      }

      super_saiyan
          ? goku.GetMutableSprite().PlayAnimation(AnimationType::kSsRunLeft)
          : goku.GetMutableSprite().PlayAnimation(AnimationType::kRunLeft);
    } else {
      super_saiyan
          ? goku.GetMutableSprite().PlayAnimation(AnimationType::kSsIdle)
          : goku.GetMutableSprite().PlayAnimation(AnimationType::kDefault);
    }

    if ((input_.WasKeyPressed(SDL_SCANCODE_T) ||
         input_.IsKeyHeld(SDL_SCANCODE_T)) &&
        !super_saiyan) {
      goku.GetMutableSprite().PlayAnimation(AnimationType::kSsTransformation);
      super_saiyan = true;
    }
    if (input_.WasKeyPressed(SDL_SCANCODE_U) ||
        input_.IsKeyHeld(SDL_SCANCODE_U)) {
      super_saiyan = false;
    }

    Perf::GetPerf()->StopTimer("input");

    graphics_.AddSprite(goku.GetSprite(), goku.GetLocation());
    Perf::GetPerf()->StartTimer("draw");
    graphics_.DrawNextFrame();
    Perf::GetPerf()->StopTimer("draw");

    LimitFrameRate();
    Perf::GetPerf()->StopTimer("game_loop");
    Perf::GetPerf()->ReportResults();
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
