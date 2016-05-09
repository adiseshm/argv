/* Copyright (C) 2016 adiseshm

   Argument parsing in C.
   . t1.synopsis.spec test program

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
