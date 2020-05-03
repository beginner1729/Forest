FLAG = c++11

all: outfile clean

outfile: main.o node.o
	g++ -std=$(FLAG) main.o node.o -o outfile

node.o: node_class.cpp
	g++ -std=$(FLAG) -c node_class.cpp -o node.o

main.o : testingstacknode.cpp
	g++ -std=$(FLAG) -c testingstacknode.cpp -o main.o

clean:
	rm *.o