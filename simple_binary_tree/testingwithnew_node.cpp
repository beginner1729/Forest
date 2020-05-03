#include <iostream>
#include "node_class.cpp"

int main(){
    NodeClass<int>* noob = new NodeClass<int>(4);
    NodeClass<int>* head = NULL;
    NodeClass<int>* head2 = NULL;
    noob->change_val(6);
    int ar[7] = {12,3,21,15,8,33,9};

    for(auto i : ar){
        head = noob->enter_graph(head,i);
    }
    std::cout<<"--------------------------------------\n";

    for(auto i:ar){
        head2 = noob->enter_graph_iterative(head2,i);
    }
    head->traverse_graph();
    head2->traverse_graph();

    head->clear_tree();
    head2->clear_tree();
    delete(head2);
    delete(head);
    return 0;
}