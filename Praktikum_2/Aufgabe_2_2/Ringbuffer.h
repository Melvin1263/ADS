#pragma once
#include "RingNode.h"

class Ringbuffer
{
    RingNode* anker;
    int size;
public:
    Ringbuffer(int n);
    ~Ringbuffer();
    bool addNode(const std::string, const std::string);
    RingNode* search(std::string);
    void print();
};
