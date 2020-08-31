#pragma once

#include <type_traits>

namespace pgl {

	template<typename T>
		concept number = std::is_arithmetic_v<T>;

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

} /* end of namespace pgl */
