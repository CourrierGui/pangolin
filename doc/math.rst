Math Library (pgl-math)
#######################

Concepts
********

pgl::base_vector
****************

The `base_vector` templates is a static array that can contain elements
following the concept `pgl::integral` and of size `dim`. This is the basis of
every numeric container in **pgl::math**. The code sample bellow demonstrates
how to use it simply:

.. code:: c++

   template<pgl::integral type, pgl::length dim>
   struct vector : public pgl::base_vector<type, dim, vector> {
       constexpr vector(std::convertible_to<type> auto ... args) noexcept :
           pgl::base_vector<type, dim, vector>{ args... }
       {
       }
   };


This template is specialized for small values of `dim` (e.g `2`, `3` and `4`):

.. code:: cpp

   int main()
   {
       vector<int, 4> v4{1, 2, 3, 4};

       assert(v4.x == 1);
       assert(v4.y == 2);
       assert(v4.z == 3);
       assert(v4.w == 4);
   }


pgl::algebric_vector
********************

pgl::vector
***********

pgl::quaternion
***************


