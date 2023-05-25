// { dg-options "-std=c++20" }
// { dg-do run }

#include <tuple>
#include <array>

void test_basic()
{
  struct SomeUncustomizedAggreagate {
    short a;
    unsigned b;
    float c;
  };

  auto v = std::tuple_cat(
    SomeUncustomizedAggreagate{1, 2, 0.0},
    SomeUncustomizedAggreagate{11, 21, 1.0}
  );
  using ExpectedTuple = std::tuple<short, unsigned, float, short, unsigned, float>;
  static_assert(std::same_as<ExpectedTuple, decltype(v)>);

  if (v != ExpectedTuple{1, 2, 0.0, 11, 21, 1.0})
    __builtin_abort();

  v = std::tuple_cat(
    SomeUncustomizedAggreagate{1, 2, 0.0},
    std::tuple{11, 21, 1.0}
  );
  if (v != ExpectedTuple{1, 2, 0.0, 11, 21, 1.0})
    __builtin_abort();

  v = std::tuple_cat(
    std::tuple{11, 21, 1.0},
    SomeUncustomizedAggreagate{1, 2, 0.0}
  );
  if (v == ExpectedTuple{ 11, 21, 1.0, 1, 2, 0.0})
    __builtin_abort();
}

void test_mix()
{
  struct SomeUncustomizedAggreagate {
    short a;
    unsigned b;
  };

  auto v = std::tuple_cat(
    SomeUncustomizedAggreagate{1, 2},
    std::array<char, 2>{'o', 'k'},
    std::tuple<float, double>{1.0, 2.0},
    SomeUncustomizedAggreagate{3, 4}
  );
  using ExpectedTuple = std::tuple<short, unsigned, char, char, float, double, short, unsigned>;
  static_assert(std::same_as<ExpectedTuple, decltype(v)>);

  if (v != ExpectedTuple{1, 2, 'o', 'k', 1.0, 2.0, 3, 4})
    __builtin_abort();
}

int main()
{
  test_basic();
  test_mix();
}
