/* #include <pgl-math/impl/vector.hpp> */
/* #include <pgl-math/impl/base-vector.hpp> */
#include <pgl-math/utils.hpp>
#include <pgl-math/base-vector.hpp>
#include <pgl-math/vector.hpp>

//TODO add function template

template struct pgl::base_vector<bool,2>;
template struct pgl::base_vector<bool,3>;
template struct pgl::base_vector<bool,4>;

template struct pgl::base_vector<unsigned int,2>;
template struct pgl::base_vector<unsigned int,3>;
template struct pgl::base_vector<unsigned int,4>;

template struct pgl::base_vector<int,2>;
template struct pgl::base_vector<int,3>;
template struct pgl::base_vector<int,4>;

template struct pgl::algebric_vector<int,2>;
template struct pgl::algebric_vector<int,3>;
template struct pgl::algebric_vector<int,4>;

template struct pgl::algebric_vector<unsigned int,2>;
template struct pgl::algebric_vector<unsigned int,3>;
template struct pgl::algebric_vector<unsigned int,4>;

template struct pgl::algebric_vector<float,2>;
template struct pgl::algebric_vector<float,3>;
template struct pgl::algebric_vector<float,4>;

template struct pgl::vector<unsigned int,2>;
template struct pgl::vector<unsigned int,3>;
template struct pgl::vector<unsigned int,4>;

template struct pgl::vector<bool,2>;
template struct pgl::vector<bool,3>;
template struct pgl::vector<bool,4>;

template struct pgl::vector<int,2>;
template struct pgl::vector<int,3>;
template struct pgl::vector<int,4>;

template struct pgl::vector<float,2>;
template struct pgl::vector<float,3>;
template struct pgl::vector<float,4>;
