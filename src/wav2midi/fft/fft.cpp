#include <wav2midi/fft/fft.hpp>
#include <boost/math/constants/constants.hpp>

namespace wav2midi::fft {
    namespace {
        using namespace std::complex_literals;

        constexpr auto pi = boost::math::constants::pi<double>();

        // @see http://geisterchor.blogspot.jp/2015/05/cfft.html
        std::complex<double> twiddle_factor(std::size_t n, uint32_t jk) {
            return std::exp(-1.0i * (2 * pi * jk / n));
        }

        void fft_detail(std::vector<std::complex<double>> & x, std::size_t n) {
            if (n <= 1) return;

            std::vector<std::complex<double>> x_e(n/2);
            std::vector<std::complex<double>> x_o(n/2);

            for (auto j = 0u; j < n/2; ++j) {
                x_e[j] = (x[j] + x[j + n/2]);
                x_o[j] = (x[j] - x[j + n/2]) * twiddle_factor(n, j);
            }

            fft_detail(x_e, n/2);
            fft_detail(x_o, n/2);

            for (auto j = 0u; j < n/2; ++j) {
                x[2*j    ] = x_e[j];
                x[2*j + 1] = x_o[j];
            }
        }
    }

// public
    fft::fft(const std::vector<double> & samplings, window::window_t window) {
        const auto n = samplings.size();

        for (auto i = 0u; i < n; ++i) {
            auto x = double(i) / (n - 1);
            frequencies_.emplace_back(samplings[i] * window(x));
        }
    }

    const std::vector<std::complex<double>> & fft::execute() {
        const auto n = frequencies_.size();
        fft_detail(frequencies_, n);
        return frequencies_;
    }
}
