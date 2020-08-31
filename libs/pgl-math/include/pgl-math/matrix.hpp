#pragma once

#include <utility>
#include <type_traits>
#include <string>
#include <sstream>
#include <filesystem>

#include <pgl-math/vector.hpp>

namespace pgl {

	template<number type, int rows, int cols=rows>
		struct matrix {
			type elements[rows*cols];

			inline constexpr matrix() noexcept;
			inline constexpr matrix(const type& e) noexcept;
			/* inline constexpr matrix(type&& e)      noexcept; */
			inline constexpr matrix(const type values[rows*cols]) noexcept;

			template<typename... Ts>
				inline constexpr matrix(
					const type& t0,
					const type& t1,
					Ts&&... ts
				) noexcept;

			inline constexpr auto begin()  noexcept       -> type*;
			inline constexpr auto begin()  const noexcept -> const type*;
			inline constexpr auto cbegin() const noexcept -> const type*;
			inline constexpr auto end()    noexcept       -> type*;
			inline constexpr auto end()    const noexcept -> const type*;
			inline constexpr auto cend()   const noexcept -> const type*;
			inline constexpr auto size()   const noexcept -> int;

			inline constexpr auto at(int row, int col) const -> type;
			inline constexpr auto at(int row, int col)       -> type&;

			inline constexpr auto row(int r) const -> vector<type,cols>;
			inline constexpr auto col(int c) const -> vector<type,cols>;
			inline constexpr auto row(int r, const vector<type,cols>& vect) -> void;
			inline constexpr auto col(int c, const vector<type,rows>& vect) -> void;

			static inline constexpr auto zeros() -> matrix<type,rows,cols>;
			static inline constexpr auto ones()  -> matrix<type,rows,cols>;

			template<number type2>
				inline constexpr auto operator+=(const matrix<type2,rows,cols>& mat) -> matrix<type,rows,cols>&;
			template<number type2>
				inline constexpr auto operator-=(const matrix<type2,rows,cols>& mat) -> matrix<type,rows,cols>&;

			template<number scalar_type>
				inline constexpr auto operator*=(const scalar_type& scalar) -> matrix<type,rows,cols>&;
			template<number scalar_type>
				inline constexpr auto operator/=(const scalar_type& scalar) -> matrix<type,rows,cols>&;
			template<number scalar_type>
				inline constexpr auto operator+=(const scalar_type& scalar) -> matrix<type,rows,cols>&;
			template<number scalar_type>
				inline constexpr auto operator-=(const scalar_type& scalar) -> matrix<type,rows,cols>&;
		};

	template<number type, int dim>
		struct matrix<type, dim, dim> {
			type elements[dim*dim];

			inline constexpr matrix() noexcept;
			inline constexpr matrix(const type& e) noexcept;
			/* inline constexpr matrix(type&& e)      noexcept; */
			inline constexpr matrix(const type values[dim*dim]) noexcept;

			template<typename... Ts>
				inline constexpr matrix(
					const type& t0,
					const type& t1,
					Ts&&... ts
				) noexcept;

			inline constexpr auto begin()  noexcept       -> type*;
			inline constexpr auto begin()  const noexcept -> const type*;
			inline constexpr auto cbegin() const noexcept -> const type*;
			inline constexpr auto end()    noexcept       -> type*;
			inline constexpr auto end()    const noexcept -> const type*;
			inline constexpr auto cend()   const noexcept -> const type*;
			inline constexpr auto size()   const noexcept -> int;

			inline constexpr auto inverse() -> matrix<type,dim>&;

			inline constexpr auto at(int row, int col) const -> type;
			inline constexpr auto at(int row, int col)       -> type&;

			inline constexpr auto row(int r) const -> vector<type,dim>;
			inline constexpr auto col(int c) const -> vector<type,dim>;
			inline constexpr auto row(int r, const vector<type,dim>& vect) -> void;
			inline constexpr auto col(int c, const vector<type,dim>& vect) -> void;

