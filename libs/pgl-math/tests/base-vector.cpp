#include <pgl-math/impl/base-vector.hpp>
#include <pgl-test/test_suite.hpp>
#include <cmath>

using namespace pgl::test;

template<pgl::integral type, pgl::length dim>
struct vector : public pgl::base_vector<type,dim,vector> {
    inline constexpr vector(std::convertible_to<type> auto ... args) noexcept :
        pgl::base_vector<type,dim,vector>{ args... }
    {
    }
};

/* TODO for 1D vectors v == x, ...  */
template<typename T>
bool test_accessor(T a, T b, T c, T d)
{
    vector<T, 2> v2{a, b};
    vector<T, 3> v3{a, b, c};
    vector<T, 4> v4{a, b, c, d};

    auto res = v2.x == a && v2.y == b;
    res &= v3.x == a && v3.y == b && v3.z == c;
    res &= v4.x == a && v4.y == b && v4.z == c && v4.w == d;

    return res;
}

/* TODO add size as a template parameter
 */
template<typename T>
bool test_iterators(T a, T b, T c, T d, T e, T f)
{
    vector<T, 6> val{a, b, c, d, e, f};
    auto iter = val.begin();
    bool res = true;

    res &= (*iter++ == a);
    res &= (*iter++ == b);
    res &= (*iter++ == c);
    res &= (*iter++ == d);
    res &= (*iter++ == e);
    res &= (*iter++ == f);

    return res;
}

int main()
{
    test_suite accessors{
        test_case{"init vector<int, 2>",      test_accessor<int>     },
        test_case{"init vector<uint, 2>",     test_accessor<uint>    },
        test_case{"init vector<int32_t, 2>",  test_accessor<int32_t> },
        test_case{"init vector<uint32_t, 2>", test_accessor<uint32_t>},
        test_case{"init vector<bool, 2>",     test_accessor<bool>    },
    };

    test_suite iterators{
        test_case{"iterators int",      test_iterators<int>},
        test_case{"iterators uint",     test_iterators<uint>},
        test_case{"iterators int32_t",  test_iterators<int32_t>},
        test_case{"iterators uint32_t", test_iterators<uint32_t>},
        test_case{"iterators bool",     test_iterators<bool>},
    };

    test_suite ts{
        accessors,
        iterators,
    };

    return check(ts);
}
