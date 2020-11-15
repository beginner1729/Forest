#include <iostream>
class nodeHolder{
    private:
        int compareValue;
        int *nodeNumber;
        int total_number;
    public:
        nodeHolder(int nodeValue);
        nodeHolder(int nodeValue, int nodeNumber);
        nodeHolder();

        //operator overrides
        bool operator < (const nodeHolder& node);
        bool operator > (const nodeHolder& node);
        bool operator <= (const nodeHolder& node);
        bool operator >= (const nodeHolder& node);
        bool operator == (const nodeHolder& node);
        friend std::ostream& operator <<(std::ostream &os, nodeHolder m);

        //getter funcs
        int get_compareval();
        int* get_nodenumber();
        int get_totalnumber();

        //util functions
        void add_node(int nodeNumber);
};

