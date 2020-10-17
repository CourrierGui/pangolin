#pragma once

#include <numbers>
#include <limits>
#include <cmath>
#include <utility>
#include <initializer_list>

#include <pgl-math/utils.hpp>
#include <pgl-math/base-vector.hpp>

namespace pgl {

	template<number type, uint32_t dim, template<typename T, uint32_t d> class vector_type>
		struct algebric_vector : public base_vector<type, dim,vector_type> {
			inline constexpr          algebric_vector()                                        noexcept : base_vector<type,dim,vector_type>{}     {  }
			inline constexpr explicit algebric_vector(const type& e)                           noexcept : base_vector<type,dim,vector_type>{e}    {  }
			inline constexpr          algebric_vector(const type arr[dim])                     noexcept : base_vector<type,dim,vector_type>{arr}  {  }
			// C++ 20 <3
			inline constexpr          algebric_vector(std::convertible_to<type> auto ... args) noexcept : base_vector<type,dim,vector_type>{ std::forward<type>(args)... } {  }

			//TODO create a class math_algebric_vector to factor these methods
			inline constexpr auto operator*=(const algebric_vector<type,dim,vector_type>& vect) noexcept -> algebric_vector<type,dim,vector_type>& {
				auto it = vect.cbegin();
				for (auto& e: this->elements) {
					e *= *(it++);
				}
				return *this;
			}
			inline constexpr auto operator/=(const algebric_vector<type,dim,vector_type>& vect) noexcept -> algebric_vector<type,dim,vector_type>& {
				auto it = vect.cbegin();
				for (auto& e: this->elements) {
					e /= *(it++);
				}
				return *this;
			}
			inline constexpr auto operator+=(const algebric_vector<type,dim,vector_type>& vect) noexcept -> algebric_vector<type,dim,vector_type>& {
				auto it = vect.cbegin();
				for (auto& e: this->elements) {
					e += *(it++);
				}
				return *this;
			}
			inline constexpr auto operator-=(const algebric_vector<type,dim,vector_type>& vect) noexcept -> algebric_vector<type,dim,vector_type>& {
				auto it = vect.cbegin();
				for (auto& e: this->elements) {
					e -= *(it++);
				}
				return *this;
			}

			inline constexpr auto operator*=(std::convertible_to<type> auto scalar) noexcept -> algebric_vector<type,dim,vector_type>& {
				for (auto& e: this->elements) {
					e *= scalar;
				}
				return *this;
			}
			template<number scalar_type> inline constexpr auto operator/=(std::convertible_to<type> auto scalar) noexcept -> algebric_vector<type,dim,vector_type>& {
				for (auto& e: this->elements) {
					e /= scalar;
				}
				return *this;
			}
			template<number scalar_type> inline constexpr auto operator+=(std::convertible_to<type> auto scalar) noexcept -> algebric_vector<type,dim,vector_type>& {
				for (auto& e: this->elements) {
					e += scalar;
				}
				return *this;
			}
			template<number scalar_type> inline constexpr auto operator-=(std::convertible_to<type> auto scalar) noexcept -> algebric_vector<type,dim,vector_type>& {
				for (auto& e: this->elements) {
					e -= scalar;
				}
				return *this;
			}
		};

	template<typename type, uint32_t dim> struct vector {  };

	template<number type, uint32_t dim>
		struct vector<type,dim> : public algebric_vector<type,dim,vector> {
			inline constexpr          vector()                               noexcept : algebric_vector<type,dim,vector>{}     {  }
			inline constexpr explicit vector(const type& e)                  noexcept : algebric_vector<type,dim,vector>{e}    {  }
			inline constexpr          vector(const type arr[dim])            noexcept : algebric_vector<type,dim,vector>{arr}  {  }
			inline constexpr vector(std::convertible_to<type> auto ... args) noexcept : algebric_vector<type,dim,vector>{ std::forward<type>(args)... } {  }
		};

	template<uint32_t dim>
		struct vector<bool,dim> : public base_vector<bool, dim,vector> {
			inline constexpr          vector()                    noexcept : base_vector<bool, dim,vector>{}    {  }
			inline constexpr explicit vector(bool b)              noexcept : base_vector<bool, dim,vector>{b}   {  }
			inline constexpr          vector(const bool arr[dim]) noexcept : base_vector<bool, dim,vector>{arr} {  }
			inline constexpr vector(std::convertible_to<bool> auto ... args) noexcept : base_vector<bool,dim,vector>{ std::forward<bool>(args)... } {  }

			/* inline constexpr auto operator&=(const vector<bool,dim>&) noexcept -> vector<bool,dim>&; */
			/* inline constexpr auto operator|=(const vector<bool,dim>&) noexcept -> vector<bool,dim>&; */
			/* inline constexpr auto operator^=(const vector<bool,dim>&) noexcept -> vector<bool,dim>&; */
			/* inline constexpr auto operator!=(const vector<bool,dim>&) noexcept -> vector<bool,dim>&; */
		};

