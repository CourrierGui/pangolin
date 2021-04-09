#pragma once

#include <cmath>
#include <iostream>

#include <pgl-math/impl/base-vector.hpp>
#include <pgl-math/impl/algebric-vector.hpp>

namespace pgl {

  template<number type, length dim> inline constexpr vector<type,dim>::vector() noexcept :
    algebric_vector<type,dim,vector>{} {  }

  template<number type, length dim>
    inline constexpr vector<type,dim>::vector(const type& e) noexcept :
    algebric_vector<type,dim,vector>{e} {  }

  template<number type, length dim>
    inline constexpr vector<type,dim>::vector(const type arr[dim]) noexcept :
    algebric_vector<type,dim,vector>{arr} {  }

  template<number type, length dim>
    inline constexpr vector<type,dim>::vector(
      std::convertible_to<type> auto ... args) noexcept :
    algebric_vector<type,dim,vector>{ std::forward<type>(args)... } {  }

  template<length dim>
    inline constexpr vector<bool,dim>::vector() noexcept :
    base_vector<bool, dim,vector>{}    {  }

  template<length dim>
    inline constexpr vector<bool,dim>::vector(bool b) noexcept :
    base_vector<bool, dim,vector>{b}   {  }

  template<length dim>
    inline constexpr vector<bool,dim>::vector(const bool arr[dim]) noexcept :
    base_vector<bool, dim,vector>{arr} {  }

  template<length dim>
    inline constexpr vector<bool,dim>::vector(
      std::convertible_to<bool> auto ... args) noexcept :
    base_vector<bool,dim,vector>{ std::forward<bool>(args)... } {  }

  template<number type>
    inline constexpr vector<type,2>::vector() noexcept :
    algebric_vector<type,2,vector>{} {  }

  template<number type>
    inline constexpr vector<type,2>::vector(const type& e) noexcept :
    algebric_vector<type,2,vector>{e} {  }

  template<number type>
    inline constexpr vector<type,2>::vector(const type arr[2]) noexcept :
    algebric_vector<type,2,vector>{arr} {  }

  template<number type>
    inline constexpr vector<type,2>::vector(const type& e1, const type& e2) noexcept :
    algebric_vector<type,2,vector>( e1, e2 ) {  }

  template<number type>
    inline constexpr vector<type,2> vector<type,2>::right() noexcept {
      return { type{ 1}, type{ 0} };
    }

  template<number type>
    inline constexpr vector<type,2> vector<type,2>::left() noexcept {
      return { type{-1}, type{ 0} };
    }

  template<number type>
    inline constexpr vector<type,2> vector<type,2>::up() noexcept {
      return { type{ 0}, type{ 1} };
    }

  template<number type>
    inline constexpr vector<type,2> vector<type,2>::down() noexcept {
      return { type{ 0}, type{-1} };
    }

  template<number type>
    inline constexpr vector<type,3>::vector() noexcept :
    algebric_vector<type,3,vector>{} {  }

  template<number type>
    inline constexpr vector<type,3>::vector(const type& e) noexcept :
    algebric_vector<type,3,vector>{e} {  }

  template<number type>
    inline constexpr vector<type,3>::vector(const type arr[3]) noexcept :
    algebric_vector<type,3,vector>{arr} {  }

  template<number type>
    inline constexpr vector<type,3>::vector(const type& e1,
                                            const type& e2,
                                            const type& e3) noexcept :
    algebric_vector<type,3,vector>( e1, e2, e3 )  {  }

  template<number type>
    inline constexpr vector<type,3>::vector(const vector<type,2>& v,
                                            const type& e) noexcept :
    algebric_vector<type,3,vector>( v.x, v.y, e ) {  }

  template<number type>
    inline constexpr vector<type,3> vector<type,3>::right() noexcept {
      return { type{ 1}, type{ 0}, type{ 0} };
    }

  template<number type>
    inline constexpr vector<type,3> vector<type,3>::left() noexcept {
      return { type{-1}, type{ 0}, type{ 0} };
    }

