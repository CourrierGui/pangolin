#pragma once

#include <numbers>
#include <limits>
#include <cmath>
#include <initializer_list>
#include <iostream>
#include <utility>

#include <type_traits>

template<number type, int dim> inline constexpr vector<type,dim>::raw_data::raw_data(const type values[dim]) noexcept : data{}, size{dim} {
		auto it=values;
		for (auto& d: data) { d = *(it++); }
	}

template<number type, int dim>
inline constexpr auto vector<type,dim>::data() noexcept -> raw_data { return raw_data{elements}; }

template<number type, int dim>
inline constexpr auto vector<type,dim>::size() const noexcept -> int { return dim; }

template<number type, int dim>
inline constexpr auto vector<type,dim>::begin()  noexcept       -> type*       { return elements; }
template<number type, int dim>
inline constexpr auto vector<type,dim>::begin()  const noexcept -> const type* { return elements; }
template<number type, int dim>
inline constexpr auto vector<type,dim>::cbegin() const noexcept -> const type* { return elements; }
template<number type, int dim>
inline constexpr auto vector<type,dim>::end()    noexcept       -> type*       { return elements+size(); }
template<number type, int dim>
inline constexpr auto vector<type,dim>::end()    const noexcept -> const type* { return elements+size(); }
template<number type, int dim>
inline constexpr auto vector<type,dim>::cend()   const noexcept -> const type* { return elements+size(); }

template<number type, int dim>
inline constexpr vector<type,dim>::vector() noexcept = default;
template<number type, int dim>
inline constexpr vector<type,dim>::vector(const type& e) noexcept : elements{} {
	for (auto& elem: elements) { elem = e; }
}
template<number type, int dim>
inline constexpr vector<type,dim>::vector(const type values[dim]) noexcept : elements{values} { }

template<number type, int dim>
template<number... Ts>
inline constexpr vector<type,dim>::vector(Ts&&... ts) : elements{ std::forward<Ts>(ts)... } {
	static_assert(sizeof...(Ts) == dim, "Invalid number of arguments in constructor.");
}

template<number type, int dim>
inline constexpr auto vector<type,dim>::operator*=(const vector<type,dim>& vec) noexcept -> vector<type,dim>& {
	auto it = vec.begin();
	for (auto& e: elements) { e *= *(it++); }
	return *this;
}
template<number type, int dim>
inline constexpr auto vector<type,dim>::operator/=(const vector<type,dim>& vec) noexcept -> vector<type,dim>& {
	auto it = vec.begin();
	for (auto& e: elements) { e /= *(it++); }
	return *this;
}
template<number type, int dim>
inline constexpr auto vector<type,dim>::operator+=(const vector<type,dim>& vec) noexcept -> vector<type,dim>& {
	auto it = vec.begin();
	for (auto& e: elements) { e += *(it++); }
	return *this;
}
template<number type, int dim>
inline constexpr auto vector<type,dim>::operator-=(const vector<type,dim>& vec) noexcept -> vector<type,dim>& {
	auto it = vec.begin();
	for (auto& e: elements) { e -= *(it++); }
	return *this;
}
template<number type, int dim>

template<number scalar_type>
inline constexpr auto vector<type,dim>::operator*=(const scalar_type& scalar) noexcept -> vector<type,dim>& {
	for (auto& e: elements) { e *= scalar; }
	return *this;
}
template<number type, int dim>
template<number scalar_type>
inline constexpr auto vector<type,dim>::operator/=(const scalar_type& scalar) noexcept -> vector<type,dim>& {
	for (auto& e: elements) { e /= scalar; }
	return *this;
}
template<number type, int dim>
template<number scalar_type>
inline constexpr auto vector<type,dim>::operator+=(const scalar_type& scalar) noexcept -> vector<type,dim>& {
	for (auto& e: elements) { e += scalar; }
	return *this;
}
template<number type, int dim>
template<number scalar_type>
inline constexpr auto vector<type,dim>::operator-=(const scalar_type& scalar) noexcept -> vector<type,dim>& {
	for (auto& e: elements) { e -= scalar; }
	return *this;
}

