#pragma once

#include <numbers>
#include <limits>
#include <cmath>
#include <initializer_list>
#include <iostream>
#include <utility>

#include <type_traits>

namespace pgl {

	template<typename T>
		concept number = std::is_arithmetic_v<T>;

	template<number type, int dim>
		struct vector {
			type elements[dim];

			struct raw_data {
				type data[dim];
				int size;
				raw_data(const int values[dim]) : data{}, size{dim} { auto it=values; for (auto& d: data) { d = *(it++); } }
			};
			inline constexpr auto data() noexcept -> raw_data { return raw_data{elements}; }

			inline constexpr auto size() const noexcept -> int { return dim; }

			inline constexpr auto begin()  noexcept       -> type*       { return elements; }
			inline constexpr auto begin()  const noexcept -> const type* { return elements; }
			inline constexpr auto cbegin() const noexcept -> const type* { return elements; }
			inline constexpr auto end()    noexcept       -> type*       { return elements+size(); }
			inline constexpr auto end()    const noexcept -> const type* { return elements+size(); }
			inline constexpr auto cend()   const noexcept -> const type* { return elements+size(); }


			inline constexpr vector() noexcept = default;
			inline constexpr explicit vector(const type& e) noexcept : elements{} {
				for (auto& elem: elements) { elem = e; }
			}
			inline constexpr vector(const type values[dim]) noexcept : elements{values} { }

			template<number... Ts>
				inline constexpr vector(Ts&&... ts) : elements{ std::forward<Ts>(ts)... } {
					static_assert(sizeof...(Ts) == dim, "Invalid number of arguments in constructor.");
				}

			inline constexpr auto operator*=(const vector<type,dim>& vec) noexcept -> vector<type,dim>& {
				auto it = vec.begin();
				for (auto& e: elements) { e *= *(it++); }
				return *this;
			}
			inline constexpr auto operator/=(const vector<type,dim>& vec) noexcept -> vector<type,dim>& {
				auto it = vec.begin();
				for (auto& e: elements) { e /= *(it++); }
				return *this;
			}
			inline constexpr auto operator+=(const vector<type,dim>& vec) noexcept -> vector<type,dim>& {
				auto it = vec.begin();
				for (auto& e: elements) { e += *(it++); }
				return *this;
			}
			inline constexpr auto operator-=(const vector<type,dim>& vec) noexcept -> vector<type,dim>& {
				auto it = vec.begin();
				for (auto& e: elements) { e -= *(it++); }
				return *this;
			}

			template<number scalar_type>
				inline constexpr auto operator*=(const scalar_type& scalar) noexcept -> vector<type,dim>& {
					for (auto& e: elements) { e *= scalar; }
					return *this;
				}
			template<number scalar_type>
				inline constexpr auto operator/=(const scalar_type& scalar) noexcept -> vector<type,dim>& {
					for (auto& e: elements) { e /= scalar; }
					return *this;
				}
			template<number scalar_type>
				inline constexpr auto operator+=(const scalar_type& scalar) noexcept -> vector<type,dim>& {
					for (auto& e: elements) { e += scalar; }
					return *this;
				}
			template<number scalar_type>
				inline constexpr auto operator-=(const scalar_type& scalar) noexcept -> vector<type,dim>& {
					for (auto& e: elements) { e -= scalar; }
					return *this;
				}
		};

	template<number type>
		struct vector<type,2> {
			union {
				type elements[2];
				struct { type x, y; };
			};

			struct raw_data {
				type data[2];
				int size;
				raw_data(const int values[2]) : data{values[0], values[1]}, size{2} {  }
			};
			inline constexpr auto data() noexcept -> raw_data { return raw_data{elements}; }

			inline constexpr auto size() const noexcept -> int { return 2; }

			inline constexpr auto begin()  noexcept       -> type*       { return elements; }
			inline constexpr auto begin()  const noexcept -> const type* { return elements; }
			inline constexpr auto cbegin() const noexcept -> const type* { return elements; }
			inline constexpr auto end()    noexcept 	    -> type*       { return elements+size(); }
			inline constexpr auto end()    const noexcept -> const type* { return elements+size(); }
			inline constexpr auto cend()   const noexcept -> const type* { return elements+size(); }

