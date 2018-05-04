#include <wav2midi/scale.hpp>
#include <cmath>
#include <boost/format.hpp>

namespace wav2midi {
    scale::item::item() {}
    scale::item::item(uint32_t n) {
        using namespace std;
        this->n = n;
        this->local_no = (n + 9) % 12;
        this->octave = (n + 9) / 12;
        this->frequency = 27.5 * pow(2.0, n / 12.0);
        this->name = (boost::format(item::names[this->local_no]) % this->octave).str();
    }

    const std::vector<std::string> scale::item::names{{
        "A%02d",
        "A#%02d",
        "B%02d",
        "C%02d",
        "C#%02d",
        "D%02d",
        "D#%02d",
        "E%02d",
        "F%02d",
        "F#%02d",
        "G%02d",
        "G#%02d",
    }};

    scale::scale() {
        for (auto n = 0u; n < N; ++n) {
            items.push_back({n});
        }
    }

    const scale::item & scale::operator [](uint32_t n) const {
        return items[n];
    }

    const scale::item & scale::match(double f) const {
        return items[f_to_n(f)];
    }

    uint32_t scale::f_to_n(double f) const {
        using namespace std;
        return round(12.0 * log2(f / 27.5));
    }
}
