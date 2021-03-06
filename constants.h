#ifndef CONSTANTS_H
#define CONSTANTS_H

// Constants we want to access from various places in the program.
namespace constants {
constexpr int kWindowWidth = 1000;
constexpr int kWindowHeight = 596;
constexpr float kBackgroundScale = 2.0f;
constexpr float kGokuScale = 2.0f;
// This controls how far goku moves in pixels when he runs.
constexpr int kGokuSpeed = 4;
constexpr int kSsGokuSpeedMod = 4;
constexpr int kFps = 50;
constexpr int kMaxFrameTimeMs = 1000 / kFps;
constexpr int kFramesPerFpsCheck = 100;
}  // namespace constants

#endif /* CONSTANTS_H */
