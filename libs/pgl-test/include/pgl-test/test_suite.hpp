#pragma once

#include <pgl-test/generator.hpp>

#include <functional>
#include <iostream>
#include <string>
#include <vector>

namespace pgl::test {

    template<typename... Args>
    class test_case {
        public:
            test_case(const char *str,
                      std::function<bool(Args...)> func) :
                _message{str}, _function{func}
            {
            }

            test_case(const char *str,
                      bool (*func)(Args...)) :
                test_case{str, std::function<bool(Args...)>{func}}
            {
            }

            test_case(const std::string& str,
                      bool (*func)(Args...)) :
                test_case{str, std::function{func}}
            {
            }

            test_case(const std::string& str,
                      std::function<bool(Args...)> func) :
                test_case{str.c_str(), func}
            {
            }

            int run(std::vector<std::tuple<std::remove_cvref_t<Args>...>>& args) const
            {
                std::size_t count = 0;

                for (auto arg: args) {
                    bool res = std::apply(_function, arg);
                    count++;
                    if (!res)
                        return count;
                }

                return 0;
            }

            auto message() const -> const std::string&
            {
                return _message;
            }

        private:
            std::string _message;
            std::function<bool(Args...)> _function;
    };

    template<typename... Args>
    class test_suite {
        public:
            /* test_suite(test_case<Args>... args) : */
            test_suite(Args... args) :
                _test_cases{args...}
            {
            }

        private:
            /* std::tuple<test_case<Args>...> _test_cases; */
            std::tuple<Args...> _test_cases;

            template<size_t i, typename... UArgs>
            friend int check(const test_suite<UArgs...>& ts,
                             uint32_t size);
    };

    template<typename... Args>
    int check(const test_case<Args...>& tc, uint32_t size = 100)
    {
        auto args = generate_arguments<std::remove_cvref_t<Args>...>(size);
        auto res = tc.run(args);

        if (!res) {
            std::clog << "Success: " << tc.message() << '\n';
        } else {
            std::clog << "Error:   " << tc.message() << '\n';
            std::clog
                << "Test failed after " << res
                << " attempt" << (res > 1 ? "s\n" : "\n");
            print_parameters(std::clog, args[res]);
            std::clog << '\n';
        }

        return res;
    }

    template<size_t i = 0, typename... Args>
    int check(const test_suite<Args...>& ts, uint32_t size = 100)
    {
        if constexpr (i < sizeof...(Args)) {
            int rc = check(std::get<i>(ts._test_cases), size);
            if (!rc)
                return check<i + 1, Args...>(ts, size);
            else
                return rc;
        } else {
            return 0;
        }

    }

} /* end of namespace pgl::test */
