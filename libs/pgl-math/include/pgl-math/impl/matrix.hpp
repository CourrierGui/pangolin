#include <pgl-math/utils.hpp>

template<number type, int rows, int cols>
inline constexpr matrix<type,rows,cols>::matrix() noexcept = default;

template<number type, int dim>
inline constexpr matrix<type,dim>::matrix() noexcept = default;

template<number type, int rows, int cols>
inline constexpr matrix<type,rows,cols>::matrix(const type& e) noexcept : elements() {
	for (auto& elem: elements) { elem = e; }
}

template<number type, int dim>
inline constexpr matrix<type,dim>::matrix(const type& e) noexcept
: elements() {
	for (auto& elem: elements) { elem = e; }
}

template<number type, int rows, int cols>
inline constexpr matrix<type,rows,cols>::matrix(const type values[rows*cols]) noexcept
: elements()
{
	const type* it = values;
	for (auto& elem: elements) { elem = *(it++); }
}

template<number type, int dim>
inline constexpr matrix<type,dim>::matrix(const type values[dim*dim]) noexcept
: elements()
{
	const type* it = values;
	for (auto& elem: elements) { elem = *(it++); }
}

template<number type, int rows, int cols>
template<typename... Ts>
inline constexpr matrix<type,rows,cols>::matrix(
	const type& t0,
	const type& t1,
	Ts&&... ts) noexcept
: elements{ t0, t1, std::forward<type>(ts)... }
{
	static_assert(
		sizeof...(Ts) == rows*cols-2,
		"Invalid number of arguments in constructor."
		);
}

template<number type, int dim>
template<typename... Ts>
inline constexpr matrix<type,dim>::matrix(
	const type& t0,
	const type& t1,
	Ts&&... ts) noexcept
: elements{ t0, t1, std::forward<type>(ts)... }
{
	static_assert(
		sizeof...(Ts) == dim*dim-2,
		"Invalid number of arguments in constructor."
		);
}

template<number type, int rows, int cols>
inline constexpr auto matrix<type,rows,cols>::begin() noexcept
-> type*
{
	return elements;
}

template<number type, int rows, int cols>
inline constexpr auto matrix<type,rows,cols>::begin()  const noexcept
-> const type*
{
	return elements;
}

template<number type, int rows, int cols>
inline constexpr auto matrix<type,rows,cols>::cbegin() const noexcept
-> const type*
{
	return elements;
}

template<number type, int rows, int cols>
inline constexpr auto matrix<type,rows,cols>::end()    noexcept
-> type*
{
	return elements+size();
}

template<number type, int rows, int cols>
inline constexpr auto matrix<type,rows,cols>::end()    const noexcept
-> const type*
{
	return elements+size();
}

template<number type, int rows, int cols>
inline constexpr auto matrix<type,rows,cols>::cend()   const noexcept
-> const type*
{
	return elements+size();
}

template<number type, int rows, int cols>
inline constexpr auto matrix<type,rows,cols>::size()   const noexcept
-> int
{
	return rows*cols;
}

template<number type, int dim>
inline constexpr auto matrix<type,dim>::begin() noexcept
-> type*
{
	return elements;
}

template<number type, int dim>
inline constexpr auto matrix<type,dim>::begin() const noexcept
-> const type*
{
	return elements;
}

template<number type, int dim>
inline constexpr auto matrix<type,dim>::cbegin() const noexcept
-> const type*
{
	return elements;
}

template<number type, int dim>
inline constexpr auto matrix<type,dim>::end() noexcept
-> type*
{
	return elements+size();
}

template<number type, int dim>
inline constexpr auto matrix<type,dim>::end()    const noexcept
-> const type*
{
	return elements+size();
}

template<number type, int dim>
inline constexpr auto matrix<type,dim>::cend()   const noexcept
-> const type* {
	return elements+size();
}

