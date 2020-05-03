#include <iostream>
#include <string.h>

#define MAX_SPACES 500


template <typename T>
class NodeClass
{
private:
    T val;
    NodeClass<T>* left;
    NodeClass<T>* right;
    int level;
public:
    NodeClass(T entry);
    NodeClass();
    ~NodeClass();
    T get_val();
    NodeClass<T>* get_left();
    NodeClass<T>* get_right();
    void assign_left(NodeClass<T>* left_val);
    void assign_right(NodeClass<T>* right);
    void change_val(T val);
    void assign_level(int val);
    NodeClass<T>* enter_graph(NodeClass<T>* head, T val, int level_val = 0);
    NodeClass<T>* enter_graph_iterative(NodeClass<T>* head, T val,int level_val = 0);
    void traverse_graph();
    int find_max_level(NodeClass<T>* head);
    void clear_tree();
};

template <typename T>
NodeClass<T>::NodeClass(T entry)
{
    this->val = entry;
    this->left = NULL;
    this->right = NULL;
    this->level = 0;
}

template <typename T>
NodeClass<T>::NodeClass()
{
    this->val = NULL;
    this->left = NULL;
    this->right = NULL;
    this->level = 0;
}

template<typename T>
NodeClass<T>::~NodeClass(){
    std::cout << "This node with value "<<this->get_val() << " will be freed"<<std::endl;
}


template<typename T>
T NodeClass<T>::get_val(){
    return this->val;
}

template<typename T>
NodeClass<T>* NodeClass<T>::get_left(){
    return this->left;
}

template<typename T>
NodeClass<T>* NodeClass<T>::get_right(){
    return this->right;
}

template<typename T>
void NodeClass<T>::assign_left(NodeClass* left_val){
    this->left = left_val;
}

template<typename T>
void NodeClass<T>::assign_right(NodeClass* right_val){
    this->right = right_val;
}

template<typename T>
void NodeClass<T>::change_val(T val){
    this->val = val;
}

template<typename T>
void NodeClass<T>::assign_level(int val){
    this->level = val;
}

template<typename T>
NodeClass<T>* NodeClass<T>::enter_graph(NodeClass<T>* head, T val,int level_val){
    if (head == NULL){
        head = new NodeClass<T>(val);
        head->assign_level(level_val);
    }
    else if (head->get_val() > val){
        head->assign_left(head->enter_graph(head->get_left(),val,level_val+1));
    }
    else{
        head->assign_right(head->enter_graph(head->get_right(),val,level_val+1));
    }
    return head;
}

template<typename T>
NodeClass<T>* NodeClass<T>::enter_graph_iterative(NodeClass<T>* head, T val,int level_val){
    if(head == NULL){
        head = new NodeClass<T>(val);
        head->assign_level(level_val);
        head->assign_level(level_val);
        return head;
    }
    NodeClass<T>* add_holder = head;
    NodeClass<T>* child_holder = NULL;
    bool is_left;
    int temp_level_val = level_val+1;
    while(true){
        if (add_holder->get_val() <= val){
            child_holder = add_holder->get_right();
            is_left = false;
        }
        else{
            child_holder = add_holder->get_left();
            is_left = true;
        }
        if (child_holder == NULL){
            if(is_left){
                add_holder->assign_left(new NodeClass<T>(val));
                add_holder->get_left()->assign_level(temp_level_val);
            }
            else{
                add_holder->assign_right(new NodeClass<T>(val));
                add_holder->get_right()->assign_level(temp_level_val);
            }
            break;
        }
        add_holder = child_holder;
        temp_level_val++;
    }
    return head;
}

template<typename T>
int NodeClass<T>::find_max_level(NodeClass<T>* head){
    if (head == NULL)
        return -1;
    int temp_val;
    temp_val = std::max(head->find_max_level(head->get_left()),
                        head->find_max_level(head->get_right()));
    return std::max(head->level,temp_val);
}

template<typename T>
void NodeClass<T>::traverse_graph(){
    int max_level,curr_level = 0,temp_counter = 0,temp_size_holder;
    long int spaces = 1;
    std::string spaces_string;
    NodeClass<T>** generator = NULL;
    NodeClass<T>** consumer = new NodeClass<T>*[1];

    max_level = this->find_max_level(this);
    spaces = spaces << (max_level);
    consumer[0] = this; // intitialization
    if (spaces > MAX_SPACES){
        std::cout << "Too many elements cannot be printed"<< std::endl;
        return;
    }
    temp_size_holder = 1;
    while(curr_level <= max_level){
        spaces_string = "";
        spaces_string.insert(0,spaces,' ');
        for (int i =0; i<temp_size_holder;i++){
            if (consumer[i] != NULL)
                std::cout << spaces_string << consumer[i]->get_val() << spaces_string;
            else
                std::cout << spaces_string << "_" << spaces_string;
        }
        std::cout<<std::endl;
        spaces_string.clear();
        spaces_string.shrink_to_fit();
        generator = consumer;
        consumer = new NodeClass<T>*[(1<<curr_level)];
        temp_counter = 0;
        for(int i=0; i<temp_size_holder;i++){
            if (generator[i]!=NULL){
                consumer[temp_counter] = generator[i]->get_left();
                consumer[temp_counter+1] = generator[i]->get_right();
            }
            else{
                consumer[temp_counter] = NULL;
                consumer[temp_counter+1] = NULL;
            }
            temp_counter += 2;
        }
        temp_size_holder = temp_counter;
        curr_level ++;
        spaces = spaces>>1;
        delete[] generator;
    }
    //delete [] consumer;
    //free(generator);
}

template<typename T>
void NodeClass<T>::clear_tree(){
    NodeClass<T>** consumer = NULL;
    NodeClass<T>** generator = new NodeClass<T>*[1];
    int max_level, curr_level = 1, temp_counter = 0,temp_size_holder = 1;
    max_level = this->find_max_level(this);
    generator[0] = this;
    NodeClass<T>* someholder;
    while (curr_level <= max_level)
    {
        consumer = new  NodeClass<T>*[(1<<curr_level)];
        for (int i =0; i<temp_size_holder;i++){
            if (generator[i]!=NULL){
                consumer[temp_counter] = generator[i]->get_left();
                consumer[temp_counter+1] = generator[i]->get_right();
            }
            else{
                consumer[temp_counter] = NULL;
                consumer[temp_counter+1] = NULL;
            }
            temp_counter += 2;
        }
        if (temp_size_holder > 1){
            for (int i =0; i<temp_size_holder;i++){
                if (generator[i] != NULL){
                    delete(generator[i]);
                }
            }
        }
        delete[] generator;
        temp_size_holder = 1<<curr_level;
        generator = consumer;
        curr_level ++;
        temp_counter =0;
    }
    for (int i =0; i<temp_size_holder;i++){
        if (consumer[i] != NULL){
            delete(consumer[i]);
        }
    }
    delete[] consumer;
    
}