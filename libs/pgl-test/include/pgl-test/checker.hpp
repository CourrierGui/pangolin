#pragma once

#include <random>
#include <iostream>
#include <functional>
#include <tuple>
#include <concepts>
#include <cstddef>
#include <vector>
#include <sstream>
#include <chrono>
#include <utility>
#include <map>
#include <optional>

#include <pgl-test/generator.hpp>

/*
 * TODO
 * - [ ] add reduce step if there is an error;
 * - [ ] generate random characters and strings ?;
 * - [ ] output: macro to make it easier to use (filename,
 *       function, line, ...);
 * - [ ] progress bar;
 */

namespace pgl::test {

    template<typename return_type, typename... FArgs>
    auto elapsed_ms(std::function<return_type(FArgs...)> fun,
                    FArgs... args)
      -> std::pair<float, return_type>
    {
        std::chrono::high_resolution_clock clock;
        auto start = clock.now();
        auto res = fun(args...);
        auto stop = clock.now();
        std::chrono::duration<double> duration = stop - start;
        return {duration.count()*1000, res};
    }

    template<typename... FArgs>
    auto elapsed_ms(std::function<void(FArgs...)> fun,
                    FArgs... args)
        -> float
    {
        std::chrono::high_resolution_clock clock;
        auto start = clock.now();
        fun(args...);
        auto stop = clock.now();
        std::chrono::duration<double> duration = stop - start;
        return duration.count()*1000;
    }

    template<typename... Args>
        class Checker {
            private:
                template<typename Type>
                    using Func = std::function<Type(Args...)>;
                using ResultType = std::tuple<bool,uint32_t,int32_t>;

                Func<bool>                       _func;
                std::optional<Func<bool>>        _is_trivial;
                std::optional<Func<std::string>> _classifier;
                std::map<std::string,uint32_t>   _label_distribution;

                std::tuple<std::remove_cvref_t<Args>...> _false_arg;

            public:
                Checker(const Func<bool>& func) :
                    _func(func), _is_trivial{}, _classifier{},
                    _label_distribution{}, _false_arg{} {  };

                bool check(const std::string& message="", uint32_t size=100) {
                    using namespace std::placeholders;
                    auto f = std::function<ResultType(uint32_t)>{
                        std::bind(&Checker::make_checks, this, _1)
                    };

                    std::clog << "Checking that " << message << ":\n";
                    auto res = elapsed_ms(f, size);
                    display_result(res, size);
                    return std::get<0>(res.second);
                }

                void is_trival(const Func<bool>& func) {
                    _is_trivial = func;
                }

                void classify(const Func<std::string>& func) {
                    _classifier = func;
                }

            private:
                auto make_checks(uint32_t size)
                    -> ResultType
                    {
                        auto args{generate_arguments<Args...>(size)};
                        bool res{true};
                        uint32_t count{1};
                        uint32_t nb_trivial{0};
                        for (auto& val: args) {
                            if (_is_trivial.has_value()) {
                                std::apply([this, &nb_trivial](auto&&... i) {
                                    if (_is_trivial.value()(i...)) {
                                        ++nb_trivial;
                                    }
                                },
                                val);
                            }
                            if (_classifier.has_value()) {
                                std::apply([this](auto&&... i) {
                                    auto label = _classifier.value()(i...);
                                    if (_label_distribution.count(label)) {
                                        ++_label_distribution[label];
                                    } else {
                                        _label_distribution[label] = 1;
                                    }
                                },
                                val);
                            }
                            std::apply([this, &res](auto... i) {
                                res &= _func(i...);
                            },
                            val);

                            if (not res) {
                                _false_arg = val;
                                return {res, count, nb_trivial};
                            }
                            ++count;
                        }
                        return {res, count-1, nb_trivial};
                    }

                void display_result(
                    std::pair<float, ResultType>& values,
                    unsigned int size)
                {
                    auto [duration, res] = values;
                    auto [success, count, nb_trivial] = res;

                    if (success) {
                        std::clog << count << " tests passed";
                        if (_is_trivial.has_value()) {
                            std::clog << " with "
                                << std::floor(float(nb_trivial)/size*100) << "% of trivial cases" ;
                        }
                        std::clog << " (elapsed " << duration << " ms).\n";
                        if (_classifier.has_value()) {
                            for (const auto& [label, count]: _label_distribution) {
                                std::clog << "* " << label
                                    << ": " << std::floor(float(count)/size*100) << "%\n";
                            }
                        }
                        std::clog << '\n';
                    } else {
                        std::clog << "Test failed after " << count
                            << " attempt" << (count == 1 ? "" : "s" );
                        std::clog << " (" << duration << " ms).\n";
                        print_parameters(std::clog, _false_arg);
                        std::clog << "\n\n";
                    }
                }
        };

    template<typename... Args>
        auto make_checker_helper(const std::function<bool(Args...)>& f) {
            return Checker<Args...>{std::function{f}};
        }

    template<typename Function>
        auto make_checker(Function&& f) {
            return make_checker_helper(std::function{f});
        }

    template<typename Function>
        void check(const std::string& msg, Function&& f) {
            make_checker(f).check(msg);
        }

    template<typename Ret, typename Args>
        auto is_commutative(Ret (*func)(Args,Args)) {
            return make_checker([func](Args lhs, Args rhs) {
                return func(lhs,rhs) == func(rhs,lhs);
            });
        }

} /* end of namespace pgl::test */
