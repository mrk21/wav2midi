#ifndef WAV2MIDI_AUDIO_SCALE_HPP
#define WAV2MIDI_AUDIO_SCALE_HPP

#include <vector>
#include <string>

namespace wav2midi {
    class scale {
    public:
        static constexpr auto n = 88u;

        class item {
        public:
            uint32_t no() const;
            uint32_t local_no() const;
            uint32_t octave() const;
            double frequency() const;
            const std::string & name() const;

            item(uint32_t no);
        private:
            uint32_t no_;
            uint32_t local_no_;
            uint32_t octave_;
            double frequency_;
            std::string name_;
        };

        scale();
        const item & operator [](uint32_t no) const;
        const item & match(double frequency) const;

        static uint32_t frequency_to_no(double frequency);
        static double no_to_frequency(uint32_t no);

    private:
        std::vector<item> items_;
    };
}

#endif