			inline constexpr vector() noexcept = default;
			inline constexpr explicit vector(const type& e)       noexcept : elements{e, e}           { }
			inline constexpr vector(const type& x, const type& y) noexcept : elements{x, y}           { }
			inline constexpr vector(const type val[2])            noexcept : elements{val[0], val[1]} { }

			static inline constexpr vector<type,2> right() noexcept { return { 1,  0}; }
			static inline constexpr vector<type,2> left()  noexcept { return {-1,  0}; }
			static inline constexpr vector<type,2> up()    noexcept { return { 0,  1}; }
			static inline constexpr vector<type,2> down()  noexcept { return { 0, -1}; }

			inline constexpr auto operator*=(const vector<type,2>& vec) noexcept -> vector<type,2>& {
				x *= vec.x, y *= vec.y;
				return *this;
			}
			inline constexpr auto operator/=(const vector<type,2>& vec) noexcept -> vector<type,2>& {
				x /= vec.x, y /= vec.y;
				return *this;
			}
			inline constexpr auto operator+=(const vector<type,2>& vec) noexcept -> vector<type,2>& {
				x += vec.x, y += vec.y;
				return *this;
			}
			inline constexpr auto operator-=(const vector<type,2>& vec) noexcept -> vector<type,2>& {
				x -= vec.x, y -= vec.y;
				return *this;
			}

			template<number scalar_type>
				inline constexpr auto operator*=(const scalar_type& scalar) noexcept -> vector<type,2>& {
					x *= scalar, y *= scalar;
					return *this;
				}
			template<number scalar_type>
				inline constexpr auto operator/=(const scalar_type& scalar) noexcept -> vector<type,2>& {
					x /= scalar, y /= scalar;
					return *this;
				}
			template<number scalar_type>
				inline constexpr auto operator+=(const scalar_type& scalar) noexcept -> vector<type,2>& {
					x += scalar, y += scalar;
					return *this;
				}
			template<number scalar_type>
				inline constexpr auto operator-=(const scalar_type& scalar) noexcept -> vector<type,2>& {
					x -= scalar, y -= scalar;
					return *this;
				}
		};

	template<number type>
		struct vector<type,3> {
			union {
				type elements[3];
				struct { type x, y, z; };
				struct { vector<type,2> xy; };
			};

			struct raw_data {
				type data[3];
				int size;
				raw_data(int values[3]) : data{values[0], values[1], values[2]}, size{3} {  }
			};
			inline constexpr auto data() noexcept -> raw_data { return raw_data{elements}; }

			inline constexpr auto size() const noexcept -> int { return 3; }

			inline constexpr auto begin()  noexcept       -> type*       { return elements; }
			inline constexpr auto begin()  const noexcept -> const type* { return elements; }
			inline constexpr auto cbegin() const noexcept -> const type* { return elements; }
			inline constexpr auto end()    noexcept       -> type*       { return elements+size(); }
			inline constexpr auto end()    const noexcept -> const type* { return elements+size(); }
			inline constexpr auto cend()   const noexcept -> const type* { return elements+size(); }

			inline constexpr vector() noexcept = default;
			inline constexpr explicit vector(const type& e)                         noexcept : elements{e, e, e}                { }
			inline constexpr vector(const type& t0, const type& t1, const type& t2) noexcept : elements{t0, t1, t2}             { }
			inline constexpr vector(const type val[3])                              noexcept : elements{val[0], val[1], val[2]} { }
			inline constexpr vector(const vector<type,2>& vect, const type& z)      noexcept : elements{vect.x, vect.y, z}      { }

