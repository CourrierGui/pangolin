/* #pragma once */

/* #include <pgl-math/vector.hpp> */
/* #include <pgl-math/base-vector.hpp> */
/* #include <pgl-math/impl/base-vector.hpp> */

/* namespace pgl { */

/* 	template<number type, int dim> inline constexpr algebric_vector<type,dim>::algebric_vector()                noexcept : base_vector<type,dim>{} {} */
/* 	template<number type, int dim> inline constexpr algebric_vector<type,dim>::algebric_vector(const type& t)     noexcept : base_vector<type,dim>{t} {} */
/* 	template<number type, int dim> inline constexpr algebric_vector<type,dim>::algebric_vector(const type arr[dim]) noexcept : base_vector<type,dim>{} { */
/* 		auto it = arr; */
/* 		for (auto& elem: this->elements) { */
/* 			elem = *(it++); */
/* 		} */
/* 	} */

/* 	template<number type, int dim> inline constexpr algebric_vector<type,dim>::algebric_vector(const std::initializer_list<type>& args) noexcept : base_vector<type,dim>{args} {  } */
/* 	/1* template<number type, int dim> *1/ */
/* 	/1* 	template<number... Ts> *1/ */
/* 	/1* 	inline constexpr algebric_vector<type,dim>::algebric_vector(const type& t, Ts&&... ts) noexcept *1/ */
/* 	/1* 	: base_vector<type,dim>{ t, std::forward<Ts>(ts)... } {} *1/ */

/* 	template<number type, int dim> inline constexpr vector<type,dim>::vector()                        noexcept : algebric_vector<type,dim>{}    {  } */
/* 	template<number type, int dim> inline constexpr vector<type,dim>::vector(const type& t)           noexcept : algebric_vector<type,dim>{t}   {  } */
/* 	template<number type, int dim> inline constexpr vector<type,dim>::vector(const type arr[dim])     noexcept : algebric_vector<type,dim>{arr} {  } */
/* 	template<number type, int dim> inline constexpr vector<type,dim>::vector(const type& values, ...) noexcept : algebric_vector<type,dim>{values} {  } */

/* 	template<int dim> inline constexpr vector<bool,dim>::vector()                    noexcept : base_vector<bool,dim>{}    {  } */
/* 	template<int dim> inline constexpr vector<bool,dim>::vector(bool t)              noexcept : base_vector<bool,dim>{t}   {  } */
/* 	template<int dim> inline constexpr vector<bool,dim>::vector(const bool arr[dim]) noexcept : base_vector<bool,dim>{arr} {  } */
/* 	template<int dim> inline constexpr vector<bool,dim>::vector(bool values, ...)    noexcept : base_vector<bool,dim>{values} {  } */

/* 	template<number type> inline constexpr vector<type,2>::vector()                               noexcept : algebric_vector<type,2>{}       {  } */
/* 	template<number type> inline constexpr vector<type,2>::vector(const type& t)                  noexcept : algebric_vector<type,2>{t}      {  } */
/* 	template<number type> inline constexpr vector<type,2>::vector(const type arr[2])              noexcept : algebric_vector<type,2>{arr}    {  } */
/* 	template<number type> inline constexpr vector<type,2>::vector(const type& t1, const type& t2) noexcept : algebric_vector<type,2>{t1, t2} {  } */

/* 	template<number type> inline constexpr vector<type,3>::vector()                                               noexcept : algebric_vector<type,3>{}            {  } */
/* 	template<number type> inline constexpr vector<type,3>::vector(const type& t)                                  noexcept : algebric_vector<type,3>{t}           {  } */
/* 	template<number type> inline constexpr vector<type,3>::vector(const type arr[3])                              noexcept : algebric_vector<type,3>{arr}         {  } */
/* 	template<number type> inline constexpr vector<type,3>::vector(const type& t1, const type& t2, const type& t3) noexcept : algebric_vector<type,3>{t1,t2,t3}    {  } */
/* 	template<number type> inline constexpr vector<type,3>::vector(const vector<type,2>& v, const type& t)         noexcept : algebric_vector<type,3>{v.x, v.y, t} {  } */

