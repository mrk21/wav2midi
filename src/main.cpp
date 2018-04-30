#include <wav2midi/audio_stream.hpp>
#include <iostream>
#include <fstream>

int main() {
    std::ofstream ofs("data.dat");
    wav2midi::audio_stream as("../test/fixture/sound/c3.wav");

    as.read([&ofs](auto frame, auto vol) {
        std::cout << vol.channel.l << " ";
        ofs << frame << " " << vol.channel.l << "\n";
    });
    std::cout << std::endl;

    return 0;
}
