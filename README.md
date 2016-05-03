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

## Build

autoreconf --install
./configure
make
make install

## API

* argv\_parse  
* argv\_usage  
* struct argv\_spec\_s  
    * id  
    * name\_long  
    * name\_val  
    * help\_arg  
    * help  
    * type.data
    * type.flags
    * type.multiples
    * spec.range
    * spec.list
* struct argv\_synopsis\_s  
    * name  
    * cmd  
    * ids\_m  
    * ids\_o  
* struct argv\_error\_s  
    * errmsg
* ARGV\_SPEC\_* macros  

**Last updated 12 April 2016**
