#pragma once

#include <limits>

#include <pgl-math/algorithms.hpp>

namespace pgl {

	template<container cont>
		inline constexpr auto max(const cont& vec) noexcept
		-> typename cont::value_type
		{
			auto max = std::numeric_limits<typename cont::value_type>::min();
			for (auto elem: vec) {
				if (elem > max)
					max = elem;
			}
			return max;
		}

	template<container cont>
		inline constexpr auto min(const cont& vec) noexcept
		-> typename cont::value_type
		{
			auto min = std::numeric_limits<typename cont::value_type>::max();
			for (auto elem: vec) {
				if (elem < min)
					min = elem;
			}
			return min;
		}

	template<container cont>
		inline constexpr auto operator<(
			const cont& lhs,
			const cont& rhs) noexcept
		-> typename cont::template container_of<bool>
		{
			typename cont::template container_of<bool> res;
			auto lhs_it=lhs.begin(), rhs_it=rhs.begin();
			for (auto& elem: res) {
				elem = (*(lhs_it++) < *(rhs_it++));
			}
			return res;
		}

	template<container cont>
		inline constexpr auto operator>(
			const cont& lhs,
			const cont& rhs) noexcept
		-> typename cont::template container_of<bool>
		{
			typename cont::template container_of<bool> res;
			auto lhs_it=lhs.begin(), rhs_it=rhs.begin();
			for (auto& elem: res) {
				elem = (*(lhs_it++) > *(rhs_it++));
			}
			return res;
		}

	template<container cont>
		inline constexpr auto operator<=(
			const cont& lhs,
			const cont& rhs) noexcept
		-> typename cont::template container_of<bool>
		{
			typename cont::template container_of<bool> res;
			auto lhs_it=lhs.begin(), rhs_it=rhs.begin();
			for (auto& elem: res) {
				elem = (*(lhs_it++) <= *(rhs_it++));
			}
			return res;
		}

	template<container cont>
		inline constexpr auto operator>=(
			const cont& lhs,
			const cont& rhs) noexcept
		-> typename cont::template container_of<bool>
		{
			typename cont::template container_of<bool> res;
			auto lhs_it=lhs.begin(), rhs_it=rhs.begin();
			for (auto& elem: res) {
				elem = (*(lhs_it++) >= *(rhs_it++));
			}
			return res;
		}

	template<container cont>
		inline constexpr auto operator==(
			const cont& lhs,
			const cont& rhs) noexcept
		-> typename cont::template container_of<bool>
		{
			typename cont::template container_of<bool> res;
			auto lhs_it=lhs.begin(), rhs_it=rhs.begin();
			for (auto& elem: res) {
				elem = (*(lhs_it++) == *(rhs_it++));
			}
			return res;
		}

	template<container cont>
		inline constexpr auto operator!=(
			const cont& lhs,
			const cont& rhs) noexcept
		-> typename cont::template container_of<bool>
		{
			typename cont::template container_of<bool> res;
			auto lhs_it=lhs.begin(), rhs_it=rhs.begin();
			for (auto& elem: res) {
				elem = (*(lhs_it++) != *(rhs_it++));
			}
			return res;
		}

	template<container cont>
		inline constexpr auto min_element(cont& vect) noexcept
		-> typename cont::value_type&
		{
			auto min_elem = vect.begin();
			auto min      = *min_elem;
			for (auto it=vect.begin(); it!=vect.end(); ++it) {
				if (*it < min) {
					min = *it;
					min_elem = it;
				}
			}
			return *min_elem;
		}

	template<container cont>
		inline constexpr auto max_element(cont& vect) noexcept
		-> typename cont::value_type&
		{
			auto max_elem = vect.begin();
			auto max = *max_elem;
			for (auto it=vect.begin(); it!=vect.end(); ++it) {
				if (*it > max) {
					max = *it;
					max_elem = it;
				}
			}
			return *max_elem;
		}

	template<container cont>
		inline constexpr auto min(const cont& vect, typename cont::value_type min_val) noexcept
		-> cont
		{
			cont res{vect};
			for (auto& e: res) { if (e < min_val) { e = min_val; } }
			return res;
		}

	template<container cont>
		inline constexpr auto max(const cont& vect, typename cont::value_type max_val) noexcept
		-> cont
		{
			cont res{vect};
			for (auto& e: res) { if (e > max_val) { e = max_val; } }
			return res;
		}

	template<container cont>
		inline constexpr auto clamp(const cont& vect, typename cont::value_type lb, typename cont::value_type ub) noexcept
		-> cont
		{
			return min(max(vect, lb), ub);
		}

	template<container cont>
		inline constexpr auto saturate(const cont& vect) -> cont {
			return clamp(vect, typename cont::value_type{0}, typename cont::value_type{1});
		}

