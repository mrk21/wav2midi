#include <wav2midi/dft.hpp>
#include <boost/math/constants/constants.hpp>

namespace wav2midi {
    std::vector<std::complex<double>> dft::execute(const std::vector<double> & f_s) {
        using namespace std::complex_literals;
        const auto N = f_s.size();
        const auto pi = boost::math::constants::pi<double>();
        std::vector<std::complex<double>> F_s;

        for (auto k = 0u; k < N; ++k) {
            std::complex<double> F_sk = 0.0 + 0.0i;

            for (auto j = 0u; j < N; ++j) {
                F_sk += f_s[j] * std::exp(-1.0i * (2.0 * pi * j * k / N));
            }

            F_s.push_back(F_sk);
        }

        return F_s;
    }
}
