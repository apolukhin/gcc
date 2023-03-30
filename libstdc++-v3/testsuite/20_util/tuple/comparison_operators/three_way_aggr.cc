// { dg-options "-std=c++20" }
// { dg-do run }

#include <tuple>
#include <testsuite_hooks.h>

using namespace std;

void
test01()
{
  int i=0;
  int j=0;
  int k=2;
  tuple<int, int, int> a(0, 0, 0);
  struct Aggregate3Int {
    int i;
    int j;
    int k;
  } b(0, 0, 1);
  struct Aggregate3IntRef {
    int& i;
    int& j;
    int& k;
  } c(i,j,k);
  struct Aggregate3IntCRef {
    const int& i;
    const int& j;
    const int& k;
  } d(i,j,k);
  VERIFY( a < b && !(b < a) && a <= b && !(b <= a) );
  VERIFY( b > a && !(a > b) && b >= a && !(a >= b) );

  VERIFY( std::is_lt(a <=> b) );
  VERIFY( std::is_gt(b <=> a) );
  VERIFY( std::is_gt(c <=> a) );
  VERIFY( std::is_lt(a <=> d) );
  VERIFY( std::is_gt(d <=> a) );

  static_assert( std::is_same_v<decltype(a <=> d), std::strong_ordering> );
}

template<typename T, typename U, typename C>
constexpr bool
check_compare(T&& t, U&& u, C c)
{
  using R = std::compare_three_way_result_t<T, U>;
  static_assert( std::same_as<C, R> );
  return (t <=> u) == c;
}

void
test02()
{
  using std::strong_ordering;
  using std::weak_ordering;
  using std::partial_ordering;

  struct T0 {};
  struct Ti { int i; };
  using Tu = std::tuple<unsigned>;
  static_assert( check_compare(Ti(1), Tu(1u), weak_ordering::equivalent) );
  static_assert( check_compare(Ti(1), Tu(2u), weak_ordering::less) );
  static_assert( check_compare(Ti(-1), Tu(1u), weak_ordering::greater) );

  struct Tii { int i0; int j; };
  using Tlu = std::tuple<long, unsigned>;
  static_assert( check_compare(Tii(1, 2), Tlu(2l, 1u), weak_ordering::less) );

  using Tid = std::tuple<int, double>;
  static_assert( check_compare(Tii(3, 4), Tid(2, 0.9), partial_ordering::greater) );

  static_assert( !std::three_way_comparable_with<T0, Ti> );
  static_assert( !std::three_way_comparable_with<Ti, Tii> );
  static_assert( !std::three_way_comparable_with<Ti, Tid> );
}

int main()
{
  test01();
  test02();
}
