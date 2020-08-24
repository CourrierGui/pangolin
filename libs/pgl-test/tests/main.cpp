#include <iostream>

#include <pgl-test/test.hpp>

class Adder {
	private:
		int constant;

	public:
		Adder() = default;
		Adder(int c) : constant(c) {  }
		int add(int val) const { return constant + val; }
		int get() const { return constant; }
};

Adder make_adder(int c) {
	return Adder{c};
}

int add(int x, int y) {
	return x + y;
}

bool commutative_property(int x, int y) {
	return add(x, y) == add(y, x);
}

bool adder_add_zero(const Adder& a, int y) {
	return a.add(0) == a.get();
}

struct S {
	bool operator()(const Adder& a, int x) {
		return a.add(0) == a.get();
	}
};

struct T {
	bool operator()(int x, int y) {
		return add(x, 0) == x && add(0, y) == y;
	}
};

int main() {
	std::clog
		<< pgl::test::function_property(add, commutative_property)
		<< '\n'
		<< pgl::test::function_property(add, [](int x, int y){ return add(x,0) == x && add(0, y) == y; })
		<< '\n'
		<< pgl::test::function_property(add, T())
		<< '\n'
		<< pgl::test::function_property(make_adder, &Adder::add, adder_add_zero)
		<< '\n'
		<< pgl::test::function_property(make_adder, &Adder::add, [](const Adder& a, int x) { return a.add(0)==a.get(); })
		<< '\n'
		<< pgl::test::function_property(make_adder, &Adder::add, S())
		<< '\n';

	return 0;
}
