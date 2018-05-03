#include <vector>
#include <complex>

namespace wav2midi {
    class dft {
    public:
        std::vector<std::complex<double>> execute(const std::vector<double> &);
    };
}
