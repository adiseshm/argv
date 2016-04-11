/* Copyright (C) 2016 adiseshm

   Argument parsing in C.
   . argv-val utility functions

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

#ifndef __ARGV_VAL_H__
#define __ARGV_VAL_H__

#include "api/argv.h"

extern const char * argv_val_strtypedata(int data_type);
extern int argv_val_set_default(struct argv_spec_s *p_s, struct argv_error_s *p_e);
extern int argv_val_process(struct argv_spec_s *p, char *optarg, struct argv_error_s *p_e);
extern void argv_val_print(struct argv_spec_s *p_s, FILE *fp);

#endif
