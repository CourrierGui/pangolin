#include <pgl-math/impl/vector.hpp>
/* #include <pgl-math/impl/base-vector.hpp> */

#include <pgl-math/utils.hpp>
#include <pgl-math/base-vector.hpp>
#include <pgl-math/vector.hpp>

//TODO add function template

/* template<template<typename T,uint32_t d> class vector_type, typename... Args> */
/* struct Declare { */

/* }; */

/* template<template<typename T,uint32_t d> class vector_type, typename type, typename... Args> */
/* struct Declare<vector_type, type, Args...> { */
/* 	using t2 = vector_type<type,2>; */
/* 	using t3 = vector_type<type,3>; */
/* 	using t4 = vector_type<type,4>; */
/* }; */

/* template struct Declare<pgl::vector, bool>; */

template struct pgl::base_vector<bool,2,pgl::vector>;
template struct pgl::base_vector<bool,3,pgl::vector>;
template struct pgl::base_vector<bool,4,pgl::vector>;

template struct pgl::base_vector<uint32_t,2,pgl::vector>;
template struct pgl::base_vector<uint32_t,3,pgl::vector>;
template struct pgl::base_vector<uint32_t,4,pgl::vector>;

template struct pgl::base_vector<int32_t,2,pgl::vector>;
template struct pgl::base_vector<int32_t,3,pgl::vector>;
template struct pgl::base_vector<int32_t,4,pgl::vector>;

template struct pgl::algebric_vector<int32_t,2,pgl::vector>;
template struct pgl::algebric_vector<int32_t,3,pgl::vector>;
template struct pgl::algebric_vector<int32_t,4,pgl::vector>;

/* template struct pgl::algebric_vector<uint32_t,2,pgl::vector>; */
/* template struct pgl::algebric_vector<uint32_t,3,pgl::vector>; */
/* template struct pgl::algebric_vector<uint32_t,4,pgl::vector>; */

template struct pgl::algebric_vector<float,2,pgl::vector>;
template struct pgl::algebric_vector<float,3,pgl::vector>;
template struct pgl::algebric_vector<float,4,pgl::vector>;

/* template struct pgl::vector<uint32_t,2>; */
/* template struct pgl::vector<uint32_t,3>; */
/* template struct pgl::vector<uint32_t,4>; */

template struct pgl::vector<bool,2>;
template struct pgl::vector<bool,3>;
template struct pgl::vector<bool,4>;

template struct pgl::vector<int32_t,2>;
template struct pgl::vector<int32_t,3>;
template struct pgl::vector<int32_t,4>;

template struct pgl::vector<float,2>;
template struct pgl::vector<float,3>;
template struct pgl::vector<float,4>;

template float pgl::dot<float, 3>(pgl::float3 const&, pgl::float3 const&);
template float pgl::dot<float, 3>(pgl::float3 const&);
template float pgl::sum<float, 3>(pgl::float3 const&);

template pgl::float3 pgl::normalize<float, 3>(pgl::float3 const&);
template pgl::float3 pgl::abs<float, 3>      (pgl::float3 const&);