template<number type> inline constexpr vector<type,2>::raw_data::raw_data(const type values[2]) noexcept : data{values[0], values[1]}, size{2} {  }
template<number type>
inline constexpr auto vector<type,2>::data() noexcept -> raw_data { return raw_data{elements}; }

template<number type>
inline constexpr auto vector<type,2>::size() const noexcept -> int { return 2; }

template<number type>
inline constexpr auto vector<type,2>::begin()  noexcept       -> type*       { return elements; }
template<number type>
inline constexpr auto vector<type,2>::begin()  const noexcept -> const type* { return elements; }
template<number type>
inline constexpr auto vector<type,2>::cbegin() const noexcept -> const type* { return elements; }
template<number type>
inline constexpr auto vector<type,2>::end()    noexcept 	    -> type*       { return elements+size(); }
template<number type>
inline constexpr auto vector<type,2>::end()    const noexcept -> const type* { return elements+size(); }
template<number type>
inline constexpr auto vector<type,2>::cend()   const noexcept -> const type* { return elements+size(); }

template<number type>
inline constexpr vector<type,2>::vector() noexcept = default;
template<number type>
inline constexpr vector<type,2>::vector(const type& e)       noexcept : elements{e, e}           { }
template<number type>
inline constexpr vector<type,2>::vector(const type& x, const type& y) noexcept : elements{x, y}           { }
template<number type>
inline constexpr vector<type,2>::vector(const type val[2])            noexcept : elements{val[0], val[1]} { }

template<number type> inline constexpr vector<type,2> vector<type,2>::right() noexcept { return { 1,  0}; }
template<number type> inline constexpr vector<type,2> vector<type,2>::left()  noexcept { return {-1,  0}; }
template<number type> inline constexpr vector<type,2> vector<type,2>::up()    noexcept { return { 0,  1}; }
template<number type> inline constexpr vector<type,2> vector<type,2>::down()  noexcept { return { 0, -1}; }

template<number type>
inline constexpr auto vector<type,2>::operator*=(const vector<type,2>& vec) noexcept -> vector<type,2>& {
	x *= vec.x, y *= vec.y;
	return *this;
}
template<number type>
inline constexpr auto vector<type,2>::operator/=(const vector<type,2>& vec) noexcept -> vector<type,2>& {
	x /= vec.x, y /= vec.y;
	return *this;
}
template<number type>
inline constexpr auto vector<type,2>::operator+=(const vector<type,2>& vec) noexcept -> vector<type,2>& {
	x += vec.x, y += vec.y;
	return *this;
}
template<number type>
inline constexpr auto vector<type,2>::operator-=(const vector<type,2>& vec) noexcept -> vector<type,2>& {
	x -= vec.x, y -= vec.y;
	return *this;
}

template<number type>
template<number scalar_type>
inline constexpr auto vector<type,2>::operator*=(const scalar_type& scalar) noexcept -> vector<type,2>& {
	x *= scalar, y *= scalar;
	return *this;
}
template<number type>
template<number scalar_type>
inline constexpr auto vector<type,2>::operator/=(const scalar_type& scalar) noexcept -> vector<type,2>& {
	x /= scalar, y /= scalar;
	return *this;
}
template<number type>
template<number scalar_type>
inline constexpr auto vector<type,2>::operator+=(const scalar_type& scalar) noexcept -> vector<type,2>& {
	x += scalar, y += scalar;
	return *this;
}
template<number type>
template<number scalar_type>
inline constexpr auto vector<type,2>::operator-=(const scalar_type& scalar) noexcept -> vector<type,2>& {
	x -= scalar, y -= scalar;
	return *this;
}

template<number type> inline constexpr vector<type,3>::raw_data::raw_data(const type values[3]) noexcept : data{values[0], values[1], values[2]}, size{3} {  }
template<number type>
inline constexpr auto vector<type,3>::data() noexcept -> raw_data { return raw_data{elements}; }

template<number type>
inline constexpr auto vector<type,3>::size() const noexcept -> int { return 3; }

