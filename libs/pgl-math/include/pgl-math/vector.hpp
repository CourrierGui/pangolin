#pragma once

#include <limits>
#include <cmath>
#include <initializer_list>
#include <iostream>

namespace pgl {

	template<typename type, int size>
		struct vector {
			type elements[size];

			constexpr vector() noexcept = default;
			constexpr explicit vector(const type& e) noexcept {
				for (auto& elem: elements) { elem = e; }
			}

			constexpr vector(const type values[size]) noexcept {
				const type* it = values;
				for (auto& elem: elements) { elem = *(it++); }
			}
		};

	template<typename type>
		struct vector<type,2> {
			union {
				type elements[2];
				struct { type x, y; };
			};

			constexpr vector() noexcept = default;
			constexpr explicit vector(const type& e)       noexcept : elements{e, e}           { }
			constexpr vector(const type& x, const type& y) noexcept : elements{x, y}           { }
			constexpr vector(const type val[2])            noexcept : elements{val[0], val[1]} { }

			static vector<type,2> right() { return { 1,  0}; }
			static vector<type,2> left()  { return {-1,  0}; }
			static vector<type,2> up()    { return { 0,  1}; }
			static vector<type,2> down()  { return { 0, -1}; }
		};

	template<typename type>
		struct vector<type,3> {
			union {
				type elements[3];
				struct { type x, y, z; };
				struct { vector<type,2> xy; };
			};

			constexpr vector() noexcept = default;
			constexpr explicit vector(const type& e)                         noexcept : elements{e, e, e}                { }
			constexpr vector(const type& t0, const type& t1, const type& t2) noexcept : elements{t0, t1, t2}             { }
			constexpr vector(const type val[3])                              noexcept : elements{val[0], val[1], val[2]} { }
			constexpr vector(const vector<type,2>& vect, const type& z)      noexcept : elements{vect.x, vect.y, z}      { }

			static vector<type,3> right() noexcept { return { 1,  0,  0}; }
			static vector<type,3> left()  noexcept { return {-1,  0,  0}; }
			static vector<type,3> up()    noexcept { return { 0,  1,  0}; }
			static vector<type,3> down()  noexcept { return { 0, -1,  0}; }
			static vector<type,3> front() noexcept { return { 0,  0,  1}; }
			static vector<type,3> back()  noexcept { return { 0,  0, -1}; }
		};

	template<typename type>
		struct vector<type,4> {
			union {
				type elements[4];
				struct { type x, y, z, w; };
				struct { vector<type,3> xyz; };
				struct { vector<type,2> xy, zw; };
			};

			constexpr vector() noexcept = default;
			constexpr explicit vector(const type& e)                                         noexcept : elements{e, e, e, e}                     { }
			constexpr vector(const type val[4])                                              noexcept : elements{val[0], val[1], val[2], val[3]} { }
			constexpr vector(const type& t0, const type& t1, const type& t2, const type& t3) noexcept : elements{t0, t1, t2, t3}                 { }
			constexpr vector(const vector<type,3>& vect, type w)                             noexcept : elements{vect.x, vect.y, vect.z, w}      { }
			constexpr vector(const vector<type,2>& lhs, const vector<type,2>& rhs)           noexcept : elements{lhs.x, lhs.y, rhs.x, rhs.y}     { }

			static vector<type,4> right() noexcept { return { 1,  0,  0, 0}; }
			static vector<type,4> left()  noexcept { return {-1,  0,  0, 0}; }
			static vector<type,4> up()    noexcept { return { 0,  1,  0, 0}; }
			static vector<type,4> down()  noexcept { return { 0, -1,  0, 0}; }
			static vector<type,4> front() noexcept { return { 0,  0,  1, 0}; }
			static vector<type,4> back()  noexcept { return { 0,  0, -1, 0}; }
		};

	template<typename type, int size>
	inline auto operator*(const vector<type,size>& lhs, const vector<type,size>& rhs) noexcept
		-> vector<type,size>
		{
			vector<type,size> res(lhs);
			auto rhs_it = rhs.elements;
			for (auto& elem: res.elements)
				elem *= *(rhs_it++);
			return res;
		}

