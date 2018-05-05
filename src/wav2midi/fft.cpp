#include <wav2midi/fft.hpp>
#include <boost/math/constants/constants.hpp>

namespace wav2midi {
    using namespace std::complex_literals;
    constexpr auto pi = boost::math::constants::pi<double>();

// public
    const std::vector<std::complex<double>> & fft::execute() {
        const auto N = x.size();
        fft_(x, N);
        return x;
    }

// private
    // @see http://geisterchor.blogspot.jp/2015/05/cfft.html
    std::complex<double> fft::W(uint32_t n, std::size_t N) {
        return std::exp(-1.0i * (2 * pi * n / N));
    }

    void fft::fft_(std::vector<std::complex<double>> & x, std::size_t N) {
        if (N <= 1) return;

        std::vector<std::complex<double>> x_E(N/2);
        std::vector<std::complex<double>> x_O(N/2);

        for (auto j = 0u; j < N/2; ++j) {
            x_E[j] = (x[j] + x[N/2 + j]);
            x_O[j] = (x[j] - x[N/2 + j]) * W(j, N);
        }

        fft_(x_E, N/2);
        fft_(x_O, N/2);

        for (auto j = 0u; j < N/2; ++j) {
            x[2*j    ] = x_E[j];
            x[2*j + 1] = x_O[j];
        }
    }
}
