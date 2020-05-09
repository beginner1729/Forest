lang = python
compiler = g++
includefiles = /usr/include/python3.6m/


all: final_wrapper clean

swig_wrapper : btree_interface.i
	swig -c++ -$(lang) btree_interface.i

wrapper_objectfile: swig_wrapper
	$(compiler) -fPIC -c btree_interface_wrap.cxx -I$(includefiles)

node_object: node_class.cpp
	$(compiler) -fPIC -c node_class.cpp

final_wrapper: node_object wrapper_objectfile
	$(compiler) -shared node_class.o btree_interface_wrap.o -o _BinaryTree.so

clean:
	rm -f *.o