FLAG = c++11

all: outfile clean

outfile: main.o node.o
	g++ -std=$(FLAG) -O3 main.o node.o -o outfile

node.o: node_class.cpp
	g++ -std=$(FLAG) -c node_class.cpp -o node.o

main.o : testingwithnew_node.cpp
	g++ -std=$(FLAG) -c testingwithnew_node.cpp -o main.o

clean:
	rm *.o