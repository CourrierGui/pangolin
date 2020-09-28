#pragma once

#include <numbers>
#include <limits>
#include <cmath>
#include <utility>
#include <initializer_list>

#include <pgl-math/utils.hpp>
#include <pgl-math/base-vector.hpp>

namespace pgl {

	//TODO create only one base_vector and math_vector but specialize vector as it contains the methods which should be specialized
	// Is this still usefull ?
	template<number type, int dim>
		struct algebric_vector : public base_vector<type, dim> {
			inline constexpr          algebric_vector()                               noexcept : base_vector<type,dim>{}     {  }
			inline constexpr explicit algebric_vector(const type& e)                  noexcept : base_vector<type,dim>{e}    {  }
			inline constexpr          algebric_vector(const type arr[dim])            noexcept : base_vector<type,dim>{arr}  {  }
			inline constexpr algebric_vector(std::convertible_to<type> auto ... args) noexcept : base_vector<type,dim>{ std::forward<type>(args)... } {  } // C++ 20 <3

			//TODO create a class math_algebric_vector to factor these methods
			/* inline constexpr auto operator*=(const algebric_vector<type,dim>&) noexcept -> algebric_vector<type,dim>&; */
			/* inline constexpr auto operator/=(const algebric_vector<type,dim>&) noexcept -> algebric_vector<type,dim>&; */
			/* inline constexpr auto operator+=(const algebric_vector<type,dim>&) noexcept -> algebric_vector<type,dim>&; */
			/* inline constexpr auto operator-=(const algebric_vector<type,dim>&) noexcept -> algebric_vector<type,dim>&; */

			/* template<number scalar_type> inline constexpr auto operator*=(const scalar_type&) noexcept -> algebric_vector<type,dim>&; */
			/* template<number scalar_type> inline constexpr auto operator/=(const scalar_type&) noexcept -> algebric_vector<type,dim>&; */
			/* template<number scalar_type> inline constexpr auto operator+=(const scalar_type&) noexcept -> algebric_vector<type,dim>&; */
			/* template<number scalar_type> inline constexpr auto operator-=(const scalar_type&) noexcept -> algebric_vector<type,dim>&; */
		};

	template<typename type, int size> struct vector {  };

	template<number type, int dim>
		struct vector<type,dim> : public algebric_vector<type,dim> {
			inline constexpr          vector()                               noexcept : algebric_vector<type,dim>{}     {  }
			inline constexpr explicit vector(const type& e)                  noexcept : algebric_vector<type,dim>{e}    {  }
			inline constexpr          vector(const type arr[dim])            noexcept : algebric_vector<type,dim>{arr}  {  }
			/* inline constexpr vector(const std::initializer_list<type>& args) noexcept : algebric_vector<type,dim>{args} {  } */
			template<number... Types> inline constexpr vector(const type& t, Types&&... types) noexcept : algebric_vector<type,dim>{ t, std::forward<Types>(types)... } {  }

			/* static inline constexpr vector<type,dim> right() noexcept; */
			/* static inline constexpr vector<type,dim> left()  noexcept; */
			/* static inline constexpr vector<type,dim> up()    noexcept; */
			/* static inline constexpr vector<type,dim> down()  noexcept; */
			/* static inline constexpr vector<type,dim> front() noexcept; */
			/* static inline constexpr vector<type,dim> back()  noexcept; */
		};

	template<int dim>
		struct vector<bool,dim> : public base_vector<bool, dim> {
			inline constexpr          vector()                noexcept;
			inline constexpr explicit vector(bool)            noexcept;
			inline constexpr          vector(const bool[dim]) noexcept;
			/* template<number... Ts> inline constexpr vector(Ts&&... ts) noexcept; */
			inline constexpr vector(bool values, ...) noexcept;

			/* inline constexpr auto operator&=(const vector<bool,dim>&) noexcept -> vector<bool,dim>&; */
			/* inline constexpr auto operator|=(const vector<bool,dim>&) noexcept -> vector<bool,dim>&; */
			/* inline constexpr auto operator^=(const vector<bool,dim>&) noexcept -> vector<bool,dim>&; */
			/* inline constexpr auto operator!=(const vector<bool,dim>&) noexcept -> vector<bool,dim>&; */
		};

	template<number type>
		struct vector<type,2> : public algebric_vector<type,2> {
			inline constexpr          vector()                      noexcept : algebric_vector<type,2>{}       {  }
			inline constexpr explicit vector(const type& e)         noexcept : algebric_vector<type,2>{e}      {  }
			inline constexpr          vector(const type arr[2])     noexcept : algebric_vector<type,2>{arr}    {  }
			inline constexpr vector(const type& e1, const type& e2) noexcept : algebric_vector<type,2>( e1, e2 ) {  }

			/* static inline constexpr vector<type,2> right() noexcept; */
			/* static inline constexpr vector<type,2> left()  noexcept; */
			/* static inline constexpr vector<type,2> up()    noexcept; */
			/* static inline constexpr vector<type,2> down()  noexcept; */
		};

	template<number type>
		struct vector<type,3> : public algebric_vector<type,3> {
			inline constexpr vector()                                               noexcept : algebric_vector<type,3>{}            {  }
			inline constexpr explicit vector(const type& e)                         noexcept : algebric_vector<type,3>{e}           {  }
			inline constexpr vector(const type arr[3])                              noexcept : algebric_vector<type,3>{arr}         {  }
			inline constexpr vector(const type& e1, const type& e2, const type& e3) noexcept : algebric_vector<type,3>( e1, e2, e3 )  {  }
			inline constexpr vector(const vector<type,2>& v, const type& e)         noexcept : algebric_vector<type,3>( v.x, v.y, e ) {  }

