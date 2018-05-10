#include <wav2midi/fft/window.hpp>
#include <boost/math/constants/constants.hpp>
#include <cmath>

namespace wav2midi::fft::window {
    namespace {
        constexpr auto pi = boost::math::constants::pi<double>();
    }

    double rectangular(double x) {
        return 0.0 <= x && x <= 1.0 ? 1.0 : 0.0;
    }

    double hanning(double x) {
        using namespace std;
        return rectangular(x) * (0.5 - 0.5 * cos(2 * pi * x));
    }

    // @see https://jp.mathworks.com/help/signal/ref/flattopwin.html
    double flat_top(double x) {
        using namespace std;
        static constexpr auto a0 = 0.21557895;
        static constexpr auto a1 = 0.41663158;
        static constexpr auto a2 = 0.277263158;
        static constexpr auto a3 = 0.083578947;
        static constexpr auto a4 = 0.006947368;

        return rectangular(x) * (
            a0
            - a1 * cos(2 * pi * x)
            + a2 * cos(4 * pi * x)
            - a3 * cos(6 * pi * x)
            + a4 * cos(8 * pi * x)
        );
    }
}
