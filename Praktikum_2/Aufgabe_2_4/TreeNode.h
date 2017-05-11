#pragma once
#include <string>

class TreeNode
{
    int NodePosID;
    int NodeID;
    std::string Name;
    int Alter;
    double Einkommen;
    int PLZ;
    TreeNode* Links;
    TreeNode* Rechts;
public:
    TreeNode(TreeNode* links = nullptr, TreeNode* rechts = nullptr);
    std::string getName() const;
    int getAlter() const;
    double getEinkommen() const;
    int getPLZ() const;
    int getNodeID() const;
    int getNodePosID() const;
    void setName(std::string);
    void setAlter(int);
    void setEinkommen(double);
    void setPLZ(int);
    void printData();
    void setLinks(TreeNode*);
    void setRechts(TreeNode*);
    TreeNode* getLinks();
    TreeNode* getRechts();

    friend class Tree;
};