/* 	template<number type> inline constexpr vector<type,4>::vector()                                                           noexcept : algebric_vector<type,4>{}                   { } */
/* 	template<number type> inline constexpr vector<type,4>::vector(const type& t)                                              noexcept : algebric_vector<type,4>{t}                  { } */
/* 	template<number type> inline constexpr vector<type,4>::vector(const type arr[4])                                          noexcept : algebric_vector<type,4>{arr}                { } */
/* 	template<number type> inline constexpr vector<type,4>::vector(const type& x, const type& y, const type& z, const type& w) noexcept : algebric_vector<type,4>{x,y,z,w}            { } */
/* 	template<number type> inline constexpr vector<type,4>::vector(const vector<type,3>& v, const type& w)                     noexcept : algebric_vector<type,4>{v.x, v.y, v.z, w}   { } */
/* 	template<number type> inline constexpr vector<type,4>::vector(const vector<type,2>& v, const vector<type,2>& u)           noexcept : algebric_vector<type,4>{v.x, v.y, u.x, u.y} { } */

/* 	template<number type> inline constexpr vector<type,2> vector<type,2>::right() noexcept { return {1, 0      }; } */
/* 	template<number type> inline constexpr vector<type,3> vector<type,3>::right() noexcept { return {1, 0, 0   }; } */
/* 	template<number type> inline constexpr vector<type,4> vector<type,4>::right() noexcept { return {1, 0, 0, 0}; } */

/* 	template<number type> inline constexpr vector<type,2> vector<type,2>::left()  noexcept { return {-1, 0      }; } */
/* 	template<number type> inline constexpr vector<type,3> vector<type,3>::left()  noexcept { return {-1, 0, 0   }; } */
/* 	template<number type> inline constexpr vector<type,4> vector<type,4>::left()  noexcept { return {-1, 0, 0, 0}; } */

/* 	template<number type> inline constexpr vector<type,2> vector<type,2>::up()    noexcept { return {0, 1      }; } */
/* 	template<number type> inline constexpr vector<type,3> vector<type,3>::up()    noexcept { return {0, 1, 0   }; } */
/* 	template<number type> inline constexpr vector<type,4> vector<type,4>::up()    noexcept { return {0, 1, 0, 0}; } */

/* 	template<number type> inline constexpr vector<type,2> vector<type,2>::down()  noexcept { return {0, -1      }; } */
/* 	template<number type> inline constexpr vector<type,3> vector<type,3>::down()  noexcept { return {0, -1, 0   }; } */
/* 	template<number type> inline constexpr vector<type,4> vector<type,4>::down()  noexcept { return {0, -1, 0, 0}; } */

/* 	template<number type> inline constexpr vector<type,3> vector<type,3>::front() noexcept { return {0, 0, 1   }; } */
/* 	template<number type> inline constexpr vector<type,4> vector<type,4>::front() noexcept { return {0, 0, 1, 0}; } */

/* 	template<number type> inline constexpr vector<type,3> vector<type,3>::back()  noexcept { return {0, 0, -1   }; } */
/* 	template<number type> inline constexpr vector<type,4> vector<type,4>::back()  noexcept { return {0, 0, -1, 0}; } */

/* 	/1* template<> inline constexpr          vector<bool,2>::vector()                               noexcept : base_vector<bool,2>{}       {  } *1/ */
/* 	/1* template<> inline constexpr explicit vector<bool,2>::vector(const bool& t)                  noexcept : base_vector<bool,2>{t}      {  } *1/ */
/* 	/1* template<> inline constexpr          vector<bool,2>::vector(const bool arr[2])              noexcept : base_vector<bool,2>{arr}    {  } *1/ */
/* 	/1* template<> inline constexpr          vector<bool,2>::vector(const bool& t1, const bool& t2) noexcept : base_vector<bool,2>{t1, t2} {  } *1/ */

/* 	/1* template<> inline constexpr          vector<bool,3>::vector()                                               noexcept : base_vector<bool,3>{}         {  } *1/ */
/* 	/1* template<> inline constexpr explicit vector<bool,3>::vector(const bool& t)                                  noexcept : base_vector<bool,3>{t}        {  } *1/ */
/* 	/1* template<> inline constexpr          vector<bool,3>::vector(const bool& t1, const bool& t2, const bool& t3) noexcept : base_vector<bool,3>{t1,t2,t3} {  } *1/ */
/* 	/1* template<> inline constexpr          vector<bool,3>::vector(const bool arr[3])                              noexcept : base_vector<bool,3>{arr}      {  } *1/ */
/* 	/1* template<> inline constexpr          vector<bool,3>::vector(const vector<bool,2>& v, const bool& t)         noexcept : base_vector<bool,3>{v, t}     {  } *1/ */