			static inline constexpr vector<type,3> right() noexcept { return { 1,  0,  0}; }
			static inline constexpr vector<type,3> left()  noexcept { return {-1,  0,  0}; }
			static inline constexpr vector<type,3> up()    noexcept { return { 0,  1,  0}; }
			static inline constexpr vector<type,3> down()  noexcept { return { 0, -1,  0}; }
			static inline constexpr vector<type,3> front() noexcept { return { 0,  0,  1}; }
			static inline constexpr vector<type,3> back()  noexcept { return { 0,  0, -1}; }

			inline constexpr auto operator*=(const vector<type,3>& vec) noexcept -> vector<type,3>& {
				x *= vec.x, y *= vec.y, z *= vec.z;
				return *this;
			}
			inline constexpr auto operator/=(const vector<type,3>& vec) noexcept -> vector<type,3>& {
				x /= vec.x, y /= vec.y, z /= vec.z;
				return *this;
			}
			inline constexpr auto operator+=(const vector<type,3>& vec) noexcept -> vector<type,3>& {
				x += vec.x, y += vec.y, z += vec.z;
				return *this;
			}
			inline constexpr auto operator-=(const vector<type,3>& vec) noexcept -> vector<type,3>& {
				x -= vec.x, y -= vec.y, z -= vec.z;
				return *this;
			}

			template<number scalar_type>
				inline constexpr auto operator*=(const scalar_type& scalar) noexcept -> vector<type,3>& {
					x *= scalar, y *= scalar, z *= scalar;
					return *this;
				}
			template<number scalar_type>
				inline constexpr auto operator/=(const scalar_type& scalar) noexcept -> vector<type,3>& {
					x /= scalar, y /= scalar, z /= scalar;
					return *this;
				}
			template<number scalar_type>
				inline constexpr auto operator+=(const scalar_type& scalar) noexcept -> vector<type,3>& {
					x += scalar, y += scalar, z += scalar;
					return *this;
				}
			template<number scalar_type>
				inline constexpr auto operator-=(const scalar_type& scalar) noexcept -> vector<type,3>& {
					x -= scalar, y -= scalar, z -= scalar;
					return *this;
				}
		};

	template<number type>
		struct vector<type,4> {
			union {
				type elements[4];
				struct { type x, y, z, w; };
				struct { vector<type,3> xyz; };
				struct { vector<type,2> xy, zw; };
			};

			struct raw_data {
				type data[4];
				int size;
				raw_data(type val[4]) : data{val[0], val[1], val[2], val[3]}, size{4} {  }
			};
			inline constexpr auto data() noexcept -> raw_data { return raw_data{elements}; }

			inline constexpr auto size() const noexcept -> int { return 4; }

			inline constexpr auto begin()  noexcept       -> type*       { return elements; }
			inline constexpr auto begin()  const noexcept -> const type* { return elements; }
			inline constexpr auto cbegin() const noexcept -> const type* { return elements; }
			inline constexpr auto end()    noexcept       -> type*       { return elements+size(); }
			inline constexpr auto end()    const noexcept -> const type* { return elements+size(); }
			inline constexpr auto cend()   const noexcept -> const type* { return elements+size(); }

			inline constexpr vector() noexcept = default;
			inline constexpr explicit vector(const type& e)                                         noexcept : elements{e, e, e, e}                     { }
			inline constexpr vector(const type val[4])                                              noexcept : elements{val[0], val[1], val[2], val[3]} { }
			inline constexpr vector(const type& t0, const type& t1, const type& t2, const type& t3) noexcept : elements{t0, t1, t2, t3}                 { }
			inline constexpr vector(const vector<type,3>& vect, type w)                             noexcept : elements{vect.x, vect.y, vect.z, w}      { }
			inline constexpr vector(const vector<type,2>& lhs, const vector<type,2>& rhs)           noexcept : elements{lhs.x, lhs.y, rhs.x, rhs.y}     { }

