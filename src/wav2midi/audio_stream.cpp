#include <wav2midi/audio_stream.hpp>
#include <vector>
#include <array>

namespace wav2midi {
    audio_stream::audio_stream(std::string path) {
        this->file = sf_open(path.c_str(), SFM_READ, &this->info);
    }

    void audio_stream::read(std::size_t n, read_callback block) {
        std::vector<std::array<double, 2>> buffer(n);
        std::vector<double> volumes;

        while (true) {
            const std::size_t readcount = sf_readf_double(this->file, &buffer[0][0], buffer.size());
            if (readcount == 0) break;

            std::for_each(buffer.cbegin(), buffer.cbegin() + readcount, [&volumes](const auto & v) {
                volumes.push_back(v[0]);
            });

            if (block(std::move(volumes))) break;
        }
    }
}
