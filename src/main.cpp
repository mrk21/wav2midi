#include <wav2midi/audio_stream.hpp>
#include <wav2midi/fft.hpp>
#include <wav2midi/scale.hpp>
#include <iostream>
#include <fstream>
#include <cstdio>
#include <boost/format.hpp>

int main(int argc, char * argv[]) {
    std::string path = argc == 1 ? "/dev/stdin" : argv[1];
    std::cout << "Read from " << path << std::endl;;

    FILE * gnuplot = popen("gnuplot", "w");
    fprintf(gnuplot, "set tmargin 5\n");
    fprintf(gnuplot, "set bmargin 5\n");
    fprintf(gnuplot, "set rmargin 8\n");
    fprintf(gnuplot, "set lmargin 8\n");
    fprintf(gnuplot, "set xrange [20:5000]\n");
    fprintf(gnuplot, "set yrange [0:1000]\n");
    fprintf(gnuplot, "plot 0\n");
    fflush(gnuplot);

    while (true) {
        wav2midi::audio_stream as(path);
        wav2midi::scale scale;

        as.read(std::pow(2, 12), [&gnuplot, &scale](auto f_s) {
            auto F_s = wav2midi::fft(f_s).execute();
            const auto N = F_s.size();
            const auto threshold_amp = 50;
            auto max_amp = 0.0;
            auto max_freq = 0.0;

            {
                std::ofstream ofs("data.dat");

                auto k_f = [N](double f) -> uint32_t { return std::round(f / (44.1 * 1000) * N); };
                auto k_begin = k_f(scale[0].frequency);
                auto k_end = k_f(scale[87].frequency);

                for (auto k = k_begin; k < k_end; ++k) {
                    auto freq = 44.1 * 1000 * k / N;

                    auto amp = std::abs(F_s[k]);
                    ofs << freq << " " << amp << std::endl;
                    if (max_amp < amp && amp > threshold_amp) {
                        max_amp = amp;
                        max_freq = freq;
                    }
                    ofs << freq << " " << amp << std::endl;
                }
                std::cout << "========================" << std::endl;
            }
            auto item = scale.match(max_freq);
            auto label = (
                boost::format("%f [Hz]: %f => %s: %f [Hz]")
                % max_freq
                % max_amp
                % item.name
                % item.frequency
            ).str();
            auto gp_label1 = (
                boost::format("{/=16 %s}{/=12 : %.2f [Hz]}")
                % item.name
                % item.frequency
            ).str();
            auto gp_label2 = (
                boost::format("{/=12 %.2f [Hz]: %.2f}")
                % max_freq
                % max_amp
            ).str();
            std::cout << label << std::endl;
            fprintf(gnuplot, "plot 'data.dat' using 1:2 with lines\n");
            fprintf(gnuplot, "set label 1 at screen 0.05, 0.05 \"%s\"\n", gp_label1.c_str());
            fprintf(gnuplot, "set label 2 at screen 0.65, 0.05 \"%s\"\n", gp_label2.c_str());
            fflush(gnuplot);

            return false;
        });

        if (path == "/dev/stdin") {
            break;
        }
        else {
            std::cout << "=====================================================================" << std::endl;
            std::cout << "You can finish this program when you entered \"q\"; otherwise you can retry this program." << std::endl;
            std::cout << ">> ";
            std::string command;
            std::cin >> command;
            if (command == "q") break;
        }
    }

    fclose(gnuplot);
    return 0;
}
