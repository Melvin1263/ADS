#include "RingNode.h"

int RingNode::getAge()
{
    return OldAge;
}

void RingNode::setAge(int age)
{
    OldAge = age;
}

std::string RingNode::getDescription()
{
    return Description;
}

void RingNode::setDescription(std::string description)
{
    Description = description;
}

std::string RingNode::getData()
{
    return SymbolicData;
}

void RingNode::setData(std::string data)
{
    SymbolicData = data;
}
