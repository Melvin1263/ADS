#pragma once
#include "RingNode.h"
#include "Tree.h"

class Ringbuffer
{
    RingNode* anker;
    int size;
public:
    Ringbuffer(int n);
    ~Ringbuffer();
    bool addNode(const std::string, const Tree&);
    RingNode* search(std::string);
    void print();
};
