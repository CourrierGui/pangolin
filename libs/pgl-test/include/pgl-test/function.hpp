#include <iostream>
#include <tuple>
#include <functional>
#include <string>
#include <sstream>

/**************************
 * Generic helper TMP stuff
 * ************************/

template<typename...>
struct type_sequence {};

template <typename T>
class has_operator_func {

	template <typename C>
		static char test( decltype(&C::operator()) );
	template <typename C>
		static long test(...);

	public:
	enum { value = sizeof(test<T>(0)) == sizeof(char) };
};

template <typename T>
struct function_type_forced {
	static_assert(
		has_operator_func<T>::value,
		"function_traits may only act on objects with operator() or defined functions"
	);
	using type = decltype(&T::operator());
};

template <typename T>
using force_function_type = typename function_type_forced<T>::type;

template <typename T>
struct function_traits
	: public function_traits<force_function_type<T>>
{
};

template <typename R, typename... Args>
struct function_traits_base {

	typedef R result_type;

	enum { arg_num = sizeof...(Args) };
	template <size_t i>
		struct arg {
			using type = typename std::tuple_element<i, std::tuple<Args...>>::type;
		};

	using arg_types = type_sequence<Args...>;
};

template <typename C, typename R, typename... Args>
struct function_traits<R(C::*)(Args...) const>
	: public function_traits_base<R, Args...>
{
};

template <typename C, typename R, typename... Args>
struct function_traits<R(C::*)(Args...)>
	: public function_traits_base<R, Args...>
{
};

template <typename R, typename... Args>
struct function_traits<R(Args...)>
	: public function_traits_base<R, Args...>
{
};

template <typename F>
using function_arg_sequence = typename function_traits<F>::arg_types;


/**************************
 * Stuff to call the function invariably
 * ************************/

template<typename F>
struct func_caller {
	static_assert(
		has_operator_func<F>::value || std::is_function<F>::value,
		"Only functions, functors, etc. may be used with 'func_caller'"
	);
	using result_type = typename function_traits<F>::result_type;

	template<typename... Args, size_t... Ints>
		static inline result_type real_call(
			const std::tuple<Args...>& tuple,
			const std::function<result_type(Args...)>& func,
			std::index_sequence<Ints...>)
		{
			return func(std::get<Ints>(tuple)...);
		}

	template<typename... Args>
		static inline result_type call_typed(
			const std::tuple<Args...>& tuple,
			const F& func,
			type_sequence<Args...>)
		{
			return real_call(
				tuple,
				std::function<result_type(Args...)>(func),
				std::index_sequence_for<Args...>{}
			);
		}

	template<typename Tuple>
		static inline result_type call(const Tuple& tuple, const F& func) {
			return call_typed(tuple, func, function_arg_sequence<F>{});
		}
};

template <typename R, typename... Args>
struct func_caller<R(Args...)> {

	using result_type = R;

	template<size_t... Ints>
		static inline R real_call(
			const std::tuple<Args...>& tuple,
			const std::function<R(Args...)>& func,
			std::index_sequence<Ints...>)
		{
			return func(std::get<Ints>(tuple)...);
		}

	template <typename F>
		static inline R call_typed(
			const std::tuple<Args...>& tuple,
			const F& func)
		{
			return real_call(tuple, std::function<R(Args...)>(func), std::index_sequence_for<Args...>{});
		}

	static inline R call(const std::tuple<Args...>& tuple, R (*func)(Args...))
	{
		return call_typed(tuple, func);
	}
};

/*
 * In  a real world use, something like this might be useful instead of calling
 * func_caller immediately, so as to exit the compile easier...  In this
 * example, on ideone.com, you still get pretty gnarly compile errors, though
 * it should be obvious what the problem is early on ;)
 *
 * template <typename F>
 * struct call_func_proof {
 * 	 static_assert(has_operator_func<F>::value || std::is_function<F>::value,
 * 	 "Only functions, functors, etc. may be passed to 'call_func'");
 *
 * 	 static inline auto call_func(const F& func)
 * 	 -> decltype(func_caller<F>::call(func))
 * 	 {
 *   	 return func_caller<F>::call(func);
 * 	 }
 * };
 */

template <typename Tuple, typename F>
static inline auto call_func(
	const Tuple& tuple,
	const F& func)
	-> decltype(func_caller<F>::call(tuple, func))
{
	return func_caller<F>::call(tuple, func);
}

template <typename Tuple, typename FType, typename F>
static inline auto call_func_t(const Tuple& tuple, const F& func)
	-> decltype(func_caller<FType>::call_typed(tuple, func))
{
	return func_caller<FType>::call_typed(tuple, func);
}

/**************************
 * And example using it
 * ************************/

void test_func(int i1, double d1, int i2, std::string str1, std::string str2, double d2) {
	std::cout << i1 << ", " << d1 << ", " << i2 << ", " << str1 << ", " << str2 << ", " << d2 << std::endl;
}

struct test_obj {

	void operator()(double d1, std::string str1, double d2, double d3, int i, std::string str2, double d4) {
		std::cout << d1 << ", " << str1 << ", " << d2 << ", " << d3 << ", " << i << ", " << str2 << ", " << d4 << std::endl;
	}

	void operator()() {
		std::cout << "O.o" << std::endl;
	} // This throws an error with call_func, because the overloaded () can't be resolved. call_func_t is required
};

/* int main() { */
/* 	using namespace std::placeholders; */

/* 	call_func( */
/* 		[](int i, std::string str1, std::string str2, double d) { */
/* 			std::cout << i << ", " << str1 << ", " << str2 << ", " << d << std::endl; */
/* 		} */
/* 	); */

/* 	std::string stated_str = "My str"; */
/* 	call_func( */
/* 		[&](int i, double d, std::string s) { */
/* 			std::cout << stated_str << ", " << i << ", " << d << ", " << s << std::endl; */
/* 		} */
/* 	); */
/* 	call_func(test_func); */
/* 	//call_func(test_obj{}); */
/* 	call_func_t<void(double, std::string, double, double, int, std::string, double)>(test_obj{}); */

/* 	call_func( */
/* 		std::function<void(double, int, std::string, double)>( */
/* 			std::bind(test_func, 634, _1, _2, "This one's messed up", _3, _4) */
/* 		) */
/* 	); */

/* 	return 0; */
/* } */