			static inline constexpr auto identity() -> matrix<type,dim>;
			static inline constexpr auto zeros()    -> matrix<type,dim>;
			static inline constexpr auto ones()     -> matrix<type,dim>;

			template<number type2>
				inline constexpr auto operator*=(const matrix<type2,dim>& mat) -> matrix<type,dim>&;
			template<number type2>
				inline constexpr auto operator+=(const matrix<type2,dim>& mat) -> matrix<type,dim>&;
			template<number type2>
				inline constexpr auto operator-=(const matrix<type2,dim>& mat) -> matrix<type,dim>&;

			template<number scalar_type>
				inline constexpr auto operator*=(const scalar_type& scalar) -> matrix<type,dim>&;
			template<number scalar_type>
				inline constexpr auto operator/=(const scalar_type& scalar) -> matrix<type,dim>&;
			template<number scalar_type>
				inline constexpr auto operator+=(const scalar_type& scalar) -> matrix<type,dim>&;
			template<number scalar_type>
				inline constexpr auto operator-=(const scalar_type& scalar) -> matrix<type,dim>&;
		};

	template<number type, int dim>
		inline constexpr auto inverse(const matrix<type,dim>& m)
		-> matrix<type,dim>;

	template<number type, int rows, int cols>
		inline constexpr auto transpose(const matrix<type,rows,cols>& m)
		-> matrix<type,cols,rows>;

	template<number type, int dim>
		inline constexpr type trace(const matrix<type,dim>& m);

	template<number type, int dim>
		inline constexpr auto determinant(const matrix<type,dim>& m)
		-> type;

	template<number type>
		inline constexpr auto determinant(const matrix<type,3>& m)
		-> type;

	template<number type>
		inline constexpr auto determinant(const matrix<type,2>& m)
		-> type;

	template<number type, int cols, std::same_as<vector<type,cols>>... VectorTypes>
		inline constexpr auto matrix_from_row_vectors(
			const vector<type,cols>& v0,
			VectorTypes&&... args)
		-> matrix<type, 1+sizeof...(VectorTypes), cols>;

	template<number type, int rows, std::same_as<vector<type,rows>>... VectorTypes>
		inline constexpr auto matrix_from_col_vectors(
			const vector<type,rows>& v0,
			VectorTypes&&... args)
		-> matrix<type, rows, 1+sizeof...(VectorTypes)>;

	template<number type, number type2, int rows, int cols>
		inline constexpr auto operator<(
			const matrix<type,rows,cols>& lhs,
			const matrix<type2,rows,cols>& rhs)
		-> matrix<bool,rows,cols>;

	template<number type, number type2, int rows, int cols>
		inline constexpr auto operator>(
			const matrix<type,rows,cols>& lhs,
			const matrix<type2,rows,cols>& rhs)
		-> matrix<bool,rows,cols>;

	template<number type, number type2, int rows, int cols>
		inline constexpr auto operator<=(
			const matrix<type,rows,cols>& lhs,
			const matrix<type2,rows,cols>& rhs)
		-> matrix<bool,rows,cols>;

	template<number type, number type2, int rows, int cols>
		inline constexpr auto operator>=(
			const matrix<type,rows,cols>& lhs,
			const matrix<type2,rows,cols>& rhs)
		-> matrix<bool,rows,cols>;

	template<number type, number type2, int rows, int cols>
		inline constexpr auto operator==(
			const matrix<type,rows,cols>& lhs,
			const matrix<type2,rows,cols>& rhs)
		-> matrix<bool,rows,cols>;

	template<number type, number type2, int rows, int cols>
		inline constexpr auto operator!=(
			const matrix<type,rows,cols>& lhs,
			const matrix<type2,rows,cols>& rhs)
		-> matrix<bool,rows,cols>;

