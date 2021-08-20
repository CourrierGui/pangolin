#include <gtest/gtest.h>

#include <sstream>

#include <pgl-tools/logger.hpp>

/* TODO test fixture */
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

TEST_F(Logger, Info)
{
    pgl::info() << "toto";
    ASSERT_EQ(ss.str(), "toto");
}

TEST_F(Logger, Format)
{
    pgl::info().format("toto");
    ASSERT_EQ(ss.str(), "toto");
}

TEST_F(Logger, FormatWithArguments)
{
    pgl::info().format("toto {} {}", 10, 11);
    ASSERT_EQ(ss.str(), "toto 10 11");
}

TEST_F(Logger, FormatWithArgumentsAndStream)
{
    pgl::info().format("toto {} ", 10) << 11;
    ASSERT_EQ(ss.str(), "toto 10 11");
}