template<number type, int dim>
inline constexpr auto matrix<type,dim>::size() const noexcept
-> int
{
	return dim*dim;
}


	template<number type, int dim>
inline constexpr auto matrix<type,dim>::inverse()
	-> matrix<type,dim>& {
		//TODO add general formula
		return *this;
	}

	template<number type, int dim>
inline constexpr auto inverse(const matrix<type,dim>& m)
	-> matrix<type,dim>
{
	matrix<type,dim> res{m};
	return res.inverse();
}

	template<number type, int rows, int cols>
inline constexpr auto transpose(const matrix<type,rows,cols>& m)
	-> matrix<type,cols,rows>
{
	matrix<type,cols,rows> res;
	for (int r=0; r<rows; ++r) {
		for (int c=0; c<cols; ++c) {
			res.at(r,c) = m.at(c, r);
		}
	}
	return res;
}

template<number type, int dim>
inline constexpr type trace(const matrix<type,dim>& m) {
	type res{0};
	for (int d=0; d<dim; ++d) { res += m.at(d, d); }
	return res;
}

	template<number type, int dim>
inline constexpr auto determinant(const matrix<type,dim>& m)
	-> type
{
	type det{0};
	//TODO general determinant formula
	return det;
}

	template<number type>
inline constexpr auto determinant(const matrix<type,3>& m)
	-> type
{
	return (  m.at(0, 0) * m.at(1, 1) * m.at(2, 2)
					+ m.at(0, 1) * m.at(1, 2) * m.at(2, 0)
					+ m.at(0, 2) * m.at(1, 0) * m.at(2, 1)
					- m.at(0, 2) * m.at(1, 1) * m.at(2, 0)
					- m.at(0, 1) * m.at(1, 0) * m.at(2, 2)
					- m.at(0, 0) * m.at(1, 2) * m.at(2, 1));
}

	template<number type>
inline constexpr auto determinant(const matrix<type,2>& m)
	-> type
{
	return (m.at(0, 0) * m.at(1, 1) - m.at(0, 1) * m.at(1, 0));
}

template<number type, int cols, std::same_as<vector<type,cols>>... VectorTypes>
inline constexpr auto matrix_from_row_vectors(
	const vector<type,cols>& v0,
	VectorTypes&&... args)
	-> matrix<type, 1+sizeof...(VectorTypes), cols>
{
	matrix<type, 1+sizeof...(VectorTypes), cols> res;
	res.row(0, v0);
	int i=1;
	auto make_matrix = [&res, &i](auto&& arg) {
		res.row(i++, arg);
	};
	(make_matrix(args), ...);

	return res;
}

template<number type, int rows, std::same_as<vector<type,rows>>... VectorTypes>
inline constexpr auto matrix_from_col_vectors(
	const vector<type,rows>& v0,
	VectorTypes&&... args)
	-> matrix<type, rows, 1+sizeof...(VectorTypes)>
{
	matrix<type, rows, 1+sizeof...(VectorTypes)> res;
	res.col(0, v0);
	int i=1;
	auto make_matrix = [&res, &i](auto&& arg) {
		res.col(i++, arg);
	};
	(make_matrix(args), ...);
	return res;
}

template<number type, int rows, int cols>
inline constexpr auto matrix<type,rows,cols>::at(int row, int col) const
-> type
{
	return elements[col + cols * row];
}

template<number type, int dim>
inline constexpr auto matrix<type,dim>::at(int row, int col) const
-> type
{
	return elements[col + dim * row];
}

	template<number type, int rows, int cols>
inline constexpr auto matrix<type,rows,cols>::at(int row, int col)
	-> type&
{
	return elements[col + cols * row];
}

	template<number type, int dim>
inline constexpr auto matrix<type,dim>::at(int row, int col)
	-> type&
{
	return elements[col + dim * row];
}

