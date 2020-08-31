#pragma once

#include <numbers>
#include <limits>
#include <cmath>
#include <initializer_list>
#include <iostream>
#include <utility>

#include <pgl-math/utils.hpp>

namespace pgl {

	template<number type, int dim>
		struct vector {
			using value_type     = type;
			using size_type      = int;
			using iterator       = type*;
			using const_iterator = const type*;
			template<typename T> using container_of = vector<T,dim>;

			type elements[dim];

			struct raw_data {
				type data[dim];
				int size;
				inline constexpr raw_data(const type[dim]) noexcept;
			};
			inline constexpr auto data() noexcept -> raw_data;
			inline constexpr auto size() const noexcept -> int;

			inline constexpr auto begin()  noexcept       -> type*;
			inline constexpr auto begin()  const noexcept -> const type*;
			inline constexpr auto cbegin() const noexcept -> const type*;
			inline constexpr auto end()    noexcept       -> type*;
			inline constexpr auto end()    const noexcept -> const type*;
			inline constexpr auto cend()   const noexcept -> const type*;


			inline constexpr vector() noexcept;
			inline constexpr explicit vector(const type&) noexcept;
			inline constexpr vector(const type[dim]) noexcept;

			template<number... Ts>
				inline constexpr vector(Ts&&... ts);
			inline constexpr auto operator*=(const vector<type,dim>&) noexcept -> vector<type,dim>&;
			inline constexpr auto operator/=(const vector<type,dim>&) noexcept -> vector<type,dim>&;
			inline constexpr auto operator+=(const vector<type,dim>&) noexcept -> vector<type,dim>&;
			inline constexpr auto operator-=(const vector<type,dim>&) noexcept -> vector<type,dim>&;

			template<number scalar_type> inline constexpr auto operator*=(const scalar_type&) noexcept -> vector<type,dim>&;
			template<number scalar_type> inline constexpr auto operator/=(const scalar_type&) noexcept -> vector<type,dim>&;
			template<number scalar_type> inline constexpr auto operator+=(const scalar_type&) noexcept -> vector<type,dim>&;
			template<number scalar_type> inline constexpr auto operator-=(const scalar_type&) noexcept -> vector<type,dim>&;
		};

	template<number type>
		struct vector<type,2> {
			union {
				type elements[2];
				struct { type x, y; };
			};
			using value_type     = type;
			using size_type      = int;
			using iterator       = type*;
			using const_iterator = const type*;
			template<typename T> using container_of = vector<T,2>;

			struct raw_data {
				type data[2];
				int size;
				inline constexpr raw_data(const type[2]) noexcept;
			};
			inline constexpr auto data() noexcept -> raw_data;

			inline constexpr auto size() const noexcept -> int;

			inline constexpr auto begin()  noexcept       -> type*;
			inline constexpr auto begin()  const noexcept -> const type*;
			inline constexpr auto cbegin() const noexcept -> const type*;
			inline constexpr auto end()    noexcept 	    -> type*;
			inline constexpr auto end()    const noexcept -> const type*;
			inline constexpr auto cend()   const noexcept -> const type*;

			inline constexpr vector()                         noexcept;
			inline constexpr explicit vector(const type&)     noexcept;
			inline constexpr vector(const type&, const type&) noexcept;
			inline constexpr vector(const type[2])            noexcept;

			static inline constexpr vector<type,2> right() noexcept;
			static inline constexpr vector<type,2> left()  noexcept;
			static inline constexpr vector<type,2> up()    noexcept;
			static inline constexpr vector<type,2> down()  noexcept;

			inline constexpr auto operator*=(const vector<type,2>&) noexcept -> vector<type,2>&;
			inline constexpr auto operator/=(const vector<type,2>&) noexcept -> vector<type,2>&;
			inline constexpr auto operator+=(const vector<type,2>&) noexcept -> vector<type,2>&;
			inline constexpr auto operator-=(const vector<type,2>&) noexcept -> vector<type,2>&;

			template<number scalar_type> inline constexpr auto operator*=(const scalar_type& scalar) noexcept -> vector<type,2>&;
			template<number scalar_type> inline constexpr auto operator/=(const scalar_type& scalar) noexcept -> vector<type,2>&;
			template<number scalar_type> inline constexpr auto operator+=(const scalar_type& scalar) noexcept -> vector<type,2>&;
			template<number scalar_type> inline constexpr auto operator-=(const scalar_type& scalar) noexcept -> vector<type,2>&;
		};

