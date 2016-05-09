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
#include "inc/val.h"

void argv_dump_specs(struct argv_spec_s *p_s)
{
	int i;

	printf("ARG-SPECS\n");
	printf("\t%-3s    %-3s    %-12s    %-15s    %s\n", "No", "Id", "Type", "Name", "CliArg");

	for(i=0; p_s[i].name_long; i++) {
		printf("\t%-3d    %-3d    %-6s-%d-%-3d    %-15s    %s\n",
				i,
				p_s[i].id,
				argv_val_strtypedata(p_s[i].type.data),
				p_s[i].type.flags,
				p_s[i].type.multiples,
				p_s[i].name_long,
				p_s[i].arg);
	}

	return;
}
