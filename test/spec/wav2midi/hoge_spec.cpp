#include <bandit/bandit.h>
#include <wav2midi/hoge.hpp>

namespace {

using namespace snowhouse;
using namespace bandit;

go_bandit([]{
    describe("wav2midi::hoge", []{
        it("should pass", [&]{
            wav2midi::hoge instance;
            AssertThat(instance.str(), Equals("hoge"));
        });
    });
});
}
