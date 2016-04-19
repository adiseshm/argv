/* Copyright (C) 2016 adiseshm

   Argument parsing in C.
   . t1.c test program

   The argv C Library test program is free software; you can redistribute it 
   and/or modify it under the terms of the GNU General Public
   License as published by the Free Software Foundation; either
   version 3.0 of the License, or (at your option) any later version.

   This argv C Library test program is distributed in the hope that it will 
   be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU General Public
   License along with the argv C Library; if not, write to the Free
   Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA
   02111-1307 USA.
*/

#include <stdio.h>
#include <inttypes.h>
#include <string.h>

#include "api/argv.h"
#include "src/inc/dump.h"

struct t1_args_s
{
	char *file;
	uint32_t offset;
	int16_t qwerty;
	uint64_t uint64;
	int32_t int32r;
	uint16_t uint16r;
	uint16_t uint16l;
	int32_t int32l;
	char * charpl;
};

enum
{
	ARG_FILE    = 10,
	ARG_OFFSET  = 20,
	ARG_QWERTY  = 30,
	ARG_UINT64  = 40,
	ARG_INT32R  = 50,
	ARG_UINT16R = 60,
	ARG_UINT16L = 70,
	ARG_INT32L  = 80,
	ARG_CHARPL  = 90,
};

struct argv_spec_s arg_spec[] =
{

/* file */
{.id = ARG_FILE,  
 .name_long = "file", 
 .name_val = 'f',
 .help_arg = "filename",
 .help = "name of the file",
 .type.data  = ARGV_TYPE_CHARP,
 .type.flags = ARGV_TYPE_FLAGS_ZERO,
 .type.multiples = 1,
 .defval.charp = "hello.argp",
 .uptr.ARGV_VAL_UPTR_CHARP(struct t1_args_s, file)
},

/* offset */
{.id = ARG_OFFSET,
 .name_long = "offset",
 .name_val = 'o',
 .help_arg = "offset",
 .help = "offset in the file",
 .type.data  = ARGV_TYPE_UINT32,
 .type.flags = ARGV_TYPE_FLAGS_ZERO,
 .type.multiples = 1,
 .defval.uint32 = 32,
 .uptr.ARGV_VAL_UPTR_UINT32(struct t1_args_s, offset)
},

/* qwerty */
{.id = ARG_QWERTY,
 .name_long = "qwerty",
 .name_val = 'q',
 .help_arg = "uint16",
 .help = "qwerty uint16 option",
 .type.data  = ARGV_TYPE_INT16,
 .type.flags = ARGV_TYPE_FLAGS_ZERO,
 .type.multiples = 16,
 .defval.int16 = 16,
 .uptr.ARGV_VAL_UPTR_INT16(struct t1_args_s, qwerty)
},

/* uint64 */
{.id = ARG_UINT64,
 .name_long = "uint64",
 .name_val = '6',
 .help_arg = "uint64",
 .help = "random uint64 value",
 .type.data  = ARGV_TYPE_UINT64,
 .type.flags = ARGV_TYPE_FLAGS_ZERO,
 .type.multiples = 1,
 .defval.uint64 = 64,
 .uptr.ARGV_VAL_UPTR_UINT64(struct t1_args_s, uint64)
},

/* uint32-range */
{.id = ARG_INT32R,
 .name_long = "int32r",
 .name_val = '2',
 .help_arg = "int32r",
 .help = "int32 value in 22-33 range",
 .type.data  = ARGV_TYPE_INT32,
 .type.flags = ARGV_TYPE_FLAGS_NUM_RANGE,
 .spec.range.i.start = 22,
 .spec.range.i.end = 33,
 .type.multiples = 1,
 .defval.int32 = 77,
 .uptr.ARGV_VAL_UPTR_INT32(struct t1_args_s, int32r)
},

/* uint16-range */
{.id = ARG_UINT16R,
 .name_long = "int16r",
 .name_val = '1',
 .help_arg = "int16r",
 .help = "int16 value in 22-33 range",
 .type.data  = ARGV_TYPE_INT16,
 .type.flags = ARGV_TYPE_FLAGS_NUM_RANGE,
 .spec.range.i.start = 44,
 .spec.range.i.end = 55,
 .type.multiples = 1,
 .defval.uint16 = 77,
 .uptr.ARGV_VAL_UPTR_UINT16(struct t1_args_s, uint16r)
},

/* uint16-list */
{.id = ARG_UINT16L,
 .name_long = "uint16l",
 .name_val = 'u',
 .help_arg = "uint16l",
 .help = "uint16 list 1,3,5,7,11,13,17,19",
 .type.data  = ARGV_TYPE_UINT16,
 .type.flags = ARGV_TYPE_FLAGS_LIST,
 .spec.list.u.nums = {1, 3, 5, 7, 11, 13, 17, 19},
 .type.multiples = 1,
 .defval.uint16 = 19,
 .uptr.ARGV_VAL_UPTR_UINT16(struct t1_args_s, uint16l)
},

/* int32-list */
{.id = ARG_INT32L,
 .name_long = "int32l",
 .name_val = 'l',
 .help_arg = "int32l",
 .help = "int32 list -1, 200, 400, -1000, -300000",
 .type.data  = ARGV_TYPE_INT32,
 .type.flags = ARGV_TYPE_FLAGS_LIST,
 .spec.list.i.nums = {-1, 200, 400, -1000, -300000},
 .type.multiples = 1,
 .defval.int32 = -1000,
 .uptr.ARGV_VAL_UPTR_INT32(struct t1_args_s, int32l)
},

/* charp-list */
{.id = ARG_CHARPL,
 .name_long = "charpl",
 .name_val = 'c',
 .help_arg = "charpl",
 .help = "charp list hello world whoa",
 .type.data  = ARGV_TYPE_CHARP,
 .type.flags = ARGV_TYPE_FLAGS_LIST,
 .spec.list.s.strings = {"hello", "world", "whoa", NULL },
 .type.multiples = 1,
 .defval.charp = "whoa",
 .uptr.ARGV_VAL_UPTR_CHARP(struct t1_args_s, charpl)
},

/* last zero entry */
{
 .name_long = 0,
},

};


