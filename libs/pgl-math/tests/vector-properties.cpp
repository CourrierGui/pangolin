#include <pgl-test/checker.hpp>
#include <pgl-math/base-vector.hpp>
#include <pgl-math/vector.hpp>
#include <pgl-math/algorithms.hpp>

template<typename type>
auto multiplication_by_0(type x, type y, type z, type w)
	-> bool
{
	pgl::vector<type,2> f2{x, y};
	pgl::vector<type,3> f3{x, y, z};
	pgl::vector<type,4> f4{x, y, z, w};

	return pgl::all(pgl::vector<type,2>{0, 0}       == f2 * 0) && pgl::all(pgl::vector<type,2>{0, 0}       == 0 * f2)
			&& pgl::all(pgl::vector<type,3>{0, 0, 0}    == f3 * 0) && pgl::all(pgl::vector<type,3>{0, 0, 0}    == 0 * f3)
			&& pgl::all(pgl::vector<type,4>{0, 0, 0, 0} == f4 * 0) && pgl::all(pgl::vector<type,4>{0, 0, 0, 0} == 0 * f4);
}

template<typename type>
auto multiplication_by_1(type x, type y, type z, type w)
	-> bool
{
	pgl::vector<type,2> f2{x, y};
	pgl::vector<type,3> f3{x, y, z};
	pgl::vector<type,4> f4{x, y, z, w};

	return pgl::all(f2 == f2 * 1) && pgl::all(f2 == 1 * f2)
			&& pgl::all(f3 == f3 * 1) && pgl::all(f3 == 1 * f3)
			&& pgl::all(f4 == f4 * 1) && pgl::all(f4 == 1 * f4);
}

template<typename type>
auto is_commutative(
	type x1, type y1, type z1, type w1,
	type x2, type y2, type z2, type w2)
	-> bool
{
	pgl::vector<type,2> f21{x1, y1}, f22{x2, y2};
	pgl::vector<type,3> f31{x1, y1, z1}, f32{x2, y2, z2};
	pgl::vector<type,4> f41{x1, y1, z1, w1}, f42{x2, y2, z2, w2};

	return pgl::all(f21 * f22 == f22 * f21)
			&& pgl::all(f31 * f32 == f32 * f31)
			&& pgl::all(f41 * f42 == f42 * f41);
}

template<typename type>
void check_multiplication() {
	auto multiplication_by_1_checker = pgl::test::make_checker(multiplication_by_1<type>);
	multiplication_by_1_checker.check("multiplication by 1 is constant");

	auto multiplication_by_0_checker = pgl::test::make_checker(multiplication_by_0<type>);
	multiplication_by_0_checker.check("multiplication by 0 is null");

	auto multiplication_is_commutative = pgl::test::make_checker(is_commutative<type>);
	multiplication_is_commutative.check("multiplication is commutative");
}

int main() {
	check_multiplication<float>  ();
	check_multiplication<double> ();
	check_multiplication<int16_t>();
	check_multiplication<int32_t>();
	check_multiplication<int64_t>();

	return 0;
}
