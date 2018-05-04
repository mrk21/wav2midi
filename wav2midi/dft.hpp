#ifndef WAV2MIDI_DFT_HPP
#define WAV2MIDI_DFT_HPP

#include <vector>
#include <complex>

namespace wav2midi {
    class dft {
    public:
        std::vector<std::complex<double>> execute(const std::vector<double> &);
    };
}

#endif
