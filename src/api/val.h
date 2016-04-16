/* Copyright (C) 2016 adiseshm

   Argument parsing in C.

   The argv C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 3.0 of the License, or (at your option) any later version.

   This argv C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the argv C Library; if not, write to the Free
   Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA
   02111-1307 USA.
*/

#pragma once

#include <stdint.h>
#include <stddef.h>

enum
{
	//  !! argv_val_get_typestr() should be in 
	//  sync with below !!

	//  arg type - data type
	ARGV_TYPE_INT16,
	ARGV_TYPE_UINT16,

	ARGV_TYPE_INT32,
	ARGV_TYPE_UINT32,

	ARGV_TYPE_INT64,
	ARGV_TYPE_UINT64,

	ARGV_TYPE_CHARP,

	ARGV_TYPE_BOOL,

	//  arg type - flags
	ARGV_TYPE_FLAGS_ZERO = 0,
	ARGV_TYPE_FLAGS_NUM_RANGE,
	ARGV_TYPE_FLAGS_LIST,
};

union __argv_val
{
	int16_t  int16;
	uint16_t uint16;

	int32_t  int32;
	uint32_t uint32;

	int64_t  int64;
	uint64_t uint64;

	char    *charp;

	int      bool;
};

struct __argv_val_uptr
{
	size_t offset_in_uptr;
	union 
	{
		void     *p_void;

		int16_t  *p_int16;
		uint16_t *p_uint16;

		int32_t  *p_int32;
		uint32_t *p_uint32;

		int64_t  *p_int64;
		uint64_t *p_uint64;

		char    **p_charp;

		int      *p_bool;
	} p;
};

/* do type checking and set offset_in_uptr */
#define ARGV_VAL_UPTR(__s, __f, __p)  p.__p = &((__s *)0)->__f,  .uptr.offset_in_uptr = offsetof(__s, __f)

#define ARGV_VAL_UPTR_INT16(__s, __f)  ARGV_VAL_UPTR(__s, __f, p_int16)
#define ARGV_VAL_UPTR_UINT16(__s, __f) ARGV_VAL_UPTR(__s, __f, p_uint16)

#define ARGV_VAL_UPTR_INT32(__s, __f)  ARGV_VAL_UPTR(__s, __f, p_int32)
#define ARGV_VAL_UPTR_UINT32(__s, __f) ARGV_VAL_UPTR(__s, __f, p_uint32)

#define ARGV_VAL_UPTR_INT64(__s, __f)  ARGV_VAL_UPTR(__s, __f, p_int64)
#define ARGV_VAL_UPTR_UINT64(__s, __f) ARGV_VAL_UPTR(__s, __f, p_uint64)

#define ARGV_VAL_UPTR_CHARP(__s, __f)  ARGV_VAL_UPTR(__s, __f, p_charp)
#define ARGV_VAL_UPTR_BOOL(__s, __f)   ARGV_VAL_UPTR(__s, __f, p_bool)


struct argv_spec_s;
