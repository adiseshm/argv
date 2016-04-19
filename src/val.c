/* Copyright (C) 2016 adiseshm

   Argument parsing in C
   - argv-val utility functions

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
#include <stdlib.h>
#include <errno.h>
#include <inttypes.h>

#include "api/argv.h"
#include "api/val.h"

static char * argv_val_get_typestr(int type)
{
	//  NOTE : to be kept in sync with the corresponding
	//  ARGV_TYPE_* enum's in api/parse.h
	static char * type_str[] = {
		"INT16",
		"UINT16",
		"INT32",
		"UINT32",
		"INT64",
		"UINT64",
		"CHARP",
		"BOOL",
	};

	if( type < ARGV_TYPE_UINT16 || type > ARGV_TYPE_BOOL ) {
		return "Unknown";
	}

	return type_str[type];
}

static int argv_val_seti(struct argv_spec_s *p_s, long long int val,
						struct argv_error_s *p_e)
{
	long long int vStart = 0, vEnd = 0;

	if( p_s->type.flags == ARGV_TYPE_FLAGS_LIST ) {
		int i, found = 0;

		//  handle : list
		for(i=0; i<ARGV_MAX_LIST && p_s->spec.list.i.nums[i]; i++) {
			if( p_s->spec.list.i.nums[i] == val ) {
				found = 1;
				break;
			}
		}
		if( 0 == found ) {
			snprintf(p_e->errmsg, ARGV_MAX_ERRMSG_LEN,
				"option %s, value %lld not in the given list of %s numbers", 
				p_s->name_long, val, argv_val_get_typestr(p_s->type.data));
			return EINVAL;
		}
	} else {

		//  handle : given-range / generic-type-based-range
		//  .  get the allowed ranges
		//  .  get the type string
		if( p_s->type.flags == ARGV_TYPE_FLAGS_NUM_RANGE ) {
			vStart = p_s->spec.range.i.start;
			vEnd = p_s->spec.range.i.end;

		} else if( p_s->type.flags == ARGV_TYPE_FLAGS_ZERO ) {
			switch( p_s->type.data )
			{
				case ARGV_TYPE_INT16:
					vStart = INT16_MIN;
					vEnd = INT16_MAX;
					break;
				case ARGV_TYPE_INT32:
					vStart = INT32_MIN;
					vEnd = INT32_MAX;
					break;
				case ARGV_TYPE_INT64:
					vStart = INT64_MIN;
					vEnd = INT64_MAX;
					break;
			}
		}

		//  validate the range
		if( val < vStart || val > vEnd ) {
			snprintf(p_e->errmsg, ARGV_MAX_ERRMSG_LEN,
				"value %lld out of range (%lld-%lld) for %s", 
				val, vStart, vEnd, argv_val_get_typestr(p_s->type.data));
			return EINVAL;
		}
	}


	//  update *uptr and val
	if( p_s->type.data == ARGV_TYPE_INT16 ) {
		p_s->val.int16 = val;
		*p_s->uptr.p.p_int16 = val;

	} else if( p_s->type.data == ARGV_TYPE_INT32 ) {
		p_s->val.int32 = val;
		*p_s->uptr.p.p_int32 = val;

	} else if( p_s->type.data == ARGV_TYPE_INT64 ) {
		p_s->val.int64 = val;
		*p_s->uptr.p.p_int64 = val;
	}

	return 0;
}

static int argv_val_setu(struct argv_spec_s *p_s, unsigned long long int val,
						struct argv_error_s *p_e)
{
	unsigned long long int vStart, vEnd;

	if( p_s->type.flags == ARGV_TYPE_FLAGS_LIST ) {
		int i, found = 0;

		//  handle : list
		for(i=0; i<ARGV_MAX_LIST && p_s->spec.list.u.nums[i]; i++) {
			if( p_s->spec.list.u.nums[i] == val ) {
				found = 1;
				break;
			}
		}
		if( 0 == found ) {
			snprintf(p_e->errmsg, ARGV_MAX_ERRMSG_LEN,
				"option %s, value %llu not in the given list of %s numbers", 
				p_s->name_long, val, argv_val_get_typestr(p_s->type.data));
			return EINVAL;
		}
	} else {
		//  handle : given-range / generic-type-based-range
		//  .  get the allowed ranges
		//  .  get the type string
		if( p_s->type.flags == ARGV_TYPE_FLAGS_NUM_RANGE ) {
			vStart = p_s->spec.range.u.start;
			vEnd = p_s->spec.range.u.end;
		} else if( p_s->type.flags == ARGV_TYPE_FLAGS_ZERO ) {
			vStart = 0;
			switch( p_s->type.data )
			{
				case ARGV_TYPE_UINT16:
					vEnd = UINT16_MAX;
					break;
				case ARGV_TYPE_UINT32:
					vEnd = UINT32_MAX;
					break;
				case ARGV_TYPE_UINT64:
					vEnd = UINT64_MAX;
					break;
			}
		}

		//  validate the range
		if( val < vStart || val > vEnd ) {
			snprintf(p_e->errmsg, ARGV_MAX_ERRMSG_LEN,
				"option %s, value %lld out of range (%llu-%llu) for %s", 
				p_s->name_long, val, vStart, vEnd, argv_val_get_typestr(p_s->type.data));
			return EINVAL;
		}
	}

	//  update user given pointer and val
	if( p_s->type.data == ARGV_TYPE_UINT16 ) {
		p_s->val.uint16 = val;
		*p_s->uptr.p.p_uint16 = val;

	} else if( p_s->type.data == ARGV_TYPE_UINT32 ) {
		p_s->val.uint32 = val;
		*p_s->uptr.p.p_uint32 = val;

	} else if( p_s->type.data == ARGV_TYPE_UINT64 ) {
		p_s->val.uint64 = val;
		*p_s->uptr.p.p_uint64 = val;
	}

	return 0;
}

static int argv_val_setcharp(struct argv_spec_s *p_s, char *p_val)
{
	p_s->val.charp  = p_val;
	*p_s->uptr.p.p_charp = p_val;

	return 0;
}

static int argv_val_setbool(struct argv_spec_s *p_s)
{
	p_s->val.bool = 1;
	*p_s->uptr.p.p_bool = 1;

	return 0;
}

int argv_val_set_default(struct argv_spec_s *p_s, struct argv_error_s *p_e)
{
	int r;

	switch( p_s->type.data ) {
		case ARGV_TYPE_BOOL:
			if( p_s->defval.bool ) {
				r = argv_val_setbool(p_s);
			}
			break;

		case ARGV_TYPE_CHARP:
			r = argv_val_setcharp(p_s, p_s->defval.charp);
			break;

		case ARGV_TYPE_INT16:
			r = argv_val_seti(p_s, p_s->defval.int16, p_e);
			break;

		case ARGV_TYPE_UINT16:
			r = argv_val_setu(p_s, p_s->defval.uint16, p_e);
			break;

		case ARGV_TYPE_INT32:
			r = argv_val_seti(p_s, p_s->defval.int32, p_e);
			break;

		case ARGV_TYPE_UINT32:
			r = argv_val_setu(p_s, p_s->defval.uint32, p_e);
			break;

		case ARGV_TYPE_INT64:
			r = argv_val_seti(p_s, p_s->defval.int64, p_e);
			break;

		case ARGV_TYPE_UINT64:
			r = argv_val_setu(p_s, p_s->defval.uint64, p_e);
			break;

		default:
			r = EINVAL;
	}

	return r;
}

const char * argv_val_strtypedata(int data_type)
{
	char *p;

	switch( data_type ) {
		case ARGV_TYPE_BOOL:
			p = "bool";
			break;

		case ARGV_TYPE_CHARP:
			p = "charp";
			break;

		case ARGV_TYPE_INT16:
			p = "int16";
			break;

		case ARGV_TYPE_UINT16:
			p = "uint16";
			break;

		case ARGV_TYPE_INT32:
			p = "int32";
			break;

		case ARGV_TYPE_UINT32:
			p = "uint32";
			break;

		case ARGV_TYPE_INT64:
			p = "int64";
			break;

		case ARGV_TYPE_UINT64:
			p = "uint64";
			break;

		default:
			p = "unknown";
	}

	return p;
}

void argv_val_print(struct argv_spec_s *p_s, FILE *fp)
{
	switch( p_s->type.data ) {
		case ARGV_TYPE_BOOL:
			fprintf(fp, "%d", p_s->val.bool);
			break;

		case ARGV_TYPE_CHARP:
			fprintf(fp, "%s", p_s->val.charp);
			break;

		case ARGV_TYPE_INT16:
			fprintf(fp, "%d", (int)p_s->val.int16);
			break;

		case ARGV_TYPE_UINT16:
			fprintf(fp, "%d", (unsigned int)p_s->val.uint16);
			break;

		case ARGV_TYPE_INT32:
			fprintf(fp, "%d", (int)p_s->val.uint32);
			break;

		case ARGV_TYPE_UINT32:
			fprintf(fp, "%u", (unsigned int)p_s->val.uint32);
			break;

		case ARGV_TYPE_INT64:
			fprintf(fp, "%" PRIi64, p_s->val.int64);
			break;

		case ARGV_TYPE_UINT64:
			fprintf(fp, "%" PRIu64, p_s->val.uint64);
			break;

		default:
			fprintf(fp, "unknown type %d", p_s->type.data);
	}
}

int argv_val_process(struct argv_spec_s *p, char *optarg, struct argv_error_s *p_e)
{
	int r = EINVAL;

	p->arg = optarg;

	// inc num-occurences
	p->num_occurences++;

	if( p->type.data == ARGV_TYPE_BOOL ) {
		r = argv_val_setbool(p);
	}

	else if( p->type.data == ARGV_TYPE_CHARP ) {
		r = argv_val_setcharp(p, p->arg);
	}

	else if( p->type.data == ARGV_TYPE_INT16 || 
		p->type.data == ARGV_TYPE_INT32 || 
		p->type.data == ARGV_TYPE_INT64   ) {

		long int val;
		char *p_invalid;

		errno = 0;
		val = strtoll(p->arg, &p_invalid, 0);
		if( errno ) {
			int e = errno;
			snprintf(p_e->errmsg, ARGV_MAX_ERRMSG_LEN,
						"strtoll failed for %s", p->arg);
			return e;
		}

		//  invalid digit seen !!
		//  no valid digit is included in this check
		if( *p_invalid ) {
			snprintf(p_e->errmsg, ARGV_MAX_ERRMSG_LEN,
						"strtoll failed, invalid digit seen in %s",
						p->arg);
			return EINVAL;
		}

		//  set signed integer type value
		r = argv_val_seti(p, val, p_e);
	}

	else if( p->type.data == ARGV_TYPE_UINT16 || 
		p->type.data == ARGV_TYPE_UINT32 || 
		p->type.data == ARGV_TYPE_UINT64   ) {

		unsigned long long int val;
		char *p_invalid;

		errno = 0;
		val = strtoull(p->arg, &p_invalid, 0);
		if( errno ) {
			int e = errno;
			snprintf(p_e->errmsg, ARGV_MAX_ERRMSG_LEN,
						"strtoull failed for %s", p->arg);
			return e;
		}

		//  invalid digit seen !!
		//  no valid digit is included in this check
		if( *p_invalid ) {
			snprintf(p_e->errmsg, ARGV_MAX_ERRMSG_LEN,
						"strtoull failed, invalid digit seen in %s",
						p->arg);
			return EINVAL;
		}

		//  set unsigned integer type value
		r = argv_val_setu(p, val, p_e);
	}

	return r;
}
