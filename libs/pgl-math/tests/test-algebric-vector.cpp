#include <gtest/gtest.h>

#include <pgl-math/impl/algebric-vector.hpp>
#include <pgl-math/impl/base-vector.hpp>

#include <cmath>

template<pgl::integral type, pgl::length dim>
struct vector : public pgl::algebric_vector<type,dim,vector> {
  inline constexpr vector(std::convertible_to<type> auto ... args) noexcept
    : pgl::algebric_vector<type,dim,vector>{ args... }
  {

  }
};

template<pgl::integral type, uint32_t dim>
void assert_equal(
  const vector<type,dim>& lhs,
  const vector<type,dim>& rhs)
{
  auto lhs_it = lhs.begin();
  auto rhs_it = rhs.begin();

  while (lhs_it != lhs.end()) {
    ASSERT_EQ(*(lhs_it++), *(rhs_it++));
  }
}

TEST(AlgebricVector, Construction) {
  vector<int32_t,2> i2{1, 2};
  vector<int32_t,3> i3{1, 2, 3};
  vector<int32_t,4> i4{1, 2, 3, 4};
  vector<int32_t,5> i5{1, 2, 3, 4, 5};

  assert_equal(vector<int32_t,2>{1, 2},          i2);
  assert_equal(vector<int32_t,3>{1, 2, 3},       i3);
  assert_equal(vector<int32_t,4>{1, 2, 3, 4},    i4);
  assert_equal(vector<int32_t,5>{1, 2, 3, 4, 5}, i5);

  ASSERT_EQ(1, i2.x);
  ASSERT_EQ(2, i2.y);

  ASSERT_EQ(1, i3.x);
  ASSERT_EQ(2, i3.y);
  ASSERT_EQ(3, i3.z);

  ASSERT_EQ(1, i4.x);
  ASSERT_EQ(2, i4.y);
  ASSERT_EQ(3, i4.z);
  ASSERT_EQ(4, i4.w);
}
