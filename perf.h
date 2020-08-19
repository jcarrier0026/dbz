#ifndef PERF_H
#define PERF_H

#include <memory>
#include <string>
#include <unordered_map>

// Perf is a class designed to keep track of performance when performance
// profiling is desired. It can be enabled or disabled.
//
// It is a singleton that is not thread-safe.
//
// Usage:
//   For each phase of execution, call StartTimer with a name.
//   When that phase completes, call StopTimer with the same name.
//   The total time is accumulated for the desired number of frames,
//   specified in the ctor with the print_freq_in_frames variable.
//   Each timer should only be updated once per frame.
//   Start must be called before Stop for a given timer name.
class Perf {
 public:
  virtual ~Perf() = default;

  static Perf* GetPerf();

  // Start the timer with the given name.
  void StartTimer(std::string phase_name);

  // Stop the timer with the given name and accumulate the duration in the
  // total.
  void StopTimer(std::string phase_name);

  // Reports the timing results and clears the internal maps
  // if the number of displayed frames is equal to the desired
  // value specified by print_freq_in_frames.
  void ReportResults();

 private:
  // Ctor is private - this is a singleton.
  Perf(bool enabled, int print_freq_in_frames)
      : enabled_(enabled),
        print_freq_in_frames_(print_freq_in_frames),
        total_frames_(0) {}

  // The only perf object instance.
  static std::unique_ptr<Perf> instance_;

  // Computes and returns the FPS.
  float CalculateFps();

  int last_fps_check_time_ms_;
  bool enabled_;
  size_t print_freq_in_frames_;
  // Track the number of times ReportResults is called (once per frame).
  int total_frames_;

  std::unordered_map<std::string, int> phase_start_timers_;
  std::unordered_map<std::string, int> phase_accumulated_time_;
};

#endif /* PERF_H */
