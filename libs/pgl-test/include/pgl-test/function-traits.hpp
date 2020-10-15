#include <cstddef>
#include <tuple>
#include <functional>

template<typename T>
struct remove_first_type { };

template<typename T, typename... Ts>
struct remove_first_type<std::tuple<T, Ts...>> { using type = std::tuple<Ts...>; };

template<class F>
struct function_traits; 

template<class R, class... Args>
struct function_traits<R(*)(Args...)> : public function_traits<R(Args...)> {  };

template<class R, class... Args>
struct function_traits<R(Args...)> {
	using return_type = R;
	using arguments = std::tuple<Args...>;
	static constexpr std::size_t arity = sizeof...(Args);
};

template<class C, class R, class... Args>
struct function_traits<R(C::*)(Args...)> : public function_traits<R(C&,Args...)> {  };

template<class C, class R, class... Args>
struct function_traits<R(C::*)(Args...) const> : public function_traits<R(C&,Args...)> {  };

template<class C, class R>
struct function_traits<R(C::*)> : public function_traits<R(C&)> {  };

// functor
template<class F>
struct function_traits {
	private:
		using call_type = function_traits<decltype(&F::operator())>;
	public:
		using return_type = typename call_type::return_type;
		static constexpr std::size_t arity = call_type::arity - 1;
		using arguments = typename remove_first_type<typename call_type::arguments>::type;
};

template<class F>
struct function_traits<F&> : public function_traits<F> {};

template<class F>
struct function_traits<F&&> : public function_traits<F> {};

/* float func(int x, bool y) { */
/* 	return 0.0f; */
/* } */

/* struct Functor { */
/* 	int operator()(float,double) { return 0; } */
/* }; */

/* int main() */
/* { */

/* 	using Trait = function_traits<decltype(func)>; */
/* 	static_assert(std::is_same_v<Trait::return_type, float>, ""); */
/* 	static_assert(std::is_same_v<Trait::arguments,std::tuple<int,bool>>, ""); */
/* 	static_assert(Trait::arity == 2, ""); */

/* 	using StdTrait = function_traits<std::function<int(float,double)>>; */
/* 	static_assert(std::is_same_v<StdTrait::return_type, int>, ""); */
/* 	static_assert(std::is_same_v<StdTrait::arguments, std::tuple<float,double>>, ""); */
/* 	static_assert(StdTrait::arity == 2, ""); */

/* 	using FunctorTrait = function_traits<Functor>; */
/* 	static_assert(std::is_same_v<FunctorTrait::return_type, int>, ""); */
/* 	static_assert(std::is_same_v<FunctorTrait::arguments, std::tuple<float,double>>, ""); */
/* 	static_assert(FunctorTrait::arity == 2, ""); */

/* 	auto lambda = [](int,double) -> bool { return false; }; */

/* 	using LambdaTrait = function_traits<decltype(lambda)>; */
/* 	static_assert(std::is_same_v<LambdaTrait::return_type, bool>, ""); */
/* 	static_assert(std::is_same_v<LambdaTrait::arguments, std::tuple<int,double>>, ""); */
/* 	static_assert(LambdaTrait::arity == 2, ""); */

/* 	return 0; */
/* } */
