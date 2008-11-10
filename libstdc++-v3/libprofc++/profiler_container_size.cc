// -*- C++ -*-
//
// Copyright (C) 2008 Free Software Foundation, Inc.
//
// This file is part of the GNU ISO C++ Library.  This library is free
// software; you can redistribute it and/or modify it under the terms
// of the GNU General Public License as published by the Free Software
// Foundation; either version 2, or (at your option) any later
// version.

// This library is distributed in the hope that it will be useful, but
// WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this library; see the file COPYING.  If not, write to
// the Free Software Foundation, 59 Temple Place - Suite 330, Boston,
// MA 02111-1307, USA.

// As a special exception, you may use this file as part of a free
// software library without restriction.  Specifically, if other files
// instantiate templates or use macros or inline functions from this
// file, or you compile this file and link it with other files to
// produce an executable, this file does not by itself cause the
// resulting executable to be covered by the GNU General Public
// License.  This exception does not however invalidate any other
// reasons why the executable file might be covered by the GNU General
// Public License.

/** @file libprofc++/profiler_container_size.cc
 *  @brief Data structures to represent profiling traces.
 */

// Written by Lixia Liu

#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <cassert>
#include "profiler.h"
#include "profiler_node.h"
#include "profiler_trace.h"
#include "profiler_state.h"
#include "profiler_container_size.h"

namespace cxxprof_runtime
{

void container_size_info::write(FILE* f) const
{
  fprintf(f, "%Zu %Zu %Zu %Zu %Zu %Zu %Zu %Zu %Zu %Zu\n", 
          _M_init, _M_count, _M_cost,_M_resize, _M_min, _M_max, _M_total,
          _M_item_min, _M_item_max, _M_item_total);
}

void trace_container_size::destruct(const void* __obj, size_t __num, 
                                    size_t __inum)
{
  if (!is_on()) return;

  object_t obj = static_cast<object_t>(__obj);

  container_size_info* object_info = get_object_info(obj);
  if (!object_info)
    return;

  object_info->destruct(__num, __inum);
  retire_object(obj);
}

void trace_container_size::resize(const void* __obj, int __from, int __to)
{
  if (!is_on()) return;

  container_size_info* object_info = get_object_info(__obj);
  if (!object_info)
    return;

  object_info->resize(__from, __to);
}

} // namespace cxxprof_runtime
