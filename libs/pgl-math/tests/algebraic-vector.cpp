#include <pgl-math/impl/algebraic-vector.hpp>

#include <pgl-test/test_suite.hpp>

using namespace pgl::test;

template<pgl::integral type, pgl::length dim>
struct vector : public pgl::algebraic_vector<type,dim,vector> {
    inline constexpr vector(std::convertible_to<type> auto ... args) noexcept :
        pgl::algebraic_vector<type,dim,vector>{ args... }
    {
    }
};

/* COMMENT: this may probably be generic and could
 * be extracted from this file.
 */
bool multiply_by_one(int a, int b)
{
    vector<int, 2> v{a, b};

    v *= 1;

    return v.x == a && v.y == b;
}

bool multiply_by_zero(int a, int b)
{
    vector<int, 2> v{a, b};

    v *= 0;

    return v.x == 0 && v.y == 0;
}

bool add_zero(int a, int b)
{
    vector<int, 2> v{a, b};

    v += 0;

    return v.x == a && v.y == b;
}

bool addition_is_commutative(int a, int b, int c, int d)
{
    vector<int, 2> v1{a, b};
    vector<int, 2> v2{c, d};

    vector<int, 2> v{0, 0};
    v += v1;
    v += v2;

    vector<int, 2> w{0, 0};
    w += v2;
    w += v1;

    return v.x == w.x && v.y == w.y;
}

bool sub_zero(int a, int b)
{
    vector<int, 2> v{a, b};

    v -= 0;

    return v.x == a && v.y == b;
}

int main()
{
    test_suite multiplication {
        test_case{ "multiply by 1 is constant", multiply_by_one  },
        test_case{ "multiply by 0 is nul",      multiply_by_zero },
    };

    test_suite addition {
        test_case{ "adding 0 is constant",    add_zero                },
        test_case{ "addition is commutative", addition_is_commutative },
    };

    test_suite substraction {
        test_case{ "substracting 0 is constant", sub_zero },
    };

    test_suite ts{
        multiplication,
        addition,
        substraction,
    };

    return check(ts);
}
