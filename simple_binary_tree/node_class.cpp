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
    bool is_present(T key_val);
    void assign_left(NodeClass<T>* left_val);
    void assign_right(NodeClass<T>* right);
    void change_val(T val);
    void assign_level(int val);
    NodeClass<T>* enter_graph(NodeClass<T>* head, T val, int level_val = 0);
    NodeClass<T>* enter_graph_iterative(NodeClass<T>* head, T val,int level_val = 0);
    void traverse_graph();
    int find_max_level(NodeClass<T>* head);
    int get_non_nulls(NodeClass<T>** array, int arlength);
    void clear_tree();
    NodeClass<T>* left_successor(NodeClass<T>* node);
    NodeClass<T>* right_successor(NodeClass<T>* node);
    std::pair<NodeClass<T>*, bool> get_successor(NodeClass<T>*node , std::string sucessor_type);
    bool delete_key(T key_val, std::string succesor_type="l");

};

template <typename T>
NodeClass<T>::NodeClass(T entry)
{
    this->val = entry;
    this->left = nullptr;
    this->right = nullptr;
    this->level = 0;
}

template <typename T>
NodeClass<T>::NodeClass()
{
    this->val = NULL;
    this->left = nullptr;
    this->right = nullptr;
    this->level = 0;
}

template<typename T>
NodeClass<T>::~NodeClass(){
    return;
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
void NodeClass<T>::assign_left(NodeClass<T>* left_val){
    this->left = left_val;
}

template<typename T>
void NodeClass<T>::assign_right(NodeClass<T>* right_val){
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
        if (child_holder){
            add_holder = child_holder;
            temp_level_val++;
        }
        else
        {
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
        
    }
    return head;
}

template<typename T>
int NodeClass<T>::get_non_nulls(NodeClass<T> **array, int arlength){
    
    int i, non_nulls = 0;
    for (i=0; i < arlength; i++){
        if (array[i] == nullptr)
            continue;
        auto left = array[i]->get_left();
        auto right = array[i]->get_right();
        if (left != nullptr)
            non_nulls++;
        if (right != nullptr)
            non_nulls++;
    }
    return non_nulls;
}

template<typename T>
int NodeClass<T>::find_max_level(NodeClass<T>* head){

    NodeClass<T>** parents;
    NodeClass<T>** childs;
    size_t pointer_size = sizeof(NodeClass<T> *);
    int count = 0, non_nulls, num_parents = 1, iterator = 0,i;

    parents = new NodeClass<T>*[1];
    parents[0] = this;
    
    while(true){
        iterator = 0;
        non_nulls = this->get_non_nulls(parents, num_parents);
        if (non_nulls == 0){
            delete[] parents;
            return count;
        }
        childs = new NodeClass<T>*[non_nulls];
        for (i=0; i < num_parents; i++){
            if (parents[i] == nullptr)
                continue;
            auto left = parents[i]->get_left();
            auto right = parents[i]->get_right();
            if (left != nullptr){
                childs[iterator] = left;
                iterator ++;
            }
            if (right != nullptr){
                childs[iterator] = right;
                iterator ++;
            }
        }
        count ++;
        delete[] parents;
        parents = childs;
        num_parents = non_nulls;
    }
    return -1;
}

template<typename T>
void NodeClass<T>::traverse_graph(){
    int max_level,curr_level = 1,temp_counter = 0,temp_size_holder;
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
    while(curr_level <= max_level+1){
        spaces_string = "";
        spaces_string.insert(0,spaces,' ');
        for (int i =0; i<temp_size_holder;i++){
            if (consumer[i] != NULL)
                std::cout << spaces_string << consumer[i]->get_val() << spaces_string;
            else
                std::cout << spaces_string << "_" << spaces_string;
        }
        std::cout<< std::endl;
        spaces_string.clear();
        spaces_string.shrink_to_fit();
        generator = consumer;
        consumer = new NodeClass<T>*[(1<<curr_level)];
        temp_counter = 0;
        
        for(int i=0; i<temp_size_holder;i++){
            if (generator[i]){
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
    delete[] consumer;
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
    this->assign_left(nullptr);
    this->assign_right(nullptr);
}

template<typename T>
bool NodeClass<T>::is_present(T key_val){

    NodeClass<T> *current_node;
    current_node = this;
    while (current_node != nullptr)
    {
        if (current_node->get_val() == key_val)
            return true;
        if (current_node->get_val() < key_val)
            current_node = current_node->get_right();
        else
            current_node = current_node->get_left();
    }
    return false;
}

template<typename T>
NodeClass<T>* NodeClass<T>::left_successor(NodeClass<T>* node){
    if (node == nullptr)
        return nullptr;
    NodeClass<T>* node_holder = node->get_left();

    while(node_holder && node_holder->get_right()){
        node_holder = node_holder->get_right();
    }
    return node_holder;
}

template<typename T>
NodeClass<T>* NodeClass<T>::right_successor(NodeClass<T>* node){
    
    if (node == nullptr)
        return nullptr;
    NodeClass<T>* node_holder = node->get_right();

    while(node_holder && node_holder->get_left()){
        node_holder = node_holder->get_left();
    }
    return node_holder;
}

template<typename T>
std::pair<NodeClass<T>*, bool> NodeClass<T>::get_successor(NodeClass<T>*node , std::string sucessor_type){
    NodeClass<T> * succesor;
    std::pair<NodeClass<T> *, bool> return_vals;
    succesor = sucessor_type == "l" ?
                this->left_successor(node) : this->right_successor(node);
    if (succesor){
        return_vals.first = succesor;
        return_vals.second = sucessor_type == "l";
        return return_vals;
    }
    //tring for other type of successor
    succesor = sucessor_type != "l" ?
                this->left_successor(node) : this->right_successor(node);
    
    return_vals.first = succesor;
    return_vals.second = sucessor_type != "l";
    return return_vals;
}

template<typename T>
bool NodeClass<T>::delete_key(T key_val, std::string succesor_type){

    NodeClass<T>* pos_holder = this;
    NodeClass<T>* succesor;
    NodeClass<T>* prev_val = NULL;
    bool is_left = false;
    
    while(true){
        //value found
        if (pos_holder != nullptr && pos_holder->get_val() == key_val){
            auto pair_vals = this->get_successor(pos_holder, succesor_type);
            succesor = pair_vals.first;
            if (succesor){
                //succesor found
                key_val = succesor->get_val();
                pos_holder->change_val(key_val);
                prev_val = pos_holder;
                is_left = pair_vals.second;
                pos_holder = is_left ? pos_holder->get_left() : pos_holder->get_right();
            }
            else{
                //node freed and deleted
                delete pos_holder;
                if (is_left){
                    prev_val->assign_left(nullptr);
                }
                else
                    prev_val->assign_right(nullptr);
                return true; //deletion successfull
            }
        }

        else if(pos_holder != nullptr && pos_holder->get_val() < key_val){
            prev_val = pos_holder;
            pos_holder = pos_holder->get_right();
            is_left = false;
        }
        else if(pos_holder != nullptr && pos_holder->get_val() > key_val){
            prev_val = pos_holder;
            pos_holder = pos_holder->get_left();
            is_left = true;
        }
        else{
            //value not found anywhere
            //deletion not successfull
            return false;
        }
    }
}