			/* static inline constexpr vector<type,3> right() noexcept; */
			/* static inline constexpr vector<type,3> left()  noexcept; */
			/* static inline constexpr vector<type,3> up()    noexcept; */
			/* static inline constexpr vector<type,3> down()  noexcept; */
			/* static inline constexpr vector<type,3> front() noexcept; */
			/* static inline constexpr vector<type,3> back()  noexcept; */
		};

	template<number type>
		struct vector<type,4> : public algebric_vector<type,4> {
			inline constexpr vector()                                                               noexcept : algebric_vector<type,4>{}                   {  }
			inline constexpr explicit vector(const type& e)                                         noexcept : algebric_vector<type,4>{e}                  {  }
			inline constexpr vector(const type arr[4])                                              noexcept : algebric_vector<type,4>{arr}                {  }
			inline constexpr vector(const type& e1, const type& e2, const type& e3, const type& e4) noexcept : algebric_vector<type,4>( e1, e2, e3, e4 )     {  }

			// Can these constructors be one template ?
			inline constexpr vector(const vector<type,3>& v, const type& e)                         noexcept : algebric_vector<type,4>( v.x, v.y, v.z, e )   {  }
			inline constexpr vector(const vector<type,2>& v, const vector<type,2>& w)               noexcept : algebric_vector<type,4>( v.x, v.y, w.x, w.y ) {  }

			/* static inline constexpr vector<type,4> right() noexcept; */
			/* static inline constexpr vector<type,4> left()  noexcept; */
			/* static inline constexpr vector<type,4> up()    noexcept; */
			/* static inline constexpr vector<type,4> down()  noexcept; */
			/* static inline constexpr vector<type,4> front() noexcept; */
			/* static inline constexpr vector<type,4> back()  noexcept; */
		};

/*	template<number type, int dim>                     inline constexpr auto operator*(const vector<type,dim>&, const vector<type,dim>&) noexcept -> vector<type,dim>;*/
/*	template<number type, number scalar_type, int dim> inline constexpr auto operator*(const vector<type,dim>&, const scalar_type&     ) noexcept -> vector<type,dim>;*/
/*	template<number type, number scalar_type, int dim> inline constexpr auto operator*(const scalar_type&,      const vector<type,dim>&) noexcept -> vector<type,dim>;*/

/*	template<number type, int dim>                     inline constexpr auto operator/(const vector<type,dim>&, const vector<type,dim>&) noexcept -> vector<type,dim>;*/
/*	template<number type, number scalar_type, int dim> inline constexpr auto operator/(const vector<type,dim>&, const scalar_type&     ) noexcept -> vector<type,dim>;*/
/*	template<number type, number scalar_type, int dim> inline constexpr auto operator/(const scalar_type&,      const vector<type,dim>&) noexcept -> vector<type,dim>;*/

/*	template<number type, int dim>                     inline constexpr auto operator-(const vector<type,dim>&, const vector<type,dim>&) noexcept -> vector<type,dim>;*/
/*	template<number type, number scalar_type, int dim> inline constexpr auto operator-(const vector<type,dim>&, const scalar_type&     ) noexcept -> vector<type,dim>;*/
/*	template<number type, number scalar_type, int dim> inline constexpr auto operator-(const scalar_type&,      const vector<type,dim>&) noexcept -> vector<type,dim>;*/

/*	template<number type, int dim>                     inline constexpr auto operator+(const vector<type,dim>&, const vector<type,dim>&) noexcept -> vector<type,dim>;*/
/*	template<number type, number scalar_type, int dim> inline constexpr auto operator+(const vector<type,dim>&, const scalar_type&     ) noexcept -> vector<type,dim>;*/
/*	template<number type, number scalar_type, int dim> inline constexpr auto operator+(const scalar_type&,      const vector<type,dim>&) noexcept -> vector<type,dim>;*/

/*	template<number type, int dim> inline constexpr auto dot(const vector<type,dim>&, const vector<type,dim>&) noexcept -> type;*/
/*	template<number type, int dim> inline constexpr auto dot(const vector<type,dim>&)                          noexcept -> type;*/
/*	template<number type, int dim> inline constexpr auto sum(const vector<type,dim>&)                          noexcept -> type;*/
/*	template<number type, int dim> inline constexpr auto abs(const vector<type,dim>&)                          noexcept -> vector<type,dim>;*/
/*	template<number type, int dim> inline constexpr auto normalize(const vector<type,dim>&)                    noexcept -> vector<type,dim>;*/
/*	template<number type, int dim> constexpr inline auto lerp(const vector<type,dim>&, const vector<type,dim>&, type) noexcept -> vector<type,dim>;*/

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

	using uint2 = vector<unsigned int,2>;
	using uint3 = vector<unsigned int,3>;
	using uint4 = vector<unsigned int,4>;

	using int2 = vector<int,2>;
	using int3 = vector<int,3>;
	using int4 = vector<int,4>;

	using float2 = vector<float,2>;
	using float3 = vector<float,3>;
	using float4 = vector<float,4>;

} /* end of namespace pgl */
