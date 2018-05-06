#ifndef WAV2MIDI_GNUPLOT_HPP
#define WAV2MIDI_GNUPLOT_HPP

#include <cstdlib>
#include <string>
#include <boost/format.hpp>

namespace wav2midi {
    class gnuplot {
    public:
        gnuplot();
        ~gnuplot();
        void open();
        void flush();

        template<typename ... T>
        void command(const std::string & cmd, const T ... params) {
            auto formatted_cmd = (boost::format(cmd) % ... % params);
            std::fprintf(pipe, "%s\n", formatted_cmd.str().c_str());
            std::fflush(pipe);
        }

    private:
        FILE * pipe;
    };
}

#endif
