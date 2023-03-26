// { dg-do compile { target c++23 } }

// Test noexcept-specifier on std::apply with aggregates

#include <tuple>

using std::declval;

void f1();

struct EmptyAggregate{};

static_assert( !noexcept(apply(f1, declval<EmptyAggregate>())) );
static_assert( !noexcept(apply(f1, declval<EmptyAggregate&>())) );
static_assert( !noexcept(apply(f1, declval<const EmptyAggregate>())) );
static_assert( !noexcept(apply(f1, declval<const EmptyAggregate&>())) );

void f2() noexcept;

static_assert( noexcept(apply(f2, declval<EmptyAggregate>())) );
static_assert( noexcept(apply(f2, declval<EmptyAggregate&>())) );
static_assert( noexcept(apply(f2, declval<const EmptyAggregate>())) );
static_assert( noexcept(apply(f2, declval<const EmptyAggregate&>())) );

struct F3 {
  void operator()(int&);
  void operator()(int&&) noexcept;
  void operator()(const int&) noexcept;
  void operator()(const int&&);
} f3;

struct IntAggregate{
  int i;
};

static_assert( noexcept(apply(f3, declval<IntAggregate>())) );
static_assert( !noexcept(apply(f3, declval<IntAggregate&>())) );
static_assert( !noexcept(apply(f3, declval<const IntAggregate>())) );
static_assert( noexcept(apply(f3, declval<const IntAggregate&>())) );

struct F4 {
  void operator()(int&, const int&);
  void operator()(int&&, int&&) noexcept;
} f4;

struct IntIntAggregate{
  int i;
  int j;
};

static_assert( noexcept(apply(f4, declval<IntIntAggregate>())) );
static_assert( !noexcept(apply(f4, declval<IntIntAggregate&>())) );