	template<number type>
		struct vector<type,2> : public algebric_vector<type,2,vector> {
			inline constexpr          vector()                      noexcept : algebric_vector<type,2,vector>{}         {  }
			inline constexpr explicit vector(const type& e)         noexcept : algebric_vector<type,2,vector>{e}        {  }
			inline constexpr          vector(const type arr[2])     noexcept : algebric_vector<type,2,vector>{arr}      {  }
			inline constexpr vector(const type& e1, const type& e2) noexcept : algebric_vector<type,2,vector>( e1, e2 ) {  }

			static inline constexpr vector<type,2> right() noexcept { return { type{ 1}, type{ 0} }; }
			static inline constexpr vector<type,2> left()  noexcept { return { type{-1}, type{ 0} }; }
			static inline constexpr vector<type,2> up()    noexcept { return { type{ 0}, type{ 1} }; }
			static inline constexpr vector<type,2> down()  noexcept { return { type{ 0}, type{-1} }; }
		};

	template<number type>
		struct vector<type,3> : public algebric_vector<type,3,vector> {
			inline constexpr vector()                                               noexcept : algebric_vector<type,3,vector>{}              {  }
			inline constexpr explicit vector(const type& e)                         noexcept : algebric_vector<type,3,vector>{e}             {  }
			inline constexpr vector(const type arr[3])                              noexcept : algebric_vector<type,3,vector>{arr}           {  }
			inline constexpr vector(const type& e1, const type& e2, const type& e3) noexcept : algebric_vector<type,3,vector>( e1, e2, e3 )  {  }
			inline constexpr vector(const vector<type,2>& v, const type& e)         noexcept : algebric_vector<type,3,vector>( v.x, v.y, e ) {  }

			static inline constexpr vector<type,3> right() noexcept { return { type{ 1}, type{ 0}, type{ 0} }; }
			static inline constexpr vector<type,3> left()  noexcept { return { type{-1}, type{ 0}, type{ 0} }; }
			static inline constexpr vector<type,3> up()    noexcept { return { type{ 0}, type{ 1}, type{ 0} }; }
			static inline constexpr vector<type,3> down()  noexcept { return { type{ 0}, type{-1}, type{ 0} }; }
			static inline constexpr vector<type,3> front() noexcept { return { type{ 0}, type{ 0}, type{ 1} }; }
			static inline constexpr vector<type,3> back()  noexcept { return { type{ 0}, type{ 0}, type{-1} }; }
		};

	template<number type>
		struct vector<type,4> : public algebric_vector<type,4,vector> {
			inline constexpr vector()                                                               noexcept : algebric_vector<type,4,vector>{}                   {  }
			inline constexpr explicit vector(const type& e)                                         noexcept : algebric_vector<type,4,vector>{e}                  {  }
			inline constexpr vector(const type arr[4])                                              noexcept : algebric_vector<type,4,vector>{arr}                {  }
			inline constexpr vector(const type& e1, const type& e2, const type& e3, const type& e4) noexcept : algebric_vector<type,4,vector>( e1, e2, e3, e4 )   {  }

			// Can these constructors be one template ?
			inline constexpr vector(const vector<type,3>& v, const type& e)                         noexcept : algebric_vector<type,4,vector>( v.x, v.y, v.z, e )   {  }
			inline constexpr vector(const vector<type,2>& v, const vector<type,2>& w)               noexcept : algebric_vector<type,4,vector>( v.x, v.y, w.x, w.y ) {  }

			static inline constexpr vector<type,4> right() noexcept { return { type{ 1}, type{ 0}, type{ 0}, type{0} }; }
			static inline constexpr vector<type,4> left()  noexcept { return { type{-1}, type{ 0}, type{ 0}, type{0} }; }
			static inline constexpr vector<type,4> up()    noexcept { return { type{ 0}, type{ 1}, type{ 0}, type{0} }; }
			static inline constexpr vector<type,4> down()  noexcept { return { type{ 0}, type{-1}, type{ 0}, type{0} }; }
			static inline constexpr vector<type,4> front() noexcept { return { type{ 0}, type{ 0}, type{ 1}, type{0} }; }
			static inline constexpr vector<type,4> back()  noexcept { return { type{ 0}, type{ 0}, type{-1}, type{0} }; }
		};

	template<number type, uint32_t dim>
		inline constexpr auto operator*(const vector<type,dim>& lhs, const vector<type,dim>& rhs) noexcept
		-> vector<type,dim>
		{
			vector<type,dim> res{lhs};
			res *= rhs;
			return res;
		}
	template<number type, number scalar_type, uint32_t dim>
		inline constexpr auto operator*(const vector<type,dim>& lhs, const scalar_type& rhs) noexcept
		-> vector<type,dim>
		{
			vector<type,dim> res{lhs};
			res *= rhs;
			return res;
		}
	template<number type, number scalar_type, uint32_t dim>
		inline constexpr auto operator*(const scalar_type& lhs, const vector<type,dim>& rhs) noexcept
		-> vector<type,dim>
		{
			vector<type,dim> res{lhs};
			res *= rhs;
			return res;
		}