			inline constexpr auto operator*=(const vector<type,4>& vec) noexcept -> vector<type,4>& {
				x *= vec.x, y *= vec.y, z *= vec.z, w *= vec.w;
				return *this;
			}
			inline constexpr auto operator/=(const vector<type,4>& vec) noexcept -> vector<type,4>& {
				x /= vec.x, y /= vec.y, z /= vec.z, w /= vec.w;
				return *this;
			}
			inline constexpr auto operator+=(const vector<type,4>& vec) noexcept -> vector<type,4>& {
				x += vec.x, y += vec.y, z += vec.z, w += vec.w;
				return *this;
			}
			inline constexpr auto operator-=(const vector<type,4>& vec) noexcept -> vector<type,4>& {
				x -= vec.x, y -= vec.y, z -= vec.z, w -= vec.w;
				return *this;
			}

			template<number scalar_type>
				inline constexpr auto operator*=(const scalar_type& scalar) noexcept -> vector<type,4>& {
					x *= scalar, y *= scalar, z *= scalar, w *= scalar;
					return *this;
				}
			template<number scalar_type>
				inline constexpr auto operator/=(const scalar_type& scalar) noexcept -> vector<type,4>& {
					x /= scalar, y /= scalar, z /= scalar, w /= scalar;
					return *this;
				}
			template<number scalar_type>
				inline constexpr auto operator+=(const scalar_type& scalar) noexcept -> vector<type,4>& {
					x += scalar, y += scalar, z += scalar, w += scalar;
					return *this;
				}
			template<number scalar_type>
				inline constexpr auto operator-=(const scalar_type& scalar) noexcept -> vector<type,4>& {
					x -= scalar, y -= scalar, z -= scalar, w -= scalar;
					return *this;
				}
		};

	template<number type, int dim>
		inline constexpr auto operator*(
			const vector<type,dim>& lhs,
			const vector<type,dim>& rhs) noexcept
		-> vector<type,dim>
		{
			vector<type,dim> res{lhs};
			auto rhs_it = rhs.begin();
			for (auto& elem: res) {
				elem *= *(rhs_it++);
			}
			return res;
		}

	template<number type, number scalar_type, int dim>
		inline constexpr auto operator*(
			const vector<type,dim>& lhs,
			const scalar_type& rhs) noexcept
		-> vector<type,dim>
		{
			vector<type,dim> res{lhs};
			for (auto& elem: res) {
				elem *= rhs;
			}
			return res;
		}

	template<number type, number scalar_type, int dim>
		inline constexpr auto operator*(
			const scalar_type& lhs,
			const vector<type,dim>& rhs) noexcept
		-> vector<type,dim>
		{
			return rhs * lhs;
		}

	template<number type, int dim>
		inline constexpr auto operator/(
			const vector<type,dim>& lhs,
			const vector<type,dim>& rhs) noexcept
		-> vector<type,dim>
		{
			vector<type,dim> res{lhs};
			auto rhs_it = rhs.begin();
			for (auto& elem: res) {
				elem /= *(rhs_it++);
			}
			return res;
		}

	template<number type, number scalar_type, int dim>
		inline constexpr auto operator/(
			const vector<type,dim>& lhs,
			const scalar_type& rhs) noexcept
		-> vector<type,dim>
		{
			vector<type,dim> res{lhs};
			for (auto& elem: res) {
				elem /= rhs;
			}
			return res;
		}

	template<number type, number scalar_type, int dim>
		inline constexpr auto operator/(
			const scalar_type& rhs,
			const vector<type,dim>& lhs) noexcept
		-> vector<type,dim>
		{
			vector<type,dim> res{lhs};
			for (auto& elem: res) {
				elem = rhs/elem;
			}
			return res;
		}

	template<number type, int dim>
		inline constexpr auto operator-(
			const vector<type,dim>& lhs,
			const vector<type,dim>& rhs) noexcept
		-> vector<type,dim>
		{
			vector<type,dim> res{lhs};
			auto rhs_it = rhs.begin();
			for (auto& elem: res) {
				elem -= *(rhs_it++);
			}
			return res;
		}

	template<number type, number scalar_type, int dim>
		inline constexpr auto operator-(
			const vector<type,dim>& lhs,
			const scalar_type& rhs) noexcept
		-> vector<type,dim>
		{
			vector<type,dim> res{lhs};
			for (auto& elem: res) {
				elem = elem - rhs;
			}
			return res;
		}

