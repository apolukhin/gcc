// { dg-options "-std=c++20" }
// { dg-do run }

// Verify that std::get for aggregates does not break structured bindings.

#include <tuple>
#include <utility>

#include <testsuite_hooks.h>

namespace users_ns {

struct CustomizedBinding1 {
  short first;
  int second : 3;
  unsigned third;
};

template <std::size_t I>
decltype(auto) get(const CustomizedBinding1& v) {
  if constexpr (I == 0) {
    return v.first;
  } else {
    static_assert(I == 1);
    return v.third;
  }
}

struct CustomizedBinding2 {
  short first;
  int second : 3;
  unsigned third;

  template <std::size_t I>
  decltype(auto) get() {
    if constexpr (I == 0) {
      return first;
    } else {
      static_assert(I == 1);
      return third;
    }
  }

  template <std::size_t I>
  decltype(auto) get() const {
    if constexpr (I == 0) {
      return first;
    } else {
      static_assert(I == 1);
      return third;
    }
  }
};

}  // namespace users_ns

struct CustomizedBinding3 {
  short first;
  int second : 3;
  unsigned third;
};

template <std::size_t I>
decltype(auto) get(const CustomizedBinding3& v) {
  if constexpr (I == 0) {
    return v.first;
  } else {
    static_assert(I == 1);
    return v.third;
  }
}

namespace std {

template <>
struct tuple_size<users_ns::CustomizedBinding1> {
  static const std::size_t value = 2;
};

template <>
struct tuple_element<0, users_ns::CustomizedBinding1> {
  using type = int;
};

template <>
struct tuple_element<1, users_ns::CustomizedBinding1> {
  using type = unsigned;
};

template <>
struct tuple_size<users_ns::CustomizedBinding2> {
  static const std::size_t value = 2;
};

template <>
struct tuple_element<0, users_ns::CustomizedBinding2> {
  using type = int;
};

template <>
struct tuple_element<1, users_ns::CustomizedBinding2> {
  using type = unsigned;
};

template <>
struct tuple_size<CustomizedBinding3> {
  static const std::size_t value = 2;
};

template <>
struct tuple_element<0, CustomizedBinding3> {
  using type = int;
};

template <>
struct tuple_element<1, CustomizedBinding3> {
  using type = unsigned;
};

}  // namespace std


template <class T>
void test_binding(T value) {
  {
    auto& [first, last] = value;
    VERIFY(first == 1 && last == 3);
  }
  {
    auto& [first, last] = std::as_const(value);
    VERIFY(first == 1 && last == 3);
  }
  {
    auto& [first, last] = std::move(std::as_const(value));
    VERIFY(first == 1 && last == 3);
  }
  {
    auto [first, last] = std::move(value);
    VERIFY(first == 1 && last == 3);
  }
}

template <class T>
void test_get(T x) {
  VERIFY(std::get<0>(x) == 1);
  VERIFY(std::get<1>(x) == 3);
  VERIFY(std::get<0>(std::as_const(x)) == 1);
  VERIFY(std::get<1>(std::as_const(x)) == 3);
  VERIFY(std::get<0>(std::move(std::as_const(x))) == 1);
  VERIFY(std::get<1>(std::move(std::as_const(x))) == 3);
  VERIFY(std::get<0>(std::move(x)) == 1);
  VERIFY(std::get<1>(std::move(x)) == 3);
  
  static_assert(std::same_as<short&, decltype(std::get<0>(x))>);
  static_assert(std::same_as<unsigned&, decltype(std::get<1>(x))>);
  static_assert(std::same_as<const short&, decltype(std::get<0>(std::as_const(x)))>);
  static_assert(std::same_as<const unsigned&, decltype(std::get<1>(std::as_const(x)))>);
  static_assert(std::same_as<const short&&, decltype(std::get<0>(std::move(std::as_const(x))))>);
  static_assert(std::same_as<const unsigned&&, decltype(std::get<1>(std::move(std::as_const(x))))>);
  static_assert(std::same_as<short&&, decltype(std::get<0>(std::move(x)))>);
  static_assert(std::same_as<unsigned&&, decltype(std::get<1>(std::move(x)))>);
}

template <class T>
void test_tuple_element(T /*value*/) {
  static_assert(std::same_as<short, std::tuple_element_t<0, T>>);
  static_assert(std::same_as<unsigned, std::tuple_element_t<1, T>>);

  static_assert(std::same_as<const short, std::tuple_element_t<0, const T>>);
  static_assert(std::same_as<const unsigned, std::tuple_element_t<1, const T>>);
}

int main()
{
  test_binding(users_ns::CustomizedBinding1{1, 2, 3});
  test_binding(users_ns::CustomizedBinding2{1, 2, 3});
  test_binding(CustomizedBinding3{1, 2, 3});

  test_binding(std::tuple<short, unsigned>{1, 3});
  test_binding(std::pair<short, unsigned>{1, 3});

  test_get(std::tuple<short, unsigned>{1, 3});
  test_get(std::pair<short, unsigned>{1, 3});

  test_tuple_element(std::tuple<short, unsigned>{});
  test_tuple_element(std::pair<short, unsigned>{});

  struct UncustomizedAggreagate {
    short a;
    unsigned b;
  };
  test_binding(UncustomizedAggreagate{1, 3});
  test_get(UncustomizedAggreagate{1, 3});
  test_tuple_element(UncustomizedAggreagate{1, 3});
}