	template<typename type, int size>
	inline auto operator*(const vector<type,size>& lhs, const type& rhs) noexcept
		-> vector<type,size>
		{
			vector<type,size> res(lhs);
			for (auto& elem: res.elements)
				elem *= rhs;
			return res;
		}

	template<typename type, int size>
	inline auto operator*(const type& lhs, const vector<type,size>& rhs) noexcept
		-> vector<type,size>
		{
			return rhs * lhs;
		}

	template<int size>
	inline auto operator/(const vector<float,size>& lhs, const vector<float,size>& rhs) noexcept
		-> vector<float,size>
		{
			vector<float,size> res(lhs);
			auto rhs_it = rhs.elements;
			for (auto& elem: res.elements)
				elem /= *(rhs_it++);
			return res;
		}

	template<int size>
	inline auto operator/(const vector<float,size>& lhs, const float& rhs) noexcept
		-> vector<float,size>
		{
			vector<float,size> res(lhs);
			for (auto& elem: res.elements)
				elem /= rhs;
			return res;
		}

	template<typename type, int size>
	inline auto operator-(const vector<type,size>& lhs, const vector<type,size>& rhs) noexcept
		-> vector<type,size>
		{
			vector<type,size> res(lhs);
			auto rhs_it = rhs.elements;
			for (auto& elem: res.elements)
				elem -= *(rhs_it++);
			return res;
		}

	template<typename type, int size>
	inline auto operator-(const vector<type,size>& lhs, const type& rhs) noexcept
		-> vector<type,size>
		{
			vector<type,size> res(lhs);
			for (auto& elem: res.elements)
				elem = elem - rhs;
			return res;
		}

	template<typename type, int size>
	inline auto operator-(const type& lhs, const vector<type,size>& rhs) noexcept
		-> vector<type,size>
		{
			vector<type,size> res(rhs);
			for (auto& elem: res.elements)
				elem = lhs - elem;
			return res;
		}

	template<typename type, int size>
	inline auto operator+(const vector<type,size>& lhs, const vector<type,size>& rhs) noexcept
		-> vector<type,size>
		{
			vector<type,size> res(lhs);
			auto rhs_it = rhs.elements;
			for (auto& elem: res.elements)
				elem += *(rhs_it++);
			return res;
		}

	template<typename type, int size>
	inline auto operator+(const vector<type,size>& lhs, const type& rhs) noexcept
		-> vector<type,size>
		{
			vector<type,size> res(lhs);
			for (auto& elem: res.elements)
				elem += rhs;
			return res;
		}

	template<typename type, int size>
	inline auto operator+(const type& lhs, const vector<type,size>& rhs) noexcept
		-> vector<type,size>
		{
			return rhs + lhs;
		}

	template<typename type, int size>
		inline auto dot(const vector<type,size>& lhs, const vector<type,size>& rhs) noexcept -> type {
			type res(0);
			auto lhs_it = lhs.elements;
			auto rhs_it = rhs.elements;
			for (;lhs_it != lhs.elements + size; ++lhs_it,++rhs_it)
				res += *(lhs_it) * *(rhs_it);
			return res;
		}

	template<typename type, int size>
		inline auto dot(const vector<type,size>& arg) noexcept -> type {
			return dot(arg,arg);
		}

	template<typename type, int size>
		inline auto sum(const vector<type,size>& arg) noexcept -> type {
			type res(0);
			for (auto elem: arg.elements)
				res += elem;
			return res;
		}

	template<int size>
		inline auto normalize(const vector<float,size>& arg) noexcept -> vector<float,size> {
			float s = sum(arg);
			return arg/s;
		}

	template<typename type, int size>
		inline auto max(const vector<type,size>& vec) noexcept -> type {
			type max = std::numeric_limits<type>::min();
			for (auto elem: vec.elements) {
				if (elem > max)
					max = elem;
			}
			return max;
		}

