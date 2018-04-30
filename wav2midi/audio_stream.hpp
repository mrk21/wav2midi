#include <sndfile.h>
#include <string>
#include <functional>

namespace wav2midi {
    class audio_stream {
    public:
        union volume {
            int data[2];
            struct {
                alignas(int) int l;
                alignas(int) int r;
            } channel;

            volume() : data{0} {}
        };

        using read_callback = std::function<void(std::size_t, const volume &)>;

        audio_stream(std::string path);
        void read(read_callback block);

    private:
        SF_INFO info;
        SNDFILE * file;
    };
}
