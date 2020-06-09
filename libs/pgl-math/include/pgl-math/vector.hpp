#pragma once

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

	using int2 = Vector<int,2>;
	using int3 = Vector<int,3>;
	using int4 = Vector<int,4>;

	using float2 = Vector<float,2>;
	using float3 = Vector<float,3>;
	using float4 = Vector<float,4>;

} /* end of namespace pgl */
