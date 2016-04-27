## Build

cd src; make  
cd ..  
cd tests; make  

LD\_LIBRARY\_PATH=../src  ./t1  --file myfile --offset 123456

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
