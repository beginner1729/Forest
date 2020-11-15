#include "machine_creator.h"


Automata_Machine::Automata_Machine(){
    this->num_states = 0;
    this->num_finalstates = 0;
    this->final_states = nullptr;
    this->all_states = nullptr;
    this->num_chars = 0;
    this->symbols = nullptr;
    this->current_state=-1;
    this->initial_state=-1;
    nodeHolder dummynode = nodeHolder(0);
    NodeClass<nodeHolder>* headholder = new NodeClass<nodeHolder>(dummynode);
    this->transition_matrix = 
        headholder->enter_graph(this->transition_matrix, dummynode);
    this->int_space = sizeof(int) * 8;
}

// Getters and the setters
int* Automata_Machine::get_states(){
    return this->all_states;
}

int* Automata_Machine::get_finalstates(){
    return this->final_states;
}

char* Automata_Machine::get_symbols(){
    return this->symbols;
}

int Automata_Machine::get_initialstate(){
    return this->initial_state;
}

int Automata_Machine::get_currentstate(){
    return this->current_state;
}

int Automata_Machine::get_numstates(){
    return this->num_states;
}
int Automata_Machine::get_numfinalstates(){
    return this->num_finalstates;
}
int Automata_Machine::get_numchars(){
    return this->num_chars;
}

NodeClass<nodeHolder>* Automata_Machine::get_transitiontree(){
    return this->transition_matrix;
}

// adding something to the automata
template<class T>
bool Automata_Machine::add_something(T value, T*& value_container, 
    int& container_len){
    if (value_container == nullptr){
        value_container = (T *)malloc(1 * sizeof(T));
        value_container[0] = value;
        container_len = 1;
        return true;
    }
    for (int i=0; i < container_len; i++){
        if (value == value_container[i]){
            std::cout << "Value already present" << std::endl;
            return true;
        }
    }
    container_len += 1;
    T *temp_array_holder = (T *)malloc((container_len) * sizeof(T));
    for (int i=0; i < (container_len-1); i++)
        temp_array_holder[i] = value_container[i];
    temp_array_holder[container_len-1] = value;
    free(value_container);
    value_container = temp_array_holder;
    return true;
}

bool Automata_Machine::add_state(int state_number){
    return this->add_something(state_number, this->all_states,
         this->num_states);
}

bool Automata_Machine::add_finalstate(int state_number){

    int prev_numfinal = this->num_finalstates;
    bool to_return  = this->add_something(state_number, this->final_states,
         this->num_finalstates), check_state=true;
    if (this->num_finalstates > prev_numfinal)
    {
        check_state = this->add_state(state_number);
        if (!check_state){
            std::cout << "Something went wrong in adding to the all state list";
            std::cout << std::endl;
        }
    }
    return to_return;
}

bool Automata_Machine::add_charecter(char symbol){
    return this->add_something(symbol, this->symbols,
         this->num_chars);
}

bool Automata_Machine::add_arc(int state1, int state2, char symbol){
    this->add_state(state1);
    this->add_state(state2);
    this->add_charecter(symbol);
    std::vector<int> state_binary = this->get_binaryvalue(state1);
    std::vector<int> symbol_binary = this->get_binaryvalue(int(symbol));
    NodeClass<nodeHolder>* next_node = this->transition_matrix;
    for (auto bin_val : state_binary){
        //turn right
        if (bin_val){
            next_node->assign_right(this->add_totree(next_node->get_right()));
            next_node = next_node->get_right();
        }
        else{
            next_node->assign_left(this->add_totree(next_node->get_left()));
            next_node = next_node->get_left();
        }
    }
    for (auto bin_val : symbol_binary){
        //turn right
        if (bin_val){
            next_node->assign_right(this->add_totree(next_node->get_right()));
            next_node = next_node->get_right();
        }
        else{
            next_node->assign_left(this->add_totree(next_node->get_left()));
            next_node = next_node->get_left();
        }
    }
    // convention is that the value is stroed in the left node
    nodeHolder new_node = nodeHolder(0, state2);
    if (next_node->get_left() == nullptr){
        next_node->assign_left(this->add_totree(next_node->get_left()));
    }
    else{
        // this is the case for NDFA where there could be more than one states
        new_node = next_node->get_val();
        new_node.add_node(state2);
    }
    //changing the left val
    next_node->get_left()->change_val(new_node);
    return true;
}

nodeHolder Automata_Machine::query_arc(int startstate, char symbol){
    std::vector<int> state_binary = this->get_binaryvalue(startstate);
    std::vector<int> symbol_binary = this->get_binaryvalue(int(symbol));
    NodeClass<nodeHolder>* next_node = this->transition_matrix;
    nodeHolder node_value = nodeHolder();
    for (auto bin_val : state_binary){
        if (next_node == nullptr)
        {
            std::cout << "Node does not exist in the transition matrix" << std::endl;
            return node_value;
        }
        //turn right
        if (bin_val){
            next_node = next_node->get_right();
        }
        else{
            next_node = next_node->get_left();
        }
    }
    
    for (auto bin_val : symbol_binary){
        if (next_node == nullptr)
        {
            std::cout << "Symbol does not exist in the transition matrix" << std::endl;
            return node_value;
        }
        //turn right
        if (bin_val){
            next_node = next_node->get_right();
        }
        else{
            next_node = next_node->get_left();
        }
    }

    if (next_node == nullptr){
        std::cout << "Sorry nothing found for the given node and the symbol" << std::endl;
        return node_value;
    }
    node_value = next_node->get_left()->get_val();
    
    
    return node_value;
}

//utils function
std::vector<int> Automata_Machine::get_binaryvalue(int value){
    std::vector<int> binary_values;
    int temp_value = value;
    
    for (int i=0; i < this->int_space; i++){
        binary_values.insert(binary_values.begin(), (temp_value & 1));
        temp_value = temp_value >> 1;
    }
    return binary_values;
}

NodeClass<nodeHolder>* Automata_Machine::add_totree(NodeClass<nodeHolder>* trans_matrix){
    
    if (trans_matrix == nullptr){
        nodeHolder dummynode = nodeHolder(0);
        return (new NodeClass<nodeHolder>(dummynode));
    }
    return trans_matrix;

}

int* Automata_Machine::get_state_fromnode(nodeHolder node){
    return nullptr;
}