	template<number type, number type2, int rows, int cols, int free_dim>
		inline constexpr auto operator*(
			const matrix<type,rows,free_dim>& lhs,
			const matrix<type2,free_dim,cols>& rhs) noexcept
		-> matrix<decltype(std::declval<type>()*std::declval<type2>()),rows,cols>;

	template<number type, number type2, int rows, int cols>
		inline constexpr auto operator+(
			const matrix<type,rows,cols>& lhs,
			const matrix<type2,rows,cols>& rhs)
		-> matrix<decltype(std::declval<type>()+std::declval<type2>()),rows,cols>;

	template<number type, number type2, int rows, int cols>
		inline constexpr auto operator-(
			const matrix<type,rows,cols>& lhs,
			const matrix<type2,rows,cols>& rhs)
		-> matrix<decltype(std::declval<type>()-std::declval<type2>()),rows,cols>;

	template<number type, number scalar_type, int rows, int cols>
		inline constexpr auto operator*(
			const matrix<type,rows,cols>& mat,
			const scalar_type& scalar)
		-> matrix<decltype(scalar*std::declval<type>()),rows,cols>;

	template<number type, number scalar_type, int rows, int cols>
		inline constexpr auto operator/(
			const matrix<type,rows,cols>& mat,
			const scalar_type& scalar)
		-> matrix<decltype(scalar/std::declval<type>()),rows,cols>;

	template<number type, number scalar_type, int rows, int cols>
		inline constexpr auto operator+(
			const matrix<type,rows,cols>& mat,
			const scalar_type& scalar)
		-> matrix<decltype(scalar+std::declval<type>()),rows,cols>;

	template<number type, number scalar_type, int rows, int cols>
		inline constexpr auto operator-(
			const matrix<type,rows,cols>& mat,
			const scalar_type& scalar)
		-> matrix<decltype(scalar-std::declval<type>()),rows,cols>;

	template<number type, number scalar_type, int rows, int cols>
		inline constexpr auto operator*(
			const scalar_type& scalar,
			const matrix<type,rows,cols>& mat)
		-> matrix<decltype(scalar*std::declval<type>()),rows,cols>;

	template<number type, number scalar_type, int rows, int cols>
		inline constexpr auto operator/(
			const scalar_type& scalar,
			const matrix<type,rows,cols>& mat)
		-> matrix<decltype(scalar/std::declval<type>()),rows,cols>;

	template<number type, number scalar_type, int rows, int cols>
		inline constexpr auto operator+(
			const scalar_type& scalar,
			const matrix<type,rows,cols>& mat)
		-> matrix<decltype(scalar+std::declval<type>()),rows,cols>;

	template<number type, number scalar_type, int rows, int cols>
		inline constexpr auto operator-(
			const scalar_type& scalar,
			const matrix<type,rows,cols>& mat)
		-> matrix<decltype(scalar-std::declval<type>()),rows,cols>;

	using bool22 = matrix<bool,2,2>;
	using bool33 = matrix<bool,3,3>;
	using bool44 = matrix<bool,4,4>;

	using int22 = matrix<int,2,2>;
	using int33 = matrix<int,3,3>;
	using int44 = matrix<int,4,4>;

	using uint22 = matrix<unsigned int,2,2>;
	using uint33 = matrix<unsigned int,3,3>;
	using uint44 = matrix<unsigned int,4,4>;

	using float22 = matrix<float,2,2>;
	using float33 = matrix<float,3,3>;
	using float44 = matrix<float,4,4>;

	/*
	 *
	 * ========================
	 * ======= TODO !!! =======
	 * ========================
	 *
	 * inline
	 * cross, inverse
	 * template some of the utility functions for containers (quaternion, vector, matrix, ...), for ex: max, min, clamp, min_element, max_element, ...
	 * operator[] ?
	 * rotation matrix
	 * constexpr
	 * iterator ?
	 * how to handle out of bounds ?
	 * make elements private and change struct to class
	 *
	 */

#include <pgl-math/impl/matrix.hpp>

} /* end of namespace pgl */
