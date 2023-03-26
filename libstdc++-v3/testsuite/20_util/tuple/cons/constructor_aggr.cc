// { dg-options "-std=c++20" }
// { dg-do run }

#include <tuple>

#include <testsuite_hooks.h>

template <class T>
struct ExplicitFrom {
  explicit ExplicitFrom(T);
};

template <typename ExpectedTuple, typename SomeAggreagate>
void test_tuple_construction_x_elements(ExpectedTuple tuple, SomeAggreagate aggr) {    
  static_assert(std::is_constructible_v<ExpectedTuple, SomeAggreagate>);

  {
    ExpectedTuple new_tuple = aggr;
    VERIFY(new_tuple == tuple);
  }
  {
    ExpectedTuple new_tuple = std::as_const(aggr);
    VERIFY(new_tuple == tuple);
  }
  {
    ExpectedTuple new_tuple = SomeAggreagate{aggr};
    VERIFY(new_tuple == tuple);
  }
  {
    const SomeAggreagate tmp{aggr};
    ExpectedTuple new_tuple = std::move(tmp);
    VERIFY(new_tuple == tuple);
  }

  // Checking explcit/implicit conversions
  static_assert(std::is_convertible_v<SomeAggreagate, ExpectedTuple>);
  static_assert(!std::is_convertible_v<ExpectedTuple, SomeAggreagate>);

  struct local_only_type{};
  struct local_aggregate0 {
    local_only_type a, b, c, d, e, f, g;
  };
  static_assert(!std::is_constructible_v<ExpectedTuple, local_aggregate0>);
  static_assert(!std::is_convertible_v<ExpectedTuple, local_aggregate0>);

  #ifndef __clang__
  // TODO: report the issue
  static_assert(!std::is_constructible_v<ExpectedTuple, local_only_type>);
  #endif

  static_assert(!std::is_convertible_v<ExpectedTuple, local_only_type>);
}

template <typename ExpectedTuple, typename SomeAggreagate>
void test_tuple_assignment_3_elements() {
  ExpectedTuple tuple{1, 2, 3};

  tuple = SomeAggreagate{4, 5, 6};
  VERIFY((tuple == ExpectedTuple{4, 5, 6}));

  {
    SomeAggreagate aggr{10, 11, 12};
    tuple = aggr;
    VERIFY((tuple == ExpectedTuple{10, 11, 12}));
  }
  {
    const SomeAggreagate aggr{16, 17, 18};
    tuple = aggr;
    VERIFY((tuple == ExpectedTuple{16, 17, 18}));
  }
}

template <typename ExpectedTuple, typename SomeAggreagate>
void test_tuple_assignment_2_elements() {
  ExpectedTuple tuple{1, 2};

  tuple = SomeAggreagate{4, 5};
  VERIFY((tuple == ExpectedTuple{4, 5}));

  {
    SomeAggreagate aggr{10, 11};
    tuple = aggr;
    VERIFY((tuple == ExpectedTuple{10, 11}));
  }
  {
    const SomeAggreagate aggr{16, 17};
    tuple = aggr;
    VERIFY((tuple == ExpectedTuple{16, 17}));
  }
}

void test_tuple_construction_and_assignment_3_elements() {
  using ExpectedTuple = std::tuple<short, unsigned, float>;
  struct SomeAggreagate {
    int a;
    unsigned b;
    float c;
  };

  test_tuple_construction_x_elements(
    ExpectedTuple{1, 2, 0.0}, SomeAggreagate{1, 2, 0.0}
  );
  test_tuple_construction_x_elements<const ExpectedTuple, SomeAggreagate>(
    ExpectedTuple{1, 2, 0.0}, SomeAggreagate{1, 2, 0.0}
  );
  
  // Checking explciit/implicit conversions
  static_assert(!std::is_convertible_v<SomeAggreagate, std::tuple<short, unsigned, ExplicitFrom<float>>>);
  static_assert(!std::is_convertible_v<SomeAggreagate, std::tuple<ExplicitFrom<short>, unsigned, float>>);
  static_assert(!std::is_convertible_v<SomeAggreagate, std::tuple<short, ExplicitFrom<unsigned>, float>>);

  test_tuple_assignment_3_elements<ExpectedTuple, SomeAggreagate>();

  using OnlyAssignableTuple = std::tuple<OnlyAssignable, OnlyAssignable, OnlyAssignable>;

  struct OnlyAssignableAggregate {
    OnlyAssignable x;
    OnlyAssignable y;
    OnlyAssignable z;
  };

  test_tuple_assignment_3_elements<OnlyAssignableTuple, OnlyAssignableAggregate>();
  test_tuple_assignment_3_elements<const OnlyAssignableTuple, OnlyAssignableAggregate>();
}

void test_tuple_construction_and_assignment_2_elements() {
  using ExpectedTuple = std::tuple<long, short>;
  struct SomeAggreagate {
    long a;
    short b;
  };

  test_tuple_construction_x_elements(
    ExpectedTuple{1, 2}, SomeAggreagate{1, 2}
  );
  test_tuple_construction_x_elements<const ExpectedTuple, SomeAggreagate>(
    ExpectedTuple{1, 2}, SomeAggreagate{1, 2}
  );
  
  // Checking explciit/implicit conversions
  static_assert(!std::is_convertible_v<SomeAggreagate, std::tuple<ExplicitFrom<long>, short>>);
  static_assert(!std::is_convertible_v<SomeAggreagate, std::tuple<long, ExplicitFrom<short>>>);

  test_tuple_assignment_2_elements<ExpectedTuple, SomeAggreagate>();

  using OnlyAssignableTuple = std::tuple<OnlyAssignable, OnlyAssignable>;

  struct OnlyAssignableAggregate {
    OnlyAssignable x;
    OnlyAssignable y;
  };

  test_tuple_assignment_2_elements<OnlyAssignableTuple, OnlyAssignableAggregate>();
  test_tuple_assignment_2_elements<const OnlyAssignableTuple, OnlyAssignableAggregate>();
}

int main()
{
  test_tuple_construction_and_assignment_3_elements();
  test_tuple_construction_and_assignment_2_elements();
}
