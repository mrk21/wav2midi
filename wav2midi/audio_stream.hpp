#ifndef WAV2MIDI_AUDIO_STREAM_HPP
#define WAV2MIDI_AUDIO_STREAM_HPP

#include <sndfile.h>
#include <string>
#include <functional>

namespace wav2midi {
    class audio_stream {
    public:
        using read_callback = std::function<bool(std::vector<double>)>;

        audio_stream(std::string path);
        void read(std::size_t n, read_callback block);

    private:
        SF_INFO info;
        SNDFILE * file;
    };
}

#endif
