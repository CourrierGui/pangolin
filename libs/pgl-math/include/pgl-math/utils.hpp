#pragma once

#include <type_traits>
#include <numbers>

namespace pgl {

	template<typename T>
		concept integral = std::is_arithmetic_v<T>;

	template<typename T>
		concept number = std::is_arithmetic_v<T> && !std::is_same_v<T,bool>;

	template<typename T>
		concept container =
		requires(T a) {
			typename T::value_type;
			typename T::size_type;
			typename T::iterator;
			typename T::const_iterator;
			{a.size()  };
			{a.begin() };
			{a.end()   };
			{a.cbegin()};
			{a.cend()  };
		};

	constexpr float  pi  {std::numbers::pi_v<float>};
	constexpr double dpi {std::numbers::pi_v<double>};

	template<typename type>
		type radians(type degrees) {
			return std::numbers::pi_v<type>*degrees/180;
		}

	template<typename type>
		type degrees(type radians) {
			return 180*radians/std::numbers::pi_v<type>;
		}

} /* end of namespace pgl */
