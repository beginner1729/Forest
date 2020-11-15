#include <iostream>

#include "node_charecter.h"

//overloads
bool nodeHolder::operator < (const nodeHolder& node){
    return this->compareValue < node.compareValue;
}

bool nodeHolder::operator <= (const nodeHolder& node){
    return this->compareValue <= node.compareValue;
}

bool nodeHolder::operator > (const nodeHolder& node){
    return this->compareValue > node.compareValue;
}

bool nodeHolder::operator >= (const nodeHolder& node){
    return this->compareValue >= node.compareValue;
}

bool nodeHolder::operator == (const nodeHolder& node){
    return this->compareValue == node.compareValue;
}

std::ostream& operator <<(std::ostream &os, nodeHolder m) { 
    return os << m.get_compareval();
}

//constructors
nodeHolder::nodeHolder(){
    this->compareValue = 0;
    this->total_number = 0;
    this->nodeNumber = nullptr;
}

nodeHolder::nodeHolder(int nodeValue){
    this->compareValue = nodeValue;
    this->total_number = 0;
    this->nodeNumber = nullptr;
}
nodeHolder::nodeHolder(int nodeValue, int nodeNumber){
    this->total_number = 0;
    this->compareValue = 0;
    this->add_node(nodeNumber);
}

void nodeHolder::add_node(int nodeNumber){
    if (this->total_number == 0){
        this->nodeNumber = (int *)malloc(1 * sizeof(int));
        this->nodeNumber[0] = nodeNumber;
        this->total_number = 1;
    }
    else{
        int* temp_holder = (int *)malloc((this->total_number+1) * sizeof(int));
        for (int i=0; i < this->total_number; i++){
            temp_holder[i] = this->nodeNumber[i];
        }
        temp_holder[this->total_number] = nodeNumber;
        free(this->nodeNumber);
        this->nodeNumber = temp_holder;
        this->total_number += 1;
    }
}

int nodeHolder::get_compareval(){
    return this->compareValue;
}

int* nodeHolder::get_nodenumber(){
    return this->nodeNumber;
}

int nodeHolder::get_totalnumber(){
    return this->total_number;
}

