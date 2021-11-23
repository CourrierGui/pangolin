#include <gtest/gtest.h>

#include <sstream>

#include <pgl-tools/logger.hpp>

class Logger : public testing::Test {
    public:
        virtual void SetUp() override {
            pgl::logstream(ss);
            pgl::loglevel(pgl::level::info);
        }

        virtual void TearDown() override {
            ss.str(std::string{});
        }

    protected:
        std::stringstream ss;
};

void ends_with(const std::string& lhs, const std::string& rhs)
{
    ASSERT_GE(lhs.size(), rhs.size());
    ASSERT_EQ(lhs.substr(lhs.size()-rhs.size(), rhs.size()), rhs);
}

TEST_F(Logger, Info)
{
    pgl::info() << "toto";
    ends_with(ss.str(), "toto");
}

TEST_F(Logger, Format)
{
    pgl::info().format("toto");
    ends_with(ss.str(), "toto");
}

TEST_F(Logger, FormatWithArguments)
{
    pgl::info().format("toto {} {}", 10, 11);
    ends_with(ss.str(), "toto 10 11");
}

TEST_F(Logger, FormatWithArgumentsAndStream)
{
    pgl::info().format("toto {} ", 10) << 11;
    ends_with(ss.str(), "toto 10 11");
}

TEST_F(Logger, LowerLevelIsNotDisplayed)
{
    pgl::loglevel(pgl::level::error);
    pgl::info() << "This will not be displayed.";
    ASSERT_EQ(ss.str(), "");
}

TEST_F(Logger, HigherLevelIsDisplayed)
{
    pgl::loglevel(pgl::level::warn);
    pgl::error() << "This is important";
    ends_with(ss.str(), "This is important");
}

TEST_F(Logger, DebugNotDisplayByDefault)
{
    pgl::debug() << "This should not be displayed";
    ASSERT_EQ(ss.str(), "");
}
