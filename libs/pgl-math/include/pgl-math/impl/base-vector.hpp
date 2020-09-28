/* #pragma once */

/* #include <numbers> */
/* #include <limits> */
/* #include <cmath> */
/* #include <initializer_list> */
/* #include <iostream> */
/* #include <utility> */

/* #include <type_traits> */

/* #include <pgl-math/utils.hpp> */
/* #include <pgl-math/base-vector.hpp> */

/* namespace pgl { */

/* 	template<integral type, int dim> inline constexpr base_vector<type,dim>::raw_data::raw_data(const type values[dim]) noexcept */
/* 		: data{}, size{dim} */
/* 	{ */
/* 		auto it=values; */
/* 		for (auto& d: data) { d = *(it++); } */
/* 	} */

/* 	template<integral type, int dim> inline constexpr auto base_vector<type,dim>::size() const noexcept -> int { return dim; } */

/* 	template<integral type> inline constexpr base_vector<type,2>::raw_data::raw_data(const type values[2]) noexcept : data{values[0], values[1]}, size{2}            {  } */
/* 	template<integral type> inline constexpr base_vector<type,3>::raw_data::raw_data(const type values[3]) noexcept : data{values[0], values[1], values[2]}, size{3} {  } */
/* 	template<integral type> inline constexpr base_vector<type,4>::raw_data::raw_data(const type val[4])    noexcept : data{val[0], val[1], val[2], val[3]}, size{4}  {  } */

/* 	template<integral type, int dim> inline constexpr auto base_vector<type,dim>::data() noexcept -> raw_data { return raw_data{elements}; } */
/* 	template<integral type>          inline constexpr auto base_vector<type,2>::data()   noexcept -> raw_data { return raw_data{elements}; } */
/* 	template<integral type>          inline constexpr auto base_vector<type,3>::data()   noexcept -> raw_data { return raw_data{elements}; } */
/* 	template<integral type>          inline constexpr auto base_vector<type,4>::data()   noexcept -> raw_data { return raw_data{elements}; } */

/* 	template<integral type, int dim> inline constexpr auto base_vector<type,dim>::begin()  noexcept       -> type*       { return elements; } */
/* 	template<integral type, int dim> inline constexpr auto base_vector<type,dim>::begin()  const noexcept -> const type* { return elements; } */
/* 	template<integral type, int dim> inline constexpr auto base_vector<type,dim>::cbegin() const noexcept -> const type* { return elements; } */
/* 	template<integral type, int dim> inline constexpr auto base_vector<type,dim>::end()    noexcept       -> type*       { return elements+size(); } */
/* 	template<integral type, int dim> inline constexpr auto base_vector<type,dim>::end()    const noexcept -> const type* { return elements+size(); } */
/* 	template<integral type, int dim> inline constexpr auto base_vector<type,dim>::cend()   const noexcept -> const type* { return elements+size(); } */

/* 	template<integral type, int dim> inline constexpr base_vector<type,dim>::base_vector()                       noexcept = default; */
/* 	template<integral type, int dim> inline constexpr base_vector<type,dim>::base_vector(const type& e)          noexcept : elements{} { for (auto& elem: elements) { elem = e; } } */
/* 	template<integral type, int dim> inline constexpr base_vector<type,dim>::base_vector(const type values[dim]) noexcept : elements{} { */
/* 		auto it = values; */
/* 		for (auto& elem: elements) { */
/* 			elem = *(it++); */
/* 		} */
/* 	} */

/* 	template<integral type, int dim> inline constexpr base_vector<type,dim>::base_vector(const std::initializer_list<type>& args) noexcept : elements{} { */
/* 		auto it = args.begin(); */
/* 		for (auto& elem: elements) { */
/* 			elem = *(it++); */
/* 		} */
/* 	} */
/* 	/1* template<integral type, int dim> *1/ */
/* 	/1* 	template<integral... Values> *1/ */
/* 	/1* 	inline constexpr base_vector<type,dim>::base_vector(const type& t, Values&&... ts) noexcept : elements{ t, std::forward<Values>(ts)... } { *1/ */
/* 	/1* 		static_assert(sizeof...(Values) == dim-1, "Invalid number of arguments in constructor."); *1/ */
/* 	/1* 	} *1/ */

/* 	/1* template<integral type, int dim> inline constexpr base_vector<type,dim>::base_vector(const type& t, const type& values, ...) noexcept : elements{t, values} { } *1/ */

/* 	template<integral type> inline constexpr auto base_vector<type,2>::size()   const noexcept -> int         { return 2;               } */
/* 	template<integral type> inline constexpr auto base_vector<type,2>::begin()  noexcept       -> type*       { return elements;        } */
/* 	template<integral type> inline constexpr auto base_vector<type,2>::begin()  const noexcept -> const type* { return elements;        } */
/* 	template<integral type> inline constexpr auto base_vector<type,2>::cbegin() const noexcept -> const type* { return elements;        } */
/* 	template<integral type> inline constexpr auto base_vector<type,2>::end()    noexcept 	    -> type*        { return elements+size(); } */
/* 	template<integral type> inline constexpr auto base_vector<type,2>::end()    const noexcept -> const type* { return elements+size(); } */
/* 	template<integral type> inline constexpr auto base_vector<type,2>::cend()   const noexcept -> const type* { return elements+size(); } */