	template<number type, number scalar_type, int dim>
		inline constexpr auto operator-(
			const scalar_type& lhs,
			const vector<type,dim>& rhs) noexcept
		-> vector<type,dim>
		{
			vector<type,dim> res{rhs};
			for (auto& elem: res) {
				elem = lhs - elem;
			}
			return res;
		}

	template<number type, int dim>
		inline constexpr auto operator+(
			const vector<type,dim>& lhs,
			const vector<type,dim>& rhs) noexcept
		-> vector<type,dim>
		{
			vector<type,dim> res{lhs};
			auto rhs_it = rhs.begin();
			for (auto& elem: res) {
				elem += *(rhs_it++);
			}
			return res;
		}

	template<number type, number scalar_type, int dim>
		inline constexpr auto operator+(
			const vector<type,dim>& lhs,
			const scalar_type& rhs) noexcept
		-> vector<type,dim>
		{
			vector<type,dim> res{lhs};
			for (auto& elem: res) {
				elem += rhs;
			}
			return res;
		}

	template<number type, number scalar_type, int dim>
		inline constexpr auto operator+(
			const scalar_type& lhs,
			const vector<type,dim>& rhs) noexcept
		-> vector<type,dim>
		{
			return rhs + lhs;
		}

	template<number type, int dim>
		inline constexpr auto dot(
			const vector<type,dim>& lhs,
			const vector<type,dim>& rhs) noexcept
		-> type {
			type res{0};
			for (auto lhs_it=lhs.begin(), rhs_it=rhs.begin();
					 lhs_it != lhs.end();
					 ++lhs_it,++rhs_it)
			{
				res += *(lhs_it) * *(rhs_it);
			}
			return res;
		}

	template<number type, int dim>
		inline constexpr auto dot(const vector<type,dim>& arg) noexcept
		-> type
		{
			return dot(arg,arg);
		}

	template<number type, int dim>
		inline constexpr auto sum(const vector<type,dim>& arg) noexcept
		-> type {
			type res{0};
			for (auto elem: arg) {
				res += elem;
			}
			return res;
		}

	template<number type, int dim>
		inline constexpr auto normalize(const vector<type,dim>& arg) noexcept
		-> vector<type,dim>
		{
			type s = sum(arg);
			return arg/s;
		}

	template<number type, int dim>
		inline constexpr auto max(const vector<type,dim>& vec) noexcept
		-> type
		{
			type max = std::numeric_limits<type>::min();
			for (auto elem: vec) {
				if (elem > max)
					max = elem;
			}
			return max;
		}

	template<number type, int dim>
		inline constexpr auto min(const vector<type,dim>& vec) noexcept
		-> type
		{
			type min = std::numeric_limits<type>::max();
			for (auto elem: vec) {
				if (elem < min)
					min = elem;
			}
			return min;
		}

	template<number type, int dim>
		inline constexpr auto abs(const vector<type,dim>& vec) noexcept
		-> vector<type,dim>
		{
			vector<type,dim> res;
			auto vec_it = vec.begin();
			for (auto& elem: res)
				elem = std::abs(*(vec_it++));
			return res;
		}

	template<number type, int dim>
		inline constexpr auto operator<(
			const vector<type,dim>& lhs,
			const vector<type,dim>& rhs) noexcept
		-> vector<bool,dim>
		{
			vector<bool,dim> res;
			auto lhs_it=lhs.begin(), rhs_it=rhs.begin();
			for (auto& elem: res) {
				elem = (*(lhs_it++) < *(rhs_it++));
			}
			return res;
		}

	template<number type, int dim>
		inline constexpr auto operator>(
			const vector<type,dim>& lhs,
			const vector<type,dim>& rhs) noexcept
		-> vector<bool,dim>
		{
			vector<bool,dim> res;
			auto lhs_it=lhs.begin(), rhs_it=rhs.begin();
			for (auto& elem: res) {
				elem = (*(lhs_it++) > *(rhs_it++));
			}
			return res;
		}

