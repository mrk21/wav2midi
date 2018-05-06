#include <wav2midi/scale.hpp>
#include <cmath>
#include <boost/format.hpp>

namespace wav2midi {
    scale::item::item() {}
    scale::item::item(uint32_t n) {
        using namespace std;
        this->n = n;
        this->local_no = n % 12u;
        this->octave = (n + 9u) / 12u;
        this->frequency = 27.5 * pow(2.0, n / 12.0);
        this->name = (boost::format(item::names[this->local_no]) % this->octave).str();
    }
}

namespace wav2midi {
    const std::vector<std::string> scale::item::names{{
        "A%d",
        "A#%d",
        "B%d",
        "C%d",
        "C#%d",
        "D%d",
        "D#%d",
        "E%d",
        "F%d",
        "F#%d",
        "G%d",
        "G#%d",
    }};

    scale::scale() {
        for (auto n = 0u; n < N; ++n) {
            items.push_back({n});
        }
    }

    const scale::item & scale::operator [](uint32_t n) const {
        static item unknown{0};
        return n < 88u ? items[n] : unknown;
    }

    const scale::item & scale::match(double f) const {
        return (*this)[f_to_n(f)];
    }

    uint32_t scale::f_to_n(double f) const {
        using namespace std;
        return round(12.0 * log2(f / 27.5));
    }
}
