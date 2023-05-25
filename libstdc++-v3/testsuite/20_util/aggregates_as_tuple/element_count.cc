// { dg-options "-std=c++20" }
// { dg-do compile }

#include <utility>

template <class T>
concept ElementsCountComplete = requires(T&) { std::element_count<T>::value; };

struct UncustomizedAggreagate { int i; char c; };

static_assert(std::element_count<UncustomizedAggreagate>::value == 2);
static_assert(std::element_count<const UncustomizedAggreagate>::value ==2);

static_assert(!ElementsCountComplete<int>);
static_assert(!ElementsCountComplete<void>);
