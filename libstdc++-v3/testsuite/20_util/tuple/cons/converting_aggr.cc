// { dg-options "-std=c++20" }
// { dg-do compile }

#include <tuple>

struct Aggr1 {
  int i;
} ts1;
std::tuple<unsigned> tu1(ts1);

struct Aggr2 {
  int i;
  int j;
} ts2;
std::tuple<unsigned, unsigned> tu2(ts2);

struct Aggr3 {
  int i;
  int j;
  int k;
} ts3;
std::tuple<unsigned, unsigned, unsigned> tu3(ts3);


struct AggrMixed1 {
  int i;
  unsigned j;
} tm2;
std::tuple<unsigned, int> tm2_(tm2);

struct AggrMixed2 {
  int i;
  unsigned j;
  int k;
} tm3;
std::tuple<unsigned, int, unsigned> tm3_(tm3);