/* 	/1* template<number type, int dim> *1/ */
/* 	/1* 	inline constexpr auto vector<type,dim>::operator*=(const vector<type,dim>& vec) noexcept -> vector<type,dim>& { *1/ */
/* 	/1* 		auto it = vec.begin(); *1/ */
/* 	/1* 		for (auto& e: this->elements) { e *= *(it++); } *1/ */
/* 	/1* 		return *this; *1/ */
/* 	/1* 	} *1/ */
/* 	/1* template<number type, int dim> *1/ */
/* 	/1* 	inline constexpr auto vector<type,dim>::operator/=(const vector<type,dim>& vec) noexcept -> vector<type,dim>& { *1/ */
/* 	/1* 		auto it = vec.begin(); *1/ */
/* 	/1* 		for (auto& e: this->elements) { e /= *(it++); } *1/ */
/* 	/1* 		return *this; *1/ */
/* 	/1* 	} *1/ */
/* 	/1* template<number type, int dim> *1/ */
/* 	/1* 	inline constexpr auto vector<type,dim>::operator+=(const vector<type,dim>& vec) noexcept -> vector<type,dim>& { *1/ */
/* 	/1* 		auto it = vec.begin(); *1/ */
/* 	/1* 		for (auto& e: this->elements) { e += *(it++); } *1/ */
/* 	/1* 		return *this; *1/ */
/* 	/1* 	} *1/ */
/* 	/1* template<number type, int dim> *1/ */
/* 	/1* 	inline constexpr auto vector<type,dim>::operator-=(const vector<type,dim>& vec) noexcept -> vector<type,dim>& { *1/ */
/* 	/1* 		auto it = vec.begin(); *1/ */
/* 	/1* 		for (auto& e: this->elements) { e -= *(it++); } *1/ */
/* 	/1* 		return *this; *1/ */
/* 	/1* 	} *1/ */
/* 	/1* template<number type, int dim> *1/ */

/* 	/1* 	template<number scalar_type> *1/ */
/* 	/1* 	inline constexpr auto vector<type,dim>::operator*=(const scalar_type& scalar) noexcept -> vector<type,dim>& { *1/ */
/* 	/1* 		for (auto& e: this->elements) { e *= scalar; } *1/ */
/* 	/1* 		return *this; *1/ */
/* 	/1* 	} *1/ */
/* 	/1* template<number type, int dim> *1/ */
/* 	/1* 	template<number scalar_type> *1/ */
/* 	/1* 	inline constexpr auto vector<type,dim>::operator/=(const scalar_type& scalar) noexcept -> vector<type,dim>& { *1/ */
/* 	/1* 		for (auto& e: this->elements) { e /= scalar; } *1/ */
/* 	/1* 		return *this; *1/ */
/* 	/1* 	} *1/ */
/* 	/1* template<number type, int dim> *1/ */
/* 	/1* 	template<number scalar_type> *1/ */
/* 	/1* 	inline constexpr auto vector<type,dim>::operator+=(const scalar_type& scalar) noexcept -> vector<type,dim>& { *1/ */
/* 	/1* 		for (auto& e: this->elements) { e += scalar; } *1/ */
/* 	/1* 		return *this; *1/ */
/* 	/1* 	} *1/ */
/* 	/1* template<number type, int dim> *1/ */
/* 	/1* 	template<number scalar_type> *1/ */
/* 	/1* 	inline constexpr auto vector<type,dim>::operator-=(const scalar_type& scalar) noexcept -> vector<type,dim>& { *1/ */
/* 	/1* 		for (auto& e: this->elements) { e -= scalar; } *1/ */
/* 	/1* 		return *this; *1/ */
/* 	/1* 	} *1/ */

