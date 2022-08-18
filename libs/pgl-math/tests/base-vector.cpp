#include <pgl-math/impl/base-vector.hpp>
#include <pgl-test/test_suite.hpp>
#include <cmath>

#include <array>

using namespace pgl::test;

template<pgl::integral type, pgl::length dim>
struct vector : public pgl::base_vector<type,dim,vector> {
    /* FIXME bool * is convertible to bool */
    inline constexpr vector(std::convertible_to<type> auto ... args) noexcept :
        pgl::base_vector<type,dim,vector>{ args... }
    {
    }

    inline constexpr vector(type arr[dim]) noexcept :
        pgl::base_vector<type,dim,vector>{ arr }
    {
    }

};

template<typename T>
bool test_default()
{
    vector<T, 2> v;

    return v.x == T{0} && v.y == T{0};
}

template<typename T>
bool test_single_value(T a)
{
    vector<T, 2> v(a);

    return v.x == a && v.y == a;
}

template<typename T>
bool test_accessor(T a, T b)
{
    vector<T, 2> v2{a, b};

    return v2.x == a && v2.y == b;
}

template<typename T>
bool test_from_array(T a, T b)
{
    T data[2] = { a, b };
    vector<T, 2> v(data);

    return v.x == a && v.y == b;
}

template<typename T>
bool test_raw_data(T a, T b)
{
    vector<T, 2> v(a, b);
    auto rd = v.data();

    return rd.size == 2 && rd.data[0] == a && rd.data[1] == b;
}

template<typename T>
bool test_size()
{
    vector<T, 2> v;

    return v.size() == 2;
}

template<typename T>
bool test_begin(T a, T b)
{
    vector<T, 2> v(a, b);

    return *v.begin() == a;
}

template<typename T>
bool test_end(T a, T b)
{
    vector<T, 2> v(a, b);
    auto end = v.end();

    return *(--end) == b;
}

/* FIXME make the input const by creating a data() const member function */
template<typename T, uint32_t N>
bool test_iterators(vector<T, N>& arr)
{
    vector<T, N> val((T *)arr.data().data);
    auto iter = val.begin();

    for (auto v: arr) {
        if (*iter++ != v)
            return false;
    }

    return true;
}

int main()
{
    test_suite constructors{
        test_case{"init vector from array", test_from_array<int>   },
        test_case{"init x and y accessors", test_accessor<int>     },
        test_case{"init from single value", test_single_value<int> },
        test_case{"init vector from array", test_from_array<int>   },
        test_case{"raw data accessors",     test_raw_data<int>     },
        test_case{"size accessor",          test_size<int>         },
        test_case{"begin accessor",         test_begin<int>        },
        test_case{"end accessor",           test_end<int>          },
        /* test_case{"init vector<uint, 2>",     test_accessor<uint>    }, */
        /* test_case{"init vector<int32_t, 2>",  test_accessor<int32_t> }, */
        /* test_case{"init vector<uint32_t, 2>", test_accessor<uint32_t>}, */
        /* test_case{"init vector<bool, 2>",     test_accessor<bool>    }, */
    };


    test_suite iterators{
        /* test_case{"iterators int",      test_iterators<int, 5>}, */
        /* test_case{"iterators uint",     test_iterators<uint, 5>}, */
        /* test_case{"iterators int32_t",  test_iterators<int32_t, 5>}, */
        test_case{"iterators uint32_t", test_iterators<uint32_t, 5>},
        // FIXME this test does not work because bool * is convertible to bool
        /* test_case{"iterators bool",     test_iterators<bool, 5>}, */
    };

    test_suite ts{
        /* constructors, */
        iterators,
    };

    return check(ts);
}