	template<number type>
		struct vector<type,3> {
			union {
				type elements[3];
				struct { type x, y, z; };
				struct { vector<type,2> xy; };
			};
			using value_type     = type;
			using size_type      = int;
			using iterator       = type*;
			using const_iterator = const type*;
			template<typename T> using container_of = vector<T,3>;

			struct raw_data {
				type data[3];
				int size;
				inline constexpr raw_data(const type[3]) noexcept;
			};
			inline constexpr auto data() noexcept -> raw_data;

			inline constexpr auto size() const noexcept -> int;

			inline constexpr auto begin()  noexcept       -> type*;
			inline constexpr auto begin()  const noexcept -> const type*;
			inline constexpr auto cbegin() const noexcept -> const type*;
			inline constexpr auto end()    noexcept       -> type*;
			inline constexpr auto end()    const noexcept -> const type*;
			inline constexpr auto cend()   const noexcept -> const type*;

			inline constexpr vector()                                         noexcept;
			inline constexpr explicit vector(const type&)                     noexcept;
			inline constexpr vector(const type& t0, const type&, const type&) noexcept;
			inline constexpr vector(const type[3])                            noexcept;
			inline constexpr vector(const vector<type,2>&, const type&)       noexcept;

			static inline constexpr vector<type,3> right() noexcept;
			static inline constexpr vector<type,3> left()  noexcept;
			static inline constexpr vector<type,3> up()    noexcept;
			static inline constexpr vector<type,3> down()  noexcept;
			static inline constexpr vector<type,3> front() noexcept;
			static inline constexpr vector<type,3> back()  noexcept;

			inline constexpr auto operator*=(const vector<type,3>& vec) noexcept -> vector<type,3>&;
			inline constexpr auto operator/=(const vector<type,3>& vec) noexcept -> vector<type,3>&;
			inline constexpr auto operator+=(const vector<type,3>& vec) noexcept -> vector<type,3>&;
			inline constexpr auto operator-=(const vector<type,3>& vec) noexcept -> vector<type,3>&;

			template<number scalar_type> inline constexpr auto operator*=(const scalar_type& scalar) noexcept -> vector<type,3>&;
			template<number scalar_type> inline constexpr auto operator/=(const scalar_type& scalar) noexcept -> vector<type,3>&;
			template<number scalar_type> inline constexpr auto operator+=(const scalar_type& scalar) noexcept -> vector<type,3>&;
			template<number scalar_type> inline constexpr auto operator-=(const scalar_type& scalar) noexcept -> vector<type,3>&;
		};

	template<number type>
		struct vector<type,4> {
			union {
				type elements[4];
				struct { type x, y, z, w; };
				struct { vector<type,3> xyz; };
				struct { vector<type,2> xy, zw; };
			};
			using value_type     = type;
			using size_type      = int;
			using iterator       = type*;
			using const_iterator = const type*;
			template<typename T> using container_of = vector<T,4>;

			struct raw_data {
				type data[4];
				int size;
				inline constexpr raw_data(const type[4]) noexcept;
			};
			inline constexpr auto data() noexcept -> raw_data;

			inline constexpr auto size() const noexcept -> int;

			inline constexpr auto begin()  noexcept       -> type*;
			inline constexpr auto begin()  const noexcept -> const type*;
			inline constexpr auto cbegin() const noexcept -> const type*;
			inline constexpr auto end()    noexcept       -> type*;
			inline constexpr auto end()    const noexcept -> const type*;
			inline constexpr auto cend()   const noexcept -> const type*;

			inline constexpr vector() noexcept;
			inline constexpr explicit vector(const type&)                                  noexcept;
			inline constexpr vector(const type[4])                                         noexcept;
			inline constexpr vector(const type& t0, const type&, const type&, const type&) noexcept;
			inline constexpr vector(const vector<type,3>&, type)                           noexcept;
			inline constexpr vector(const vector<type,2>&, const vector<type,2>&)          noexcept;

