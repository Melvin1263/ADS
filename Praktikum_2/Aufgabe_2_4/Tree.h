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
    Tree::Tree(const Tree& t);
    const Tree& Tree::operator=(Tree t);
    bool addNode(std::string, int, int, double);
    bool deleteNode(int id);
    TreeNode* search(std::string name);
    void print();
    TreeNode *minNode(TreeNode *k, TreeNode*&parent);
    TreeNode *maxNode(TreeNode *k);
    TreeNode *findNode(int item);
    void swap(Tree& t1, Tree& t2);
    void traversePreorder(std::function<void(const TreeNode *k)> callback) const;
private:
    void printPreorder(TreeNode* k);
    void traversePreorder(TreeNode* k, std::function<void(TreeNode *k)> callback);
    void traverseInorder(TreeNode* k, std::function<void(TreeNode *k)> callback);
    void traversePostorder(TreeNode* k, std::function<void(TreeNode *k)> callback);
    void traversePreorder(const TreeNode* k, std::function<void(const TreeNode *k)> callback) const;
    void traverseInorder(const TreeNode* k, std::function<void(const TreeNode *k)> callback) const;
    void traversePostorder(const TreeNode* k, std::function<void(const TreeNode *k)> callback) const;
};
