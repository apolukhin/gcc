// { dg-do compile { target c++20 } }

// Copyright (C) 2019 Free Software Foundation, Inc.
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

// You should have received a copy of the GNU General Public License along
// with this library; see the file COPYING3.  If not see
// <http://www.gnu.org/licenses/>.

#include <algorithm>

constexpr int data[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
static_assert(!std::is_heap(std::begin(data), std::end(data)), "");


constexpr int heap[] = {9, 5, 4, 1, 1, 3};
static_assert(std::is_heap(std::begin(heap), std::end(heap)), "");;

