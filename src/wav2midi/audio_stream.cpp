#include <wav2midi/audio_stream.hpp>
#include <vector>
#include <array>
#include <cstdlib>

namespace wav2midi {
    audio_stream::audio_stream(std::string path) {
        file_ = sf_open(path.c_str(), SFM_READ, &info_);
    }

    void audio_stream::read(std::size_t n, read_callback block) {
        std::vector<std::array<double, 2>> buffer(n);
        std::vector<double> volumes;

        while (true) {
            const std::size_t readcount = sf_readf_double(file_, &buffer[0][0], buffer.size());
            if (readcount == 0) break;

            std::for_each(buffer.begin(), buffer.begin() + readcount, [&volumes](const auto & v) {
                volumes.push_back(v[0]);
            });

            if (block(std::move(volumes))) break;
        }
    }
}
