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

/*
 * TODO
 * - [ ] add reduce step if there is an error;
 * - [ ] generate random characters and strings ?;
 * - [ ] output: macro to make it easier to use (filename, function, line, ...);
 * - [ ] progress bar;
 */

#define MAX_CONTAINER_SIZE 5

namespace pgl {
  namespace test {

    template<typename return_type, typename... FArgs>
      auto elapsed_ms(std::function<return_type(FArgs...)> fun, FArgs... args)
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
      auto elapsed_ms(std::function<void(FArgs...)> fun, FArgs... args)
      -> float
      {
        std::chrono::high_resolution_clock clock;
        auto start = clock.now();
        fun(args...);
        auto stop = clock.now();
        std::chrono::duration<double> duration = stop - start;
        return duration.count()*1000;
      }

    template<typename T>
      concept SequenceContainer = requires(T x) {
        { x.size() } -> std::convertible_to<size_t>;
      };

    template<typename Type>
      class RandomGenerator : public std::false_type {  };

    template<std::integral Type>
      class RandomGenerator<Type> {
        private:
          std::mt19937 gen;
          std::uniform_int_distribution<Type> distrib;

        public:
          RandomGenerator() :
            gen{std::random_device{}()},
            distrib{std::numeric_limits<Type>::min(),
              std::numeric_limits<Type>::max()} { }

          Type get() { return distrib(gen); }
      };

    template<std::floating_point Type>
      class RandomGenerator<Type> {
        private:
          std::mt19937 gen;
          std::uniform_real_distribution<Type> distrib;

        public:
          RandomGenerator() :
            gen{std::random_device{}()},
            /* distrib{std::numeric_limits<Type>::min(), */
            /* std::numeric_limits<Type>::max()} { } */
            distrib{-100'000'000, 100'000'000} { }

          Type get() { return distrib(gen); }
      };

    template<>
      class RandomGenerator<std::string> {
        private:
          std::mt19937 gen;
          std::uniform_int_distribution<char> distrib;

        public:
          RandomGenerator() :
            gen{std::random_device{}()},
            distrib{1, 127} {  }

          std::string get() {
            char size = distrib(gen);
            std::string res;
            res.reserve(size);
            while (res.size() != (std::size_t)size) {
              res.push_back(distrib(gen));
            }
            return res;
          }
      };

    template<template<typename T, uint32_t d> typename range,
             typename Type, uint32_t dim>
      class RandomGenerator<range<Type,dim>> {
        public:
          RandomGenerator() { }

          auto get() -> range<Type,dim> {
            range<Type,dim> t{};
            for (auto& val: t) {
              val = RandomGenerator<Type>().get();
            }
            return t;
          }
      };

    template<SequenceContainer Type>
      class RandomGenerator<Type> {
        private:
          using ValueType = typename Type::value_type;
          std::mt19937 gen;
          std::uniform_int_distribution<typename Type::size_type> distrib;

        public:
          RandomGenerator() : gen{std::random_device{}()},
            distrib{ValueType{0}, MAX_CONTAINER_SIZE} { }

          Type get() {
            Type t{};
            uint32_t size = distrib(gen);
            for (uint32_t i=0; i<size; ++i) {
              t.insert(t.end(), RandomGenerator<ValueType>().get());
            }
            return t;
          }
      };

    template<typename... Args>
      auto generate_arguments(uint32_t size)
      -> std::vector<std::tuple<std::remove_cvref_t<Args>...>>
      {
        std::vector<std::tuple<std::remove_cvref_t<Args>...>> res;
        for (uint32_t i=0; i<size; ++i) {
          res.push_back(
            std::make_tuple(RandomGenerator<std::remove_cvref_t<Args>>().get()...));
        }
        return res;
      }

    template<typename Type>
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
        for (const auto& val: t) {
          ss << val << (++n != t.size() ? ", " : "");
        }
        ss << '}';
        return ss.str();
      }

    template<typename... Args>
      void print_parameters(std::ostream& os, const std::tuple<Args...>& tpl) {
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

  } /* end of namespace test */
} /* end of namespace pgl */
