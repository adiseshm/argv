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

/* user defined output structure */
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

/* Get the argument specifications */
#include "t1.argv.spec"

/* Get the synopsis specifications */
/* Typically dependent on the enums in t1.argv.spec */
#include "t1.synopsis.spec"

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
