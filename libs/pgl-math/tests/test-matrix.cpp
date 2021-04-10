#include <pgl-math/impl/matrix.hpp>
#include <pgl-math/impl/vector.hpp>
#include <pgl-math/impl/algorithms.hpp>

#include <glm/glm.hpp>
#include <glm/ext/matrix_transform.hpp>

#include <gtest/gtest.h>

/* template<pgl::number type, uint32_t rows, uint32_t size> */
/* void assert_equal( */
/*   const pgl::matrix<type,rows,size>& lhs, */
/*   const pgl::matrix<type,rows,size>& rhs) */
/* { */
/*   auto lhs_it = lhs.begin(); */
/*   auto rhs_it = rhs.begin(); */
/*   while (lhs_it!=lhs.end() && rhs_it!=rhs.end()) { */
/*     ASSERT_EQ(*(lhs_it++), *(rhs_it++)); */
/*   } */
/* } */

/* TEST(Matrix, Construction) { */
/*   pgl::int22 A{0}; */
/*   for (auto e: A.elements) { */
/*     ASSERT_EQ(0, e); */
/*   } */

/*   pgl::float44 B{ */
/*     0,  1,  2,  3, */
/*     4,  5,  6,  7, */
/*     8,  9, 10, 11, */
/*     12, 13, 14, 15 */
/*   }; */
/*   for (int i=0; i<4; ++i) { */
/*     ASSERT_EQ(i, B.elements[i]); */
/*   } */

/*   const unsigned int values[4] = {0, 1, 2, 3}; */
/*   pgl::uint22 expected_values{ */
/*     0, 1, */
/*     2, 3 */
/*   }; */
/*   assert_equal(expected_values, {values}); */


/*   pgl::matrix<int,2,3> col = pgl::matrix_from_col_vectors( */
/*     pgl::int2{0}, */
/*     pgl::int2{1}, */
/*     pgl::int2{2} */
/*     ); */
/*   pgl::matrix<int,2,3> expected_col{ */
/*     0, 1, 2, */
/*       0, 1, 2 */
/*   }; */
/*   assert_equal(expected_col, col); */

/*   pgl::matrix<int,2,3> row = pgl::matrix_from_row_vectors( */
/*     pgl::int3{1}, */
/*     pgl::int3{2} */
/*     ); */
/*   pgl::matrix<int,2,3> expected_row{ */
/*     1, 1, 1, */
/*       2, 2, 2 */
/*   }; */
/*   assert_equal(expected_row, row); */
/* } */

/* TEST(Matrix, Operations) { */
/*   pgl::float22 id{pgl::float22::identity()}; */
/*   pgl::float33 zero{pgl::float33::zeros()}; */
/*   assert_equal(id, id*id); */
/*   assert_equal(zero, zero*zero); */

/*   pgl::float22 lhs{1, 2, 3, 4}; */

/*   lhs *= pgl::float22{1, 1, 1, 1}; */
/*   assert_equal({3, 3, 7, 7}, lhs); */
/*   lhs = pgl::float22{1, 2, 3, 4}; */
/*   lhs += pgl::float22{1, 2, 3, 4}; */
/*   assert_equal({2, 4, 6, 8}, lhs); */
/*   lhs -= pgl::float22{1, 2, 3, 4}; */
/*   assert_equal({1, 2, 3, 4}, lhs); */
/*   lhs *= 2; */
/*   assert_equal({2, 4, 6, 8}, lhs); */
/*   lhs /= 2; */
/*   assert_equal({1, 2, 3, 4}, lhs); */
/*   lhs += 1; */
/*   assert_equal({2, 3, 4, 5}, lhs); */
/*   lhs -= 1; */
/*   assert_equal({1, 2, 3, 4}, lhs); */

/*   /1* assert_equal( *1/ */
/*   /1* 	{true, false, true, false}, *1/ */
/*   /1* 	lhs == pgl::float22{1, 3, 3, 3} *1/ */
/*   /1* ); *1/ */
/*   /1* assert_equal( *1/ */
/*   /1* 	{true, false, true, false}, *1/ */
/*   /1* 	lhs != pgl::float22{2, 2, 2, 4} *1/ */
/*   /1* ); *1/ */
/*   /1* assert_equal( *1/ */
/*   /1* 	{true, false, true, false}, *1/ */
/*   /1* 	lhs < pgl::float22{2, 2, 4, 4} *1/ */
/*   /1* ); *1/ */
/*   /1* assert_equal( *1/ */
/*   /1* 	{true, false, true, false}, *1/ */
/*   /1* 	lhs > pgl::float22{0, 2, 1, 4} *1/ */
/*   /1* ); *1/ */
/*   /1* assert_equal( *1/ */
/*   /1* 	{true, false, true, false}, *1/ */
/*   /1* 	lhs <= pgl::float22{1, 1, 3, 3} *1/ */
/*   /1* ); *1/ */
/*   /1* assert_equal( *1/ */
/*   /1* 	{true, false, true, false}, *1/ */
/*   /1* 	lhs >= pgl::float22{1, 3, 3, 5} *1/ */
/*   /1* ); *1/ */

