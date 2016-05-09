/* Copyright (C) 2016 adiseshm

   Argument parsing in C.
   . t1.argv.spec test program

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

 .type.multiples = 1,
 ARGV_SPEC_CHARP(ARGV_TYPE_FLAGS_ZERO, "hello.argp"/*defval*/, struct t1_args_s, file)
},

/* offset */
{.id = ARG_OFFSET,
 .name_long = "offset",
 .name_val = 'o',
 .help_arg = "offset",
 .help = "offset in the file",

 .type.multiples = 1,
 ARGV_SPEC_UINT32(ARGV_TYPE_FLAGS_ZERO, 32/*defval*/, struct t1_args_s, offset)
},

/* qwerty */
{.id = ARG_QWERTY,
 .name_long = "qwerty",
 .name_val = 'q',
 .help_arg = "int16",
 .help = "qwerty int16 option",

 .type.multiples = 16,
 ARGV_SPEC_INT16(ARGV_TYPE_FLAGS_ZERO, 16/*defval*/, struct t1_args_s, qwerty)
},

/* uint64 */
{.id = ARG_UINT64,
 .name_long = "uint64",
 .name_val = '6',
 .help_arg = "uint64",
 .help = "random uint64 value",

 .type.multiples = 1,
 ARGV_SPEC_UINT64(ARGV_TYPE_FLAGS_ZERO, 64/*defval*/, struct t1_args_s, uint64)
},

/* uint32-range */
{.id = ARG_INT32R,
 .name_long = "int32r",
 .name_val = '2',
 .help_arg = "int32r",
 .help = "int32 value in 22-33 range",

 .spec.range.i.start = 22,
 .spec.range.i.end = 33,
 .type.multiples = 1,
 ARGV_SPEC_INT32(ARGV_TYPE_FLAGS_NUM_RANGE, 77/*defval*/, struct t1_args_s, int32r)
},

/* uint16-range */
{.id = ARG_UINT16R,
 .name_long = "uint16r",
 .name_val = '1',
 .help_arg = "uint16r",
 .help = "uint16 value in 22-33 range",

 .spec.range.i.start = 44,
 .spec.range.i.end = 55,
 .type.multiples = 1,
 ARGV_SPEC_UINT16(ARGV_TYPE_FLAGS_NUM_RANGE, 77/*defval*/, struct t1_args_s, uint16r)
},

/* uint16-list */
{.id = ARG_UINT16L,
 .name_long = "uint16l",
 .name_val = 'u',
 .help_arg = "uint16l",
 .help = "uint16 list 1,3,5,7,11,13,17,19",

 .spec.list.u.nums = {1, 3, 5, 7, 11, 13, 17, 19},
 .type.multiples = 1,
 ARGV_SPEC_UINT16(ARGV_TYPE_FLAGS_LIST, 19/*defval*/, struct t1_args_s, uint16l)
},

/* int32-list */
{.id = ARG_INT32L,
 .name_long = "int32l",
 .name_val = 'l',
 .help_arg = "int32l",
 .help = "int32 list -1, 200, 400, -1000, -300000",

 .spec.list.i.nums = {-1, 200, 400, -1000, -300000},
 .type.multiples = 1,
 ARGV_SPEC_INT32(ARGV_TYPE_FLAGS_LIST, -1000/*defval*/, struct t1_args_s, int32l)
},

/* charp-list */
{.id = ARG_CHARPL,
 .name_long = "charpl",
 .name_val = 'c',
 .help_arg = "charpl",
 .help = "charp list hello world whoa",

 .spec.list.s.strings = {"hello", "world", "whoa", NULL },
 .type.multiples = 1,
 ARGV_SPEC_CHARP(ARGV_TYPE_FLAGS_LIST, "whoa"/*defval*/, struct t1_args_s, charpl)
},

/* last zero entry */
{
 .name_long = 0,
},

};
