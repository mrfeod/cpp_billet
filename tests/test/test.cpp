#define DOCTEST_CONFIG_IMPLEMENT
#include <doctest/doctest.h>

#include <fmt/format.h>

#include <utils/random.h>
#include <utils/logging/log.h>

#include <utils/enum.h>

#include <constants.h>

namespace fs = std::filesystem;

using namespace sloth;
using namespace sloth::util;

namespace {

}  // namespace

struct TestFixture  // NOLINT(cppcoreguidelines-*)
{
};

//NOLINTNEXTLINE(readability-function-cognitive-complexity)
TEST_CASE_FIXTURE(TestFixture, "Test") { CHECK(true); }

int main(int argc, char** argv)
{
    // sloth::logging::Logger::Instance().SetLogLevel(L_TRACE);
    // QApplication app(argc, argv);
    return doctest::Context(argc, argv).run();
}