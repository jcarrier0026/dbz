#include "perf.h"

#include <SDL2/SDL.h>

#include <iomanip>
#include <iostream>
#include <utility>

#include "constants.h"

constexpr float kMsPerSecond = 1000.0;

// Static members must be initialized out-of-line.
std::unique_ptr<Perf> Perf::instance_ = nullptr;

Perf* Perf::GetPerf() {
  if (!instance_) {
    // Calling `new` to access private ctor.
    instance_ =
        std::unique_ptr<Perf>(new Perf(true, constants::kFramesPerFpsCheck));
  }
  return instance_.get();
}

void Perf::StartTimer(std::string phase_name) {
  if (enabled_) {
    phase_start_timers_[phase_name] = SDL_GetTicks();
  }
}

void Perf::StopTimer(std::string phase_name) {
  if (enabled_) {
    if (phase_start_timers_.find(phase_name) == phase_start_timers_.end()) {
      std::cout << "Unable to stop nonexistant timer " << phase_name
                << std::endl;
      return;
    }
    int current_time_ms = SDL_GetTicks();
    int elapsed_time_ms = current_time_ms - phase_start_timers_[phase_name];
    bool new_timer = phase_accumulated_time_.find(phase_name) ==
                     phase_accumulated_time_.end();
    int current_accumulated_time_ms =
        new_timer ? 0 : phase_accumulated_time_[phase_name];
    phase_accumulated_time_[phase_name] =
        current_accumulated_time_ms + elapsed_time_ms;
  }
}

float Perf::CalculateFps() {
  return kMsPerSecond / (phase_accumulated_time_["game_loop"] /
                         static_cast<float>(print_freq_in_frames_));
}

void Perf::ReportResults() {
  total_frames_++;
  if (enabled_ && (total_frames_ % print_freq_in_frames_ == 0)) {
    std::cout << "Performance Report After " << print_freq_in_frames_
              << " Frames" << std::endl;
    std::cout << "Average FPS: " << CalculateFps() << std::endl;

    for (const auto& [name, time] : phase_accumulated_time_) {
      float timer_average = static_cast<float>(time) / print_freq_in_frames_;
      std::cout << std::setw(15) << name << ": " << timer_average << "ms"
                << std::endl;
    }
    // Put a space between reports.
    std::cout << std::endl;

    // Clear the internal maps
    phase_start_timers_.clear();
    phase_accumulated_time_.clear();
  }
}
