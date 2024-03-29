/* Target definitions for Darwin (Mac OS X) systems.
   Copyright (C) 2009-2015 Free Software Foundation, Inc.
   Contributed by Jack Howarth <howarth.at.gcc@gmail.com>.

This file is part of GCC.

GCC is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 3, or (at your option)
any later version.

GCC is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with GCC; see the file COPYING3.  If not see
<http://www.gnu.org/licenses/>.  */

#undef  LINK_GCC_C_SEQUENCE_SPEC
#define LINK_GCC_C_SEQUENCE_SPEC \
"%:version-compare(>= 10.6 mmacosx-version-min= -no_compact_unwind) \
   %{rdynamic:-export_dynamic} %{!static:%{!static-libgcc: \
      %:version-compare(>= 10.6 mmacosx-version-min= -lSystem) } } \
   %{fno-pic|fno-PIC|fno-pie|fno-PIE|fapple-kext|mkernel|static|mdynamic-no-pic: \
      %:version-compare(>= 10.7 mmacosx-version-min= -no_pie) } %G %L"
