#ifndef WAV2MIDI_FFT_FFT_HPP
#define WAV2MIDI_FFT_FFT_HPP

#include <wav2midi/fft/window.hpp>
#include <vector>
#include <complex>
#include <iterator>
#include <algorithm>

namespace wav2midi::fft {
    class fft {
    public:
        fft(const std::vector<double> & f, window::window_t w = window::hanning);
        const std::vector<std::complex<double>> & execute();

    private:
        std::complex<double> W(std::size_t N, uint32_t n);
        void fft_(std::vector<std::complex<double>> & x, std::size_t N);

        std::vector<std::complex<double>> x;
    };
}

#endif