/* 	/1* template<number type> *1/ */
/* 	/1* 	inline constexpr auto vector<type,2>::operator*=(const vector<type,2>& vec) noexcept -> vector<type,2>& { *1/ */
/* 	/1* 		this->x *= vec.x, this->y *= vec.y; *1/ */
/* 	/1* 		return *this; *1/ */
/* 	/1* 	} *1/ */
/* 	/1* template<number type> *1/ */
/* 	/1* 	inline constexpr auto vector<type,2>::operator/=(const vector<type,2>& vec) noexcept -> vector<type,2>& { *1/ */
/* 	/1* 		this->x /= vec.x, this->y /= vec.y; *1/ */
/* 	/1* 		return *this; *1/ */
/* 	/1* 	} *1/ */
/* 	/1* template<number type> *1/ */
/* 	/1* 	inline constexpr auto vector<type,2>::operator+=(const vector<type,2>& vec) noexcept -> vector<type,2>& { *1/ */
/* 	/1* 		this->x += vec.x, this->y += vec.y; *1/ */
/* 	/1* 		return *this; *1/ */
/* 	/1* 	} *1/ */
/* 	/1* template<number type> *1/ */
/* 	/1* 	inline constexpr auto vector<type,2>::operator-=(const vector<type,2>& vec) noexcept -> vector<type,2>& { *1/ */
/* 	/1* 		this->x -= vec.x, this->y -= vec.y; *1/ */
/* 	/1* 		return *this; *1/ */
/* 	/1* 	} *1/ */

/* 	/1* template<number type> *1/ */
/* 	/1* 	template<number scalar_type> *1/ */
/* 	/1* 	inline constexpr auto vector<type,2>::operator*=(const scalar_type& scalar) noexcept -> vector<type,2>& { *1/ */
/* 	/1* 		this->x *= scalar, this->y *= scalar; *1/ */
/* 	/1* 		return *this; *1/ */
/* 	/1* 	} *1/ */
/* 	/1* template<number type> *1/ */
/* 	/1* 	template<number scalar_type> *1/ */
/* 	/1* 	inline constexpr auto vector<type,2>::operator/=(const scalar_type& scalar) noexcept -> vector<type,2>& { *1/ */
/* 	/1* 		this->x /= scalar, this->y /= scalar; *1/ */
/* 	/1* 		return *this; *1/ */
/* 	/1* 	} *1/ */
/* 	/1* template<number type> *1/ */
/* 	/1* 	template<number scalar_type> *1/ */
/* 	/1* 	inline constexpr auto vector<type,2>::operator+=(const scalar_type& scalar) noexcept -> vector<type,2>& { *1/ */
/* 	/1* 		this->x += scalar, this->y += scalar; *1/ */
/* 	/1* 		return *this; *1/ */
/* 	/1* 	} *1/ */
/* 	/1* template<number type> *1/ */
/* 	/1* 	template<number scalar_type> *1/ */
/* 	/1* 	inline constexpr auto vector<type,2>::operator-=(const scalar_type& scalar) noexcept -> vector<type,2>& { *1/ */
/* 	/1* 		this->x -= scalar, this->y -= scalar; *1/ */
/* 	/1* 		return *this; *1/ */
/* 	/1* 	} *1/ */

/* 	/1* template<number type> *1/ */
/* 	/1* 	inline constexpr auto vector<type,3>::operator*=(const vector<type,3>& vec) noexcept -> vector<type,3>& { *1/ */
/* 	/1* 		this->x *= vec.x, this->y *= vec.y, this->z *= vec.z; *1/ */
/* 	/1* 		return *this; *1/ */
/* 	/1* 	} *1/ */
/* 	/1* template<number type> *1/ */
/* 	/1* 	inline constexpr auto vector<type,3>::operator/=(const vector<type,3>& vec) noexcept -> vector<type,3>& { *1/ */
/* 	/1* 		this->x /= vec.x, this->y /= vec.y, this->z /= vec.z; *1/ */
/* 	/1* 		return *this; *1/ */
/* 	/1* 	} *1/ */
/* 	/1* template<number type> *1/ */
/* 	/1* 	inline constexpr auto vector<type,3>::operator+=(const vector<type,3>& vec) noexcept -> vector<type,3>& { *1/ */
/* 	/1* 		this->x += vec.x, this->y += vec.y, this->z += vec.z; *1/ */
/* 	/1* 		return *this; *1/ */
/* 	/1* 	} *1/ */
/* 	/1* template<number type> *1/ */
/* 	/1* 	inline constexpr auto vector<type,3>::operator-=(const vector<type,3>& vec) noexcept -> vector<type,3>& { *1/ */
/* 	/1* 		this->x -= vec.x, this->y -= vec.y, this->z -= vec.z; *1/ */
/* 	/1* 		return *this; *1/ */
/* 	/1* 	} *1/ */

