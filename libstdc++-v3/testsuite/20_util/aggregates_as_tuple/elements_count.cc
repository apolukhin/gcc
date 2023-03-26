// { dg-options "-std=c++20" }
// { dg-do compile }

// Verify that std::get works the same way as std::get for tuples.

#include <tuple>
#include <utility>

template <class T>
concept ElementsCountComplete = requires(T&) { std::elements_count<T>::value; };

struct UncustomizedAggreagate { int i; char c; };

static_assert(std::elements_count<UncustomizedAggreagate>::value == 2);
static_assert(std::elements_count<const UncustomizedAggreagate>::value ==2);

static_assert(!ElementsCountComplete<int>);
static_assert(!ElementsCountComplete<void>);