	template<typename type, int size>
		inline auto min(const vector<type,size>& vec) noexcept -> type {
			type min = std::numeric_limits<type>::max();
			for (auto elem: vec.elements) {
				if (elem < min)
					min = elem;
			}
			return min;
		}

	template<typename type, int size>
		inline auto abs(const vector<type,size>& vec) noexcept -> vector<type,size> {
			vector<type,size> res;
			auto vec_it = vec.elements;
			for (auto& elem: res.elements)
				elem = std::abs(*(vec_it++));
			return res;
		}

	template<typename type, int size>
		inline auto operator<(const vector<type,size>& lhs, const vector<type,size>& rhs)
		-> vector<bool,size>
		{
			vector<bool,size> res;
			auto lhs_it=lhs.elements, rhs_it=rhs.elements;
			for (auto& elem: res.elements) {
				elem = (*(lhs_it++) < *(rhs_it++));
			}
			return res;
		}

	template<typename type, int size>
		inline auto operator>(const vector<type,size>& lhs, const vector<type,size>& rhs)
		-> vector<bool,size>
		{
			vector<bool,size> res;
			auto lhs_it=lhs.elements, rhs_it=rhs.elements;
			for (auto& elem: res.elements) {
				elem = (*(lhs_it++) > *(rhs_it++));
			}
			return res;
		}

	template<typename type, int size>
		inline auto operator<=(const vector<type,size>& lhs, const vector<type,size>& rhs)
		-> vector<bool,size>
		{
			vector<bool,size> res;
			auto lhs_it=lhs.elements, rhs_it=rhs.elements;
			for (auto& elem: res.elements) {
				elem = (*(lhs_it++) <= *(rhs_it++));
			}
			return res;
		}

	template<typename type, int size>
		inline auto operator>=(const vector<type,size>& lhs, const vector<type,size>& rhs)
		-> vector<bool,size>
		{
			vector<bool,size> res;
			auto lhs_it=lhs.elements, rhs_it=rhs.elements;
			for (auto& elem: res.elements) {
				elem = (*(lhs_it++) >= *(rhs_it++));
			}
			return res;
		}

	template<typename type, int size>
		inline auto operator==(const vector<type,size>& lhs, const vector<type,size>& rhs)
		-> vector<bool,size>
		{
			vector<bool,size> res;
			auto lhs_it=lhs.elements, rhs_it=rhs.elements;
			for (auto& elem: res.elements) {
				elem = (*(lhs_it++) == *(rhs_it++));
			}
			return res;
		}

	template<typename type, int size>
		type& min_element(vector<type,size>& vect) {
			type min = vect.elements[0];
			type* min_elem = vect.elements;

			for (type* it=vect.elements; it!=vect.elements+size; ++it) {
				if (*it < min) {
					min = *it;
					min_elem = it;
				}
			}
			return *min_elem;
		}

	template<typename type, int size>
		type& max_element(vector<type,size>& vect) {
			type max = vect.elements[0];
			type* max_elem = vect.elements;

			for (type* it=vect.elements; it!=vect.elements+size; ++it) {
				if (*it > max) {
					max = *it;
					max_elem = it;
				}
			}
			return *max_elem;
		}

	/*
	 *
	 * ========================
	 * ======= TODO !!! =======
	 * ========================
	 *
	 * std::initializer_list<T>: useless ?
	 * compound assignement operator: *=, /=, +=, -=, ...
	 * clamp, staturate, lerp(mix)
	 * all() (AND), any() (OR)
	 * select() -> component wise ?:
	 * frame ?
	 *
	 * SIMD
	 * benchmark
	 * tests
	 *
	 * more utility functions
	 */

	using int2 = vector<int,2>;
	using int3 = vector<int,3>;
	using int4 = vector<int,4>;

	using float2 = vector<float,2>;
	using float3 = vector<float,3>;
	using float4 = vector<float,4>;

} /* end of namespace pgl */
