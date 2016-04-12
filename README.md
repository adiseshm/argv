## Build

cd src; make  
cd ..  
cd tests; make  

LD\_LIBRARY\_PATH=../src  ./t1  --file myfile --offset 123456

## API

* argv\_parse  
* argv\_usage  
* struct argv\_spec\_s  
* struct argv\_synopsis\_s  
* struct argv\_error\_s
* ARGV\_VAL\_UPTR\_* macros  

**Last updated 12 April 2016**