/* 	/1* template<number type> *1/ */
/* 	/1* 	template<number scalar_type> *1/ */
/* 	/1* 	inline constexpr auto vector<type,3>::operator*=(const scalar_type& scalar) noexcept -> vector<type,3>& { *1/ */
/* 	/1* 		this->x *= scalar, this->y *= scalar, this->z *= scalar; *1/ */
/* 	/1* 		return *this; *1/ */
/* 	/1* 	} *1/ */
/* 	/1* template<number type> *1/ */
/* 	/1* 	template<number scalar_type> *1/ */
/* 	/1* 	inline constexpr auto vector<type,3>::operator/=(const scalar_type& scalar) noexcept -> vector<type,3>& { *1/ */
/* 	/1* 		this->x /= scalar, this->y /= scalar, this->z /= scalar; *1/ */
/* 	/1* 		return *this; *1/ */
/* 	/1* 	} *1/ */
/* 	/1* template<number type> *1/ */
/* 	/1* 	template<number scalar_type> *1/ */
/* 	/1* 	inline constexpr auto vector<type,3>::operator+=(const scalar_type& scalar) noexcept -> vector<type,3>& { *1/ */
/* 	/1* 		this->x += scalar, this->y += scalar, this->z += scalar; *1/ */
/* 	/1* 		return *this; *1/ */
/* 	/1* 	} *1/ */
/* 	/1* template<number type> *1/ */
/* 	/1* 	template<number scalar_type> *1/ */
/* 	/1* 	inline constexpr auto vector<type,3>::operator-=(const scalar_type& scalar) noexcept -> vector<type,3>& { *1/ */
/* 	/1* 		this->x -= scalar, this->y -= scalar, this->z -= scalar; *1/ */
/* 	/1* 		return *this; *1/ */
/* 	/1* 	} *1/ */

/* 	/1* template<number type> *1/ */
/* 	/1* 	inline constexpr auto vector<type,4>::operator*=(const vector<type,4>& vec) noexcept -> vector<type,4>& { *1/ */
/* 	/1* 		this->x *= vec.x, this->y *= vec.y, this->z *= vec.z, this->w *= vec.w; *1/ */
/* 	/1* 		return *this; *1/ */
/* 	/1* 	} *1/ */
/* 	/1* template<number type> *1/ */
/* 	/1* 	inline constexpr auto vector<type,4>::operator/=(const vector<type,4>& vec) noexcept -> vector<type,4>& { *1/ */
/* 	/1* 		this->x /= vec.x, this->y /= vec.y, this->z /= vec.z, this->w /= vec.w; *1/ */
/* 	/1* 		return *this; *1/ */
/* 	/1* 	} *1/ */
/* 	/1* template<number type> *1/ */
/* 	/1* 	inline constexpr auto vector<type,4>::operator+=(const vector<type,4>& vec) noexcept -> vector<type,4>& { *1/ */
/* 	/1* 		this->x += vec.x, this->y += vec.y, this->z += vec.z, this->w += vec.w; *1/ */
/* 	/1* 		return *this; *1/ */
/* 	/1* 	} *1/ */
/* 	/1* template<number type> *1/ */
/* 	/1* 	inline constexpr auto vector<type,4>::operator-=(const vector<type,4>& vec) noexcept -> vector<type,4>& { *1/ */
/* 	/1* 		this->x -= vec.x, this->y -= vec.y, this->z -= vec.z, this->w -= vec.w; *1/ */
/* 	/1* 		return *this; *1/ */
/* 	/1* 	} *1/ */

