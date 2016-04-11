#  Copyright (C) 2016 adiseshm
# 
#  Argument parsing in C.
# 
#  The argv C Library is free software; you can redistribute it and/or
#  modify it under the terms of the GNU Lesser General Public
#  License as published by the Free Software Foundation; either
#  version 3.0 of the License, or (at your option) any later version.
#
#  This argv C Library is distributed in the hope that it will be useful,
#  but WITHOUT ANY WARRANTY; without even the implied warranty of
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
#  Lesser General Public License for more details.
#
#  You should have received a copy of the GNU Lesser General Public
#  License along with the argv C Library; if not, write to the Free
#  Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA
#  02111-1307 USA.
#

LN=ln
CC=gcc
CFLAGS= -I ../ -g -Werror -Wall
CPPFLAGS=

LDFLAGS=
LOADLIBES=
LDLIBS=../src/libargv.so


#  cancel this implicit rule, so as to kick
#  in the below pattern rules
%: %.c


#  pre-processed file
%.i: %.c
	$(CC) -DMKRULE=c2i    $(CPPFLAGS) $(CFLAGS) $< -o $@ -E

#  simple object file
%.o: %.c
	@#$(CC) -DMKRULE=c2d    $(CPPFLAGS) $(CFLAGS) $< -MM -MD
	$(CC) -DMKRULE=c2o    $(CPPFLAGS) $(CFLAGS) $< -o $@ -c

#  PIC object file
%.pic: %.c
	@#$(CC) -DMKRULE=c2d    $(CPPFLAGS) $(CFLAGS) $< -MM -MD
	$(CC) -DMKRULE=c2pic  $(CPPFLAGS) $(CFLAGS) $< -o $@ -c -fpic

#  shared object file
lib%.so:
	$(CC) -DMKRULE=pic2so -shared $^ -Wl,-soname=$@.$(LIBVER) -o $@.$(LIBVER)
	@echo -e "ln  -DMKRULE=pic2so \c"
	$(LN) -f -s $@.$(LIBVER) $@

#  executable object file
%: %.o
	$(CC) -DMKRULE=o2e    $^ $(LDFLAGS) $(LOADLIBES) $(LDLIBS) -o $@
