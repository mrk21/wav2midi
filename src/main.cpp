#include <wav2midi/audio_stream.hpp>
#include <wav2midi/fft.hpp>
#include <wav2midi/scale.hpp>
#include <iostream>
#include <fstream>
#include <cstdio>
#include <boost/format.hpp>

int main() {
    FILE * gnuplot = popen("gnuplot", "w");
    fprintf(gnuplot, "set tmargin 5\n");
    fprintf(gnuplot, "set bmargin 5\n");
    fprintf(gnuplot, "set rmargin 8\n");
    fprintf(gnuplot, "set lmargin 8\n");
    fprintf(gnuplot, "set xrange [160:2000]\n");
    fprintf(gnuplot, "set yrange [0:800]\n");
    fprintf(gnuplot, "plot 0\n");
    fflush(gnuplot);

    while (true) {
        wav2midi::audio_stream as("../test/fixture/sound/octave4.wav");
        wav2midi::scale scale;

        as.read(std::pow(2, 12), [&gnuplot, &scale](auto f_s) {
            auto F_s = wav2midi::fft(f_s).execute();
            const auto N = F_s.size();
            auto max_amp = 0.0;
            auto max_freq = 0.0;

            {
                std::ofstream ofs("data.dat");

                for (auto k = 0u; k < N; ++k) {
                    auto freq = 44.1 * 1000 * k / N;
                    if (freq < 160) continue;
                    if (freq > 2000) continue;

                    auto amp = std::abs(F_s[k]);
                    ofs << freq << " " << amp << std::endl;
                    if (max_amp < amp) {
                        max_amp = amp;
                        max_freq = freq;
                    }
                    ofs << freq << " " << amp << std::endl;
                }
                std::cout << "========================" << std::endl;
            }
            auto item = scale.match(max_freq);
            auto label = (boost::format("%s: %f Hz => %f") % item.name % max_freq % max_amp).str();
            std::cout << label << std::endl;
            fprintf(gnuplot, "plot 'data.dat' using 1:2 with lines\n");
            fprintf(gnuplot, "set label 1 at screen 0.05, 0.05 \"%s\"\n", label.c_str());
            fflush(gnuplot);

            return false;
        });

        std::cout << "=====================================================================" << std::endl;
        std::cout << "You can finish this program when you entered \"q\"; otherwise you can retry this program." << std::endl;
        std::cout << ">> ";
        std::string command;
        std::cin >> command;
        if (command == "q") break;
    }

    fclose(gnuplot);
    return 0;
}