enum 
{
	CMD_FILE,
	CMD_QWERTY,
	CMD_INT32R,
};

struct argv_synopsis_s synopsis[] = 
{
	/* file : synopsis */
	{
		.name   = "file",
		.cmd    = CMD_FILE,
		.ids_m  = (int []) { ARG_FILE, ARG_OFFSET, ARG_LAST },
		.ids_o  = (int []) { ARG_UINT64, ARG_LAST },
	},

	/* qwerty : synopsis */
	{
		.name   = "qwerty",
		.cmd    = CMD_QWERTY,
		.ids_m  = (int []) { ARG_QWERTY, ARG_LAST },
		.ids_o  = (int []) { ARG_UINT64, ARG_LAST },
	},

	/* t1 : synopsis */
	{
		.name   = "cmd-int32r/u16l/32l",
		.cmd    = CMD_INT32R,
		.ids_m  = (int []) { ARG_INT32R, ARG_LAST },
		.ids_o  = (int []) { ARG_UINT16R, ARG_UINT16L, ARG_INT32L, ARG_CHARPL, ARG_LAST },
	},

	/* last zero entry */
	{
		.name   = "zero",
		.ids_m  = 0,
		.ids_o  = 0,
	}
};


static void info_dump(int argc, char **argv, int non_option_start,
						struct t1_args_s *p_args, 
						int num_spec, struct argv_spec_s *p_spec,
						int synop_idx, struct argv_synopsis_s *p_synop)
{
	printf("COMMAND\n");
	printf("\t%s (%d)\n", p_synop[synop_idx].name, synop_idx);

	if( non_option_start < argc ) {
		int i = non_option_start;

		printf ("NON-OPTION ARGV-ELEMENTS\n");
		printf ("\tstart %d\n", non_option_start);
		while (i < argc) printf ("\t%s ", argv[i++]);
		printf ("\n");
	}

	printf("ARGUMENTS\n");
	printf("\tfile %s\n", p_args->file);
	printf("\toffset %d\n", p_args->offset);
	printf("\tqwerty %d\n", p_args->qwerty);
	printf("\tuint64 %" PRIu64 "\n", p_args->uint64);
	printf("\tcharpl %s\n", p_args->charpl);

	//  dump the argv-specs
	argv_dump_specs(p_spec, num_spec);

	return;
}

int main(int argc, char **argv)
{
	int r, synop_idx, num_spec, non_option_start;
	struct argv_error_s e;
	struct t1_args_s args;

	num_spec = sizeof(arg_spec)/sizeof(arg_spec[0]);
	r = argv_parse(argc, argv, arg_spec, synopsis, &args,
					&non_option_start, &synop_idx, &e);
	if( r ) {
		fprintf(stderr, "argv_parse(): %s. %s(rc=%d)\n",
				e.errmsg, strerror(r), r);

		argv_usage(stderr, argv[0], synopsis, arg_spec, &e);
	} else {
		info_dump(argc, argv, non_option_start, &args, num_spec, arg_spec,
					synop_idx, synopsis);
	}

	return r ? 1 : 0;
}
