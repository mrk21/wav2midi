#ifndef WAV2MIDI_FFT_FFT_HPP
#define WAV2MIDI_FFT_FFT_HPP

#include <wav2midi/fft/window.hpp>
#include <vector>
#include <complex>

namespace wav2midi::fft {
    class fft {
    public:
        fft(const std::vector<double> & samplings, window::window_t window);
        const std::vector<std::complex<double>> & execute();

    private:
        std::vector<std::complex<double>> frequencies_;
    };
}

#endif
