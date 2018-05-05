#ifndef WAV2MIDI_FFT_HPP
#define WAV2MIDI_FFT_HPP

#include <vector>
#include <complex>
#include <iterator>
#include <algorithm>

namespace wav2midi {
    class fft {
    public:
        template<typename CollectionType>
        fft(const CollectionType & f) {
            std::copy(f.begin(), f.end(), std::back_inserter(x));
        }

        const std::vector<std::complex<double>> & execute();

    private:
        std::complex<double> W(uint32_t n, std::size_t N);
        void fft_(std::vector<std::complex<double>> & x, std::size_t N);

        std::vector<std::complex<double>> x;
    };
}

#endif
