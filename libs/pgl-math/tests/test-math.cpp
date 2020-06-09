#include <gtest/gtest.h>

#include <pgl-math/vector.hpp>

template<int size>
void assert_same_values(const pgl::Vector<int,size>& vec, int val) noexcept {
	for (auto elem: vec.elements)
		ASSERT_EQ(elem, val);
}

template<int size>
void assert_same_values(const pgl::Vector<float,size>& vec, float val) noexcept {
	for (auto elem: vec.elements)
		ASSERT_FLOAT_EQ(elem, val);
}

class VectorTest : public testing::Test {
	protected:
		void SetUp() override {
			i2 = pgl::int2(2);
			ii2 = pgl::int2(3);

			i3 = pgl::int3(3);
			ii3 = pgl::int3(4);

			i4 = pgl::int4(4);
			ii4 = pgl::int4(5);

			f3 = pgl::float3(1.0);
			ff3 = pgl::float3(2.0);
		}

		void TearDown() override {

		}

		pgl::int2 i2, ii2;
		pgl::int3 i3, ii3;
		pgl::int4 i4, ii4;
		pgl::float3 f3, ff3;
};

TEST_F(VectorTest, Construction) {
	ASSERT_EQ(i2.x+1, ii2.x);
	ASSERT_EQ(i2.y+1, ii2.y);
}

TEST_F(VectorTest, Math) {
	ASSERT_EQ(dot(i2, ii2), 12);
	ASSERT_EQ(dot(i3), 27);

	ASSERT_FLOAT_EQ(sum(f3), 3.0);
	ff3 = pgl::normalize(f3);
	for (auto elem: ff3.elements)
		ASSERT_FLOAT_EQ(elem, 1.0/3.0);
}

TEST_F(VectorTest, Operators) {
	pgl::int3 i = i3 + ii3;
	assert_same_values(i, 7);
	i = i + 1;
	assert_same_values(i, 8);
	i = 1 + i + 1;
	assert_same_values(i, 10);

	i = ii3 - i3;
	assert_same_values(i, 1);
	i = ii3 - 1;
	assert_same_values(i, 3);
	i = 1 - ii3;
	assert_same_values(i, -3);

	pgl::float3 f = f3/ff3;
	assert_same_values(f, 0.5f);

	i = ii3 * 3;
	assert_same_values(i, 12);
	i = 2 * ii3 * 3;
	assert_same_values(i, 24);
	i = ii3 * i3;
	assert_same_values(i, 12);
	f = f3 * ff3;
	assert_same_values(f, 2.0f);
}

TEST_F(VectorTest, UtilityFunctions) {
	pgl::int3 i(5, 3, 7);
	int max = pgl::max(i);
	ASSERT_EQ(max, 7);
	int min = pgl::min(i);
	ASSERT_EQ(min, 3);

	pgl::float4 f(-1.0f, 2.0f, -0.4f, 0.1f);
	f = pgl::abs(f);
	ASSERT_FLOAT_EQ(f.x, 1.0f);
	ASSERT_FLOAT_EQ(f.y, 2.0f);
	ASSERT_FLOAT_EQ(f.z, 0.4f);
	ASSERT_FLOAT_EQ(f.w, 0.1f);
}
