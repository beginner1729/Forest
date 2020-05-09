%module BinaryTree

%{
    #include "node_class.cpp"
%}

%include "node_class.cpp"

%template(IntBinaryClass) NodeClass<int>;
%template(DoubleBinaryClass) NodeClass<double>;
%template(CharBinaryClass) NodeClass<char>;