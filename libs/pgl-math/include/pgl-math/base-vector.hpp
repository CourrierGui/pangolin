#pragma once

#include <pgl-math/utils.hpp>
#include <initializer_list>

namespace pgl {

	template<integral type, int dim>
		struct base_vector {
			using value_type     = type;
			using size_type      = int;
			using iterator       = type*;
			using const_iterator = const type*;
			template<typename T> using container_of = base_vector<T,dim>;

			/*
			 * All these overloads just to generalize this structure, can it be generalized alone and used here?
			 *
			 * Inherit form it ?
			 *
			 * so that this is legal:
			 *
			 * pgl::vector<int,2> i2;
			 * pgl::vector<int,3> i3;
			 * pgl::vector<int,4> i4;
			 *
			 * i2.x; i2.y;
			 * i3.x; i3.y, i3.z, i3.xy;
			 * i4.x; i4.y, i4.z, i4.w, i4.xyz;
			 */
			type elements[dim];

			struct raw_data {
				type data[dim];
				int size;
				inline constexpr raw_data(const type arr[dim]) noexcept : data{}, size{dim} { auto it=data, val=arr; while (it!=data+dim) { *(it++) = *(val++); } }
			};
			inline constexpr auto data() noexcept -> raw_data { return raw_data{elements}; }
			inline constexpr auto size() const noexcept -> int { return dim; }

			inline constexpr auto begin()  noexcept       -> type*       { return elements; }
			inline constexpr auto begin()  const noexcept -> const type* { return elements; }
			inline constexpr auto cbegin() const noexcept -> const type* { return elements; }
			inline constexpr auto end()    noexcept       -> type*       { return elements+size(); }
			inline constexpr auto end()    const noexcept -> const type* { return elements+size(); }
			inline constexpr auto cend()   const noexcept -> const type* { return elements+size(); }

			inline constexpr          base_vector()                    noexcept : elements{} {  }
			inline constexpr explicit base_vector(const type& e)       noexcept : elements{} { for (auto& elem: elements) { elem = e; } }
			inline constexpr          base_vector(const type arr[dim]) noexcept : elements{} { auto it=arr; for (auto& elem: elements) { elem = *(it++); } }
			inline constexpr          base_vector(const std::initializer_list<type>& args) noexcept : elements{} { auto it=args.begin(); for (auto& elem: elements) { elem = *(it++); } }
		};

	template<number type>
		struct base_vector<type,2> {
			union {
				type elements[2];
				struct { type x, y; };
			};
			using value_type     = type;
			using size_type      = int;
			using iterator       = type*;
			using const_iterator = const type*;
			template<typename T> using container_of = base_vector<T,2>;

			struct raw_data {
				type data[2];
				int size;
				inline constexpr raw_data(const type arr[2]) noexcept : data{ arr[0], arr[1] }, size{2} {  }
			};
			inline constexpr auto data() noexcept -> raw_data { return raw_data{elements}; }

			inline constexpr auto size() const noexcept -> int { return 2; }

			inline constexpr auto begin()  noexcept       -> type*       { return elements; }
			inline constexpr auto begin()  const noexcept -> const type* { return elements; }
			inline constexpr auto cbegin() const noexcept -> const type* { return elements; }
			inline constexpr auto end()    noexcept 	    -> type*       { return elements+size(); }
			inline constexpr auto end()    const noexcept -> const type* { return elements+size(); }
			inline constexpr auto cend()   const noexcept -> const type* { return elements+size(); }

			inline constexpr base_vector()                               noexcept : elements{}               {  }
			inline constexpr explicit base_vector(const type& e)         noexcept : elements{e, e}           {  }
			inline constexpr base_vector(const type arr[2])              noexcept : elements{arr[0], arr[1]} {  }
			// this constructor can be a template
			inline constexpr base_vector(const type& e1, const type& e2) noexcept : elements{e1, e2}         {  }
		};

	template<number type>
		struct base_vector<type,3> {
			union {
				type elements[3];
				struct { type x, y, z; };
				struct { base_vector<type,2> xy; };
			};
			using value_type     = type;
			using size_type      = int;
			using iterator       = type*;
			using const_iterator = const type*;
			template<typename T> using container_of = base_vector<T,2>;

			struct raw_data {
				type data[3];
				int size;
				inline constexpr raw_data(const type arr[3]) noexcept : data{ arr[0], arr[1], arr[2] }, size{3} {  }
			};
			inline constexpr auto data() noexcept -> raw_data { return raw_data{elements}; }

			inline constexpr auto size() const noexcept -> int { return 3; }

			inline constexpr auto begin()  noexcept       -> type*       { return elements; }
			inline constexpr auto begin()  const noexcept -> const type* { return elements; }
			inline constexpr auto cbegin() const noexcept -> const type* { return elements; }
			inline constexpr auto end()    noexcept 	    -> type*       { return elements+size(); }
			inline constexpr auto end()    const noexcept -> const type* { return elements+size(); }
			inline constexpr auto cend()   const noexcept -> const type* { return elements+size(); }

			inline constexpr base_vector()                                               noexcept : elements{}                       {  }
			inline constexpr explicit base_vector(const type& e)                         noexcept : elements{e, e, e}                {  }
			inline constexpr base_vector(const type& e1, const type& e2, const type& e3) noexcept : elements{e1, e2, e3}             {  }
			inline constexpr base_vector(const type arr[3])                              noexcept : elements{arr[0], arr[1], arr[2]} {  }
		};

	template<number type>
		struct base_vector<type,4> {
			union {
				type elements[4];
				struct { type x, y, z, w; };
				struct { base_vector<type,3> xyz; };
				struct { base_vector<type,2> xy, zw; };
			};
			using value_type     = type;
			using size_type      = int;
			using iterator       = type*;
			using const_iterator = const type*;
			template<typename T> using container_of = base_vector<T,2>;

			struct raw_data {
				type data[4];
				int size;
				inline constexpr raw_data(const type arr[4]) noexcept : data{ arr[0], arr[1], arr[2], arr[3] }, size{4} {  }
			};
			inline constexpr auto data() noexcept -> raw_data { return raw_data{elements}; }

			inline constexpr auto size() const noexcept -> int { return 4; }

			inline constexpr auto begin()  noexcept       -> type*       { return elements; }
			inline constexpr auto begin()  const noexcept -> const type* { return elements; }
			inline constexpr auto cbegin() const noexcept -> const type* { return elements; }
			inline constexpr auto end()    noexcept       -> type*       { return elements+size(); }
			inline constexpr auto end()    const noexcept -> const type* { return elements+size(); }
			inline constexpr auto cend()   const noexcept -> const type* { return elements+size(); }

			inline constexpr base_vector()                                                               noexcept : elements{}                               {  }
			inline constexpr explicit base_vector(const type& e)                                         noexcept : elements{e, e, e, e}                     {  }
			inline constexpr base_vector(const type& e1, const type& e2, const type& e3, const type& e4) noexcept : elements{e1, e2, e3, e4}                 {  }
			inline constexpr base_vector(const type arr[2])                                              noexcept : elements{arr[0], arr[1], arr[2], arr[3]} {  }
		};

} /* end of namespace pgl */
