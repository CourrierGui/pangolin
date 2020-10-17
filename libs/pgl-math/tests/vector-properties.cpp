#include <pgl-test/checker.hpp>

#include <pgl-math/base-vector.hpp>
#include <pgl-math/vector.hpp>
#include <pgl-math/algorithms.hpp>
#include <pgl-math/matrix.hpp>

#include <glm/glm.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

template<typename type>
auto multiplication_by_0(type x, type y, type z, type w)
	-> bool
{
	pgl::vector<type,2> f2{x, y};
	pgl::vector<type,3> f3{x, y, z};
	pgl::vector<type,4> f4{x, y, z, w};

	return pgl::all(pgl::vector<type,2>{0, 0}       == f2      * type{0})
			&& pgl::all(pgl::vector<type,2>{0, 0}       == type{0} * f2     )
			&& pgl::all(pgl::vector<type,3>{0, 0, 0}    == f3      * type{0})
			&& pgl::all(pgl::vector<type,3>{0, 0, 0}    == type{0} * f3     )
			&& pgl::all(pgl::vector<type,4>{0, 0, 0, 0} == f4      * type{0})
			&& pgl::all(pgl::vector<type,4>{0, 0, 0, 0} == type{0} * f4     );
}

template<typename type>
auto multiplication_by_1(type x, type y, type z, type w)
	-> bool
{
	pgl::vector<type,2> f2{x, y};
	pgl::vector<type,3> f3{x, y, z};
	pgl::vector<type,4> f4{x, y, z, w};

	return pgl::all(f2 == f2 * type{0}) && pgl::all(f2 == type{0} * f2)
			&& pgl::all(f3 == f3 * type{0}) && pgl::all(f3 == type{0} * f3)
			&& pgl::all(f4 == f4 * type{0}) && pgl::all(f4 == type{0} * f4);
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

bool approximatelyEqual(double a, double b, double epsilon) {
	return (std::abs(a - b) <= (std::max(std::abs(a), std::abs(b)) * epsilon));
}

bool approximatelyEqualAbsRel(double a, double b, double absEpsilon, double relEpsilon) {
	// Check if the numbers are really close -- needed when comparing numbers near zero.
	double diff{ std::abs(a - b) };
	if (diff <= absEpsilon)
		return true;

	// Otherwise fall back to Knuth's algorithm
	return (diff <= (std::max(std::abs(a), std::abs(b)) * relEpsilon));
}

int main() {
	/* check_multiplication<float>  (); */
	/* check_multiplication<double> (); */
	/* check_multiplication<int16_t>(); */
	/* check_multiplication<int32_t>(); */
	/* check_multiplication<int64_t>(); */

	auto check_norm = pgl::test::make_checker(
		[](float x) -> bool {
			return pgl::norm(pgl::float3{x, 0, 0}) == std::abs(x)
					&& pgl::norm(pgl::float3{0, x, 0}) == std::abs(x)
					&& pgl::norm(pgl::float3{0, 0, x}) == std::abs(x);
		});
	check_norm.check("norm of vector colinear to unit");

	auto check_norm_positivity = pgl::test::make_checker(
		[](const pgl::float3& x) -> bool {
			if (pgl::norm(x) > 0.0f) {
				return pgl::any(x != pgl::float3{0.0f});

			} else if (pgl::norm(x) == 0.0f) {
				return pgl::all(x == pgl::float3{0.0f});

			} else {
				return false;
			}
		});
	check_norm_positivity.check("norm positivity");

	auto check_norm_prop = pgl::test::make_checker(
		[](const pgl::float3& x, float k) -> bool {
			return approximatelyEqual(std::abs(k)*pgl::norm(x), pgl::norm(k*x), 1e-6);
		});
	check_norm_prop.check("norm proportionality", 100);

	auto check_norm_inequality = pgl::test::make_checker(
		[](const pgl::float3& x, const pgl::float3& y) -> bool {
			return pgl::norm(x + y) <= pgl::norm(x) + pgl::norm(y);
		});
	check_norm_inequality.check("norm inequality");

	auto check_normalize = pgl::test::make_checker(
		[](const pgl::float3& vect) -> bool {
			return approximatelyEqual(pgl::norm(pgl::normalize(vect)), 1.0f, 1e-6);
		});
	check_normalize.check("norm of normalized vector is 1");

	auto check_look_at = pgl::test::make_checker(
		[](const pgl::float3& camera, const pgl::float3& target)
		-> bool
		{
			auto up = pgl::float3{0, 0, 1};
			auto pgl_mat = pgl::look_at(camera, target, up);
			auto glm_mat = glm::lookAt(
				glm::vec3{camera.x, camera.y, camera.z},
				glm::vec3{target.x, target.y, target.z},
				glm::vec3{up.x, up.y, up.z}
			);
			auto glm_it = glm::value_ptr(glm_mat);
			bool res = true;
			for (const auto& pgl_elem: pgl_mat) {
				res &= (approximatelyEqualAbsRel(pgl_elem, *(glm_it++), 1e-5, 1e-5));
			}
			return res;
		}
	);
	check_look_at.check("look_at function");

	auto check_ortho = pgl::test::make_checker(
		[](float left, float right, float bottom, float top)
		-> bool
		{
			auto pgl_mat = pgl::ortho(left, right, bottom, top);
			auto glm_mat = glm::ortho(left, right, bottom, top);
			auto glm_it = glm::value_ptr(glm_mat);
			bool res = true;
			for (const auto& pgl_elem: pgl_mat) {
				res &= (approximatelyEqualAbsRel(pgl_elem, *(glm_it++), 1e-5, 1e-5));
			}
			return res;
		}
	);
	check_ortho.check("ortho function");

	auto check_ortho2 = pgl::test::make_checker(
		[](float left, float right, float bottom, float top, float zNear, float zFar)
		-> bool
		{
			auto pgl_mat = pgl::ortho(left, right, bottom, top, zNear, zFar);
			auto glm_mat = glm::ortho(left, right, bottom, top, zNear, zFar);
			auto glm_it = glm::value_ptr(glm_mat);
			bool res = true;
			for (const auto& pgl_elem: pgl_mat) {
				res &= (approximatelyEqualAbsRel(pgl_elem, *(glm_it++), 1e-5, 1e-5));
			}
			return res;
		}
	);
	check_ortho2.check("ortho2 function");

	return 0;
}
