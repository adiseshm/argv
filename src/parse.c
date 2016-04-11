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

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <getopt.h>

#include "api/argv.h"
#include "api/synopsis.h"
#include "inc/val.h"


struct argv_spec_s * argv_spec_find_by_id(int num_spec, struct argv_spec_s *p_s, int id)
{
	int i;

	for(i=0; i<num_spec; i++) {
		if( id == p_s[i].id ) {
			return &p_s[i];
		}
	}

	return 0;
}

int argv_usage(FILE *fp, char *progname,
						struct argv_synopsis_s *p_synopsis,
						struct argv_spec_s *p_s,
						struct argv_error_s *p_e)
{
	int i, synop_idx, num_spec;

	//  find the number of arg-specs
	num_spec = 0;
	while( p_s[num_spec++].name_long )
		;
	num_spec--;  //  ignore the last zero entry

	fprintf(fp, "\nUsage: \n");
	//  for each of the synopsis
	synop_idx = 0;
	while( p_synopsis[synop_idx].ids_m ) {

		struct argv_synopsis_s *p;
		struct argv_spec_s *p_spec;
		int num_mandatory, num_optional;

		//  init variables
		p = &p_synopsis[synop_idx];
			
		//  print each of the mandatory ids
		fprintf(fp, "%s ", progname);
		num_mandatory = 0;
		while( p->ids_m[num_mandatory] != ARG_LAST ) {

			p_spec = argv_spec_find_by_id(num_spec, p_s, p->ids_m[num_mandatory]);
			fprintf(fp, " --%s %s", p_spec->name_long, p_spec->help_arg);

			num_mandatory++;
		}

		//  print each of the optional ids
		num_optional = 0;
		while( p->ids_o[num_optional] != ARG_LAST ) {

			if( 0 == num_optional ) fprintf(fp, "  [");
			p_spec = argv_spec_find_by_id(num_spec, p_s, p->ids_o[num_optional]);
			fprintf(fp, " --%s %s", p_spec->name_long, p_spec->help_arg);

			num_optional++;
		}
		if( num_optional ) fprintf(fp, " ]");

		fprintf(fp, "\n");

		synop_idx++;
	}

	fprintf(fp, "\n");
	for(i=0; i<num_spec; i++) {
		fprintf(fp, "    --%-25s%s\n", p_s[i].name_long, p_s[i].help);
	}

	return 0;
}

int argv_synopsis_match(struct argv_synopsis_s *p_synopsis, int num_spec,
						struct argv_spec_s *p_s)
{
	int spec_idx, idx;
	int arg_mandatory, arg_optional;
	int max_mandatory, max_optional;

	//  compute the max mandatory, and max optional
	max_mandatory = max_optional = 0;
	while( p_synopsis->ids_m[max_mandatory] != ARG_LAST ) {
		max_mandatory++;
	}
	while( p_synopsis->ids_o[max_optional] != ARG_LAST ) {
		max_optional++;
	}

	//  init the number of seen args
	arg_mandatory = arg_optional = 0;

	//  for each of the non-NULL p_s[].arg
	for(spec_idx=0; spec_idx<num_spec; spec_idx++) {

		int found_in_m, found_in_o;


		//  ignore if arg is not set
		if( 0 == p_s[spec_idx].arg ) continue;

		// check if the arg is in p_synopsis / mandatory
		idx = 0;
		found_in_m = 0;
		while( p_synopsis->ids_m[idx] != ARG_LAST ) {
			if( p_synopsis->ids_m[idx] == p_s[spec_idx].id ) {
				arg_mandatory++;
				found_in_m = 1;
				break;  // will cause it to hit for(spec_idx...)
			}
			idx++;
		}

		// check if the arg is in p_synopsis / optional
		idx = 0;
		found_in_o = 0;
		while( found_in_m == 0 && p_synopsis->ids_o[idx] != ARG_LAST ) {
			if( p_synopsis->ids_o[idx] == p_s[spec_idx].id ) {
				arg_optional++;
				found_in_o = 1;
				break;
			}
			idx++;
		}

		// if the arg is not found in both M and O
		// return error
		if( 0 == found_in_m && 0 == found_in_o ) {
			return EINVAL;
		}
	}

	if( arg_mandatory != max_mandatory ) {
		return EINVAL;
	}
	

	return 0;
}