	template<number type, int dim>
		inline constexpr auto operator<=(
			const vector<type,dim>& lhs,
			const vector<type,dim>& rhs) noexcept
		-> vector<bool,dim>
		{
			vector<bool,dim> res;
			auto lhs_it=lhs.begin(), rhs_it=rhs.begin();
			for (auto& elem: res) {
				elem = (*(lhs_it++) <= *(rhs_it++));
			}
			return res;
		}

	template<number type, int dim>
		inline constexpr auto operator>=(
			const vector<type,dim>& lhs,
			const vector<type,dim>& rhs) noexcept
		-> vector<bool,dim>
		{
			vector<bool,dim> res;
			auto lhs_it=lhs.begin(), rhs_it=rhs.begin();
			for (auto& elem: res) {
				elem = (*(lhs_it++) >= *(rhs_it++));
			}
			return res;
		}

	template<number type, int dim>
		inline constexpr auto operator==(
			const vector<type,dim>& lhs,
			const vector<type,dim>& rhs) noexcept
		-> vector<bool,dim>
		{
			vector<bool,dim> res;
			auto lhs_it=lhs.begin(), rhs_it=rhs.begin();
			for (auto& elem: res) {
				elem = (*(lhs_it++) == *(rhs_it++));
			}
			return res;
		}

	template<number type, int dim>
		inline constexpr auto operator!=(
			const vector<type,dim>& lhs,
			const vector<type,dim>& rhs) noexcept
		-> vector<bool,dim>
		{
			vector<bool,dim> res;
			auto lhs_it=lhs.begin(), rhs_it=rhs.begin();
			for (auto& elem: res) {
				elem = (*(lhs_it++) != *(rhs_it++));
			}
			return res;
		}

	template<number type, int dim>
		inline constexpr auto min_element(vector<type,dim>& vect) noexcept
		-> type&
		{
			type* min_elem = vect.begin();
			type  min      = *min_elem;
			for (auto it=vect.begin(); it!=vect.end(); ++it) {
				if (*it < min) {
					min = *it;
					min_elem = it;
				}
			}
			return *min_elem;
		}

	template<number type, int dim>
		inline constexpr auto max_element(vector<type,dim>& vect) noexcept
		-> type&
		{
			type* max_elem = vect.begin();
			type  max = *max_elem;

			for (auto it=vect.begin(); it!=vect.end(); ++it) {
				if (*it > max) {
					max = *it;
					max_elem = it;
				}
			}
			return *max_elem;
		}

	template<number type, int dim>
		inline constexpr auto min(const vector<type,dim>& vect, type min_val)
		-> vector<type,dim>
		{
			vector<type,dim> res{vect};
			for (auto& e: res) { if (e < min_val) { e = min_val; } }
			return res;
		}

	template<number type, int dim>
		inline constexpr auto max(const vector<type,dim>& vect, type max_val)
		-> vector<type,dim>
		{
			vector<type,dim> res{vect};
			for (auto& e: res) { if (e > max_val) { e = max_val; } }
			return res;
		}

	template<number type, int dim>
		inline constexpr auto clamp(const vector<type,dim>& vect, type lb, type ub) noexcept
		-> vector<type,dim>
		{
			return min(max(vect, lb), ub);
		}

	template<number type, int dim>
		inline constexpr auto saturate(const vector<type,dim>& vect) {
			return clamp(vect, type{0}, type{1});
		}

	template<number type, int dim>
		inline constexpr auto any(const vector<type,dim>& vect) noexcept
		-> bool
		{
			bool res = false;
			for (auto e: vect) { res |= e; }
			return res;
		}

	template<number type, int dim>
		inline constexpr auto pand(const vector<type,dim>& vect) noexcept
		-> bool
		{
			bool res = true;
			for (const auto& e: vect) { res &= e; }
			return res;
		}

	template<number type, int dim, typename Function>
		inline constexpr auto select(
			const vector<type,dim>& vect,
			Function& condition,
			type on_true, type on_false) noexcept
		-> vector<type,dim>
		{
			vector<type,dim> res{vect};
			for (auto& e: res) { condition(e) ? on_true : on_false; }
			return res;
		}