template<number type, int rows, int cols>
inline constexpr auto matrix<type,rows,cols>::row(int r) const
-> vector<type,cols>
{
	vector<type,cols> res;
	const type* it = elements + (r*cols);
	for (auto& elem: res.elements) {
		elem = *(it++);
	}
	return res;
}

template<number type, int dim>
inline constexpr auto matrix<type,dim>::row(int r) const
-> vector<type,dim>
{
	vector<type,dim> res;
	const type* it = elements + (r*dim);
	for (auto& elem: res.elements) {
		elem = *(it++);
	}
	return res;
}

template<number type, int rows, int cols>
inline constexpr auto matrix<type,rows,cols>::col(int c) const
-> vector<type,cols>
{
	vector<type,cols> res;
	const type* it = elements + c;
	for (auto& elem: res.elements) {
		elem = *it;
		it += rows;
	}
	return res;
}

template<number type, int dim>
inline constexpr auto matrix<type,dim>::col(int c) const
-> vector<type,dim>
{
	vector<type,dim> res;
	const type* it = elements + c;
	for (auto& elem: res.elements) {
		elem = *it;
		it += dim;
	}
	return res;
}

	template<number type, int dim>
inline constexpr auto matrix<type, dim>::identity()
	-> matrix<type,dim>
{
	matrix<type,dim,dim> id{type{0}};
	for (int i=0; i<dim; ++i) { id.at(i, i) = 1; }
	return id;
}

	template<number type, int rows, int cols>
inline constexpr auto matrix<type,rows,cols>::zeros()
	-> matrix<type,rows,cols>
{
	return {type{0}};
}

	template<number type, int rows, int cols>
inline constexpr auto matrix<type,rows,cols>::ones()
	-> matrix<type,rows,cols>
{
	return {type{1}};
}

	template<number type, int dim>
inline constexpr auto matrix<type,dim>::zeros()
	-> matrix<type,dim>
{
	return {type{0}};
}

	template<number type, int dim>
inline constexpr auto matrix<type,dim>::ones()
	-> matrix<type,dim>
{
	return {type{1}};
}

	template<number type, int rows, int cols>
inline constexpr auto matrix<type,rows,cols>::row(int r, const vector<type,cols>& vect)
	-> void
{
	type* elem = elements + (r*cols);
	for (const auto& e: vect.elements) {
		*(elem++) = e;
	}
}

	template<number type, int rows, int cols>
inline constexpr auto matrix<type,rows,cols>::col(int c, const vector<type,rows>& vect)
	-> void
{
	type* elem = elements + c;
	for (const auto& e: vect.elements) {
		*elem = e;
		elem += cols;
	}
}

	template<number type, int dim>
inline constexpr auto matrix<type,dim>::row(int r, const vector<type,dim>& vect)
	-> void
{
	type* elem = elements + (r*dim);
	for (const auto& e: vect.elements) {
		*(elem++) = e;
	}
}

	template<number type, int dim>
inline constexpr auto matrix<type,dim>::col(int c, const vector<type,dim>& vect)
	-> void
{
	type* elem = elements + c;
	for (const auto& e: vect.elements) {
		*elem = e;
		elem += dim;
	}
}

template<number type, int dim>
	template<number type2>
inline constexpr auto matrix<type,dim>::operator*=(const matrix<type2,dim>& mat)
	-> matrix<type,dim>&
{
	pgl::matrix<type,dim> tmp{type{0}};
	for (int r=0; r<dim; ++r) {
		for (int c=0; c<dim; ++c) {
			for (int k=0; k<dim; ++k) {
				tmp.at(r,c) += at(r,k) * mat.at(k,c);
			}
		}
	}
	*this = tmp;
	return *this;
}

template<number type, int rows, int cols>
	template<number type2>
inline constexpr auto matrix<type,rows,cols>::operator+=(const matrix<type2,rows,cols>& mat)
	-> matrix<type,rows,cols>&
{
	auto this_it = begin();
	auto mat_it = mat.begin();
	while (this_it!=end()) {
		*(this_it++) += *(mat_it++);
	}
	return *this;
}

