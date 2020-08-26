# Simple Binary Tree

This is a simple binary tree implementation using templates in c++.
I have tried to explain some nuances of c++ templates through this implementation also a brush up of the ideas. Will add detailed comments soon.

# How to use

## C++ one
This implemenataion is not very user friendly the testing examples simple put the tools of the programs in the display.
Simply run the makefile node_makefile.mk with the command `make -f node_makefile.mk all` and run the `outfile` binary, enjoy.

## Python one

Python wrapper added for python version of 3.6. To create python imports just run the following

`make -f swig_makefile.mk`

This should produce 3 files `BinaryTree.py, BinaryTree.so, _BinaryTree.so` . And the file` some_python_usage.py` should work just fine.


### Dependencies

Listing some dependencies just in case one runs into trouble

__Swig version__

`swig -verison` returned me the following
```
SWIG Version 3.0.12

Compiled with g++ [x86_64-pc-linux-gnu]

Configured options: +pcre

Please see http://www.swig.org for reporting bugs and further information
```

__Make Version__

```GNU Make 4.1
Built for x86_64-pc-linux-gnu
```
__g++ version__

```
g++ (Ubuntu 7.5.0-3ubuntu1~18.04) 7.5.0
```