#pragma once

#include <pgl-math/utils.hpp>
#include <pgl-math/algebric-vector.hpp>

namespace pgl {

  /* template<typename type, length dim> struct vector {  }; */

  template<typename type, length dim>
    struct vector : public algebric_vector<type,dim,vector> {
      template<typename t> using container_of = vector<t, dim>;
      inline constexpr          vector()                               noexcept;
      inline constexpr explicit vector(const type& e)                  noexcept;
      inline constexpr          vector(const type arr[dim])            noexcept;
      inline constexpr vector(std::convertible_to<type> auto ... args) noexcept;
    };

  template<length dim>
    struct vector<bool,dim> : public base_vector<bool,dim,vector> {
      template<typename t> using container_of = vector<t, dim>;
      inline constexpr          vector()                    noexcept;
      inline constexpr explicit vector(bool b)              noexcept;
      inline constexpr          vector(const bool arr[dim]) noexcept;
      inline constexpr vector(std::convertible_to<bool> auto ... args) noexcept;

      /* inline constexpr auto operator&=(const vector<bool,dim>&) noexcept */
      /*  -> vector<bool,dim>&; */
      /* inline constexpr auto operator|=(const vector<bool,dim>&) noexcept */
      /*   -> vector<bool,dim>&; */
      /* inline constexpr auto operator^=(const vector<bool,dim>&) noexcept */
      /*   -> vector<bool,dim>&; */
      /* inline constexpr auto operator~=(const vector<bool,dim>&) noexcept */
      /*   -> vector<bool,dim>&; */
    };

  template<number type>
    struct vector<type,2> : public algebric_vector<type,2,vector> {
      template<typename t> using container_of = vector<t, 2>;
      inline constexpr          vector()                      noexcept;
      inline constexpr explicit vector(const type& e)         noexcept;
      inline constexpr          vector(const type arr[2])     noexcept;
      inline constexpr vector(const type& e1, const type& e2) noexcept;

      static inline constexpr vector<type,2> right() noexcept;
      static inline constexpr vector<type,2> left()  noexcept;
      static inline constexpr vector<type,2> up()    noexcept;
      static inline constexpr vector<type,2> down()  noexcept;
    };

  template<number type>
    struct vector<type,3> : public algebric_vector<type,3,vector> {
      template<typename t> using container_of = vector<t, 3>;
      inline constexpr vector()                                               noexcept;
      inline constexpr explicit vector(const type& e)                         noexcept;
      inline constexpr vector(const type arr[3])                              noexcept;
      inline constexpr vector(const type& e1, const type& e2, const type& e3) noexcept;
      inline constexpr vector(const vector<type,2>& v, const type& e)         noexcept;

      static inline constexpr vector<type,3> right() noexcept;
      static inline constexpr vector<type,3> left()  noexcept;
      static inline constexpr vector<type,3> up()    noexcept;
      static inline constexpr vector<type,3> down()  noexcept;
      static inline constexpr vector<type,3> front() noexcept;
      static inline constexpr vector<type,3> back()  noexcept;
    };

  template<number type>
    struct vector<type,4> : public algebric_vector<type,4,vector> {
      template<typename t> using container_of = vector<t, 4>;
      inline constexpr vector() noexcept;
      inline constexpr explicit vector(const type& e) noexcept;
      inline constexpr vector(const type arr[4]) noexcept;
      inline constexpr vector(const type& e1, const type& e2,
                              const type& e3, const type& e4) noexcept;

      // Can these constructors be one template ?
      inline constexpr vector(const vector<type,3>& v, const type& e) noexcept;
      inline constexpr vector(
        const vector<type,2>& v,
        const vector<type,2>& w) noexcept;

      static inline constexpr vector<type,4> right() noexcept;
      static inline constexpr vector<type,4> left()  noexcept;
      static inline constexpr vector<type,4> up()    noexcept;
      static inline constexpr vector<type,4> down()  noexcept;
      static inline constexpr vector<type,4> front() noexcept;
      static inline constexpr vector<type,4> back()  noexcept;
    };