/* 	template<integral type> inline constexpr base_vector<type,2>::base_vector()                             noexcept = default; */
/* 	template<integral type> inline constexpr base_vector<type,2>::base_vector(const type& e)                noexcept : elements{e, e}           { } */
/* 	template<integral type> inline constexpr base_vector<type,2>::base_vector(const type& x, const type& y) noexcept : elements{x, y}           { } */
/* 	template<integral type> inline constexpr base_vector<type,2>::base_vector(const type val[2])            noexcept : elements{val[0], val[1]} { } */

/* /1* 	template<integral type> inline constexpr auto base_vector<type,3>::size()   const noexcept -> int         { return 3;               } *1/ */
/* /1* 	template<integral type> inline constexpr auto base_vector<type,3>::begin()        noexcept -> type*       { return elements;        } *1/ */
/* /1* 	template<integral type> inline constexpr auto base_vector<type,3>::begin()  const noexcept -> const type* { return elements;        } *1/ */
/* /1* 	template<integral type> inline constexpr auto base_vector<type,3>::cbegin() const noexcept -> const type* { return elements;        } *1/ */
/* /1* 	template<integral type> inline constexpr auto base_vector<type,3>::end()          noexcept -> type*       { return elements+size(); } *1/ */
/* /1* 	template<integral type> inline constexpr auto base_vector<type,3>::end()    const noexcept -> const type* { return elements+size(); } *1/ */
/* /1* 	template<integral type> inline constexpr auto base_vector<type,3>::cend()   const noexcept -> const type* { return elements+size(); } *1/ */

/* /1* 	template<integral type> inline constexpr base_vector<type,3>::base_vector()                                               noexcept = default; *1/ */
/* /1* 	template<integral type> inline constexpr base_vector<type,3>::base_vector(const type& e)                                  noexcept : elements{e, e, e}                { } *1/ */
/* /1* 	template<integral type> inline constexpr base_vector<type,3>::base_vector(const type& t0, const type& t1, const type& t2) noexcept : elements{t0, t1, t2}             { } *1/ */
/* /1* 	template<integral type> inline constexpr base_vector<type,3>::base_vector(const type val[3])                              noexcept : elements{val[0], val[1], val[2]} { } *1/ */
/* /1* 	template<integral type> inline constexpr base_vector<type,3>::base_vector(const base_vector<type,2>& vect, const type& z) noexcept : elements{vect.x, vect.y, z}      { } *1/ */

/* /1* 	template<integral type> inline constexpr auto base_vector<type,4>::size()   const noexcept -> int         { return 4;               } *1/ */
/* /1* 	template<integral type> inline constexpr auto base_vector<type,4>::begin()        noexcept -> type*       { return elements;        } *1/ */
/* /1* 	template<integral type> inline constexpr auto base_vector<type,4>::begin()  const noexcept -> const type* { return elements;        } *1/ */
/* /1* 	template<integral type> inline constexpr auto base_vector<type,4>::cbegin() const noexcept -> const type* { return elements;        } *1/ */
/* /1* 	template<integral type> inline constexpr auto base_vector<type,4>::end()          noexcept -> type*       { return elements+size(); } *1/ */
/* /1* 	template<integral type> inline constexpr auto base_vector<type,4>::end()    const noexcept -> const type* { return elements+size(); } *1/ */
/* /1* 	template<integral type> inline constexpr auto base_vector<type,4>::cend()   const noexcept -> const type* { return elements+size(); } *1/ */

/* /1* 	template<integral type> inline constexpr base_vector<type,4>::base_vector()                  noexcept = default; *1/ */
/* /1* 	template<integral type> inline constexpr base_vector<type,4>::base_vector(const type& e)     noexcept : elements{e, e, e, e}                     { } *1/ */
/* /1* 	template<integral type> inline constexpr base_vector<type,4>::base_vector(const type val[4]) noexcept : elements{val[0], val[1], val[2], val[3]} { } *1/ */

/* /1* 	template<integral type> inline constexpr base_vector<type,4>::base_vector(const type& t0, const type& t1, const type& t2, const type& t3) noexcept *1/ */
/* /1* 		: elements{t0, t1, t2, t3}             { } *1/ */
/* /1* 	template<integral type> inline constexpr base_vector<type,4>::base_vector(const base_vector<type,3>& vect, type w) noexcept *1/ */
/* /1* 		: elements{vect.x, vect.y, vect.z, w}  { } *1/ */
/* /1* 	template<integral type> inline constexpr base_vector<type,4>::base_vector(const base_vector<type,2>& lhs, const base_vector<type,2>& rhs) noexcept *1/ */
/* /1* 		: elements{lhs.x, lhs.y, rhs.x, rhs.y} { } *1/ */

/* } /1* end of namespace pgl *1/ */