template<number type, int dim>
	template<number type2>
inline constexpr auto matrix<type,dim>::operator+=(const matrix<type2,dim>& mat)
	-> matrix<type,dim>&
{
	auto this_it = begin();
	auto mat_it = mat.begin();
	while (this_it!=end()) {
		*(this_it++) += *(mat_it++);
	}
	return *this;
}

template<number type, int rows, int cols>
	template<number type2>
inline constexpr auto matrix<type,rows,cols>::operator-=(const matrix<type2,rows,cols>& mat)
	-> matrix<type,rows,cols>&
{
	auto this_it = begin();
	auto mat_it = mat.begin();
	while (this_it!=end()) {
		*(this_it++) -= *(mat_it++);
	}
	return *this;
}

template<number type, int dim>
	template<number type2>
inline constexpr auto matrix<type,dim>::operator-=(const matrix<type2,dim>& mat)
	-> matrix<type,dim>&
{
	auto this_it = begin();
	auto mat_it = mat.begin();
	while (this_it!=end()) {
		*(this_it++) -= *(mat_it++);
	}
	return *this;
}

template<number type, int rows, int cols>
	template<number scalar_type>
inline constexpr auto matrix<type,rows,cols>::operator*=(const scalar_type& scalar)
	-> matrix<type,rows,cols>&
{
	auto this_it = begin();
	while (this_it!=end()) {
		*(this_it++) *= scalar;
	}
	return *this;
}

template<number type, int dim>
	template<number scalar_type>
inline constexpr auto matrix<type,dim>::operator*=(const scalar_type& scalar)
	-> matrix<type,dim>&
{
	auto this_it = begin();
	while (this_it!=end()) {
		*(this_it++) *= scalar;
	}
	return *this;
}

template<number type, int rows, int cols>
	template<number scalar_type>
inline constexpr auto matrix<type,rows,cols>::operator/=(const scalar_type& scalar)
	-> matrix<type,rows,cols>&
{
	auto this_it = begin();
	while (this_it!=end()) {
		*(this_it++) /= scalar;
	}
	return *this;
}

template<number type, int dim>
	template<number scalar_type>
inline constexpr auto matrix<type,dim>::operator/=(const scalar_type& scalar)
	-> matrix<type,dim>&
{
	auto this_it = begin();
	while (this_it!=end()) {
		*(this_it++) /= scalar;
	}
	return *this;
}

template<number type, int rows, int cols>
	template<number scalar_type>
inline constexpr auto matrix<type,rows,cols>::operator+=(const scalar_type& scalar)
	-> matrix<type,rows,cols>&
{
	auto this_it = begin();
	while (this_it!=end()) {
		*(this_it++) += scalar;
	}
	return *this;
}

template<number type, int dim>
	template<number scalar_type>
inline constexpr auto matrix<type,dim>::operator+=(const scalar_type& scalar)
	-> matrix<type,dim>&
{
	auto this_it = begin();
	while (this_it!=end()) {
		*(this_it++) += scalar;
	}
	return *this;
}

template<number type, int rows, int cols>
	template<number scalar_type>
inline constexpr auto matrix<type,rows,cols>::operator-=(const scalar_type& scalar)
	-> matrix<type,rows,cols>&
{
	auto this_it = begin();
	while (this_it!=end()) {
		*(this_it++) -= scalar;
	}
	return *this;
}

template<number type, int dim>
	template<number scalar_type>
inline constexpr auto matrix<type,dim>::operator-=(const scalar_type& scalar)
	-> matrix<type,dim>&
{
	auto this_it = begin();
	while (this_it!=end()) {
		*(this_it++) -= scalar;
	}
	return *this;
}

	template<number type, number type2, int rows, int cols>
