#include <pgl-test/checker.hpp>

#include <list>

float addf(float x,      float y     ) { return x + y; }
int   add (int x,        int y       ) { return x + y; }
int   mul (int& x,       int& y      ) { return x * y; }
int   sub (const int& x, const int& y) { return x - y; }

/* Stupid example but it's commutative */
std::vector<int> addv(const std::vector<int>& lhs, const std::vector<int>& rhs) {
	std::vector<int> min, max;
	if (lhs.size() == std::min(lhs.size(), rhs.size())) {
		min = lhs;
		max = rhs;
	} else {
		min = rhs;
		max = lhs;
	}

	auto res{min};
	auto it = res.begin();
	auto rit = max.begin();
	while (it != res.end() && rit != rhs.end()) {
		*(it++) += *(rit++);
	}
	return res;
}

/* Stupid example but it's commutative */
std::list<int> subl(const std::list<int>& lhs, const std::list<int>& rhs) {
	std::list<int> min, max;
	if (lhs.size() == std::min(lhs.size(), rhs.size())) {
		min = lhs;
		max = rhs;
	} else {
		min = rhs;
		max = lhs;
	}

	auto res{min};
	auto it = res.begin();
	auto rit = max.begin();
	while (it != res.end() && rit != rhs.end()) {
		*(it++) -= *(rit++);
	}
	return res;
}

int main()
{
	/*
	 * custom generator ? constraint on the generator ?
	 *
	 * constrain arguments like y = 2*x ? v1.size() == v2.size()
	 * checker.constraint() ???
	 *
	 * probably not a good idea
	 * check on destruction ?!?
	 */
	pgl::test::Checker add_commutative{std::function{pgl::test::is_commutative(add)}};
	add_commutative.is_trival([](int x, int y) { return x > y; }); // It's dumb but it works

	add_commutative.check("commutativity of add", 200);

	auto sub_commutative = pgl::test::make_checker(pgl::test::is_commutative(sub));
	sub_commutative.check("commutativity of sub");

	pgl::test::Checker<int&,int&> mul_commutative{pgl::test::is_commutative(mul)};
	mul_commutative.classify([](int& x, int& y) -> std::string {
		if (x < y) {
			return "x < y";
		} else if (x == y) {
			return "x == y";
		} else {
			return "x > y";
		}
	});
	mul_commutative.check("commutativity of mul", 200);

	pgl::test::Checker<int,int> addf_commutative{pgl::test::is_commutative(addf)};
	addf_commutative.check("commutativity of addf");

	pgl::test::Checker<int,int> addv_commutative{pgl::test::is_commutative(addf)};
	addv_commutative.check("commutativity of addf");

	pgl::test::Checker subl_commutative{std::function{pgl::test::is_commutative(subl)}};
	subl_commutative.check("commutativity of subl");

	return 0;
}
