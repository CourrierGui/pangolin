#include <pgl-test/checker.hpp>

#include <list>

float add(float x,      float y     ) { return x + y; }
int   add(int x,        int y       ) { return x + y; }
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

class adder {
  private:
    int c;
  public:
    adder(int c) : c{c} {  }
    int add(int x) {
      return x + c;
    }
};

namespace pglt = pgl::test;

int main() {
  /*
   * custom generator ? constraint on the generator ?
   *
   * constrain arguments like y = 2*x ? v1.size() == v2.size()
   * checker.constraint() ???
   *
   * probably not a good idea
   * check on destruction ?!?
   */

  auto add_commutative = pglt::is_commutative((int(*)(int,int))add);
  // It's dumb but it works
  add_commutative.is_trival([](int x, int y) { return x > y; });

  add_commutative.check("add is commutative", 200);

  auto addf_commutative = pglt::is_commutative((float(*)(float,float))add);
  addf_commutative.check("addf is commutative");

  auto sub_commutative = pglt::is_commutative(sub);
  sub_commutative.check("sub is commutative");

  auto mul_commutative = pglt::is_commutative(mul);
  mul_commutative.classify([](int& x, int& y) -> std::string {
    if (x < y) {
      return "x < y";
    } else if (x == y) {
      return "x == y";
    } else {
      return "x > y";
    }
  });
  mul_commutative.check("mul is commutative", 200);

  auto addv_commutative = pglt::is_commutative(addv);
  addv_commutative.check("addv is commutative");

  auto subl_commutative = pglt::is_commutative(subl);
  subl_commutative.check("subl is commutative");

  pglt::check("adder is commutative",
              [](int x, int y) {
                return adder{x}.add(y) == adder{y}.add(x);
              });

  return 0;
}
