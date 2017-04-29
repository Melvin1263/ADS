#pragma once
#include "TreeNode.h"

class Tree
{
    TreeNode* anker;
    int letzte_id;
public:
    Tree();
    ~Tree();
    bool addNode(std::string, int, int, double);
    bool deleteNode(int id);
    TreeNode* search();
    void print();
};
