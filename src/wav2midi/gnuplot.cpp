#include <wav2midi/gnuplot.hpp>

namespace wav2midi {
    gnuplot::gnuplot() {
        pipe = popen("gnuplot", "w");
    }

    gnuplot::~gnuplot() {
        pclose(pipe);
    }

    void gnuplot::open() {
        command("plot 0\n");
        flush();
    }

    void gnuplot::flush() {
        std::fflush(pipe);
    }
}