template<number type>
inline constexpr auto vector<type,3>::begin()  noexcept       -> type*       { return elements; }
template<number type>
inline constexpr auto vector<type,3>::begin()  const noexcept -> const type* { return elements; }
template<number type>
inline constexpr auto vector<type,3>::cbegin() const noexcept -> const type* { return elements; }
template<number type>
inline constexpr auto vector<type,3>::end()    noexcept       -> type*       { return elements+size(); }
template<number type>
inline constexpr auto vector<type,3>::end()    const noexcept -> const type* { return elements+size(); }
template<number type>
inline constexpr auto vector<type,3>::cend()   const noexcept -> const type* { return elements+size(); }

template<number type>
inline constexpr vector<type,3>::vector() noexcept = default;
template<number type>
inline constexpr vector<type,3>::vector(const type& e)                         noexcept : elements{e, e, e}                { }
template<number type>
inline constexpr vector<type,3>::vector(const type& t0, const type& t1, const type& t2) noexcept : elements{t0, t1, t2}             { }
template<number type>
inline constexpr vector<type,3>::vector(const type val[3])                              noexcept : elements{val[0], val[1], val[2]} { }
template<number type>
inline constexpr vector<type,3>::vector(const vector<type,2>& vect, const type& z)      noexcept : elements{vect.x, vect.y, z}      { }

template<number type> inline constexpr vector<type,3> vector<type,3>::right() noexcept { return { 1,  0,  0}; }
template<number type> inline constexpr vector<type,3> vector<type,3>::left()  noexcept { return {-1,  0,  0}; }
template<number type> inline constexpr vector<type,3> vector<type,3>::up()    noexcept { return { 0,  1,  0}; }
template<number type> inline constexpr vector<type,3> vector<type,3>::down()  noexcept { return { 0, -1,  0}; }
template<number type> inline constexpr vector<type,3> vector<type,3>::front() noexcept { return { 0,  0,  1}; }
template<number type> inline constexpr vector<type,3> vector<type,3>::back()  noexcept { return { 0,  0, -1}; }

template<number type>
inline constexpr auto vector<type,3>::operator*=(const vector<type,3>& vec) noexcept -> vector<type,3>& {
	x *= vec.x, y *= vec.y, z *= vec.z;
	return *this;
}
template<number type>
inline constexpr auto vector<type,3>::operator/=(const vector<type,3>& vec) noexcept -> vector<type,3>& {
	x /= vec.x, y /= vec.y, z /= vec.z;
	return *this;
}
template<number type>
inline constexpr auto vector<type,3>::operator+=(const vector<type,3>& vec) noexcept -> vector<type,3>& {
	x += vec.x, y += vec.y, z += vec.z;
	return *this;
}
template<number type>
inline constexpr auto vector<type,3>::operator-=(const vector<type,3>& vec) noexcept -> vector<type,3>& {
	x -= vec.x, y -= vec.y, z -= vec.z;
	return *this;
}

template<number type>
template<number scalar_type>
inline constexpr auto vector<type,3>::operator*=(const scalar_type& scalar) noexcept -> vector<type,3>& {
	x *= scalar, y *= scalar, z *= scalar;
	return *this;
}
template<number type>
template<number scalar_type>
inline constexpr auto vector<type,3>::operator/=(const scalar_type& scalar) noexcept -> vector<type,3>& {
	x /= scalar, y /= scalar, z /= scalar;
	return *this;
}
template<number type>
template<number scalar_type>
inline constexpr auto vector<type,3>::operator+=(const scalar_type& scalar) noexcept -> vector<type,3>& {
	x += scalar, y += scalar, z += scalar;
	return *this;
}
template<number type>
template<number scalar_type>
inline constexpr auto vector<type,3>::operator-=(const scalar_type& scalar) noexcept -> vector<type,3>& {
	x -= scalar, y -= scalar, z -= scalar;
	return *this;
}

template<number type> inline constexpr vector<type,4>::raw_data::raw_data(const type val[4]) noexcept : data{val[0], val[1], val[2], val[3]}, size{4} {  }
template<number type>
inline constexpr auto vector<type,4>::data() noexcept -> raw_data { return raw_data{elements}; }

template<number type>
inline constexpr auto vector<type,4>::size() const noexcept -> int { return 4; }

