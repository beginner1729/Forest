#include <iostream>
#include <string.h>
#include <vector>
#include "node_class.cpp"
#include "node_charecter.h"

class Automata_Machine{
    private:
        int num_states;
        int num_finalstates;
        int *final_states;
        int *all_states;
        int num_chars;
        char *symbols;
        int current_state;
        int initial_state;
        int int_space;
        NodeClass<nodeHolder> *transition_matrix;

    public:
        //constructors
        Automata_Machine(char* symbols,int num_symbols, int* states, int num_states,
            int* final_states, int num_finalstates);
        Automata_Machine(); //automata with only starting state 0 and no arcs
        template<class T> bool add_something(T value, T*& value_container, 
            int& container_len);
        
        //getters and setters
        int* get_states();
        int* get_finalstates();
        char* get_symbols();
        int get_currentstate();
        int get_initialstate();
        int get_numstates();
        int get_numfinalstates();
        int get_numchars();
        NodeClass<nodeHolder>* get_transitiontree();
        
        // various addition functions
        bool add_state(int state_number);
        bool add_finalstate(int state_number);
        bool add_charecter(char char_val);
        bool add_arc(int state1,int state2, char symbol);
        nodeHolder query_arc(int startstate, char symbol);

        //util function
        std::vector<int> get_binaryvalue(int value);
        int make_transition(char symbol, int current_state);
        int* get_state_fromnode(nodeHolder node);
        bool is_accepted();
    private:
        NodeClass<nodeHolder>* add_totree(NodeClass<nodeHolder>* trans_matrix);    
};