inline constexpr auto operator<(
	const matrix<type,rows,cols>& lhs,
	const matrix<type2,rows,cols>& rhs)
	-> matrix<bool,rows,cols>
{
	matrix<bool,rows,cols> res;
	auto lhs_it = lhs.begin();
	auto rhs_it = rhs.begin();
	auto res_it = res.begin();
	while (lhs_it!=lhs.end()) {
		*(res_it++) = (*(lhs_it++) < *(rhs_it++));
	}
	return res;
}

	template<number type, number type2, int rows, int cols>
inline constexpr auto operator>(
	const matrix<type,rows,cols>& lhs,
	const matrix<type2,rows,cols>& rhs)
	-> matrix<bool,rows,cols>
{
	matrix<bool,rows,cols> res;
	auto lhs_it = lhs.begin();
	auto rhs_it = rhs.begin();
	auto res_it = res.begin();
	while (lhs_it!=lhs.end()) {
		*(res_it++) = (*(lhs_it++) > *(rhs_it++));
	}
	return res;
}

	template<number type, number type2, int rows, int cols>
inline constexpr auto operator<=(
	const matrix<type,rows,cols>& lhs,
	const matrix<type2,rows,cols>& rhs)
	-> matrix<bool,rows,cols>
{
	matrix<bool,rows,cols> res;
	auto lhs_it = lhs.begin();
	auto rhs_it = rhs.begin();
	auto res_it = res.begin();
	while (lhs_it!=lhs.end()) {
		*(res_it++) = (*(lhs_it++) <= *(rhs_it++));
	}
	return res;
}

	template<number type, number type2, int rows, int cols>
inline constexpr auto operator>=(
	const matrix<type,rows,cols>& lhs,
	const matrix<type2,rows,cols>& rhs)
	-> matrix<bool,rows,cols>
{
	matrix<bool,rows,cols> res;
	auto lhs_it = lhs.begin();
	auto rhs_it = rhs.begin();
	auto res_it = res.begin();
	while (lhs_it!=lhs.end()) {
		*(res_it++) = (*(lhs_it++) >= *(rhs_it++));
	}
	return res;
}

	template<number type, number type2, int rows, int cols>
inline constexpr auto operator==(
	const matrix<type,rows,cols>& lhs,
	const matrix<type2,rows,cols>& rhs)
	-> matrix<bool,rows,cols>
{
	matrix<bool,rows,cols> res;
	auto lhs_it = lhs.begin();
	auto rhs_it = rhs.begin();
	auto res_it = res.begin();
	while (lhs_it!=lhs.end()) {
		*(res_it++) = (*(lhs_it++) == *(rhs_it++));
	}
	return res;
}

	template<number type, number type2, int rows, int cols>
inline constexpr auto operator!=(
	const matrix<type,rows,cols>& lhs,
	const matrix<type2,rows,cols>& rhs)
	-> matrix<bool,rows,cols>
{
	matrix<bool,rows,cols> res;
	auto lhs_it = lhs.begin();
	auto rhs_it = rhs.begin();
	auto res_it = res.begin();
	while (lhs_it!=lhs.end()) {
		*(res_it++) = (*(lhs_it++) != *(rhs_it++));
	}
	return res;
}

template<number type, number type2, int rows, int cols, int free_dim>
inline constexpr auto operator*(
	const matrix<type,rows,free_dim>& lhs,
	const matrix<type2,free_dim,cols>& rhs) noexcept
-> matrix<decltype(std::declval<type>()*std::declval<type2>()),rows,cols>
{
	matrix<decltype(std::declval<type>()*std::declval<type2>()),rows,cols> res{type{0}};
	for (int r=0; r<rows; ++r) {
		for (int c=0; c<cols; ++c) {
			for (int k=0; k<free_dim; ++k) {
				res.at(r, c) += lhs.at(r, k) * rhs.at(k, c);
			}
		}
	}
	return res;
}

	template<number type, number type2, int rows, int cols>