	template<container cont>
		inline constexpr auto any(const cont& vect) noexcept -> bool {
			bool res = false;
			for (auto e: vect) { res |= e; }
			return res;
		}

	template<container cont>
		inline constexpr auto all(const cont& vect) noexcept -> bool {
			bool res = true;
			for (const auto& e: vect) { res &= e; }
			return res;
		}

	template<container cont, typename Function>
		inline constexpr auto select(
			const cont& vect, Function& condition,
			typename cont::value_type on_true, typename cont::value_type on_false) noexcept
		-> cont
		{
			cont res{vect};
			for (auto& e: res) { condition(e) ? on_true : on_false; }
			return res;
		}

	template<container cont, number type>
		inline constexpr auto apply(
			type (*func)(type),
			const cont& vect)
		-> cont
		{
			cont res;
			auto it=vect.begin();
			for (auto& e: res) {
				e = func(*(it++));
			}
			return res;
		}

	template<container cont, number type>
		inline constexpr auto apply(
			type (*func)(type,type),
			const cont& x,
			const cont& y)
		-> cont
		{
			cont res;
			auto x_it=x.begin();
			auto y_it=y.begin();
			for (auto& e: res) {
				e = func(*(x_it++), *(y_it++));
			}
			return res;
		}

	template<container cont>
		inline constexpr auto exp(const cont& vect) noexcept -> cont {
			return apply<cont,typename cont::value_type>(std::exp, vect);
		}

	template<container cont>
		inline constexpr auto log2(const cont& vect) noexcept -> cont {
			return apply<cont, typename cont::value_type>(std::log2, vect);
		}

	template<container cont>
		inline constexpr auto log10(const cont& vect) noexcept -> cont {
			return apply<cont,typename cont::value_type>(std::log10, vect);
		}

	template<container cont>
		inline constexpr auto log(const cont& vect) noexcept -> cont {
			return apply<cont, typename cont::value_type>(std::log, vect);
		}

	template<container cont>
		inline constexpr auto tan(const cont& vect) noexcept -> cont {
			return apply<cont,typename cont::value_type>(std::tan, vect);
		}

	template<container cont>
		inline constexpr auto atan(const cont& vect) noexcept -> cont {
			return apply<cont, typename cont::value_type>(std::atan, vect);
		}

	template<container cont>
		inline constexpr auto atan(const cont& x, const cont& y) noexcept -> cont {
			return apply<cont,typename cont::value_type>(std::atan2, x, y);
		}

	template<container cont>
		inline constexpr auto cos(const cont& vect) noexcept -> cont {
			return apply<cont,typename cont::value_type>(std::cos, vect);
		}

	template<container cont>
		inline constexpr auto acos(const cont& vect) noexcept -> cont {
			return apply<cont,typename cont::value_type>(std::acos, vect);
		}

	template<container cont>
		inline constexpr auto sin(const cont& vect) noexcept -> cont {
			return apply<cont,typename cont::value_type>(std::sin, vect);
		}

	template<container cont>
		inline constexpr auto asin(const cont& vect) noexcept -> cont {
			return apply<cont,typename cont::value_type>(std::asin, vect);
		}

	template<container cont>
		inline constexpr auto cosh(const cont& vect) noexcept -> cont {
			return apply<cont,typename cont::value_type>(std::cosh, vect);
		}

	template<container cont>
		inline constexpr auto acosh(const cont& vect) noexcept -> cont {
			return apply<cont,typename cont::value_type>(std::acosh, vect);
		}

	template<container cont>
		inline constexpr auto sinh(const cont& vect) noexcept -> cont {
			return apply<cont,typename cont::value_type>(std::sinh, vect);
		}

	template<container cont>
		inline constexpr auto asinh(const cont& vect) noexcept -> cont {
			return apply<cont,typename cont::value_type>(std::asinh, vect);
		}

	/**
	 * Create a view matrix which transforms the coordinates so that the user
	 * looks at the target vector.
	 *
	 * @param camera Position of the camera
	 * @param target Position of the target to look at
	 * @param up Vector pointing in the up direction
	 *
	 * @return View matrix
	 */
	template<number type>
		inline constexpr auto look_at(const vector<type,3>& camera, const vector<type,3>& target, const vector<type,3>& up) noexcept
		-> matrix<type,4>
		{
			auto right = cross(up, target);
			matrix<type,4> rotation = {
				right.x,  right.y,  right.z,  type{0},
				up.x,     up.y,     up.z,     type{0},
				target.x, target.y, target.z, type{0},
				type{0},  type{0},  type{0},  type{1}, 
			};
			matrix<type,4> translation = {
				type{1}, type{0}, type{0}, -camera.x,
				type{0}, type{1}, type{0}, -camera.y,
				type{0}, type{0}, type{1}, -camera.z,
				type{0}, type{0}, type{0},  type{1},
			};
			return rotation * translation;
		}

} /* end of namespace pgl */
