// Utilities used throughout the library -*- C++ -*-

// Copyright (C) 2023 Free Software Foundation, Inc.
//
// This file is part of the GNU ISO C++ Library.  This library is free
// software; you can redistribute it and/or modify it under the
// terms of the GNU General Public License as published by the
// Free Software Foundation; either version 3, or (at your option)
// any later version.

// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// Under Section 7 of GPL version 3, you are granted additional
// permissions described in the GCC Runtime Library Exception, version
// 3.1, as published by the Free Software Foundation.

// You should have received a copy of the GNU General Public License and
// a copy of the GCC Runtime Library Exception along with this program;
// see the files COPYING3 and COPYING.RUNTIME respectively.  If not, see
// <http://www.gnu.org/licenses/>.

/** @file include/bits/utility_aggregate.h
 *  This is an internal header file, included by other library headers.
 *  Do not attempt to use it directly. @headername{utility}
 *
 *  This file contains the parts of `<utility>` needed by other headers,
 *  so they don't need to include the whole of `<utility>`.
 */

#ifndef _GLIBCXX_UTILITY_AGGREGATE_H
#define _GLIBCXX_UTILITY_AGGREGATE_H 1

#pragma GCC system_header

#include <bits/utility.h>

#if __cplusplus > 201703L
// Use the following to compile and test:
// CPLUS_INCLUDE_PATH=/data/code/boost/libs/pfr/include/ make -j4 bootstrap-lean
// CPLUS_INCLUDE_PATH=/data/code/boost/libs/pfr/include/ make check-target-libstdc++-v3 RUNTESTFLAGS="conformance.exp=20_util/*"
//
// All the boost::pfr::* functions should be builtins or should be implemented via P1061
# define __cpp_lib_aggregates_as_tuples 202311L
# include <boost/pfr/detail/fields_count.hpp>
# include <boost/pfr/detail/core.hpp>
#endif

namespace std _GLIBCXX_VISIBILITY(default)
{
_GLIBCXX_BEGIN_NAMESPACE_VERSION

#ifdef __cpp_lib_aggregates_as_tuples
  template <typename _Tp>
    concept _TupleLikeAggregate = is_aggregate_v<remove_cv_t<remove_reference_t<_Tp>>>;

  template<typename _Tp>
    struct __element_count;

  template<typename _Tp>
    requires requires { tuple_size<remove_cv_t<remove_reference_t<_Tp>>>{}; }
  struct __element_count<_Tp> : tuple_size<remove_cv_t<remove_reference_t<_Tp>>> {};

  template<_TupleLikeAggregate _Tp>
    requires (!requires { tuple_size<remove_cv_t<remove_reference_t<_Tp>>>{}; })
  struct __element_count<_Tp> : integral_constant<size_t, boost::pfr::detail::fields_count<
    remove_cv_t<remove_reference_t<_Tp>>
  >() > {};

  template<typename _Tp>
    using element_count = __element_count<_Tp>;

  template<typename _Tp>
    inline constexpr size_t element_count_v = element_count<_Tp>::value;

  template <size_t _Ind, _TupleLikeAggregate _Tp>
  struct tuple_element<_Ind, _Tp> : boost::pfr::detail::sequence_tuple::tuple_element<
      _Ind, decltype( ::boost::pfr::detail::tie_as_tuple(std::declval<_Tp&>()) )
    >
  {};

  template <size_t _Ind, _TupleLikeAggregate _Tp>
  constexpr tuple_element_t<_Ind, _Tp>& get(_Tp& __x) noexcept {
    return boost::pfr::detail::sequence_tuple::get<_Ind>( boost::pfr::detail::tie_as_tuple(__x) );
  }

  template <size_t _Ind, _TupleLikeAggregate _Tp>
  constexpr const tuple_element_t<_Ind, _Tp>& get(const _Tp& __x) noexcept {
    return boost::pfr::detail::sequence_tuple::get<_Ind>( boost::pfr::detail::tie_as_tuple(__x) );
  }

  template <size_t _Ind, _TupleLikeAggregate _Tp>
  constexpr tuple_element_t<_Ind, _Tp>&& get(_Tp&& __x) noexcept {
    return std::move(
        boost::pfr::detail::sequence_tuple::get<_Ind>( boost::pfr::detail::tie_as_tuple(__x) )
    );
  }

  template <size_t _Ind, _TupleLikeAggregate _Tp>
  constexpr const tuple_element_t<_Ind, _Tp>&& get(const _Tp&& __x) noexcept {
    return std::move(
        boost::pfr::detail::sequence_tuple::get<_Ind>( boost::pfr::detail::tie_as_tuple(__x) )
    );
  }
#else
  template<typename _Tp>
  using __element_count = tuple_size<typename remove_cv<
    typename remove_reference<_Tp>::type
  >::type>;
#endif // __cpp_lib_aggregates_as_tuples

_GLIBCXX_END_NAMESPACE_VERSION
} // namespace

#endif /* _GLIBCXX_UTILITY_AGGREGATE_H */