  template<number type, length dim>
    inline constexpr auto operator*(const vector<type,dim>& lhs,
                                    const vector<type,dim>& rhs) noexcept
    -> vector<type,dim>;

  template<number type, number scalar_type, length dim>
    inline constexpr auto operator*(const vector<type,dim>& lhs,
                                    const scalar_type& rhs) noexcept
    -> vector<type,dim>;

  template<number type, number scalar_type, length dim>
    inline constexpr auto operator*(const scalar_type& lhs,
                                    const vector<type,dim>& rhs) noexcept
    -> vector<type,dim>;


  template<number type, length dim>
    inline constexpr auto operator/(const vector<type,dim>& lhs,
                                    const vector<type,dim>& rhs) noexcept
    -> vector<type,dim>;

  template<number type, number scalar_type, length dim>
    inline constexpr auto operator/(const vector<type,dim>& lhs,
                                    const scalar_type& rhs) noexcept
    -> vector<type,dim>;

  template<number type, number scalar_type, length dim>
    inline constexpr auto operator/(const scalar_type& lhs,
                                    const vector<type, dim>& rhs) noexcept
    -> vector<type,dim>;

  template<number type, length dim>
    inline constexpr auto operator-(const vector<type,dim>& lhs,
                                    const vector<type,dim>& rhs) noexcept
    -> vector<type,dim>;

  template<number type, number scalar_type, length dim>
    inline constexpr auto operator-(const vector<type,dim>& lhs,
                                    const scalar_type& rhs) noexcept
    -> vector<type,dim>;

  template<number type, length dim>
    inline constexpr auto operator-(const vector<type,dim>& vec) noexcept
    -> vector<type, dim>;

  template<number type, number scalar_type, length dim>
    inline constexpr auto operator-(const scalar_type& lhs,
                                    const vector<type,
                                    dim>& rhs) noexcept
    -> vector<type,dim>;


  template<number type, length dim>
    inline constexpr auto operator+(const vector<type,dim>& lhs,
                                    const vector<type,dim>& rhs) noexcept
    -> vector<type,dim>;

  template<number type, number scalar_type, length dim>
    inline constexpr auto operator+(const vector<type,dim>& lhs,
                                    const scalar_type& rhs) noexcept
    -> vector<type,dim>;

  template<number type, number scalar_type, length dim>
    inline constexpr auto operator+(const scalar_type& lhs,
                                    const vector<type,dim>& rhs) noexcept
    -> vector<type,dim>;


  template<number type, length dim>
    inline constexpr auto dot(const vector<type,dim>&,
                              const vector<type,dim>&) noexcept
    -> type;

  template<number type, length dim>
    inline constexpr auto dot(const vector<type,dim>&) noexcept -> type;

  template<number type, length dim>
    inline constexpr auto sum(const vector<type,dim>&) noexcept -> type;

  template<number type, length dim>
    inline constexpr auto abs(const vector<type,dim>&) noexcept -> vector<type,dim>;

  template<number type, length dim>
    inline constexpr auto normalize(const vector<type,dim>&) noexcept
    -> vector<type,dim>;

  template<number type, length dim>
    inline constexpr auto norm(const vector<type,dim>&) noexcept -> type;

  template<number type, length dim>
    inline constexpr auto lerp(const vector<type,dim>&,
                               const vector<type,dim>&,
                               type) noexcept
    -> vector<type,dim>;

  template<typename type>
    inline constexpr auto cross(const vector<type,3>& lhs,
                                const vector<type,3>& rhs) noexcept
    -> vector<type,3>;

  /*
   * ====================
   * ======= TODO =======
   * ====================
   *
   * copy, move constructor
   * operator=
   * frame ?
   * decltype
   * benchmark
   * SIMD
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
