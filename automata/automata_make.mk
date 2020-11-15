FLAG = c++11

INCLUDE = ../simple_binary_tree

all: outfile clean

outfile: testingautomaton.cpp machine.o nodechar.o
	g++ -std=$(FLAG) -I $(INCLUDE) -O3 -Wall -Werror testingautomaton.cpp machine.o nodechar.o -o outfile

nodechar.o: node_charecter.cpp
	g++ -std=$(FLAG) -I $(INCLUDE) -c node_charecter.cpp -o nodechar.o

machine.o : machine_creator.cpp
	g++ -std=$(FLAG) -I $(INCLUDE) -c machine_creator.cpp -o machine.o

clean:
	rm *.o