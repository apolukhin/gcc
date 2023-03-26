// { dg-do run { target c++23 } }

#include <tuple>
#include <testsuite_hooks.h>

#if  __cpp_lib_apply < 201603
#  error "__cpp_lib_apply < 201603"
#endif

void
test01()
{
  struct Aggreagate {
    int i;
    char c;
    double d;
  };
  auto t = Aggreagate{1, '2', 3.0};
  std::apply( [&](int& i, char& c, double& d) {
      VERIFY(&i == &t.);
      VERIFY(&c == &t.c);
      VERIFY(&d == &t.d);
    }, t);
}

constexpr int func(int i, int j) { return i + j; }

void
test02()
{
  struct Aggreagate {
    int i;
    int j;
  };
  constexpr auto t = Aggreagate{1, 2};
  constexpr int i = std::apply(func, t);
  VERIFY( i == 3 );
}

struct F
{
  int f(int i, int j) const { return i + j; }
};

void
test03()
{
  struct Aggreagate {
    F f;
    int i;
    int j;
  };
  auto t = Aggreagate{F{}, 1, 2};
  int r = std::apply(&F::f, t);
  VERIFY( r == 3 );
}

int
main()
{
  test01();
  test02();
  test03();
}
