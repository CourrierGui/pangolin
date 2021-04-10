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
 * - [X] look at QuickCheck;
 * - [X] support arrays;
 * - [X] display stuff on success/faillure;
 * - [X] display elapsed time;
 * - [X] improve the interface;
 * - [ ] improve the look of the output;
 * - [ ] progress bar;
 * - [X] inspect the input data (put tags on them) to see the distribution;
 * - [X] check for trivial answers (to make sure that enough of them were tested);
 * - [ ] support class methods (It works with lambdas);
 * - [X] support lambda functions/functors;
 * - [ ] add unit test support;
 * - [ ] compile time tests;
 * - [ ] generate random characters and strings ?;
 * - [ ] learn more about property based testing;
 * - [ ] add reduce step if there is an error;
 * - [ ] implement tests for databases ?;
 * - [ ] macro to make it easier to use (filename, function, line, ...);
 * - [ ] try to figure out a way to handle overloads.
 */

#define MAX_CONTAINER_SIZE 5

namespace pgl {
  namespace test {

    //TODO complete the concept!
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
          RandomGenerator() : gen{std::random_device{}()},
            distrib{std::numeric_limits<Type>::min(), std::numeric_limits<Type>::max()} { }

          Type get() { return distrib(gen); }
      };

    template<std::floating_point Type>
      class RandomGenerator<Type> {
        private:
          std::mt19937 gen;
          std::uniform_real_distribution<Type> distrib;

        public:
          RandomGenerator() : gen{std::random_device{}()},
            /* distrib{std::numeric_limits<Type>::min(), std::numeric_limits<Type>::max()} { } */
            distrib{-100'000'000, 100'000'000} { }

          Type get() { return distrib(gen); }
      };

    template<template<typename T, uint32_t d> class range, typename Type, uint32_t dim>
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
      const Type& print(const Type& t) { return t; }

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
            /* size_t size; */
            /* int status; */
            std::size_t n{0}, arg{0};
            ((os
              << "Argument "
              << (++arg)
              << ":\n  "
              << print(std::forward<decltype(i)>(i))
              << (++n != sizeof...(Args) ? "\n" : "" ) ), ...);
          }, tpl
          );
      }

    template<typename... Args>
      class Checker {
        private:
          template<class Type>
            using Func = std::function<Type(Args...)>;

        public:
          Checker(const Func<bool>& func)
            : _func(func), _is_trivial{}, _classifier{},
            _label_distribution{}, _false_arg{}
          {  };

          bool check(const std::string& message="", uint32_t size=100) {
            std::clog << "Checking " << message << ":\n";
            std::chrono::high_resolution_clock clock;
            auto start = clock.now();
            auto [res, count, nb_trivial] = make_checks(size);
            auto stop = clock.now();
            std::chrono::duration<double> duration = stop - start;

            if (res) {
              std::clog << count << " tests passed";
              if (_is_trivial.has_value()) {
                std::clog << " with "
                  << std::floor(float(nb_trivial)/size*100) << "% of trival cases" ;
              }
              std::clog << " (elapsed " << duration.count()*1000 << " ms).\n";
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
              std::clog << " (" << duration.count()*1000 << " ms).\n";
              print_parameters(std::clog, _false_arg);
              std::clog << "\n\n";
            }
            return res;
          }

          void is_trival(const Func<bool>& func)        { _is_trivial = func; }
          void classify (const Func<std::string>& func) { _classifier = func; }

          Func<bool>                       _func;
          std::optional<Func<bool>>        _is_trivial;
          std::optional<Func<std::string>> _classifier;
          std::map<std::string,uint32_t>   _label_distribution;

          std::tuple<std::remove_cvref_t<Args>...> _false_arg;

          auto make_checks(uint32_t size)
            -> std::tuple<bool,uint32_t,int32_t>
            {
              auto args = generate_arguments<Args...>(size);
              bool res = true;
              uint32_t count = 1;
              uint32_t nb_trivial = 0;
              for (auto& val: args) {
                if (_is_trivial.has_value()) {
                  std::apply([this, &nb_trivial](auto&&... i) {
                    if (_is_trivial.value()(i...)) {
                      ++nb_trivial;
                    }
                  }, val);
                }
                if (_classifier.has_value()) {
                  std::apply([this](auto&&... i) {
                    auto label = _classifier.value()(i...);
                    if (_label_distribution.count(label)) {
                      ++_label_distribution[label];
                    } else {
                      _label_distribution[label] = 1;
                    }
                  }, val);
                }
                std::apply(
                  [this, &res](auto... i) {
                    res &= _func(i...);
                  }, val);

                if (not res) {
                  _false_arg = val;
                  return {res, count, nb_trivial};
                }
                ++count;
              }
              return {res, count-1, nb_trivial};
            }
      };

    template<typename... Args>
      auto make_checker_helper(const std::function<bool(Args...)>& f)
      -> Checker<Args...>
      {
        return Checker<Args...>{std::function{f}};
      }

    template<typename Function>
      auto make_checker(Function&& f)
      -> decltype(make_checker_helper(std::function{f}))
      {
        return make_checker_helper(std::function{f});
      }

    template<class Ret, class Args>
      auto is_commutative(Ret (*func)(Args,Args) ) {
        return [func](Args lhs, Args rhs)
          -> bool
          {
            return func(lhs,rhs) == func(rhs,lhs);
          };
      }

  } /* end of namespace test */
} /* end of namespace pgl */
