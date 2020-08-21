#pragma once

#include <pgl-math/vector.hpp>

namespace pgl {

	template<typename type>
		struct quaternion : public vector<type, 4> {
			static quaternion<type> identity() noexcept { return {0, 0, 0, 1}; }
		};

	/*
	 * ========================
	 * ======= TODO !!! =======
	 * ========================
	 *
	 * multiplication
	 * inversion
	 * conversion between euler, matrix and quaternions
	 *
	 */

} /* end of namespace pgl */
