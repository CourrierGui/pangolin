#include <tuple>
#include <random>
#include <limits>

#include <pgl-test/function.hpp>
#include <pgl-test/generator.hpp>

namespace pgl {
	namespace test {

		template<typename...Args, typename type>
			auto generate_random_args(type function(Args...))
			-> std::array<std::tuple<Args...>, 100>
			{
				std::array<std::tuple<Args...>, 100> res;
				for (int i=0; i<100; ++i) {
					res.at(i) = std::make_tuple(random_generator<Args>().get()...);
				}
				return res;
			}

		template<typename Class, typename...Args, typename type>
			auto generate_random_args(type (Class::*function)(Args...) const)
			-> std::array<std::tuple<Args...>, 100>
			{
				std::array<std::tuple<Args...>, 100> res;
				for (int i=0; i<100; ++i) {
					res.at(i) = std::make_tuple(random_generator<Args>().get()...);
				}
				return res;
			}

		template<typename Class, typename... Args>
			auto generate_random_objects(Class (*maker)(Args...))
			-> std::array<Class, 100>
			{
				std::array<Class, 100> res;
				auto arguments = generate_random_args(maker);
				int i=0;
				for (auto arg: arguments) {
					res.at(i++) = call_func(arg, *maker);
				}
				return res;
			}

		template<typename ret_type, typename... Args, typename Property>
			bool function_property(
				ret_type (*function)(Args...),
				const Property& property)
			{
				auto arguments = generate_random_args(function);
				bool ret = true;
				for (auto args: arguments) {
					ret &= call_func(args, property);
				}
				return ret;
			}

		template<
			typename Class, typename... ClassArgs,
			typename type, typename... MemberArgs,
			typename Property
		>
			bool function_property(
				Class (*maker)(ClassArgs...),
				type (Class::*member)(MemberArgs...) const,
				const Property& property)
			{
				auto objects = generate_random_objects(maker);
				auto arguments = generate_random_args(member);
				bool ret{true};
				auto obj_it = objects.begin();
				auto arg_it = arguments.begin();
				while (obj_it != objects.end() && arg_it != arguments.end()) {
					std::tuple<const Class&,MemberArgs...> tpl =
						std::tuple_cat(std::make_tuple(*(obj_it++)), *(arg_it++));
					ret &= call_func(tpl, property);
				}
				return ret;
			}

	}
}
