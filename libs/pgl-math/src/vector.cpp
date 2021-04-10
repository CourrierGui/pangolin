#include <pgl-math/utils.hpp>

#include <pgl-math/impl/base-vector.hpp>
#include <pgl-math/impl/algebric-vector.hpp>
#include <pgl-math/impl/vector.hpp>
#include <pgl-math/impl/matrix.hpp>
#include <pgl-math/impl/algorithms.hpp>

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

template float pgl::dot<float,3>(pgl::float3 const&, pgl::float3 const&);
template float pgl::dot<float,3>(pgl::float3 const&);
template float pgl::sum<float,3>(pgl::float3 const&);

template pgl::float3 pgl::normalize<float, 3>(pgl::float3 const&);
template pgl::float3 pgl::abs<float, 3>(pgl::float3 const&);
template pgl::float3 pgl::cross<float>(pgl::float3 const&, pgl::float3 const&);

template pgl::float3 pgl::operator+(const pgl::float3&, const pgl::float3&);
template pgl::float3 pgl::operator+(const float&, const pgl::float3&);

template pgl::float3 pgl::operator-(const pgl::float3&, const pgl::float3&);
template pgl::float3 pgl::operator-(const float&, const pgl::float3&);

template pgl::float3 pgl::operator*(const pgl::float3&, const pgl::float3&);
template pgl::float3 pgl::operator*(const float&, const pgl::float3&);

template pgl::float3 pgl::operator/(const pgl::float3&, const pgl::float3&);
template pgl::float3 pgl::operator/(const float&, const pgl::float3&);

template pgl::float4 pgl::operator+(const pgl::float4&, const pgl::float4&);
template pgl::float4 pgl::operator+(const float&, const pgl::float4&);

template pgl::float4 pgl::operator-(const pgl::float4&, const pgl::float4&);
template pgl::float4 pgl::operator-(const float&, const pgl::float4&);

template pgl::float4 pgl::operator*(const pgl::float4&, const pgl::float4&);
template pgl::float4 pgl::operator*(const float&, const pgl::float4&);

template pgl::float4 pgl::operator/(const pgl::float4&, const pgl::float4&);
template pgl::float4 pgl::operator/(const float&, const pgl::float4&);

template struct pgl::matrix<int, 1, 1>;
template struct pgl::matrix<int, 1, 2>;
template struct pgl::matrix<int, 1, 3>;
template struct pgl::matrix<int, 1, 4>;

template struct pgl::matrix<int, 2, 1>;
template struct pgl::matrix<int, 2, 2>;
template struct pgl::matrix<int, 2, 3>;
template struct pgl::matrix<int, 2, 4>;

template struct pgl::matrix<int, 3, 1>;
template struct pgl::matrix<int, 3, 2>;
template struct pgl::matrix<int, 3, 3>;
template struct pgl::matrix<int, 3, 4>;

template struct pgl::matrix<int, 4, 1>;
template struct pgl::matrix<int, 4, 2>;
template struct pgl::matrix<int, 4, 3>;
template struct pgl::matrix<int, 4, 4>;

template pgl::matrix<float,4,4> pgl::translate<float>(
  pgl::matrix<float,4,4> const&,
  pgl::vector<float,3> const&);
