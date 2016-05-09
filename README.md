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

## Usage

Define a structure to hold the output of argument parsing  
Define an array of struct argv\_spec\_s to hold the arguments specifications  
Define an array of struct argv\_synopsis\_s to hold the list of valid permutation combinations of the various options, incl. the optional arguments  
Call argv\_parse()  
  
tests/t1.c has an example of the above  

## API

* argv\_parse() Parse the arguments, based on given specifications and store result in p\_user\_struct  
    * argc                   IN Number of elements in argv[]  
    * argv                   IN-OUT List of argument vectors, this will be mutated  
    * p\_argv\_spec          IN Array of argument specifications  
    * p\_argv\_synopsis      IN Array of synopsis specifications  
    * p\_user\_struct        OUT Pointer to user struct, where the results are to be returned  
    * p\_non\_option\_start  OUT Returns the index in argv[] of the first non-option index  
    * p\_synop\_idx          OUT Returns the index in p\_argv\_synopsis which matches the given list of options  
    * p\_e                   OUT Returns the detailed error message, if any  
* argv\_usage Auto-generate the usage from the given specifications  
    * fp                     IN FILE pointer, where the usageinfo should be written to  
    * progname               IN The program name, which should be used as the prefix  
    * p\_argv\_spec          IN Array of argument specifications  
    * p\_argv\_synopsis      IN Array of synopsis specifications  
    * p\_e                   OUT Returns the detailed error message, if any  
* struct argv\_spec\_s    Struct specifying the details an argument  
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
* struct argv\_synopsis\_s Struct specifying the details of a synopsis  
    * name                  IN An unique name for this synopsis  
    * cmd                   IN An unique identifier for this synopsis  
    * ids\_m                IN Mandatory list of arguments  
    * ids\_o                IN Optional list of arguments  
* struct argv\_error\_s    Struct filled and returned on an error  
    * errmsg                OUT Error message string  
* ARGV\_SPEC\_* macros  

**Last updated 09 May 2016**
