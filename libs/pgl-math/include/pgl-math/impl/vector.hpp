#pragma once

#include <pgl-math/vector.hpp>
#include <pgl-math/base-vector.hpp>

namespace pgl {

	template<number type, uint32_t dim>
		inline constexpr auto dot(
			const vector<type,dim>& lhs,
			const vector<type,dim>& rhs) noexcept
		-> type {
			type res{0};
			for (auto lhs_it=lhs.begin(), rhs_it=rhs.begin();
					 lhs_it != lhs.end();
					 ++lhs_it,++rhs_it)
			{
				res += *(lhs_it) * *(rhs_it);
			}
			return res;
		}

	template<number type, uint32_t dim>
		inline constexpr auto dot(const vector<type,dim>& arg) noexcept
		-> type
		{
			return dot(arg,arg);
		}

	template<number type, uint32_t dim>
		inline constexpr auto sum(const vector<type,dim>& arg) noexcept
		-> type {
			type res{0};
			for (auto elem: arg) {
				res += elem;
			}
			return res;
		}

	template<number type, uint32_t dim>
		inline constexpr auto normalize(const vector<type,dim>& arg) noexcept
		-> vector<type,dim>
		{
			type s = sum(arg);
			return arg/s;
		}

	template<number type, uint32_t dim>
		constexpr inline auto lerp(
			const vector<type,dim>& x,
			const vector<type,dim>& y,
			type a) noexcept
		-> vector<type,dim>
		{
			return x * (static_cast<type>(1) - a) + y * a;
		}

	template<number type, uint32_t dim>
		inline constexpr auto abs(const vector<type,dim>& vec) noexcept
		-> vector<type,dim>
		{
			vector<type,dim> res;
			auto vec_it = vec.begin();
			for (auto& elem: res)
				elem = std::abs(*(vec_it++));
			return res;
		}

	constexpr float  pi  {std::numbers::pi_v<float>};
	constexpr double dpi {std::numbers::pi_v<double>};

} /* end of namespace pgl */
