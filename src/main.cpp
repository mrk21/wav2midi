#include <wav2midi/audio_stream.hpp>
#include <wav2midi/fft/fft.hpp>
#include <wav2midi/fft/window.hpp>
#include <wav2midi/scale.hpp>
#include <wav2midi/gnuplot.hpp>
#include <iostream>
#include <fstream>
#include <cstdio>
#include <boost/format.hpp>

int main(int argc, char * argv[]) {
    std::string path = argc == 1 ? "/dev/stdin" : argv[1];
    std::cout << "Read from " << path << std::endl;;

    wav2midi::gnuplot wave_gnuplot;
    wave_gnuplot.command("set title '{/=16 Wave}'");
    wave_gnuplot.command("set tmargin 5");
    wave_gnuplot.command("set bmargin 5");
    wave_gnuplot.command("set rmargin 8");
    wave_gnuplot.command("set lmargin 8");
    wave_gnuplot.command("set xrange [0:0.046]");
    wave_gnuplot.command("set yrange [-0.1:0.1]");
    wave_gnuplot.open();

    wav2midi::gnuplot fft_gnuplot;
    fft_gnuplot.command("set title '{/=16 FFT}'");
    fft_gnuplot.command("set tmargin 5");
    fft_gnuplot.command("set bmargin 5");
    fft_gnuplot.command("set rmargin 8");
    fft_gnuplot.command("set lmargin 8");
    fft_gnuplot.command("set xrange [0:5000]");
    fft_gnuplot.command("set yrange [0:20]");
    fft_gnuplot.open();

    while (true) {
        wav2midi::audio_stream as(path);
        wav2midi::scale scale;

        as.read(std::pow(2, 12), [&wave_gnuplot, &fft_gnuplot, &scale](auto samplings) {
            {
                std::ofstream ofs("wave.dat");

                for (auto x = 0u; x < samplings.size(); ++x) {
                    auto t = x * 1.0 / (44.1 * 1000);
                    auto amp = samplings[x];
                    ofs << t << " " << amp << std::endl;
                }
                wave_gnuplot.command("plot 'wave.dat' using 1:2 with lines");
                wave_gnuplot.flush();
            }

            auto frequences = wav2midi::fft::fft(samplings, wav2midi::fft::window::hanning).execute();
            const auto n = frequences.size();
            const auto threshold_amp = 1;
            auto max_amp = 0.0;
            auto max_freq = 0.0;

            {
                std::ofstream ofs("fft.dat");

                auto k_f = [n](double f) -> uint32_t { return std::round(f / (44.1 * 1000) * n); };
                auto k_begin = k_f(scale[0].frequency());
                auto k_end = k_f(scale[87].frequency());

                for (auto k = k_begin; k < k_end; ++k) {
                    auto freq = 44.1 * 1000 * k / n;

                    auto amp = std::abs(frequences[k]);
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
                % item.name()
                % item.frequency()
            ).str();
            auto gp_label1 = (
                boost::format("{/=16 %s}{/=12 : %.2f [Hz]}")
                % item.name()
                % item.frequency()
            ).str();
            auto gp_label2 = (
                boost::format("{/=12 %.2f [Hz]: %.2f}")
                % max_freq
                % max_amp
            ).str();
            std::cout << label << std::endl;
            fft_gnuplot.command("plot 'fft.dat' using 1:2 with lines");
            fft_gnuplot.command("set label 1 at screen 0.05, 0.05 '%s'", gp_label1);
            fft_gnuplot.command("set label 2 at screen 0.65, 0.05 '%s'", gp_label2);
            fft_gnuplot.flush();

            return false;
        });

        if (path == "/dev/stdin") {
            break;
        }
        else {
            std::cout << "=====================================================================" << std::endl;
            std::cout << "You can finish this program when you entered 'q'; otherwise you can retry this program." << std::endl;
            std::cout << ">> ";
            std::string command;
            std::cin >> command;
            if (command == "q") break;
        }
    }

    return 0;
}
