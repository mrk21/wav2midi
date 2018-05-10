#include <wav2midi/fft/fft.hpp>
#include <boost/math/constants/constants.hpp>

namespace wav2midi::fft {
    using namespace std::complex_literals;
    constexpr auto pi = boost::math::constants::pi<double>();

// public
    fft::fft(const std::vector<double> & f, window::window_t w) {
        const auto N = f.size();

        for (auto i = 0u; i < N; ++i) {
            auto v = double(i) / (N - 1);
            x.push_back(f[i] * w(v));
        }
    }

    const std::vector<std::complex<double>> & fft::execute() {
        const auto N = x.size();
        fft_(x, N);
        return x;
    }

// private
    // @see http://geisterchor.blogspot.jp/2015/05/cfft.html
    std::complex<double> fft::W(std::size_t N, uint32_t n) {
        return std::exp(-1.0i * (2 * pi * n / N));
    }

    void fft::fft_(std::vector<std::complex<double>> & x, std::size_t N) {
        if (N <= 1) return;

        std::vector<std::complex<double>> x_E(N/2);
        std::vector<std::complex<double>> x_O(N/2);

        for (auto j = 0u; j < N/2; ++j) {
            x_E[j] = (x[j] + x[j + N/2]);
            x_O[j] = (x[j] - x[j + N/2]) * W(N, j);
        }

        fft_(x_E, N/2);
        fft_(x_O, N/2);

        for (auto j = 0u; j < N/2; ++j) {
            x[2*j    ] = x_E[j];
            x[2*j + 1] = x_O[j];
        }
    }
}
