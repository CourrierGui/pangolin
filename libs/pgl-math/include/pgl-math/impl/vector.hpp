#pragma once

#include <cmath>
#include <iostream>

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
			for (const auto& elem: arg) {
				res += elem;
			}
			return res;
		}

	template<number type, uint32_t dim>
		inline constexpr auto normalize(const vector<type,dim>& arg) noexcept
		-> vector<type,dim>
		{
			return arg/norm(arg);
		}

	template<number type, uint32_t dim>
		inline constexpr auto norm(const vector<type,dim>& arg) noexcept
		-> type
		{
			return std::sqrt(dot(arg, arg));
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

	template<typename type>
		auto cross(const vector<type,3>& lhs, const vector<type,3>& rhs)
			-> vector<type,3>
		{
			return vector<type,3>{
				lhs.y*rhs.z - lhs.z*rhs.y,
				lhs.z*rhs.x - lhs.x*rhs.z,
				lhs.x*rhs.y - lhs.y*rhs.x
			};
		}

} /* end of namespace pgl */