	template<number type, int dim>
		inline constexpr auto apply(
			type (*func)(type),
			const vector<type,dim>& vect)
		-> vector<type,dim>
		{
			vector<type,dim> res;
			auto it=vect.begin();
			for (auto& e: res) {
				e = func(*(it++));
			}
			return res;
		}

	template<number type, int dim>
		inline constexpr auto apply(
			type (*func)(type,type),
			const vector<type,dim>& x,
			const vector<type,dim>& y)
		-> vector<type,dim>
		{
			vector<type,dim> res;
			auto x_it=x.begin();
			auto y_it=y.begin();
			for (auto& e: res) {
				e = func(*(x_it++), *(y_it++));
			}
			return res;
		}

	template<number type, int dim>
		inline constexpr auto exp(const vector<type,dim>& vect)
		-> vector<type,dim>
		{
			return apply(std::exp, vect);
		}

	template<number type, int dim>
		inline constexpr auto log2(const vector<type,dim>& vect)
		-> vector<type,dim>
		{
			return apply(std::log2, vect);
		}

	template<number type, int dim>
		inline constexpr auto log10(const vector<type,dim>& vect)
		-> vector<type,dim>
		{
			return apply(std::log10, vect);
		}

	template<number type, int dim>
		inline constexpr auto log(const vector<type,dim>& vect)
		-> vector<type,dim>
		{
			return apply(std::log, vect);
		}

	template<number type, int dim>
		inline constexpr auto tan(const vector<type,dim>& vect)
		-> vector<type,dim>
		{
			return apply(std::tan, vect);
		}

	template<number type, int dim>
		inline constexpr auto atan(const vector<type,dim>& vect)
		-> vector<type,dim>
		{
			return apply(std::atan, vect);
		}

	template<number type, int dim>
		inline constexpr auto atan(
			const vector<type,dim>& x,
			const vector<type,dim>& y)
		-> vector<type,dim>
		{
			return apply(std::atan2, x, y);
		}

	template<number type, int dim>
		inline constexpr auto cos(const vector<type,dim>& vect)
		-> vector<type,dim>
		{
			return apply(std::cos, vect);
		}

	template<number type, int dim>
		inline constexpr auto acos(const vector<type,dim>& vect)
		-> vector<type,dim>
		{
			return apply(std::acos, vect);
		}

	template<number type, int dim>
		inline constexpr auto sin(const vector<type,dim>& vect)
		-> vector<type,dim>
		{
			return apply(std::sin, vect);
		}

	template<number type, int dim>
		inline constexpr auto asin(const vector<type,dim>& vect)
		-> vector<type,dim>
		{
			return apply(std::asin, vect);
		}


	template<number type, int dim>
		inline constexpr auto cosh(const vector<type,dim>& vect)
		-> vector<type,dim>
		{
			return apply(std::cosh, vect);
		}

	template<number type, int dim>
		inline constexpr auto acosh(const vector<type,dim>& vect)
		-> vector<type,dim>
		{
			return apply(std::acosh, vect);
		}

	template<number type, int dim>
		inline constexpr auto sinh(const vector<type,dim>& vect)
		-> vector<type,dim>
		{
			return apply(std::sinh, vect);
		}


	template<number type, int dim>
		inline constexpr auto asinh(const vector<type,dim>& vect)
		-> vector<type,dim>
		{
			return apply(std::asinh, vect);
		}

	template<number type, int dim>
		constexpr inline auto lerp(
			const vector<type,dim>& x,
			const vector<type,dim>& y,
			type a) noexcept
		-> vector<type,dim>
		{
			return x * (static_cast<type>(1) - a) + y * a;
		}

	template<number type> struct make_pi { static constexpr type pi = std::numbers::pi_v<type>; };
	constexpr float  pi {make_pi<float>::pi};
	constexpr double dpi{make_pi<double>::pi};

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

} /* end of namespace pgl */