			inline constexpr auto operator*=(const vector<type,4>& vec) noexcept -> vector<type,4>&;
			inline constexpr auto operator/=(const vector<type,4>& vec) noexcept -> vector<type,4>&;
			inline constexpr auto operator+=(const vector<type,4>& vec) noexcept -> vector<type,4>&;
			inline constexpr auto operator-=(const vector<type,4>& vec) noexcept -> vector<type,4>&;

			template<number scalar_type> inline constexpr auto operator*=(const scalar_type& scalar) noexcept -> vector<type,4>&;
			template<number scalar_type> inline constexpr auto operator/=(const scalar_type& scalar) noexcept -> vector<type,4>&;
			template<number scalar_type> inline constexpr auto operator+=(const scalar_type& scalar) noexcept -> vector<type,4>&;
			template<number scalar_type> inline constexpr auto operator-=(const scalar_type& scalar) noexcept -> vector<type,4>&;
		};

	template<number type, int dim>                     inline constexpr auto operator*(const vector<type,dim>&, const vector<type,dim>&) noexcept -> vector<type,dim>;
	template<number type, number scalar_type, int dim> inline constexpr auto operator*(const vector<type,dim>&, const scalar_type&     ) noexcept -> vector<type,dim>;
	template<number type, number scalar_type, int dim> inline constexpr auto operator*(const scalar_type&,      const vector<type,dim>&) noexcept -> vector<type,dim>;

	template<number type, int dim>                     inline constexpr auto operator/(const vector<type,dim>&, const vector<type,dim>&) noexcept -> vector<type,dim>;
	template<number type, number scalar_type, int dim> inline constexpr auto operator/(const vector<type,dim>&, const scalar_type&     ) noexcept -> vector<type,dim>;
	template<number type, number scalar_type, int dim> inline constexpr auto operator/(const scalar_type&,      const vector<type,dim>&) noexcept -> vector<type,dim>;

	template<number type, int dim>                     inline constexpr auto operator-(const vector<type,dim>&, const vector<type,dim>&) noexcept -> vector<type,dim>;
	template<number type, number scalar_type, int dim> inline constexpr auto operator-(const vector<type,dim>&, const scalar_type&     ) noexcept -> vector<type,dim>;
	template<number type, number scalar_type, int dim> inline constexpr auto operator-(const scalar_type&,      const vector<type,dim>&) noexcept -> vector<type,dim>;

	template<number type, int dim>                     inline constexpr auto operator+(const vector<type,dim>&, const vector<type,dim>&) noexcept -> vector<type,dim>;
	template<number type, number scalar_type, int dim> inline constexpr auto operator+(const vector<type,dim>&, const scalar_type&     ) noexcept -> vector<type,dim>;
	template<number type, number scalar_type, int dim> inline constexpr auto operator+(const scalar_type&,      const vector<type,dim>&) noexcept -> vector<type,dim>;

	template<number type, int dim> inline constexpr auto dot(const vector<type,dim>&, const vector<type,dim>&) noexcept -> type;
	template<number type, int dim> inline constexpr auto dot(const vector<type,dim>&)                          noexcept -> type;
	template<number type, int dim> inline constexpr auto sum(const vector<type,dim>&)                          noexcept -> type;
	template<number type, int dim> inline constexpr auto abs(const vector<type,dim>&)                          noexcept -> vector<type,dim>;
	template<number type, int dim> inline constexpr auto normalize(const vector<type,dim>&)                    noexcept -> vector<type,dim>;
	template<number type, int dim> constexpr inline auto lerp (const vector<type,dim>&, const vector<type,dim>&, type) noexcept -> vector<type,dim>;

	/*
	 *
	 * ========================
	 * ======= TODO !!! =======
	 * ========================
	 *
	 * frame ?
	 * decltype
	 * benchmark
	 * SIMD
	 *
	 */

	using bool2 = vector<bool,2>;
	using bool3 = vector<bool,3>;
	using bool4 = vector<bool,4>;

	using uint2 = vector<unsigned int,2>;
	using uint3 = vector<unsigned int,3>;
	using uint4 = vector<unsigned int,4>;

	using int2 = vector<int,2>;
	using int3 = vector<int,3>;
	using int4 = vector<int,4>;

	using float2 = vector<float,2>;
	using float3 = vector<float,3>;
	using float4 = vector<float,4>;

#include <pgl-math/impl/vector.hpp>

} /* end of namespace pgl */