  template<number type>
    inline constexpr vector<type,3> vector<type,3>::up() noexcept {
      return { type{ 0}, type{ 1}, type{ 0} };
    }

  template<number type>
    inline constexpr vector<type,3> vector<type,3>::down() noexcept {
      return { type{ 0}, type{-1}, type{ 0} };
    }

  template<number type>
    inline constexpr vector<type,3> vector<type,3>::front() noexcept {
      return { type{ 0}, type{ 0}, type{ 1} };
    }

  template<number type>
    inline constexpr vector<type,3> vector<type,3>::back() noexcept {
      return { type{ 0}, type{ 0}, type{-1} };
    }

  template<number type>
    inline constexpr vector<type,4>::vector() noexcept :
    algebric_vector<type,4,vector>{} {  }

  template<number type>
    inline constexpr vector<type,4>::vector(const type& e) noexcept :
    algebric_vector<type,4,vector>{e} {  }

  template<number type>
    inline constexpr vector<type,4>::vector(const type arr[4]) noexcept :
    algebric_vector<type,4,vector>{arr} {  }

  template<number type>
    inline constexpr vector<type,4>::vector(const type& a, const type& b,
                                            const type& c, const type& d) noexcept :
    algebric_vector<type,4,vector>{a,b,c,d} {  }

  template<number type>
    inline constexpr vector<type,4>::vector(const vector<type,3>& v,
                                            const type& e) noexcept :
    algebric_vector<type,4,vector>(v.x, v.y, v.z, e) {  }

  template<number type>
    inline constexpr vector<type,4>::vector(const vector<type,2>& v,
                                            const vector<type,2>& w) noexcept :
    algebric_vector<type,4,vector>( v.x, v.y, w.x, w.y ) {  }


  template<number type>
    inline constexpr vector<type,4> vector<type,4>::right() noexcept {
      return { type{1}, type{0}, type{0}, type{0} };
    }

  template<number type>
    inline constexpr vector<type,4> vector<type,4>::left() noexcept {
      return { type{-1}, type{ 0}, type{ 0}, type{0} };
    }

  template<number type>
    inline constexpr vector<type,4> vector<type,4>::up() noexcept {
      return { type{0}, type{1}, type{0}, type{0} };
    }

  template<number type>
    inline constexpr vector<type,4> vector<type,4>::down() noexcept {
      return { type{0}, type{-1}, type{0}, type{0} };
    }

  template<number type>
    inline constexpr vector<type,4> vector<type,4>::front() noexcept {
      return { type{0}, type{0}, type{1}, type{0} };
    }

  template<number type>
    inline constexpr vector<type,4> vector<type,4>::back() noexcept {
      return { type{0}, type{0}, type{-1}, type{0} };
    }

  template<number type, length dim>
    inline constexpr auto operator*(const vector<type,dim>& lhs,
                                    const vector<type,dim>& rhs) noexcept
    -> vector<type,dim>
    {
      vector<type,dim> res{lhs};
      res *= rhs;
      return res;
    }

  template<number type, number scalar_type, length dim>
    inline constexpr auto operator*(const vector<type,dim>& lhs,
                                    const scalar_type& rhs) noexcept
    -> vector<type,dim>
    {
      vector<type,dim> res{lhs};
      res *= rhs;
      return res;
    }

  template<number type, number scalar_type, length dim>
    inline constexpr auto operator*(const scalar_type& lhs,
                                    const vector<type,dim>& rhs) noexcept
    -> vector<type,dim>
    {
      vector<type,dim> res{lhs};
      res *= rhs;
      return res;
    }

  template<number type, length dim>
    inline constexpr auto operator/(const vector<type,dim>& lhs,
                                    const vector<type,dim>& rhs) noexcept
    -> vector<type,dim>
    {
      vector<type,dim> res{lhs};
      res /= rhs;
      return res;
    }

  template<number type, number scalar_type, length dim>
    inline constexpr auto operator/(const vector<type,dim>& lhs,
                                    const scalar_type& rhs) noexcept
    -> vector<type,dim>
    {
      vector<type,dim> res{lhs};
      res /= rhs;
      return res;
    }

