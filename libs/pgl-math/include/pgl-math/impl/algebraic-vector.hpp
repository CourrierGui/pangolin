
#pragma once

#include <cmath>
#include <iostream>

#include <pgl-math/vector.hpp>

namespace pgl {

  template<number type, length dim, template<typename T, length d> class vector_type>
    inline constexpr algebraic_vector<type,dim,vector_type>::algebraic_vector() noexcept
    : base_vector<type,dim,vector_type>{} {  }

  template<number type, length dim, template<typename T, length d> class vector_type>
    inline constexpr algebraic_vector<type,dim,vector_type>::algebraic_vector(
      const type& e) noexcept :
    base_vector<type,dim,vector_type>{e} {  }

  template<number type, length dim, template<typename T, length d> class vector_type>
    inline constexpr algebraic_vector<type,dim,vector_type>::algebraic_vector(
      const type arr[dim]) noexcept :
    base_vector<type,dim,vector_type>{arr} {  }

  template<number type, length dim, template<typename T, length d> class vector_type>
    inline constexpr algebraic_vector<type,dim,vector_type>::algebraic_vector(
      std::convertible_to<type> auto ... args) noexcept :
    base_vector<type,dim,vector_type>{ std::forward<type>(args)... } {  }

  template<number type, length dim, template<typename T, length d> class vector_type>
    inline constexpr auto algebraic_vector<type,dim,vector_type>::operator*=(
      const algebraic_vector<type,dim,vector_type>& vect) noexcept
    -> algebraic_vector<type,dim,vector_type>&
    {
      auto it = vect.cbegin();
      for (auto& e: this->elements) {
        e *= *(it++);
      }
      return *this;
    }

  template<number type, length dim, template<typename T, length d> class vector_type>
    inline constexpr auto algebraic_vector<type,dim,vector_type>::operator/=(
      const algebraic_vector<type,dim,vector_type>& vect) noexcept
    -> algebraic_vector<type,dim,vector_type>&
    {
      auto it = vect.cbegin();
      for (auto& e: this->elements) {
        e /= *(it++);
      }
      return *this;
    }

  template<number type, length dim, template<typename T, length d> class vector_type>
    inline constexpr auto algebraic_vector<type,dim,vector_type>::operator+=(
      const algebraic_vector<type,dim,vector_type>& vect) noexcept
    -> algebraic_vector<type,dim,vector_type>&
    {
      auto it = vect.cbegin();
      for (auto& e: this->elements) {
        e += *(it++);
      }
      return *this;
    }

  template<number type, length dim, template<typename T, length d> class vector_type>
    inline constexpr auto algebraic_vector<type,dim,vector_type>::operator-=(
      const algebraic_vector<type,dim,vector_type>& vect) noexcept
    -> algebraic_vector<type,dim,vector_type>&
    {
      auto it = vect.cbegin();
      for (auto& e: this->elements) {
        e -= *(it++);
      }
      return *this;
    }

  template<number type, length dim, template<typename T, length d> class vector_type>
    inline constexpr auto algebraic_vector<type,dim,vector_type>::operator*=(
      std::convertible_to<type> auto scalar) noexcept
    -> algebraic_vector<type,dim,vector_type>&
    {
      for (auto& e: this->elements) {
        e *= scalar;
      }
      return *this;
    }

  template<number type, length dim, template<typename T, length d> class vector_type>
    inline constexpr auto algebraic_vector<type,dim,vector_type>::operator/=(
      std::convertible_to<type> auto scalar) noexcept
    -> algebraic_vector<type,dim,vector_type>&
    {
      for (auto& e: this->elements) {
        e /= scalar;
      }
      return *this;
    }

  template<number type, length dim, template<typename T, length d> class vector_type>
    inline constexpr auto algebraic_vector<type,dim,vector_type>::operator+=(
      std::convertible_to<type> auto scalar) noexcept
    -> algebraic_vector<type,dim,vector_type>&
    {
      for (auto& e: this->elements) {
        e += scalar;
      }
      return *this;
    }

  template<number type, length dim, template<typename T, length d> class vector_type>
    inline constexpr auto algebraic_vector<type,dim,vector_type>::operator-=(
      std::convertible_to<type> auto scalar) noexcept
    -> algebraic_vector<type,dim,vector_type>&
    {
      for (auto& e: this->elements) {
        e -= scalar;
      }
      return *this;
    }

} /* end of namespace pgl */
