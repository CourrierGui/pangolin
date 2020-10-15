#pragma once

#include <pgl-math/utils.hpp>
#include <initializer_list>
#include <cstdint>
#include <utility>

namespace pgl {

	template<integral type, uint32_t dim, template<typename T, uint32_t d> class vector_type>
		struct base {
			using value_type     = type;
			using size_type      = uint32_t;
			using iterator       = type*;
			using const_iterator = const type*;

			inline constexpr base() noexcept = default;

			inline constexpr base(const type arr[dim]) noexcept : elements{} {
				auto it=arr;
				for (auto& e: elements) { e = *(it++); }
			}

			inline constexpr explicit base(const type& e) noexcept : elements{} {
				for (auto& elem: this->elements) { elem = e; }
			}

			inline constexpr base(std::convertible_to<type> auto ... args) noexcept : elements{ std::forward<type>(args)... } {
				static_assert(sizeof...(args) == dim, "Invalid number of arguments.");
			}

			type elements[dim];
		};

	template<integral type, template<typename T, uint32_t d> class vector_type>
		struct base<type,4, vector_type> {
			inline constexpr          base()                                        noexcept = default;
			inline constexpr          base(const type arr[4])                       noexcept : elements{arr[0], arr[1], arr[2], arr[3]} { }
			inline constexpr explicit base(const type& e)                           noexcept : elements{e, e, e, e} { }
			inline constexpr          base(std::convertible_to<type> auto ... args) noexcept : elements{ std::forward<type>(args)... } {
				static_assert(sizeof...(args) == 4, "Invalid number of arguments, expected 4.");
			}

			union {
				type elements[4];
				struct { vector_type<type,3> xyz; };
				struct { vector_type<type,2> xy, zw; };
				struct { type x, y, z, w; };
			};
		};

	template<integral type, template<typename T, uint32_t d> class vector_type>
		struct base<type,3, vector_type> {
			inline constexpr          base()                                        noexcept = default;
			inline constexpr          base(const type arr[3])                       noexcept : elements{arr[0], arr[1], arr[2]} { }
			inline constexpr explicit base(const type& e)                           noexcept : elements{e, e, e} { }
			inline constexpr          base(std::convertible_to<type> auto ... args) noexcept : elements{ std::forward<type>(args)... } {
				static_assert(sizeof...(args) == 3, "Invalid number of arguments, expected 3.");
			}
			union {
				type elements[3];
				struct { vector_type<type,2> xy; };
				struct { type x, y, z; };
			};
		};

	template<integral type,template<typename T, uint32_t d> class vector_type>
		struct base<type,2,vector_type> {
			inline constexpr          base()                                        noexcept = default;
			inline constexpr          base(const type arr[2])                       noexcept : elements{arr[0], arr[1]} { }
			inline constexpr explicit base(const type& e)                           noexcept : elements{e, e} { }
			inline constexpr          base(std::convertible_to<type> auto ... args) noexcept : elements{ std::forward<type>(args)... } {
				static_assert(sizeof...(args) == 2, "Invalid number of arguments, expected 2.");
			}
			union {
				type elements[2];
				struct { type x, y; };
			};
		};

	template<integral type, uint32_t dim>
		struct base_vector : public base<type,dim,base_vector> {
			using value_type     = type;
			using size_type      = int;
			using iterator       = type*;
			using const_iterator = const type*;
			template<typename T> using container_of = base_vector<T,dim>;

			struct raw_data {
				type data[dim];
				int size;
				inline constexpr raw_data(const type arr[dim]) noexcept : data{}, size{dim} { auto it=data, val=arr; while (it!=data+dim) { *(it++) = *(val++); } }
			};
			inline constexpr auto data() noexcept -> raw_data  { return raw_data{this->elements}; }
			inline constexpr auto size() const noexcept -> int { return dim;                      }

			inline constexpr auto begin()        noexcept -> type*       { return this->elements;          }
			inline constexpr auto begin()  const noexcept -> const type* { return this->elements;          }
			inline constexpr auto cbegin() const noexcept -> const type* { return this->elements;          }
			inline constexpr auto end()          noexcept -> type*       { return this->elements + size(); }
			inline constexpr auto end()    const noexcept -> const type* { return this->elements + size(); }
			inline constexpr auto cend()   const noexcept -> const type* { return this->elements + size(); }

			inline constexpr base_vector() noexcept : base<type,dim,base_vector>{} {  }

			inline constexpr explicit base_vector(const type& e) noexcept : base<type,dim,base_vector>{e} { }

			inline constexpr base_vector(const type arr[dim]) noexcept : base<type,dim,base_vector>{arr} { }

			inline constexpr base_vector(std::convertible_to<type> auto ... args) noexcept : base<type,dim,base_vector>{ std::forward<type>(args)... } { }
		};

} /* end of namespace pgl */