/* 	/1* template<number type> *1/ */
/* 	/1* 	template<number scalar_type> *1/ */
/* 	/1* 	inline constexpr auto vector<type,4>::operator*=(const scalar_type& scalar) noexcept -> vector<type,4>& { *1/ */
/* 	/1* 		this->x *= scalar, this->y *= scalar, this->z *= scalar, this->w *= scalar; *1/ */
/* 	/1* 		return *this; *1/ */
/* 	/1* 	} *1/ */
/* 	/1* template<number type> *1/ */
/* 	/1* 	template<number scalar_type> *1/ */
/* 	/1* 	inline constexpr auto vector<type,4>::operator/=(const scalar_type& scalar) noexcept -> vector<type,4>& { *1/ */
/* 	/1* 		this->x /= scalar, this->y /= scalar, this->z /= scalar, this->w /= scalar; *1/ */
/* 	/1* 		return *this; *1/ */
/* 	/1* 	} *1/ */
/* 	/1* template<number type> *1/ */
/* 	/1* 	template<number scalar_type> *1/ */
/* 	/1* 	inline constexpr auto vector<type,4>::operator+=(const scalar_type& scalar) noexcept -> vector<type,4>& { *1/ */
/* 	/1* 		this->x += scalar, this->y += scalar, this->z += scalar, this->w += scalar; *1/ */
/* 	/1* 		return *this; *1/ */
/* 	/1* 	} *1/ */
/* 	/1* template<number type> *1/ */
/* 	/1* 	template<number scalar_type> *1/ */
/* 	/1* 	inline constexpr auto vector<type,4>::operator-=(const scalar_type& scalar) noexcept -> vector<type,4>& { *1/ */
/* 	/1* 		this->x -= scalar, this->y -= scalar, this->z -= scalar, this->w -= scalar; *1/ */
/* 	/1* 		return *this; *1/ */
/* 	/1* 	} *1/ */

/* 	/1* template<number type, int dim> *1/ */
/* 	/1* 	inline constexpr auto operator*( *1/ */
/* 	/1* 		const vector<type,dim>& lhs, *1/ */
/* 	/1* 		const vector<type,dim>& rhs) noexcept *1/ */
/* 	/1* 	-> vector<type,dim> *1/ */
/* 	/1* 	{ *1/ */
/* 	/1* 		vector<type,dim> res{lhs}; *1/ */
/* 	/1* 		auto rhs_it = rhs.begin(); *1/ */
/* 	/1* 		for (auto& elem: res) { *1/ */
/* 	/1* 			elem *= *(rhs_it++); *1/ */
/* 	/1* 		} *1/ */
/* 	/1* 		return res; *1/ */
/* 	/1* 	} *1/ */

/* 	/1* template<number type, number scalar_type, int dim> *1/ */
/* 	/1* 	inline constexpr auto operator*( *1/ */
/* 	/1* 		const vector<type,dim>& lhs, *1/ */
/* 	/1* 		const scalar_type& rhs) noexcept *1/ */
/* 	/1* 	-> vector<type,dim> *1/ */
/* 	/1* 	{ *1/ */
/* 	/1* 		vector<type,dim> res{lhs}; *1/ */
/* 	/1* 		for (auto& elem: res) { *1/ */
/* 	/1* 			elem *= rhs; *1/ */
/* 	/1* 		} *1/ */
/* 	/1* 		return res; *1/ */
/* 	/1* 	} *1/ */

/* 	/1* template<number type, number scalar_type, int dim> *1/ */
/* 	/1* 	inline constexpr auto operator*( *1/ */
/* 	/1* 		const scalar_type& lhs, *1/ */
/* 	/1* 		const vector<type,dim>& rhs) noexcept *1/ */
/* 	/1* 	-> vector<type,dim> *1/ */
/* 	/1* 	{ *1/ */
/* 	/1* 		return rhs * lhs; *1/ */
/* 	/1* 	} *1/ */

/* 	/1* template<number type, int dim> *1/ */
/* 	/1* 	inline constexpr auto operator/( *1/ */
/* 	/1* 		const vector<type,dim>& lhs, *1/ */
/* 	/1* 		const vector<type,dim>& rhs) noexcept *1/ */
/* 	/1* 	-> vector<type,dim> *1/ */
/* 	/1* 	{ *1/ */
/* 	/1* 		vector<type,dim> res{lhs}; *1/ */
/* 	/1* 		auto rhs_it = rhs.begin(); *1/ */
/* 	/1* 		for (auto& elem: res) { *1/ */
/* 	/1* 			elem /= *(rhs_it++); *1/ */
/* 	/1* 		} *1/ */
/* 	/1* 		return res; *1/ */
/* 	/1* 	} *1/ */

/* 	/1* template<number type, number scalar_type, int dim> *1/ */
/* 	/1* 	inline constexpr auto operator/( *1/ */
/* 	/1* 		const vector<type,dim>& lhs, *1/ */
/* 	/1* 		const scalar_type& rhs) noexcept *1/ */
/* 	/1* 	-> vector<type,dim> *1/ */
/* 	/1* 	{ *1/ */
/* 	/1* 		vector<type,dim> res{lhs}; *1/ */
/* 	/1* 		for (auto& elem: res) { *1/ */
/* 	/1* 			elem /= rhs; *1/ */
/* 	/1* 		} *1/ */
/* 	/1* 		return res; *1/ */
/* 	/1* 	} *1/ */

