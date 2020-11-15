#include "machine_creator.h"

int main(){
    Automata_Machine* automata = new Automata_Machine();
    automata->add_state(12);
    automata->add_state(13);
    automata->add_state(14);
    automata->add_state(15);
    automata->add_state(15);

    int* temp = automata->get_states();
    std::cout << temp[0] << " " << temp[2];
    std::cout << std::endl;
    std::cout << "Number of states is " << automata->get_numstates();
    std::cout << std::endl;

    automata->add_arc(12,13, 'a');
    automata->add_arc(12,14, 'b');
    //automata->get_transitiontree()->traverse_graph();

    std::cout <<"Quering arc 12, \'a\' "<< std::endl;
    auto query_result = automata->query_arc(12, 'a');
    if (query_result.get_totalnumber() > 0){
        std::cout <<"Result is "<< std::endl;
        std::cout << query_result.get_nodenumber()[0] <<std::endl;
    }
    std::cout <<"Quering arc 12, \'c\' "<< std::endl;
    query_result = automata->query_arc(12, 'c');
    
    if (query_result.get_totalnumber() > 0){
        std::cout <<"Result is "<< std::endl;
        std::cout << query_result.get_nodenumber()[0] <<std::endl;
    }
    return 0;
}