#include <wav2midi/audio_stream.hpp>
#include <array>

namespace wav2midi {
    audio_stream::audio_stream(std::string path) {
        this->file = sf_open(path.c_str(), SFM_READ, &this->info);
    }

    void audio_stream::read(read_callback block) {
        std::array<volume, 100> buffer;
        int frame = 0;

        while (true) {
            const std::size_t readcount = sf_readf_int(this->file, buffer[0].data, buffer.size());
            if (readcount == 0) break;
            std::for_each(buffer.begin(), buffer.begin() + readcount, [&frame, &block](const auto & v) {
                ++frame;
                block(frame, v);
            });
        }
    }
}
