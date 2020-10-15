#pragma once

#include <utility>
#include <type_traits>
#include <string>
#include <sstream>
#include <filesystem>

#include <pgl-math/vector.hpp>

namespace pgl {

	template<number type, uint32_t rows, uint32_t cols=rows>
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
			inline constexpr auto size()   const noexcept -> uint32_t;

			inline constexpr auto at(uint32_t row, uint32_t col) const -> type;
			inline constexpr auto at(uint32_t row, uint32_t col)       -> type&;

			inline constexpr auto row(uint32_t r) const -> vector<type,cols>;
			inline constexpr auto col(uint32_t c) const -> vector<type,cols>;
			inline constexpr auto row(uint32_t r, const vector<type,cols>& vect) -> void;
			inline constexpr auto col(uint32_t c, const vector<type,rows>& vect) -> void;

			static inline constexpr auto zeros() -> matrix<type,rows,cols>;
			static inline constexpr auto ones()  -> matrix<type,rows,cols>;

			template<number type2>
				inline constexpr auto operator+=(const matrix<type2,rows,cols>& mat)
				-> matrix<type,rows,cols>&;
			template<number type2>
				inline constexpr auto operator-=(const matrix<type2,rows,cols>& mat)
				-> matrix<type,rows,cols>&;

			template<number scalar_type>
				inline constexpr auto operator*=(const scalar_type& scalar) -> matrix<type,rows,cols>&;
			template<number scalar_type>
				inline constexpr auto operator/=(const scalar_type& scalar) -> matrix<type,rows,cols>&;
			template<number scalar_type>
				inline constexpr auto operator+=(const scalar_type& scalar) -> matrix<type,rows,cols>&;
			template<number scalar_type>
				inline constexpr auto operator-=(const scalar_type& scalar) -> matrix<type,rows,cols>&;
		};

	template<number type, uint32_t dim>
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
			inline constexpr auto size()   const noexcept -> uint32_t;

			inline constexpr auto inverse() -> matrix<type,dim>&;

			inline constexpr auto at(uint32_t row, uint32_t col) const -> type;
			inline constexpr auto at(uint32_t row, uint32_t col)       -> type&;

			inline constexpr auto row(uint32_t r) const -> vector<type,dim>;
			inline constexpr auto col(uint32_t c) const -> vector<type,dim>;
			inline constexpr auto row(uint32_t r, const vector<type,dim>& vect) -> void;
			inline constexpr auto col(uint32_t c, const vector<type,dim>& vect) -> void;

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

	template<number type, uint32_t dim>
		inline constexpr auto inverse(const matrix<type,dim>& m)
		-> matrix<type,dim>;

	template<number type, uint32_t rows, uint32_t cols>
		inline constexpr auto transpose(const matrix<type,rows,cols>& m)
		-> matrix<type,cols,rows>;

	template<number type, uint32_t dim>
		inline constexpr type trace(const matrix<type,dim>& m);

	template<number type, uint32_t dim>
		inline constexpr auto determinant(const matrix<type,dim>& m)
		-> type;

	template<number type>
		inline constexpr auto determinant(const matrix<type,3>& m)
		-> type;

	template<number type>
		inline constexpr auto determinant(const matrix<type,2>& m)
		-> type;

	template<number type, uint32_t cols, std::same_as<vector<type,cols>>... VectorTypes>
		inline constexpr auto matrix_from_row_vectors(
			const vector<type,cols>& v0,
			VectorTypes&&... args)
		-> matrix<type, 1+sizeof...(VectorTypes), cols>;

	template<number type, uint32_t rows, std::same_as<vector<type,rows>>... VectorTypes>
		inline constexpr auto matrix_from_col_vectors(
			const vector<type,rows>& v0,
			VectorTypes&&... args)
		-> matrix<type, rows, 1+sizeof...(VectorTypes)>;

	template<number type, number type2, uint32_t rows, uint32_t cols>
		inline constexpr auto operator<(
			const matrix<type,rows,cols>& lhs,
			const matrix<type2,rows,cols>& rhs)
		-> matrix<bool,rows,cols>;

	template<number type, number type2, uint32_t rows, uint32_t cols>
		inline constexpr auto operator>(
			const matrix<type,rows,cols>& lhs,
			const matrix<type2,rows,cols>& rhs)
		-> matrix<bool,rows,cols>;

	template<number type, number type2, uint32_t rows, uint32_t cols>
		inline constexpr auto operator<=(
			const matrix<type,rows,cols>& lhs,
			const matrix<type2,rows,cols>& rhs)
		-> matrix<bool,rows,cols>;

	template<number type, number type2, uint32_t rows, uint32_t cols>
		inline constexpr auto operator>=(
			const matrix<type,rows,cols>& lhs,
			const matrix<type2,rows,cols>& rhs)
		-> matrix<bool,rows,cols>;

	template<number type, number type2, uint32_t rows, uint32_t cols>
		inline constexpr auto operator==(
			const matrix<type,rows,cols>& lhs,
			const matrix<type2,rows,cols>& rhs)
		-> matrix<bool,rows,cols>;

	template<number type, number type2, uint32_t rows, uint32_t cols>
		inline constexpr auto operator!=(
			const matrix<type,rows,cols>& lhs,
			const matrix<type2,rows,cols>& rhs)
		-> matrix<bool,rows,cols>;

	template<number type, number type2, uint32_t rows, uint32_t cols, uint32_t free_dim>
		inline constexpr auto operator*(
			const matrix<type,rows,free_dim>& lhs,
			const matrix<type2,free_dim,cols>& rhs) noexcept
		-> matrix<decltype(std::declval<type>()*std::declval<type2>()),rows,cols>;

	template<number type, number type2, uint32_t rows, uint32_t cols>
		inline constexpr auto operator+(
			const matrix<type,rows,cols>& lhs,
			const matrix<type2,rows,cols>& rhs)
		-> matrix<decltype(std::declval<type>()+std::declval<type2>()),rows,cols>;

	template<number type, number type2, uint32_t rows, uint32_t cols>
		inline constexpr auto operator-(
			const matrix<type,rows,cols>& lhs,
			const matrix<type2,rows,cols>& rhs)
		-> matrix<decltype(std::declval<type>()-std::declval<type2>()),rows,cols>;

	template<number type, number scalar_type, uint32_t rows, uint32_t cols>
		inline constexpr auto operator*(
			const matrix<type,rows,cols>& mat,
			const scalar_type& scalar)
		-> matrix<decltype(scalar*std::declval<type>()),rows,cols>;

	template<number type, number scalar_type, uint32_t rows, uint32_t cols>
		inline constexpr auto operator/(
			const matrix<type,rows,cols>& mat,
			const scalar_type& scalar)
		-> matrix<decltype(scalar/std::declval<type>()),rows,cols>;

	template<number type, number scalar_type, uint32_t rows, uint32_t cols>
		inline constexpr auto operator+(
			const matrix<type,rows,cols>& mat,
			const scalar_type& scalar)
		-> matrix<decltype(scalar+std::declval<type>()),rows,cols>;

	template<number type, number scalar_type, uint32_t rows, uint32_t cols>
		inline constexpr auto operator-(
			const matrix<type,rows,cols>& mat,
			const scalar_type& scalar)
		-> matrix<decltype(scalar-std::declval<type>()),rows,cols>;

	template<number type, number scalar_type, uint32_t rows, uint32_t cols>
		inline constexpr auto operator*(
			const scalar_type& scalar,
			const matrix<type,rows,cols>& mat)
		-> matrix<decltype(scalar*std::declval<type>()),rows,cols>;

	template<number type, number scalar_type, uint32_t rows, uint32_t cols>
		inline constexpr auto operator/(
			const scalar_type& scalar,
			const matrix<type,rows,cols>& mat)
		-> matrix<decltype(scalar/std::declval<type>()),rows,cols>;

	template<number type, number scalar_type, uint32_t rows, uint32_t cols>
		inline constexpr auto operator+(
			const scalar_type& scalar,
			const matrix<type,rows,cols>& mat)
		-> matrix<decltype(scalar+std::declval<type>()),rows,cols>;

	template<number type, number scalar_type, uint32_t rows, uint32_t cols>
		inline constexpr auto operator-(
			const scalar_type& scalar,
			const matrix<type,rows,cols>& mat)
		-> matrix<decltype(scalar-std::declval<type>()),rows,cols>;

	using int22 = matrix<int32_t,2,2>;
	using int33 = matrix<int32_t,3,3>;
	using int44 = matrix<int32_t,4,4>;

	using uint22 = matrix<uint32_t,2,2>;
	using uint33 = matrix<uint32_t,3,3>;
	using uint44 = matrix<uint32_t,4,4>;

	using float22 = matrix<float,2,2>;
	using float33 = matrix<float,3,3>;
	using float44 = matrix<float,4,4>;

	/*
	 * ========================
	 * ======= TODO !!! =======
	 * ========================
	 *
	 * cross, inverse
	 * operator[] ?
	 * rotation matrix
	 * constexpr
	 * iterator ?
	 * how to handle out of bounds ?
	 * make elements private and change struct to class
	 */

} /* end of namespace pgl */
