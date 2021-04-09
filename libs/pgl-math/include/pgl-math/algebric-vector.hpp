#pragma once

#include <pgl-math/utils.hpp>
#include <pgl-math/base-vector.hpp>

namespace pgl {

  template<integral type, length dim, template<integral t, length d> class v>
    struct base_vector;

  template<number type, length dim, template<typename T, length d> class vector_type>
    struct algebric_vector : public base_vector<type, dim,vector_type> {
      template<typename t> using container_of = algebric_vector<t, dim,vector_type>;

      inline constexpr algebric_vector(const type& e) noexcept;
      inline constexpr algebric_vector() noexcept;
      inline constexpr algebric_vector(const type arr[dim]) noexcept;
      inline constexpr algebric_vector(std::convertible_to<type> auto ... args) noexcept;

      inline constexpr auto operator*=(
        const algebric_vector<type,dim,vector_type>& vect) noexcept
        -> algebric_vector<type,dim,vector_type>&;

      inline constexpr auto operator/=(
        const algebric_vector<type,dim,vector_type>& vect) noexcept
        -> algebric_vector<type,dim,vector_type>&;

      inline constexpr auto operator+=(
        const algebric_vector<type,dim,vector_type>& vect) noexcept
        -> algebric_vector<type,dim,vector_type>&;

      inline constexpr auto operator-=(
        const algebric_vector<type,dim,vector_type>& vect) noexcept
        -> algebric_vector<type,dim,vector_type>&;

      inline constexpr auto operator*=(std::convertible_to<type> auto scalar) noexcept
        -> algebric_vector<type,dim,vector_type>&;

      inline constexpr auto operator/=(std::convertible_to<type> auto scalar) noexcept
        -> algebric_vector<type,dim,vector_type>&;

      inline constexpr auto operator+=(std::convertible_to<type> auto scalar) noexcept
        -> algebric_vector<type,dim,vector_type>&;

      inline constexpr auto operator-=(std::convertible_to<type> auto scalar) noexcept
        -> algebric_vector<type,dim,vector_type>&;
    };

} /* end of namespace pgl */
