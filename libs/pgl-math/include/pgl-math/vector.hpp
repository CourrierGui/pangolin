#pragma once

#include <limits>
#include <cmath>

namespace pgl {

	template<typename type, int size>
		struct Vector {
			type elements[size];

			Vector() = default;
			explicit Vector(const type& e) {
				for (auto& elem: elements)
					elem = e;
			}
		};

	template<typename type>
		struct Vector<type,2> {
			union {
				type elements[2];
				struct { type x, y; };
			};

			Vector() = default;
			explicit Vector(const type& e) {
				for (auto& elem: elements)
					elem = e;
			};
		};

	template<typename type>
		struct Vector<type,3> {
			union {
				type elements[3];
				struct { type x, y, z; };
				struct { Vector<type,2> xy; };
			};

			Vector() = default;
			explicit Vector(const type& e) {
				for (auto& elem: elements)
					elem = e;
			}
			Vector(const type& t0, const type& t1, const type& t2) {
				elements[0] = t0;
				elements[1] = t1;
				elements[2] = t2;
			}
		};

	template<typename type>
		struct Vector<type,4> {
			union {
				type elements[4];
				struct { type x, y, z, w; };
				struct { Vector<type,3> xyz; };
				struct { Vector<type,2> xy, zw; };
			};

			Vector() = default;
			explicit Vector(const type& e) {
				for (auto& elem: elements)
					elem = e;
			}
			Vector(const type& t0, const type& t1, const type& t2, const type& t3) {
				elements[0] = t0;
				elements[1] = t1;
				elements[2] = t2;
				elements[3] = t3;
			}
		};

	template<typename type, int size>
	inline auto operator*(const Vector<type,size>& lhs, const Vector<type,size>& rhs) noexcept
		-> Vector<type,size>
		{
			Vector<type,size> res(lhs);
			auto rhs_it = rhs.elements;
			for (auto& elem: res.elements)
				elem *= *(rhs_it++);
			return res;
		}

	template<typename type, int size>
	inline auto operator*(const Vector<type,size>& lhs, const type& rhs) noexcept
		-> Vector<type,size>
		{
			Vector<type,size> res(lhs);
			for (auto& elem: res.elements)
				elem *= rhs;
			return res;
		}

	template<typename type, int size>
	inline auto operator*(const type& lhs, const Vector<type,size>& rhs) noexcept
		-> Vector<type,size>
		{
			return rhs * lhs;
		}

	template<int size>
	inline auto operator/(const Vector<float,size>& lhs, const Vector<float,size>& rhs) noexcept
		-> Vector<float,size>
		{
			Vector<float,size> res(lhs);
			auto rhs_it = rhs.elements;
			for (auto& elem: res.elements)
				elem /= *(rhs_it++);
			return res;
		}

	template<int size>
	inline auto operator/(const Vector<float,size>& lhs, const float& rhs) noexcept
		-> Vector<float,size>
		{
			Vector<float,size> res(lhs);
			for (auto& elem: res.elements)
				elem /= rhs;
			return res;
		}

	template<typename type, int size>
	inline auto operator-(const Vector<type,size>& lhs, const Vector<type,size>& rhs) noexcept
		-> Vector<type,size>
		{
			Vector<type,size> res(lhs);
			auto rhs_it = rhs.elements;
			for (auto& elem: res.elements)
				elem -= *(rhs_it++);
			return res;
		}

	template<typename type, int size>
	inline auto operator-(const Vector<type,size>& lhs, const type& rhs) noexcept
		-> Vector<type,size>
		{
			Vector<type,size> res(lhs);
			for (auto& elem: res.elements)
				elem = elem - rhs;
			return res;
		}

	template<typename type, int size>
	inline auto operator-(const type& lhs, const Vector<type,size>& rhs) noexcept
		-> Vector<type,size>
		{
			Vector<type,size> res(rhs);
			for (auto& elem: res.elements)
				elem = lhs - elem;
			return res;
		}

	template<typename type, int size>
	inline auto operator+(const Vector<type,size>& lhs, const Vector<type,size>& rhs) noexcept
		-> Vector<type,size>
		{
			Vector<type,size> res(lhs);
			auto rhs_it = rhs.elements;
			for (auto& elem: res.elements)
				elem += *(rhs_it++);
			return res;
		}

	template<typename type, int size>
	inline auto operator+(const Vector<type,size>& lhs, const type& rhs) noexcept
		-> Vector<type,size>
		{
			Vector<type,size> res(lhs);
			for (auto& elem: res.elements)
				elem += rhs;
			return res;
		}

	template<typename type, int size>
	inline auto operator+(const type& lhs, const Vector<type,size>& rhs) noexcept
		-> Vector<type,size>
		{
			return rhs + lhs;
		}

	template<typename type, int size>
		inline auto dot(const Vector<type,size>& lhs, const Vector<type,size>& rhs) noexcept -> type {
			type res(0);
			auto lhs_it = lhs.elements;
			auto rhs_it = rhs.elements;
			for (;lhs_it != lhs.elements + size; ++lhs_it,++rhs_it)
				res += *(lhs_it) * *(rhs_it);
			return res;
		}

	template<typename type, int size>
		inline auto dot(const Vector<type,size>& arg) noexcept -> type {
			return dot(arg,arg);
		}

	template<typename type, int size>
		inline auto sum(const Vector<type,size>& arg) noexcept -> type {
			type res(0);
			for (auto elem: arg.elements)
				res += elem;
			return res;
		}

	template<int size>
		inline auto normalize(const Vector<float,size>& arg) noexcept -> Vector<float,size> {
			float s = sum(arg);
			return arg/s;
		}

	template<typename type, int size>
		inline auto max(const Vector<type,size>& vec) noexcept -> type {
			type max = std::numeric_limits<type>::min();
			for (auto elem: vec.elements) {
				if (elem > max)
					max = elem;
			}
			return max;
		}

	template<typename type, int size>
		inline auto min(const Vector<type,size>& vec) noexcept -> type {
			type min = std::numeric_limits<type>::max();
			for (auto elem: vec.elements) {
				if (elem < min)
					min = elem;
			}
			return min;
		}

	template<typename type, int size>
		inline auto abs(const Vector<type,size>& vec) noexcept -> Vector<type,size> {
			Vector<type,size> res;
			auto vec_it = vec.elements;
			for (auto& elem: res.elements)
				elem = std::abs(*(vec_it++));
			return res;
		}

	/*
	 *
	 * ========================
	 * ======= TODO !!! =======
	 * ========================
	 *
	 * constructor from C array of type
	 * vec4 from vec3 + w, etc...
	 * std::initializer_list<T>
	 * constexpr constructor
	 * compound assignement operator ?
	 * comparison operator -> Vector<bool,size>
	 * clamp, staturate, lerp(mix), minComponent, maxComponent
	 * all() (AND), any() (OR)
	 * select() -> component wise ?:
	 *
	 * component wise constructor for matrices
	 * build matrices out of vectors (component wise and column wise) -> free functions not constructors
	 * zero and identity matrix
	 * cross, transpose, inverse
	 *
	 * SIMD
	 * benchmark
	 * tests
	 *
	 * more utility funcitons !!!
	 *
	 */

	using int2 = Vector<int,2>;
	using int3 = Vector<int,3>;
	using int4 = Vector<int,4>;

	using float2 = Vector<float,2>;
	using float3 = Vector<float,3>;
	using float4 = Vector<float,4>;

} /* end of namespace pgl */
