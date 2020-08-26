#include <iostream>
#include "node_class.cpp"

int main(){
    NodeClass<int>* noob = new NodeClass<int>(4);
    NodeClass<int>* head = NULL;
    noob->change_val(6);
    int ar[8] = {12,3,21,15,8,9,4,11};
    bool run_etarnally = true;
    int choice, val;
    for(auto i:ar){
        head = noob->enter_graph_iterative(head,i);
    }
    std::cout << "Max level is " << head->find_max_level(head)<< std::endl;
    head->traverse_graph();
    std::cout << std::endl;
    while(run_etarnally){
        std::cout << "Enter 1 to enter into tree\nEnter 2 to print tree\nEnter 3 to delete an entry\nEnter 4 to find an element\
\n Enter 5 to exit\n";
        std::cin >> choice;
        switch (choice)
        {
        case 1:
            std::cout << "Enter a value : ";
            std::cin >> val;
            head->enter_graph_iterative(head, val);
            break;
        case 2:
            head->traverse_graph();
            break;
        case 3:
            std::cout << "Enter a value : ";
            std::cin >> val;
            if(head->delete_key(val))
                std::cout << "Deleted successufully" << std::endl;
            else
                std::cout << "Not deleted" << std::endl;
            break;
        case 4:
            std::cout << "Enter a value : ";
            std::cin >> val;
            if (head->is_present(val)){
                std::cout << "Found it in the tree" << std::endl;
            }
            else{
                std::cout<<"Value not found" << std::endl;
            }
            break;
        case 5:
            head->clear_tree();
            run_etarnally = false;
            break;
        default:
            break;
        }
    }
    delete(head);
    delete(noob);
    return 0;
}