inline constexpr auto operator+(
	const matrix<type,rows,cols>& lhs,
	const matrix<type2,rows,cols>& rhs)
	-> matrix<decltype(std::declval<type>()+std::declval<type2>()),rows,cols>
{
	matrix<decltype(std::declval<type>()+std::declval<type2>()),rows,cols> res{lhs};
	res += rhs;
	return res;
}

	template<number type, number type2, int rows, int cols>
inline constexpr auto operator-(
	const matrix<type,rows,cols>& lhs,
	const matrix<type2,rows,cols>& rhs)
	-> matrix<decltype(std::declval<type>()-std::declval<type2>()),rows,cols>
{
	matrix<decltype(std::declval<type>()-std::declval<type2>()),rows,cols> res{lhs};
	res -= rhs;
	return res;
}

	template<number type, number scalar_type, int rows, int cols>
inline constexpr auto operator*(
	const matrix<type,rows,cols>& mat,
	const scalar_type& scalar)
	-> matrix<decltype(scalar*std::declval<type>()),rows,cols>
{
	matrix<type,rows,cols> res{mat};
	res *= scalar;
	return res;
}

	template<number type, number scalar_type, int rows, int cols>
inline constexpr auto operator/(
	const matrix<type,rows,cols>& mat,
	const scalar_type& scalar)
	-> matrix<decltype(scalar/std::declval<type>()),rows,cols>
{
	matrix<type,rows,cols> res{mat};
	res /= scalar;
	return res;
}

	template<number type, number scalar_type, int rows, int cols>
inline constexpr auto operator+(
	const matrix<type,rows,cols>& mat,
	const scalar_type& scalar)
	-> matrix<decltype(scalar+std::declval<type>()),rows,cols>
{
	matrix<type,rows,cols> res{mat};
	res += scalar;
	return res;
}

	template<number type, number scalar_type, int rows, int cols>
inline constexpr auto operator-(
	const matrix<type,rows,cols>& mat,
	const scalar_type& scalar)
	-> matrix<decltype(scalar-std::declval<type>()),rows,cols>
{
	matrix<type,rows,cols> res{mat};
	res -= scalar;
	return res;
}

	template<number type, number scalar_type, int rows, int cols>
inline constexpr auto operator*(
	const scalar_type& scalar,
	const matrix<type,rows,cols>& mat)
	-> matrix<decltype(scalar*std::declval<type>()),rows,cols>
{
	return mat*scalar;
}

	template<number type, number scalar_type, int rows, int cols>
inline constexpr auto operator/(
	const scalar_type& scalar,
	const matrix<type,rows,cols>& mat)
	-> matrix<decltype(scalar/std::declval<type>()),rows,cols>
{
	matrix<decltype(scalar/std::declval<type>()),rows,cols> res{mat};
	for (auto& e: res) {
		e = scalar/e;
	}
	return res;
}

	template<number type, number scalar_type, int rows, int cols>
inline constexpr auto operator+(
	const scalar_type& scalar,
	const matrix<type,rows,cols>& mat)
	-> matrix<decltype(scalar+std::declval<type>()),rows,cols>
{
	return mat+scalar;
}

	template<number type, number scalar_type, int rows, int cols>
inline constexpr auto operator-(
	const scalar_type& scalar,
	const matrix<type,rows,cols>& mat)
	-> matrix<decltype(scalar-std::declval<type>()),rows,cols>
{
	return mat-scalar;
}

/* template struct matrix<bool,2,2>; */
/* template struct matrix<bool,3,3>; */
/* template struct matrix<bool,4,4>; */

template struct matrix<int,2,2>;
template struct matrix<int,3,3>;
template struct matrix<int,4,4>;

template struct matrix<unsigned int,2,2>;
template struct matrix<unsigned int,3,3>;
template struct matrix<unsigned int,4,4>;

template struct matrix<float,2,2>;
template struct matrix<float,3,3>;
template struct matrix<float,4,4>;
