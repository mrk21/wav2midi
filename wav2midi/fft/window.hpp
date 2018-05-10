#ifndef WAV2MIDI_FFT_WINDOW_HPP
#define WAV2MIDI_FFT_WINDOW_HPP

#include <functional>

namespace wav2midi::fft::window {
    using window_t = std::function<double(double)>;

    double rectangular(double x);
    double hanning(double x);
    double flat_top(double x);
}

#endif
