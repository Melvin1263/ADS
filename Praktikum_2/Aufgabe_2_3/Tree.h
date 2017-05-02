#pragma once
#include "TreeNode.h"
#include <functional>

class Tree
{
    TreeNode* anker;
    int letzte_id;
public:
    Tree();
    ~Tree();
    bool addNode(std::string, int, int, double);
    bool deleteNode(int id);
    TreeNode* search(std::string name);
    void print();
    TreeNode *minNode(TreeNode *k, TreeNode*&parent);
    TreeNode *maxNode(TreeNode *k);
    TreeNode *findNode(int item);
private:
    void printPreorder(TreeNode* k);
    void traversePreorder(TreeNode* k, std::function<void(TreeNode *k)> callback);
    void traverseInorder(TreeNode* k, std::function<void(TreeNode *k)> callback);
    void traversePostorder(TreeNode* k, std::function<void(TreeNode *k)> callback);
};
