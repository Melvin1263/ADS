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

Tree& RingNode::getData()
{
    return SymbolicData;
}

void RingNode::setData(const Tree& data)
{
    SymbolicData = data;
}
