// { dg-options "-std=c++20" }
// { dg-do run }

// Verify that std::get works the same way as std::get for tuples.

#include <tuple>
#include <utility>

#include <testsuite_hooks.h>

template <class T, class U>
void test_get_2(T x, U y) {
  VERIFY(std::get<0>(x) == std::get<0>(y));
  VERIFY(std::get<1>(x) == std::get<1>(y));
  VERIFY(std::get<0>(std::as_const(x)) == std::get<0>(y));
  VERIFY(std::get<1>(std::as_const(x)) == std::get<1>(y));
  VERIFY(std::get<0>(std::move(std::as_const(x))) == std::get<0>(y));
  VERIFY(std::get<1>(std::move(std::as_const(x))) == std::get<1>(y));
  VERIFY(std::get<0>(std::move(x)) == std::get<0>(y));
  VERIFY(std::get<1>(std::move(x)) == std::get<1>(y));
  
  static_assert(std::same_as<decltype(std::get<0>(x)), decltype(std::get<0>(y))>);
  static_assert(std::same_as<decltype(std::get<1>(x)), decltype(std::get<1>(y))>);
  
  // TODO: a Boost.PFR issue https://github.com/boostorg/pfr/issues/102
  //static_assert(std::same_as<decltype(std::get<0>(std::as_const(x))), decltype(std::get<0>(std::as_const(y)))>);
  //static_assert(std::same_as<decltype(std::get<1>(std::as_const(x))), decltype(std::get<1>(std::as_const(y)))>);
  
  // TODO: a Boost.PFR issue https://github.com/boostorg/pfr/issues/102
  //static_assert(std::same_as<decltype(std::get<0>(std::move(std::as_const(x)))), decltype(std::get<0>(std::move(std::as_const(y))))>);
  //static_assert(std::same_as<decltype(std::get<1>(std::move(std::as_const(x)))), decltype(std::get<1>(std::move(std::as_const(y))))>);
  //static_assert(std::same_as<decltype(std::get<0>(std::move(x))), decltype(std::get<0>(std::move(y)))>);
  //static_assert(std::same_as<decltype(std::get<1>(std::move(x))), decltype(std::get<1>(std::move(y)))>);
}

int main()
{
  struct AggreagateConst {
    const short a;
    const char b;
  };
  test_get_2(AggreagateConst{42, 43}, std::tuple<const short, const char>{42, 43});

  struct AggreagateConstRef {
    const short& a;
    const char& b;
  };

  short short_val{44};
  char char_val{44};
  test_get_2(AggreagateConstRef{short_val, char_val}, std::tuple<const short&, const char&>{short_val, char_val});
  
  struct AggreagateRef {
    short& a;
    char& b;
  };
  test_get_2(AggreagateRef{short_val, char_val}, std::tuple<short&, char&>{short_val, char_val});
}
