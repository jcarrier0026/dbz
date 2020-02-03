#ifndef CONSTANTS_H
#define CONSTANTS_H

// Constants we want to access from various places in the program.
namespace constants {
constexpr int kWindowWidth = 640;
constexpr int kWindowHeight = 480;
constexpr int kFps = 50;
constexpr int kMaxFrameTimeMs = 1000 / kFps;
constexpr int kFramesPerFpsCheck = 100;
}  // namespace constants

#endif /* CONSTANTS_H */
