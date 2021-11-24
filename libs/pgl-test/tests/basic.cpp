#include <pgl-test/test_suite.hpp>

static bool commutativity(int a, int b)
{
    return a + b == b + a;
}

static bool add0(int a)
{
    return a + 0 == a;
}

template<typename type>
static bool associativity(type a, type b, type c)
{
    return (a + b) + c == (a + c) + b;
}

using namespace pgl::test;

int main()
{
    test_suite ts1{
        test_case{"addition by 1 is constant", add0},
        test_case{"addition is commutative", commutativity},
    };

    test_suite ts{
        ts1,
        test_case{"addition is associative", associativity<int>},
        test_case{"addition is associative", associativity<int32_t>},
        test_case{"addition is associative", associativity<uint32_t>},
    };

    return check(ts);
}
