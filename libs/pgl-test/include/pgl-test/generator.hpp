#pragma once

#include <random>
#include <tuple>
#include <sstream>
#include <iostream>

#define MAX_CONTAINER_SIZE 5

namespace pgl {
  namespace test {

    template<typename Type>
        class random_generator {  };

    template<typename T>
        concept SequenceContainer = requires(T x) {
            { x.size() } -> std::convertible_to<size_t>;
            { x.resize() } -> std::convertible_to<void>;
        };

    template<typename T>
        concept printable = requires(T x) {
            { std::cout << x } -> std::convertible_to<std::ostream&>;
        };

    template<printable Type>
        auto print(const Type& t)
        -> const Type&
        {
            return t;
        }

    template<SequenceContainer Type>
        std::string print(const Type& t) {
            std::stringstream ss;
            ss << '{';
            typename Type::size_type n{0};

            for (const auto& val: t)
                ss << val << (++n != t.size() ? ", " : "");

            ss << '}';
            return ss.str();
        }

    template<std::convertible_to<size_t> dim_t,
             template<typename T, dim_t dim> class range,
             typename T, dim_t dim>
        std::string print(const range<T, dim>& vec)
        {
            std::stringstream ss;
            dim_t n{0};

            ss << '{';
            for (const auto& val: vec)
                ss << val << (++n != vec.size() ? ", " : "");

            ss << '}';
            return ss.str();
        }

    template<typename... Args>
        void print_parameters(std::ostream& os,
                              const std::tuple<Args...>& tpl)
        {
            if constexpr (sizeof...(Args) == 1) {
                std::apply([&os](auto&&... i) {
                    ((os
                      << "Argument:\n  "
                      << print(std::forward<decltype(i)>(i))), ...);
                }, tpl);
            } else {
                std::apply(
                    [&os](auto&&... i) {
                        std::size_t n{0}, arg{0};
                        ((os
                          << "Argument "
                          << (++arg)
                          << ":\n  "
                          << print(std::forward<decltype(i)>(i))
                          << (++n != sizeof...(Args) ? "\n" : "" ) ), ...);
                    },
                    tpl);
            }
        }

    template<>
        class random_generator<bool> {
            private:
                std::mt19937 gen;
                std::uniform_int_distribution<int> distrib;

            public:
                random_generator() :
                    gen{std::random_device{}()},
                    distrib{0, 1}
                {
                }

                bool get() { return distrib(gen) == 1; }
        };

    template<std::integral Type>
        class random_generator<Type>
        {
            private:
                std::mt19937 gen;
                std::uniform_int_distribution<Type> distrib;

            public:
                random_generator() :
                    gen{std::random_device{}()},
                    distrib{std::numeric_limits<Type>::min(),
                    std::numeric_limits<Type>::max()}
                {
                }

                Type get() { return distrib(gen); }
        };

    template<std::floating_point Type>
        class random_generator<Type> {
            private:
                std::mt19937 gen;
                std::uniform_real_distribution<Type> distrib;

            public:
                random_generator() :
                    gen{std::random_device{}()},
                    /* distrib{std::numeric_limits<Type>::min(), */
                    /* std::numeric_limits<Type>::max()} { } */
                    distrib{-100'000'000, 100'000'000}
                {
                }

                Type get() { return distrib(gen); }
        };

    template<>
        class random_generator<std::string> {
            private:
                std::mt19937 gen;
                std::uniform_int_distribution<char> distrib;

            public:
                random_generator() :
                    gen{std::random_device{}()},
                    distrib{1, 127}
                {
                }

                std::string get()
                {
                    char size = distrib(gen);
                    std::string res;
                    res.reserve(size);

                    while (res.size() != (std::size_t)size)
                        res.push_back(distrib(gen));

                    return res;
                }
        };

    template<std::convertible_to<size_t> dim_t,
             template<typename T, dim_t dim> class range,
             typename T, dim_t dim>
        class random_generator<range<T,dim>> {
            public:
                random_generator() { }

                auto get() -> range<T,dim>
                {
                    range<T,dim> t{};

                    for (auto& val: t)
                        val = random_generator<T>().get();

                    return t;
                }
        };

    template<SequenceContainer Type>
        class random_generator<Type> {
            private:
                using ValueType = typename Type::value_type;
                std::mt19937 gen;
                std::uniform_int_distribution<typename Type::size_type> distrib;

            public:
                random_generator() :
                    gen{std::random_device{}()},
                    distrib{ValueType{0}, MAX_CONTAINER_SIZE} { }

                Type get()
                {
                    Type t{};
                    uint32_t size = distrib(gen);

                    for (uint32_t i = 0; i < size; ++i)
                        t.insert(t.end(),
                                 random_generator<ValueType>().get());
                    return t;
                }
        };

    template<typename... Args>
    auto generate_arguments(uint32_t size)
        -> std::vector<std::tuple<std::remove_cvref_t<Args>...>>
    {
        std::vector<std::tuple<std::remove_cvref_t<Args>...>> res;

        for (uint32_t i=0; i<size; ++i)
            res.push_back(
                std::make_tuple(
                    random_generator<std::remove_cvref_t<Args>>().get()...));

        return res;
    }

    /* FIXME is this usefull? */
    template<>
      class random_generator<int> {
        private:
          std::mt19937 gen;
          std::uniform_int_distribution<int> distrib;

        public:
          random_generator() :
              gen(std::random_device{}()),
              distrib{std::numeric_limits<int>::min(),
                      std::numeric_limits<int>::max()}
          {
          }

          int get() { return distrib(gen); }
      };

  }
}