int argv_parse(IN int argc, INOUT char **argv, 
				IN struct argv_spec_s *p_s,
				IN struct argv_synopsis_s *p_synopsis,
				IN void *p_uptr,
				OUT int *p_non_option_start,
				OUT int *p_synop_idx,
				OUT struct argv_error_s *p_e)
{
	int i, j, num_spec, option_index, synopsis_idx;
	int r=0, c;
	struct option *p_long_option;

	*p_synop_idx = -1;

	//  find the number of arg-specs
	num_spec = 0;
	while( p_s[num_spec++].name_long )
		;
	num_spec--;  //  ignore the last zero entry

	/* check duplicate : id, name_long, name_val */
	for(i=0; i<num_spec; i++) {
		for(j=0; j<num_spec; j++) {
			if( j == i ) continue;  /* skip the current spec */

			if( p_s[i].id == p_s[j].id ) {
				snprintf(p_e->errmsg, ARGV_MAX_ERRMSG_LEN,
							"id (%d) of options %s, and %s are same",
							p_s[i].id, p_s[i].name_long, p_s[j].name_long);
				return EEXIST;
			}

			if( strcmp(p_s[i].name_long, p_s[j].name_long) == 0 ) {
				snprintf(p_e->errmsg, ARGV_MAX_ERRMSG_LEN,
							"multiple entries with same name_long (%s)",
							p_s[j].name_long);
				return EEXIST;
			}

			if( p_s[i].name_val == p_s[j].name_val ) {
				snprintf(p_e->errmsg, ARGV_MAX_ERRMSG_LEN,
							"name_val (%d) of options %s, and %s are same",
							p_s[i].name_val, p_s[i].name_long, p_s[j].name_long);
				return EEXIST;
			}
		} // for j
	} // for i

	//  initialize the spec fields
	for(i=0; i<num_spec; i++) {
		//  zero out !!
		memset(&p_s[i].val, 0, sizeof(union __argv_val));
		p_s[i].num_occurences = 0;
		p_s[i].arg = 0;

		p_s[i].uptr.p.p_void = p_uptr + p_s[i].uptr.offset_in_uptr;

		//  set the default value
		(void)argv_val_set_default(&p_s[i], p_e);
	}

	// allocate (+1 last one as zeros) and initialize long options
	p_long_option = calloc(num_spec + 1, sizeof(struct option));
	if( !p_long_option ) {
		snprintf(p_e->errmsg, ARGV_MAX_ERRMSG_LEN,
					"Could not allocate memory for %d struct option",
					num_spec);
		return ENOMEM;
	}

	for(i=0; i<num_spec; i++) {

		p_long_option[i].name = p_s[i].name_long;
		if( p_s[i].type.flags == ARGV_TYPE_BOOL ) {
			p_long_option[i].has_arg = no_argument;
		} else {
			p_long_option[i].has_arg = required_argument;
		}
		p_long_option[i].flag    = NULL;
		p_long_option[i].val     = p_s[i].name_val;
	}

	//  parse the options
	while( 0 == r ) {
		c = getopt_long(argc, argv, ":", // : to indicate missing arg
						p_long_option, &option_index);
		if (c == -1) //  all options are parsed
			break;

		if( c == ':') { //  missing argument
			for(i=0; i<num_spec; i++) {
				if( p_s[i].name_val == optopt ) {
					break;
				}
			}

			snprintf(p_e->errmsg, ARGV_MAX_ERRMSG_LEN,
					"Option --%s is missing an argument", p_s[i].name_long);
			r = EINVAL;
			break;
		}

		if( c == '?') { //  unknown argument
			snprintf(p_e->errmsg, ARGV_MAX_ERRMSG_LEN,
					"Unknown option %s", argv[optind-1]);
			r = EINVAL;
			break;
		}

		//  process the argument
		r = argv_val_process(&p_s[option_index], optarg, p_e);

	} // while 0 == r

	//  setup the start-index of non-option ARGV-elements
	if( !r ) {
		*p_non_option_start = optind;
	} 

	//  free p_long_option
	free(p_long_option);

	if ( ! r ) {

		//  for each of the synopsis
		synopsis_idx = 0;
		while( p_synopsis[synopsis_idx].ids_m ) {
			//  see if given args matches it
			r = argv_synopsis_match(&p_synopsis[synopsis_idx], num_spec, p_s);
			if( r == 0 ) {
				*p_synop_idx = synopsis_idx;
				break;
			}

			synopsis_idx++;
		}

		if( r ) {
			snprintf(p_e->errmsg, ARGV_MAX_ERRMSG_LEN,
					"Could not match any synopsis !!");
		}
	}

	return r;
}
