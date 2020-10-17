#pragma once

#include <pgl-math/utils.hpp>
#include <pgl-math/matrix.hpp>
#include <pgl-math/vector.hpp>

namespace pgl {

	template<container cont> inline constexpr auto operator< (const cont&, const cont&) noexcept
		-> typename cont::template container_of<bool>;
	template<container cont> inline constexpr auto operator> (const cont&, const cont&) noexcept
		-> typename cont::template container_of<bool>;
	template<container cont> inline constexpr auto operator<=(const cont&, const cont&) noexcept
		-> typename cont::template container_of<bool>;
	template<container cont> inline constexpr auto operator>=(const cont&, const cont&) noexcept
		-> typename cont::template container_of<bool>;
	template<container cont> inline constexpr auto operator==(const cont&, const cont&) noexcept
		-> typename cont::template container_of<bool>;
	template<container cont> inline constexpr auto operator!=(const cont&, const cont&) noexcept
		-> typename cont::template container_of<bool>;

	template<container cont> inline constexpr auto min(const cont&)               noexcept -> typename cont::value_type;
	template<container cont> inline constexpr auto max(const cont&)               noexcept -> typename cont::value_type;
	template<container cont> inline constexpr auto min(const cont& vec, const cont& min) noexcept -> cont;
	template<container cont> inline constexpr auto max(const cont& vec, const cont& max) noexcept -> cont;
	template<container cont> inline constexpr auto min_element(cont&)             noexcept -> typename cont::value_type&;
	template<container cont> inline constexpr auto max_element(cont&)             noexcept -> typename cont::value_type&;
	template<container cont> inline constexpr auto min(const cont&, typename cont::value_type min_val) noexcept -> cont;
	template<container cont> inline constexpr auto max(const cont&, typename cont::value_type max_val) noexcept -> cont;

	template<container cont>
		inline constexpr auto clamp(const cont& vect, typename cont::value_type lb, typename cont::value_type ub) noexcept -> cont;
	template<container cont>
		inline constexpr auto clamp(const cont& x, const cont& min, const cont& max) noexcept -> cont;
	template<container cont> inline constexpr auto saturate(const cont&);

	template<container cont> inline constexpr auto any(const cont&) noexcept -> bool;
	template<container cont> inline constexpr auto all(const cont&) noexcept -> bool;

	template<container cont, typename Function>
		inline constexpr auto select(
			const cont&, Function&, typename cont::value_type, typename cont::value_type) noexcept -> cont;

	template<container cont, number type>
		inline constexpr auto apply(type (*func)(type), const cont&) -> cont;
	template<container cont, number type>
		inline constexpr auto apply(type (*func)(type,type), const cont& x, const cont& y) -> cont;

	template<container cont> inline constexpr auto exp  (const cont&) noexcept -> cont;
	template<container cont> inline constexpr auto log  (const cont&) noexcept -> cont;
	template<container cont> inline constexpr auto log2 (const cont&) noexcept -> cont;
	template<container cont> inline constexpr auto log10(const cont&) noexcept -> cont;

	template<container cont> inline constexpr auto cosh (const cont&) noexcept -> cont;
	template<container cont> inline constexpr auto acosh(const cont&) noexcept -> cont;
	template<container cont> inline constexpr auto sinh (const cont&) noexcept -> cont;
	template<container cont> inline constexpr auto asinh(const cont&) noexcept -> cont;

	template<container cont> inline constexpr auto cos  (const cont&) noexcept -> cont;
	template<container cont> inline constexpr auto acos (const cont&) noexcept -> cont;
	template<container cont> inline constexpr auto sin  (const cont&) noexcept -> cont;
	template<container cont> inline constexpr auto asin (const cont&) noexcept -> cont;
	template<container cont> inline constexpr auto tan  (const cont&) noexcept -> cont;
	template<container cont> inline constexpr auto atan (const cont&) noexcept -> cont;
	template<container cont> inline constexpr auto atan (const cont&, const cont&) noexcept -> cont;

	template<number type> inline constexpr auto look_at(const vector<type,3>&, const vector<type,3>&, const vector<type,3>&) noexcept -> matrix<type,4>;
	template<number type> inline constexpr auto ortho(type left, type right, type bottom, type top) -> matrix<type, 4>;
	template<number type> inline constexpr auto ortho(type left, type right, type bottom, type top, type zNear, type zFar) -> matrix<type,4>;

	template<number type> inline constexpr auto translate(const vector<type,3>&,const vector<type,3>&) -> vector<type,3>;
	template<number type> inline constexpr auto rotate(const vector<type,3>&,const type&,const vector<type,3>&) -> vector<type,3>;
	template<number type> inline constexpr auto scale(const vector<type,3>&,const vector<type,3>&) -> vector<type,3>;

} /* end of namespace pgl */

#include <pgl-math/impl/algorithms.hpp>
