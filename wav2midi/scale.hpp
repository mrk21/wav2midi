#ifndef WAV2MIDI_AUDIO_SCALE_HPP
#define WAV2MIDI_AUDIO_SCALE_HPP

#include <vector>
#include <string>

namespace wav2midi {
    class scale {
    public:
        static constexpr auto N = 88u;

        struct item {
            uint32_t n;
            uint32_t local_no;
            uint32_t octave;
            double frequency;
            std::string name;

            item();
            item(uint32_t n);

            static const std::vector<std::string> names;
        };

        scale();
        const item & operator [](uint32_t n) const;
        const item & match(double f) const;
        uint32_t f_to_n(double f) const;

    private:
        std::vector<item> items;
    };
}

#endif
