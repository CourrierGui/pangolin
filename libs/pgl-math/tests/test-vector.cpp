#include <gtest/gtest.h>

#include <pgl-math/vector.hpp>

template<pgl::number type, int dim>
void assert_equal(
	const pgl::vector<type,dim>& lhs,
	const pgl::vector<type,dim>& rhs)
{
	auto lhs_it = lhs.begin();
	auto rhs_it = rhs.begin();

	while (lhs_it != lhs.end()) {
		ASSERT_EQ(*(lhs_it++), *(rhs_it++));
	}
}

TEST(Vector, Construction) {
	pgl::int3 i1{1, 2, 3};
	ASSERT_EQ(1, i1.x);
	ASSERT_EQ(2, i1.y);
	ASSERT_EQ(3, i1.z);

	pgl::vector<int,7> i2{1, 2, 3, 4, 5, 6, 7};
	int i=1;
	for(auto elem: i2) {
		ASSERT_EQ(i++, elem);
	}

	pgl::int3 i3{4};
	assert_equal(pgl::int3{4, 4, 4}, i3);

	int values[4] = {1, 2, 3, 4};
	pgl::int4 i4{values};
	assert_equal(pgl::int4{1, 2, 3, 4}, i4);

	pgl::int4 i5{
		pgl::int2{1, 2},
		pgl::int2{3, 4}
	};
	assert_equal(pgl::int4{1, 2, 3, 4}, i5);

	pgl::int4 i6{ pgl::int3{1, 2, 3}, 4 };
	assert_equal(pgl::int4{1, 2, 3, 4}, i6);

	pgl::int3 i7{ pgl::int2{1, 2}, 3 };
	assert_equal(pgl::int3{1, 2, 3}, i7);
}

TEST(Vector, Makers) {
	assert_equal(pgl::int2{ 1,  0}, pgl::int2::right());
	assert_equal(pgl::int2{-1,  0}, pgl::int2::left() );
	assert_equal(pgl::int2{ 0,  1}, pgl::int2::up()   );
	assert_equal(pgl::int2{ 0, -1}, pgl::int2::down() );

	assert_equal(pgl::int3{ 1,  0,  0}, pgl::int3::right());
	assert_equal(pgl::int3{-1,  0,  0}, pgl::int3::left() );
	assert_equal(pgl::int3{ 0,  1,  0}, pgl::int3::up()   );
	assert_equal(pgl::int3{ 0, -1,  0}, pgl::int3::down() );
	assert_equal(pgl::int3{ 0,  0,  1}, pgl::int3::front());
	assert_equal(pgl::int3{ 0,  0, -1}, pgl::int3::back() );
}

TEST(Vector, Operators) {
	pgl::float3 a{1, 2, 3}, b{1, 2, 3};

	assert_equal({1, 4, 9}, a*b);
	assert_equal({2, 4, 6}, a*2);
	assert_equal({2, 4, 6}, 2*a);

	a = pgl::float3{8, 4, 2};
	b = pgl::float3{8, 4, 2};
	assert_equal({1, 1, 1}, a/b);
	assert_equal({4, 2, 1}, a/2);
	assert_equal({1, 2, 4}, 8/a);

	a = pgl::float3{1, 2, 3};
	b = pgl::float3{2, 2, 2};
	assert_equal({-1, 0, 1}, a-b);
	assert_equal({-1, 0, 1}, a-2);
	assert_equal({ 7, 6, 5}, 8-a);

	a = pgl::float3{1, 2, 3};
	b = pgl::float3{2, 2, 2};
	assert_equal({3,  4,  5}, a+b);
	assert_equal({3,  4,  5}, a+2);
	assert_equal({9, 10, 11}, 8+a);
}

TEST(Vector, UtilityFunctions) {
	pgl::float3 f1{1, 2, 3};

	ASSERT_EQ(14, pgl::dot(f1, f1));
	ASSERT_EQ(14, pgl::dot(f1));
	ASSERT_EQ(6,  pgl::sum(f1));

	assert_equal(pgl::float3{1.0/6, 2.0/6, 3.0/6}, pgl::normalize(f1));
	ASSERT_EQ(3, pgl::max(f1));
	ASSERT_EQ(1, pgl::min(f1));
	assert_equal({1, 2, 3}, pgl::abs(pgl::float3{-1, -2, 3}));

	assert_equal({true, false, true}, pgl::float3{0, 2, 0} <  f1);
	assert_equal({true, false, true}, pgl::float3{2, 2, 4} >  f1);
	assert_equal({true, false, true}, pgl::float3{1, 3, 3} <= f1);
	assert_equal({true, false, true}, pgl::float3{1, 1, 3} >= f1);
	assert_equal({true, false, true}, pgl::float3{1, 1, 3} == f1);
	assert_equal({true, false, true}, pgl::float3{2, 2, 2} != f1);

	ASSERT_EQ(1, f1.x); ASSERT_EQ(3, f1.z);
	float& x = pgl::min_element(f1);
	float& z = pgl::max_element(f1);
	x = 2; ASSERT_EQ(2, x);
	z = 2; ASSERT_EQ(2, z);
}
