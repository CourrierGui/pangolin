#pragma once

#include <pgl-math/base-vector.hpp>

#include <initializer_list>
#include <cstdint>
#include <utility>

namespace pgl {

  template<integral type, length dim, template<typename T, length d> class vector_type>
    inline constexpr base<type,dim,vector_type>::base() noexcept :
    elements{} {  }

  template<integral type, length dim, template<typename T, length d> class vector_type>
    inline constexpr base<type,dim,vector_type>::base(const type arr[dim]) noexcept :
    elements{}
  {
    auto it=arr;
    for (auto& e: elements) { e = *(it++); }
  }

  template<integral type, length dim, template<typename T, length d> class vector_type>
    inline constexpr  base<type,dim,vector_type>::base(const type& e) noexcept :
    elements{}
  {
    for (auto& elem: this->elements) { elem = e; }
  }

  template<integral type, length dim, template<typename T, length d> class vector_type>
    inline constexpr base<type,dim,vector_type>::base(
      std::convertible_to<type> auto ... args) noexcept
    : elements{ std::forward<type>(args)... }
  {
    static_assert(sizeof...(args) == dim, "Invalid number of arguments.");
  }

  template<integral type, template<typename T, length d> class vector_type>
    inline constexpr base<type,4,vector_type>::base() noexcept :
    elements{} {  }

  template<integral type, template<typename T, length d> class vector_type>
    inline constexpr base<type,4,vector_type>::base(
      const type arr[4]) noexcept :
    elements{arr[0], arr[1], arr[2], arr[3]} { }

  template<integral type, template<typename T, length d> class vector_type>
    inline constexpr base<type,4,vector_type>::base(const type& e) noexcept :
    elements{e, e, e, e} { }

  template<integral type, template<typename T, length d> class vector_type>
    inline constexpr base<type,4,vector_type>::base(
      std::convertible_to<type> auto ... args) noexcept
    : elements{ std::forward<type>(args)... }
  {
    static_assert(sizeof...(args) == 4, "Invalid number of arguments, expected 4.");
  }

  template<integral type, template<typename T, length d> class vector_type>
    inline constexpr base<type,3,vector_type>::base() noexcept :
    elements{} {  }

  template<integral type, template<typename T, length d> class vector_type>
    inline constexpr base<type,3,vector_type>::base(const type arr[3]) noexcept :
    elements{arr[0], arr[1], arr[2]} { }

  template<integral type, template<typename T, length d> class vector_type>
    inline constexpr base<type,3,vector_type>::base(const type& e) noexcept :
    elements{e, e, e} { }

  template<integral type, template<typename T, length d> class vector_type>
    inline constexpr base<type,3,vector_type>::base(
      std::convertible_to<type> auto ... args) noexcept
    : elements{ std::forward<type>(args)... }
  {
    static_assert(sizeof...(args) == 3, "Invalid number of arguments, expected 3.");
  }

  template<integral type,template<typename T, length d> class vector_type>
    inline constexpr base<type,2,vector_type>::base() noexcept :
    elements{} {  }

  template<integral type,template<typename T, length d> class vector_type>
    inline constexpr base<type,2,vector_type>::base(const type arr[2]) noexcept
    : elements{arr[0], arr[1]} { }

  template<integral type,template<typename T, length d> class vector_type>
    inline constexpr base<type,2,vector_type>::base(const type& e) noexcept
    : elements{e, e} { }

  template<integral type,template<typename T, length d> class vector_type>
    inline constexpr base<type,2,vector_type>::base(
      std::convertible_to<type> auto ... args) noexcept
    : elements{ std::forward<type>(args)... }
  {
    static_assert(sizeof...(args) == 2, "Invalid number of arguments, expected 2.");
  }

  template<integral type, length dim, template<typename T,length d> class vector_type>
    inline constexpr auto base_vector<type,dim,vector_type>::data() noexcept
    -> raw_data
    {
      return raw_data{this->elements};
    }

  template<integral type, length dim, template<typename T,length d> class vector_type>
    inline constexpr auto base_vector<type,dim,vector_type>::size() const noexcept
    -> int
    {
      return dim;
    }

  template<integral type, length dim, template<typename T,length d> class vector_type>
    inline constexpr auto base_vector<type,dim,vector_type>::begin() noexcept
    -> type*
    {
      return this->elements;
    }

  template<integral type, length dim, template<typename T,length d> class vector_type>
    inline constexpr auto base_vector<type,dim,vector_type>::begin() const noexcept
    -> const type*
    {
      return this->elements;
    }

  template<integral type, length dim, template<typename T,length d> class vector_type>
    inline constexpr auto base_vector<type,dim,vector_type>::cbegin() const noexcept
    -> const type*
    {
      return this->elements;
    }

  template<integral type, length dim, template<typename T,length d> class vector_type>
    inline constexpr auto base_vector<type,dim,vector_type>::end() noexcept
    -> type*
    {
      return this->elements + size();
    }

  template<integral type, length dim, template<typename T,length d> class vector_type>
    inline constexpr auto base_vector<type,dim,vector_type>::end() const noexcept
    -> const type*
    {
      return this->elements + size();
    }

  template<integral type, length dim, template<typename T,length d> class vector_type>
    inline constexpr auto base_vector<type,dim,vector_type>::cend() const noexcept
    -> const type*
    {
      return this->elements + size();
    }

  template<integral type, length dim, template<typename T,length d> class vector_type>
    inline constexpr base_vector<type,dim,vector_type>::base_vector() noexcept
    : base<type,dim,vector_type>{} {  }

  template<integral type, length dim, template<typename T,length d> class vector_type>
    inline constexpr base_vector<type,dim,vector_type>::base_vector(const type& e)
    noexcept : base<type,dim,vector_type>{e} { }

  template<integral type, length dim, template<typename T,length d> class vector_type>
    inline constexpr base_vector<type,dim,vector_type>::base_vector(const type arr[dim])
    noexcept : base<type,dim,vector_type>{arr} { }

  template<integral type, length dim, template<typename T,length d> class vector_type>
    inline constexpr base_vector<type,dim,vector_type>::base_vector(
      std::convertible_to<type> auto ... args) noexcept :
    base<type,dim,vector_type>{ std::forward<type>(args)... } { }

} /* end of namespace pgl */