  template<number type, number scalar_type, length dim>
    inline constexpr auto operator/(const scalar_type& lhs,
                                    const vector<type,dim>& rhs) noexcept
    -> vector<type,dim>
    {
      vector<type,dim> res{lhs};
      res /= rhs;
      return res;
    }

  template<number type, length dim>
    inline constexpr auto operator-(const vector<type,dim>& lhs,
                                    const vector<type,dim>& rhs) noexcept
    -> vector<type,dim>
    {
      vector<type,dim> res{lhs};
      res -= rhs;
      return res;
    }

  template<number type, number scalar_type, length dim>
    inline constexpr auto operator-(const vector<type,dim>& lhs,
                                    const scalar_type& rhs) noexcept
    -> vector<type,dim>
    {
      vector<type,dim> res{lhs};
      res -= rhs;
      return res;
    }

  template<number type, length dim>
    inline constexpr auto operator-(const vector<type,dim>& vec) noexcept
    -> vector<type,dim>
    {
      vector<type,dim> res(type{0});
      res -= vec;
      return res;
    }

  template<number type, number scalar_type, length dim>
    inline constexpr auto operator-(const scalar_type& lhs,
                                    const vector<type,dim>& rhs) noexcept
    -> vector<type,dim>
    {
      vector<type,dim> res{lhs};
      res -= rhs;
      return res;
    }

  template<number type, length dim>
    inline constexpr auto operator+(const vector<type,dim>& lhs,
                                    const vector<type,dim>& rhs) noexcept
    -> vector<type,dim>
    {
      vector<type,dim> res{lhs};
      res += rhs;
      return res;
    }

  template<number type, number scalar_type, length dim>
    inline constexpr auto operator+(const vector<type,dim>& lhs,
                                    const scalar_type& rhs) noexcept
    -> vector<type,dim>
    {
      vector<type,dim> res{lhs};
      res += rhs;
      return res;
    }

  template<number type, number scalar_type, length dim>
    inline constexpr auto operator+(const scalar_type& lhs,
                                    const vector<type,dim>& rhs) noexcept
    -> vector<type,dim>
    {
      vector<type,dim> res{lhs};
      res += rhs;
      return res;
    }

  template<number type, length dim>
    inline constexpr auto dot(
      const vector<type,dim>& lhs,
      const vector<type,dim>& rhs) noexcept
    -> type
    {
      type res{0};
      for (auto lhs_it=lhs.begin(), rhs_it=rhs.begin();
           lhs_it != lhs.end();
           ++lhs_it,++rhs_it)
      {
        res += *(lhs_it) * *(rhs_it);
      }
      return res;
    }

  template<number type, length dim>
    inline constexpr auto dot(const vector<type,dim>& arg) noexcept
    -> type
    {
      return dot(arg,arg);
    }

  template<number type, length dim>
    inline constexpr auto sum(const vector<type,dim>& arg) noexcept
    -> type
    {
      type res{0};
      for (const auto& elem: arg) {
        res += elem;
      }
      return res;
    }

  template<number type, length dim>
    inline constexpr auto normalize(const vector<type,dim>& arg) noexcept
    -> vector<type,dim>
    {
      return arg/norm(arg);
    }

  template<number type, length dim>
    inline constexpr auto norm(const vector<type,dim>& arg) noexcept
    -> type
    {
      return std::sqrt(dot(arg, arg));
    }

  template<number type, length dim>
    constexpr inline auto lerp(
      const vector<type,dim>& x,
      const vector<type,dim>& y,
      type a) noexcept
    -> vector<type,dim>
    {
      return x * (static_cast<type>(1) - a) + y * a;
    }

  template<number type, length dim>
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
    inline constexpr auto cross(const vector<type,3>& lhs,
                                const vector<type,3>& rhs) noexcept
    -> vector<type,3>
    {
      return vector<type,3>{
        lhs.y*rhs.z - lhs.z*rhs.y,
        lhs.z*rhs.x - lhs.x*rhs.z,
        lhs.x*rhs.y - lhs.y*rhs.x
      };
    }

} /* end of namespace pgl */