/* 	/1* template<number type, number scalar_type, int dim> *1/ */
/* 	/1* 	inline constexpr auto operator/( *1/ */
/* 	/1* 		const scalar_type& rhs, *1/ */
/* 	/1* 		const vector<type,dim>& lhs) noexcept *1/ */
/* 	/1* 	-> vector<type,dim> *1/ */
/* 	/1* 	{ *1/ */
/* 	/1* 		vector<type,dim> res{lhs}; *1/ */
/* 	/1* 		for (auto& elem: res) { *1/ */
/* 	/1* 			elem = rhs/elem; *1/ */
/* 	/1* 		} *1/ */
/* 	/1* 		return res; *1/ */
/* 	/1* 	} *1/ */

/* 	/1* template<number type, int dim> *1/ */
/* 	/1* 	inline constexpr auto operator-( *1/ */
/* 	/1* 		const vector<type,dim>& lhs, *1/ */
/* 	/1* 		const vector<type,dim>& rhs) noexcept *1/ */
/* 	/1* 	-> vector<type,dim> *1/ */
/* 	/1* 	{ *1/ */
/* 	/1* 		vector<type,dim> res{lhs}; *1/ */
/* 	/1* 		auto rhs_it = rhs.begin(); *1/ */
/* 	/1* 		for (auto& elem: res) { *1/ */
/* 	/1* 			elem -= *(rhs_it++); *1/ */
/* 	/1* 		} *1/ */
/* 	/1* 		return res; *1/ */
/* 	/1* 	} *1/ */

/* 	/1* template<number type, number scalar_type, int dim> *1/ */
/* 	/1* 	inline constexpr auto operator-( *1/ */
/* 	/1* 		const vector<type,dim>& lhs, *1/ */
/* 	/1* 		const scalar_type& rhs) noexcept *1/ */
/* 	/1* 	-> vector<type,dim> *1/ */
/* 	/1* 	{ *1/ */
/* 	/1* 		vector<type,dim> res{lhs}; *1/ */
/* 	/1* 		for (auto& elem: res) { *1/ */
/* 	/1* 			elem = elem - rhs; *1/ */
/* 	/1* 		} *1/ */
/* 	/1* 		return res; *1/ */
/* 	/1* 	} *1/ */

/* 	/1* template<number type, number scalar_type, int dim> *1/ */
/* 	/1* 	inline constexpr auto operator-( *1/ */
/* 	/1* 		const scalar_type& lhs, *1/ */
/* 	/1* 		const vector<type,dim>& rhs) noexcept *1/ */
/* 	/1* 	-> vector<type,dim> *1/ */
/* 	/1* 	{ *1/ */
/* 	/1* 		vector<type,dim> res{rhs}; *1/ */
/* 	/1* 		for (auto& elem: res) { *1/ */
/* 	/1* 			elem = lhs - elem; *1/ */
/* 	/1* 		} *1/ */
/* 	/1* 		return res; *1/ */
/* 	/1* 	} *1/ */

/* 	/1* template<number type, int dim> *1/ */
/* 	/1* 	inline constexpr auto operator+( *1/ */
/* 	/1* 		const vector<type,dim>& lhs, *1/ */
/* 	/1* 		const vector<type,dim>& rhs) noexcept *1/ */
/* 	/1* 	-> vector<type,dim> *1/ */
/* 	/1* 	{ *1/ */
/* 	/1* 		vector<type,dim> res{lhs}; *1/ */
/* 	/1* 		auto rhs_it = rhs.begin(); *1/ */
/* 	/1* 		for (auto& elem: res) { *1/ */
/* 	/1* 			elem += *(rhs_it++); *1/ */
/* 	/1* 		} *1/ */
/* 	/1* 		return res; *1/ */
/* 	/1* 	} *1/ */

/* 	/1* template<number type, number scalar_type, int dim> *1/ */
/* 	/1* 	inline constexpr auto operator+( *1/ */
/* 	/1* 		const vector<type,dim>& lhs, *1/ */
/* 	/1* 		const scalar_type& rhs) noexcept *1/ */
/* 	/1* 	-> vector<type,dim> *1/ */
/* 	/1* 	{ *1/ */
/* 	/1* 		vector<type,dim> res{lhs}; *1/ */
/* 	/1* 		for (auto& elem: res) { *1/ */
/* 	/1* 			elem += rhs; *1/ */
/* 	/1* 		} *1/ */
/* 	/1* 		return res; *1/ */
/* 	/1* 	} *1/ */

