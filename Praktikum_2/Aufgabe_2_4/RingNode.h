#pragma once
#include <string>
#include "Tree.h"

class RingNode
{
    int OldAge;
    std::string Description;
    Tree SymbolicData;
public:
    RingNode* next;
public:
    RingNode(RingNode* next = nullptr) : 
        OldAge(0), next(next) 
    {};

    int getAge();
    void setAge(int);
    std::string getDescription();
    void setDescription(std::string);
    Tree& getData();
    void setData(const Tree& data);
};
