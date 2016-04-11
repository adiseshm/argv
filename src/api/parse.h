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

#ifndef __ADIZ__ARGV_PARSE_H__
#define __ADIZ__ARGV_PARSE_H__

#include <stdio.h>
#include <stdint.h>

#include "synopsis.h"
#include "val.h"
#include "error.h"

#define ARGV_MAX_LIST  32

enum
{
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

struct argv_spec_s
{
	/* unique arg identifier */
	uint32_t id;

	/* long name */
	char *name_long;

	/* single character name or an integer representation */
	int name_val;

	/* help text */
	char *help_arg;
	char *help;

	/* type */
	struct {
		/* ARGV_TYPE_* */
		int data;
		/* ARGV_TYPE_FLAGS_*  */
		uint16_t flags;
		/* max # of times this option can occur */
		uint16_t multiples;
	} type;

	/* default value of the argument */
	union __argv_val defval;

	/* union for values the arg can take */
    union {
		/* RANGE */
		union {
			struct {
				uint64_t start;
				uint64_t end;
			} unum;
			struct {
				int64_t start;
				int64_t end;
			} snum;
		} range;

		/* LIST */
		union {
			struct {
				uint64_t nums[ARGV_MAX_LIST];
			} unum;
			struct {
				int64_t nums[ARGV_MAX_LIST];
			} snum;
			struct {
				char * strings[ARGV_MAX_LIST];
			} string;
		} list;
	} spec;

	/* use ARGV_VAL_UPTR macros to init */
	struct __argv_val_uptr uptr;

	/* impl - do not use */
	int   num_occurences;
	union __argv_val val;

	/* derived values */
	char *arg;
};

#define IN 
#define OUT 
#define INOUT

struct argv_synopsis_s;
extern int argv_parse(IN int argc, INOUT char **argv,
						IN struct argv_spec_s *p_s,
						IN struct argv_synopsis_s *p_synopsis,
						IN void *p_uptr,
						OUT int *p_non_option_start,
						OUT int *p_synop_idx,
						OUT struct argv_error_s *p_e);

extern int argv_usage(FILE *fp, char *progname,
						struct argv_synopsis_s *p_synopsis,
						struct argv_spec_s *p_s,
						struct argv_error_s *p_e);

#endif /* argv parse.h */