/* 	/1* template<number type, number scalar_type, int dim> *1/ */
/* 	/1* 	inline constexpr auto operator+( *1/ */
/* 	/1* 		const scalar_type& lhs, *1/ */
/* 	/1* 		const vector<type,dim>& rhs) noexcept *1/ */
/* 	/1* 	-> vector<type,dim> *1/ */
/* 	/1* 	{ *1/ */
/* 	/1* 		return rhs + lhs; *1/ */
/* 	/1* 	} *1/ */

/* 	/1* template<number type, int dim> *1/ */
/* 	/1* 	inline constexpr auto dot( *1/ */
/* 	/1* 		const vector<type,dim>& lhs, *1/ */
/* 	/1* 		const vector<type,dim>& rhs) noexcept *1/ */
/* 	/1* 	-> type { *1/ */
/* 	/1* 		type res{0}; *1/ */
/* 	/1* 		for (auto lhs_it=lhs.begin(), rhs_it=rhs.begin(); *1/ */
/* 	/1* 				 lhs_it != lhs.end(); *1/ */
/* 	/1* 				 ++lhs_it,++rhs_it) *1/ */
/* 	/1* 		{ *1/ */
/* 	/1* 			res += *(lhs_it) * *(rhs_it); *1/ */
/* 	/1* 		} *1/ */
/* 	/1* 		return res; *1/ */
/* 	/1* 	} *1/ */

/* 	/1* template<number type, int dim> *1/ */
/* 	/1* 	inline constexpr auto dot(const vector<type,dim>& arg) noexcept *1/ */
/* 	/1* 	-> type *1/ */
/* 	/1* 	{ *1/ */
/* 	/1* 		return dot(arg,arg); *1/ */
/* 	/1* 	} *1/ */

/* 	/1* template<number type, int dim> *1/ */
/* 	/1* 	inline constexpr auto sum(const vector<type,dim>& arg) noexcept *1/ */
/* 	/1* 	-> type { *1/ */
/* 	/1* 		type res{0}; *1/ */
/* 	/1* 		for (auto elem: arg) { *1/ */
/* 	/1* 			res += elem; *1/ */
/* 	/1* 		} *1/ */
/* 	/1* 		return res; *1/ */
/* 	/1* 	} *1/ */

/* 	/1* template<number type, int dim> *1/ */
/* 	/1* 	inline constexpr auto normalize(const vector<type,dim>& arg) noexcept *1/ */
/* 	/1* 	-> vector<type,dim> *1/ */
/* 	/1* 	{ *1/ */
/* 	/1* 		type s = sum(arg); *1/ */
/* 	/1* 		return arg/s; *1/ */
/* 	/1* 	} *1/ */

/* 	/1* template<number type, int dim> *1/ */
/* 	/1* 	constexpr inline auto lerp( *1/ */
/* 	/1* 		const vector<type,dim>& x, *1/ */
/* 	/1* 		const vector<type,dim>& y, *1/ */
/* 	/1* 		type a) noexcept *1/ */
/* 	/1* 	-> vector<type,dim> *1/ */
/* 	/1* 	{ *1/ */
/* 	/1* 		return x * (static_cast<type>(1) - a) + y * a; *1/ */
/* 	/1* 	} *1/ */

/* 	/1* template<number type, int dim> *1/ */
/* 	/1* 	inline constexpr auto abs(const vector<type,dim>& vec) noexcept *1/ */
/* 	/1* 	-> vector<type,dim> *1/ */
/* 	/1* 	{ *1/ */
/* 	/1* 		vector<type,dim> res; *1/ */
/* 	/1* 		auto vec_it = vec.begin(); *1/ */
/* 	/1* 		for (auto& elem: res) *1/ */
/* 	/1* 			elem = std::abs(*(vec_it++)); *1/ */
/* 	/1* 		return res; *1/ */
/* 	/1* 	} *1/ */

/* 	constexpr float  pi  {std::numbers::pi_v<float>}; */
/* 	constexpr double dpi {std::numbers::pi_v<double>}; */

/* } /1* end of namespace pgl *1/ */
