#include <gtest/gtest.h>

#include <sstream>

#include <pgl-tools/logger.hpp>

class Logger : public testing::Test {
    public:
        virtual void SetUp() override {
            pgl::logstream(ss);
        }

        virtual void TearDown() override {
            ss.str(std::string{});
        }

    protected:
        std::stringstream ss;
};

// TODO ends_with

void ends_with(const std::string& lhs, const std::string& rhs)
{
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
