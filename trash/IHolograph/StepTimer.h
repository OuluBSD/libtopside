#pragma once
#if 0

NAMESPACE_PARALLEL_BEGIN


namespace DX {

// Helper class for animation and simulation timing.
class StepTimer
{
public:
    StepTimer() :
        elapsed_ticks(0),
        total_ticks(0),
        left_over_ticks(0),
        frame_count(0),
        frames_per_second(0),
        frames_this_second(0),
        qpc_second_counter(0),
        is_fixed_time_step(false),
        target_elapsed_ticks(TicksPerSecond / 60)
    {
        qpc_frequency = GetPerformanceFrequency();

        // Initialize max delta to 1/10 of a second.
        qpc_max_delta = qpc_frequency / 10;
    }

    // Get elapsed time since the previous Update call.
    uint64 GetElapsedTicks() const                          { return elapsed_ticks;                  }
    double GetElapsedSeconds() const                        { return TicksToSeconds(elapsed_ticks);  }

    // Get total time since the start of the program.
    uint64 GetTotalTicks() const                            { return total_ticks;                    }
    double GetTotalSeconds() const                          { return TicksToSeconds(total_ticks);    }

    // Get total number of updates since start of the program.
    uint32 GetFrameCount() const                            { return frame_count;                    }

    // Get the current framerate.
    uint32 GetFramesPerSecond() const                       { return frames_per_second;               }

    // Set whether to use fixed or variable timestep mode.
    void SetFixedTimeStep(bool is_fixed_timestep)           { is_fixed_time_step = is_fixed_timestep;    }

    // Set how often to call Update when in fixed timestep mode.
    void SetTargetElapsedTicks(uint64 target_elapsed)       { target_elapsed_ticks = target_elapsed;   }
    void SetTargetElapsedSeconds(double target_elapsed)     { target_elapsed_ticks = SecondsToTicks(target_elapsed);   }

    // Integer format represents time using 10,000,000 ticks per second.
    static const uint64 TicksPerSecond = 10'000'000;

    static double TicksToSeconds(uint64 ticks)            { return static_cast<double>(ticks) / TicksPerSecond;     }
    static uint64 SecondsToTicks(double seconds)          { return static_cast<uint64>(seconds * TicksPerSecond);   }

    // Convenient wrapper for QueryPerformanceFrequency. Throws an exception if
    // the call to QueryPerformanceFrequency fails.
    static inline uint64 GetPerformanceFrequency()
    {
        LARGE_INTEGER freq;
        if (!QueryPerformanceFrequency(&freq))
        {
            Holo::ThrowLastError();
        }

        return freq.quad_part;
    }

    // Gets the current number of ticks from QueryPerformanceCounter. Throws an
    // exception if the call to QueryPerformanceCounter fails.
    static inline int64 GetTicks()
    {
        LARGE_INTEGER ticks;
        if (!QueryPerformanceCounter(&ticks))
        {
            Holo::ThrowLastError();
        }

        return ticks.quad_part;
    }

    // After an intentional timing discontinuity (for instance a blocking IO operation)
    // call this to avoid having the fixed timestep logic attempt a set of catch-up
    // Update calls.

    void ResetElapsedTime()
    {
        qpc_last_time = GetTicks();

        left_over_ticks    = 0;
        frames_per_second  = 0;
        frames_this_second = 0;
        qpc_second_counter = 0;
    }

    // Update timer state, calling the specified Update function the appropriate number of times.
    template<typename TUpdate>
    void Tick(const TUpdate& update)
    {
        // Query the current time.
        uint64 current_time = GetTicks();
        uint64 time_delta   = current_time - qpc_last_time;

        qpc_last_time      = current_time;
        qpc_second_counter += time_delta;

        // Clamp excessively large time deltas (e.g. after paused in the debugger).
        if (time_delta > qpc_max_delta)
        {
            time_delta = qpc_max_delta;
        }

        // Convert QPC units into a canonical tick format. This cannot overflow due to the previous clamp.
        time_delta *= TicksPerSecond;
        time_delta /= qpc_frequency;

        uint32 lastFrameCount = frame_count;

        if (is_fixed_time_step)
        {
            // Fixed timestep update logic

            // If the app is running very close to the target elapsed time (within 1/4 of a millisecond) just clamp
            // the clock to exactly match the target value. This prevents tiny and irrelevant errors
            // from accumulating over time. Without this clamping, a game that requested a 60 fps
            // fixed update, running with vsync enabled on a 59.94 NTSC display, would eventually
            // accumulate enough tiny errors that it would drop a frame. It is better to just round
            // small deviations down to zero to leave things running smoothly.

            if (abs(static_cast<int64>(time_delta - target_elapsed_ticks)) < TicksPerSecond / 4000)
            {
                time_delta = target_elapsed_ticks;
            }

            left_over_ticks += time_delta;

            while (left_over_ticks >= target_elapsed_ticks)
            {
                elapsed_ticks    = target_elapsed_ticks;
                total_ticks     += target_elapsed_ticks;
                left_over_ticks -= target_elapsed_ticks;
                frame_count++;

                update();
            }
        }
        else {
            // Variable timestep update logic.
            elapsed_ticks  = time_delta;
            total_ticks   += time_delta;
            left_over_ticks = 0;
            frame_count++;

            update();
        }

        // Track the current framerate.
        if (frame_count != lastFrameCount)
        {
            frames_this_second++;
        }

        if (qpc_second_counter >= static_cast<uint64>(qpc_frequency))
        {
            frames_per_second   = frames_this_second;
            frames_this_second  = 0;
            qpc_second_counter %= qpc_frequency;
        }
    }

private:

    // Source timing data uses QPC units.
    uint64 qpc_frequency;
    uint64 qpc_last_time;
    uint64 qpc_max_delta;

    // Derived timing data uses a canonical tick format.
    uint64 elapsed_ticks;
    uint64 total_ticks;
    uint64 left_over_ticks;

    // Members for tracking the framerate.
    uint32 frame_count;
    uint32 frames_per_second;
    uint32 frames_this_second;
    uint64 qpc_second_counter;

    // Members for configuring fixed timestep mode.
    bool   is_fixed_time_step;
    uint64 target_elapsed_ticks;
};

}


NAMESPACE_PARALLEL_END
#endif