template<number type>
inline constexpr auto vector<type,4>::begin()  noexcept       -> type*       { return elements; }
template<number type>
inline constexpr auto vector<type,4>::begin()  const noexcept -> const type* { return elements; }
template<number type>
inline constexpr auto vector<type,4>::cbegin() const noexcept -> const type* { return elements; }
template<number type>
inline constexpr auto vector<type,4>::end()    noexcept       -> type*       { return elements+size(); }
template<number type>
inline constexpr auto vector<type,4>::end()    const noexcept -> const type* { return elements+size(); }
template<number type>
inline constexpr auto vector<type,4>::cend()   const noexcept -> const type* { return elements+size(); }

template<number type>
inline constexpr vector<type,4>::vector() noexcept = default;
template<number type>
inline constexpr vector<type,4>::vector(const type& e)                                         noexcept : elements{e, e, e, e}                     { }
template<number type>
inline constexpr vector<type,4>::vector(const type val[4])                                              noexcept : elements{val[0], val[1], val[2], val[3]} { }
template<number type>
inline constexpr vector<type,4>::vector(const type& t0, const type& t1, const type& t2, const type& t3) noexcept : elements{t0, t1, t2, t3}                 { }
template<number type>
inline constexpr vector<type,4>::vector(const vector<type,3>& vect, type w)                             noexcept : elements{vect.x, vect.y, vect.z, w}      { }
template<number type>
inline constexpr vector<type,4>::vector(const vector<type,2>& lhs, const vector<type,2>& rhs)           noexcept : elements{lhs.x, lhs.y, rhs.x, rhs.y}     { }

template<number type>
inline constexpr auto vector<type,4>::operator*=(const vector<type,4>& vec) noexcept -> vector<type,4>& {
	x *= vec.x, y *= vec.y, z *= vec.z, w *= vec.w;
	return *this;
}
template<number type>
inline constexpr auto vector<type,4>::operator/=(const vector<type,4>& vec) noexcept -> vector<type,4>& {
	x /= vec.x, y /= vec.y, z /= vec.z, w /= vec.w;
	return *this;
}
template<number type>
inline constexpr auto vector<type,4>::operator+=(const vector<type,4>& vec) noexcept -> vector<type,4>& {
	x += vec.x, y += vec.y, z += vec.z, w += vec.w;
	return *this;
}
template<number type>
inline constexpr auto vector<type,4>::operator-=(const vector<type,4>& vec) noexcept -> vector<type,4>& {
	x -= vec.x, y -= vec.y, z -= vec.z, w -= vec.w;
	return *this;
}

template<number type>
template<number scalar_type>
inline constexpr auto vector<type,4>::operator*=(const scalar_type& scalar) noexcept -> vector<type,4>& {
	x *= scalar, y *= scalar, z *= scalar, w *= scalar;
	return *this;
}
template<number type>
template<number scalar_type>
inline constexpr auto vector<type,4>::operator/=(const scalar_type& scalar) noexcept -> vector<type,4>& {
	x /= scalar, y /= scalar, z /= scalar, w /= scalar;
	return *this;
}
template<number type>
template<number scalar_type>
inline constexpr auto vector<type,4>::operator+=(const scalar_type& scalar) noexcept -> vector<type,4>& {
	x += scalar, y += scalar, z += scalar, w += scalar;
	return *this;
}
template<number type>
template<number scalar_type>
inline constexpr auto vector<type,4>::operator-=(const scalar_type& scalar) noexcept -> vector<type,4>& {
	x -= scalar, y -= scalar, z -= scalar, w -= scalar;
	return *this;
}

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
constexpr inline auto lerp(
	const vector<type,dim>& x,
	const vector<type,dim>& y,
	type a) noexcept
-> vector<type,dim>
{
	return x * (static_cast<type>(1) - a) + y * a;
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

template<number type> struct make_pi { static constexpr type pi = std::numbers::pi_v<type>; };
constexpr float  pi {make_pi<float>::pi};
constexpr double dpi{make_pi<double>::pi};

template struct vector<bool,2>;
template struct vector<bool,3>;
template struct vector<bool,4>;

template struct vector<unsigned int,2>;
template struct vector<unsigned int,3>;
template struct vector<unsigned int,4>;

template struct vector<int,2>;
template struct vector<int,3>;
template struct vector<int,4>;

template struct vector<float,2>;
template struct vector<float,3>;
template struct vector<float,4>;
