#pragma once
#include <string>

class RingNode
{
    int OldAge;
    std::string Description;
    std::string SymbolicData;
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
    std::string getData();
    void setData(std::string);
};
