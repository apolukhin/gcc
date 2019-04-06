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

static_assert(std::find_end(std::begin(data), std::end(data), std::begin(data), std::begin(data) + 1) == std::begin(data), "");
static_assert(std::find_end(std::begin(data), std::end(data), std::end(data) - 1, std::end(data)) == std::end(data) - 1, "");


constexpr int data2[] = {3, 2};
static_assert(std::find_end(std::begin(data), std::end(data), std::begin(data2), std::end(data2)) == std::end(data), "");

