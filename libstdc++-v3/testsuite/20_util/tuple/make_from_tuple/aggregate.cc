// { dg-do run { target c++20 } }

#include <tuple>
#include <utility>

int main() {
    struct SomeAggreagate {
        int a;
        unsigned b;
    };
    struct SomeOtherAggreagate {
        int a;
        unsigned b;
    };
    auto new_aggregate = std::make_from_tuple<SomeOtherAggreagate>(SomeAggreagate{1, 2});
    static_assert(std::same_as<SomeOtherAggreagate, decltype(new_aggregate)>);

    if (new_aggregate.a != 1)
        __builtin_abort();
    if (new_aggregate.b != 2)
        __builtin_abort();
}
