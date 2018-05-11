#include <wav2midi/scale.hpp>
#include <cmath>
#include <boost/format.hpp>

// scale::item
namespace wav2midi {
    namespace {
        const std::vector<std::string> scale_names{{
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
    }

    scale::item::item(uint32_t no) {
        using namespace std;
        no_ = no;
        local_no_ = no_ % 12u;
        octave_ = (no_ + 9u) / 12u;
        frequency_ = scale::frequency_to_no(no_);
        name_ = (boost::format(scale_names[local_no_]) % octave_).str();
    }

    uint32_t scale::item::no() const { return no_; }
    uint32_t scale::item::local_no() const { return local_no_; }
    uint32_t scale::item::octave() const { return octave_; }
    double scale::item::frequency() const { return frequency_; }
    const std::string & scale::item::name() const { return name_; }

}

// scale
namespace wav2midi {
    scale::scale() {
        for (auto no = 0u; no < scale::n; ++no) {
            items_.emplace_back(no);
        }
    }

    const scale::item & scale::operator [](uint32_t no) const {
        static item unknown{0};
        return no < 88u ? items_[no] : unknown;
    }

    const scale::item & scale::match(double frequency) const {
        return (*this)[scale::frequency_to_no(frequency)];
    }

    uint32_t scale::frequency_to_no(double frequency) {
        using namespace std;
        return round(12.0 * log2(frequency / 27.5));
    }

    double scale::no_to_frequency(uint32_t no) {
        using namespace std;
        return 27.5 * pow(2.0, no / 12.0);
    }
}
