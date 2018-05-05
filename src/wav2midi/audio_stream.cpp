#include <wav2midi/audio_stream.hpp>
#include <vector>
#include <array>
#include <cstdlib>

namespace {
    sf_count_t sndfile_popen_get_filelen(void * user_data) {
        return 1024 * 1024 * 1024; // Dummy
    }

    sf_count_t sndfile_popen_seek(sf_count_t offset, int whence, void * user_data) {
        FILE * fp = static_cast<FILE *>(user_data);
        return std::fseek(fp, offset, whence);
    }

    sf_count_t sndfile_popen_read(void * ptr, sf_count_t count, void * user_data) {
        FILE * fp = static_cast<FILE *>(user_data);
        return std::fread(ptr, sizeof(double), count, fp);
    }

    sf_count_t sndfile_popen_write(const void * ptr, sf_count_t count, void * user_data) {
        return -1; // Do nothing
    }

    sf_count_t sndfile_popen_tell(void * user_data) {
        FILE * fp = static_cast<FILE *>(user_data);
        return std::ftell(fp);
    }
}

namespace wav2midi {
    audio_stream::audio_stream(std::string path) {
        this->file = sf_open(path.c_str(), SFM_READ, &this->info);
    }

    audio_stream::audio_stream(FILE * popen) {
        SF_VIRTUAL_IO vio;
        vio.get_filelen = sndfile_popen_get_filelen;
        vio.seek = sndfile_popen_seek;
        vio.read = sndfile_popen_read;
        vio.write = sndfile_popen_write;
        vio.tell = sndfile_popen_tell;
        this->file = sf_open_virtual(&vio, SFM_READ, &this->info, popen);
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