/*   assert_equal( */
/*     pgl::float22{3, 3, 7, 7}, */
/*     pgl::float22{1, 2, 3, 4} * pgl::float22{1, 1, 1, 1} */
/*     ); */
/*   assert_equal( */
/*     pgl::float22{2, 3, 4, 5}, */
/*     pgl::float22{1, 1, 1, 1} + pgl::float22{1, 2, 3, 4} */
/*     ); */
/*   assert_equal( */
/*     pgl::float22{1, 2, 3, 4}, */
/*     pgl::float22{2, 3, 4, 5} - pgl::float22{1, 1, 1, 1} */
/*     ); */

/*   assert_equal( */
/*     pgl::float22{2, 4, 6, 8}, */
/*     pgl::float22{1, 2, 3, 4} * 2 */
/*     ); */
/*   assert_equal( */
/*     pgl::float22{1, 2, 3, 4}, */
/*     pgl::float22{2, 4, 6, 8} / 2 */
/*     ); */
/*   assert_equal( */
/*     pgl::float22{4, 5, 6, 7}, */
/*     pgl::float22{2, 3, 4, 5} + 2 */
/*     ); */
/*   assert_equal( */
/*     pgl::float22{-1, 0, 1, 2}, */
/*     pgl::float22{ 1, 2, 3, 4 } - 2 */
/*     ); */

/*   assert_equal( */
/*     pgl::float22{2, 4, 6, 8}, */
/*     2 * pgl::float22{1, 2, 3, 4} */
/*     ); */
/*   assert_equal( */
/*     pgl::float22{1, 2, 4, 8}, */
/*     8 / pgl::float22{8, 4, 2, 1} */
/*     ); */
/*   assert_equal( */
/*     pgl::float22{4, 5, 6, 7}, */
/*     2 + pgl::float22{2, 3, 4, 5} */
/*     ); */
/*   assert_equal( */
/*     pgl::float22{-1, 0, 1, 2}, */
/*     2 - pgl::float22{ 1, 2, 3, 4 } */
/*     ); */
/* } */

/* TEST(Matrix, Getters) { */
/*   pgl::int33 mat{ */
/*     0, 1, 2, */
/*       3, 4, 5, */
/*       6, 7, 8 */
/*   }; */

/*   ASSERT_EQ(2, mat.at(0, 2)); */
/*   ASSERT_EQ(4, mat.at(1, 1)); */
/*   ASSERT_EQ(7, mat.at(2, 1)); */

/*   pgl::int3 row{mat.row(1)}; */
/*   ASSERT_EQ(3, row.x); */
/*   ASSERT_EQ(4, row.y); */
/*   ASSERT_EQ(5, row.z); */

/*   pgl::int3 col{mat.col(2)}; */
/*   ASSERT_EQ(2, col.x); */
/*   ASSERT_EQ(5, col.y); */
/*   ASSERT_EQ(8, col.z); */
/* } */

/* TEST(Matrix, MakerFunctions) { */
/*   pgl::uint33 id{ */
/*     1, 0, 0, */
/*       0, 1, 0, */
/*       0, 0, 1 */
/*   }; */
/*   assert_equal(id, pgl::uint33::identity()); */

/*   pgl::int22 zero = { */
/*     0, 0, */
/*     0, 0 */
/*   }; */
/*   assert_equal(zero, pgl::int22::zeros()); */

/*   pgl::float33 one{ */
/*     1, 1, 1, */
/*       1, 1, 1, */
/*       1, 1, 1 */
/*   }; */
/*   assert_equal(one, pgl::float33::ones()); */
/* } */

/* TEST(Matrix, Transformations) { */
/*   //TODO inverse */

/*   pgl::uint44 mat{ */
/*     0,  1,  2,  3, */
/*       4,  5,  6,  7, */
/*       8,  9, 10, 11, */
/*       12, 13, 14, 15 */
/*   }; */
/*   pgl::uint44 expected_tr{ */
/*     0, 4,  8, 12, */
/*       1, 5,  9, 13, */
/*       2, 6, 10, 14, */
/*       3, 7, 11, 15 */
/*   }; */
/*   assert_equal(expected_tr, pgl::transpose(mat)); */
/* } */

/* TEST(Matrix, Properties) { */
/*   pgl::float44 mat{ */
/*     0,  1,  2,  3, */
/*       4,  5,  6,  7, */
/*       8,  9, 10, 11, */
/*       12, 13, 14, 15 */
/*   }; */
/*   ASSERT_EQ(30, pgl::trace(mat)); */
/*   //TODO determinant */
/* } */

/* TEST(Matrix, Geometry) { */
/*   glm::vec3 glm_camera = {0.0, 0.0, 0.0}; */
/*   glm::vec3 glm_target = {0.0, 0.0, 0.0}; */
/*   glm::vec3 glm_up = {0.0, 0.0, 0.0}; */
/*   auto expected_mat = glm::lookAt(glm_camera, glm_target, glm_up); */

/*   pgl::float3 pgl_camera = {0.0, 0.0, 0.0}; */
/*   pgl::float3 pgl_target = {0.0, 0.0, 0.0}; */
/*   pgl::float3 pgl_up = {0.0, 0.0, 0.0}; */
/*   auto mat = pgl::look_at(pgl_camera, pgl_target, pgl_up); */
/* } */