	template<number type, uint32_t dim>
		inline constexpr auto operator/(const vector<type,dim>& lhs, const vector<type,dim>& rhs) noexcept
		-> vector<type,dim>
		{
			vector<type,dim> res{lhs};
			res /= rhs;
			return res;
		}
	template<number type, number scalar_type, uint32_t dim>
		inline constexpr auto operator/(const vector<type,dim>& lhs, const scalar_type& rhs) noexcept
		-> vector<type,dim>
		{
			vector<type,dim> res{lhs};
			res /= rhs;
			return res;
		}
	template<number type, number scalar_type, uint32_t dim>
		inline constexpr auto operator/(const scalar_type& lhs, const vector<type,dim>& rhs) noexcept
		-> vector<type,dim>
		{
			vector<type,dim> res{lhs};
			res /= rhs;
			return res;
		}

	template<number type, uint32_t dim>
		inline constexpr auto operator-(const vector<type,dim>& lhs, const vector<type,dim>& rhs) noexcept
		-> vector<type,dim>
		{
			vector<type,dim> res{lhs};
			res -= rhs;
			return res;
		}
	template<number type, number scalar_type, uint32_t dim>
		inline constexpr auto operator-(const vector<type,dim>& lhs, const scalar_type& rhs) noexcept
		-> vector<type,dim>
		{
			vector<type,dim> res{lhs};
			res -= rhs;
			return res;
		}
	template<number type, uint32_t dim>
		inline constexpr auto operator-(const vector<type,dim>& vec) noexcept
		-> vector<type,dim>
		{
			vector<type,dim> res(type{0});
			res -= vec;
			return res;
		}

	template<number type, number scalar_type, uint32_t dim>
		inline constexpr auto operator-(const scalar_type& lhs, const vector<type,dim>& rhs) noexcept
		-> vector<type,dim>
		{
			vector<type,dim> res{lhs};
			res -= rhs;
			return res;
		}

	template<number type, uint32_t dim>
		inline constexpr auto operator+(const vector<type,dim>& lhs, const vector<type,dim>& rhs) noexcept
		-> vector<type,dim>
		{
			vector<type,dim> res{lhs};
			res += rhs;
			return res;
		}
	template<number type, number scalar_type, uint32_t dim>
		inline constexpr auto operator+(const vector<type,dim>& lhs, const scalar_type& rhs) noexcept
		-> vector<type,dim>
		{
			vector<type,dim> res{lhs};
			res += rhs;
			return res;
		}
	template<number type, number scalar_type, uint32_t dim>
		inline constexpr auto operator+(const scalar_type& lhs, const vector<type,dim>& rhs) noexcept
		-> vector<type,dim>
		{
			vector<type,dim> res{lhs};
			res += rhs;
			return res;
		}

	template<number type, uint32_t dim> inline constexpr auto dot(const vector<type,dim>&, const vector<type,dim>&) noexcept -> type;
	template<number type, uint32_t dim> inline constexpr auto dot(const vector<type,dim>&)                          noexcept -> type;
	template<number type, uint32_t dim> inline constexpr auto sum(const vector<type,dim>&)                          noexcept -> type;
	template<number type, uint32_t dim> inline constexpr auto abs(const vector<type,dim>&)                          noexcept -> vector<type,dim>;
	template<number type, uint32_t dim> inline constexpr auto normalize(const vector<type,dim>&)                    noexcept -> vector<type,dim>;
	template<number type, uint32_t dim> inline constexpr auto norm(const vector<type,dim>&)                         noexcept -> type;

	template<number type, uint32_t dim> constexpr inline auto lerp(const vector<type,dim>&, const vector<type,dim>&, type) noexcept -> vector<type,dim>;

	template<typename type>
		auto cross(const vector<type,3>& lhs, const vector<type,3>& rhs) -> vector<type,3>;

	/*
	 *
	 * ========================
	 * ======= TODO !!! =======
	 * ========================
	 *
	 * copy, move constructor
	 * operator=
	 * frame ?
	 * decltype
	 * benchmark
	 * SIMD
	 *
	 */

	using bool2 = vector<bool,2>;
	using bool3 = vector<bool,3>;
	using bool4 = vector<bool,4>;

	using uint2 = vector<uint32_t,2>;
	using uint3 = vector<uint32_t,3>;
	using uint4 = vector<uint32_t,4>;

	using int2 = vector<int32_t,2>;
	using int3 = vector<int32_t,3>;
	using int4 = vector<int32_t,4>;

	using float2 = vector<float,2>;
	using float3 = vector<float,3>;
	using float4 = vector<float,4>;

} /* end of namespace pgl */

#include <pgl-math/impl/vector.hpp>
