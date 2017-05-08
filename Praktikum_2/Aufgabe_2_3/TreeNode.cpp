#include "TreeNode.h"
#include <iostream>

TreeNode::TreeNode(TreeNode * links, TreeNode * rechts) : 
    NodePosID(0), NodeID(0), Alter(0), 
    Einkommen(0), PLZ(0), Links(links), Rechts(rechts)
{
}

std::string TreeNode::getName()
{
    return Name;
}

int TreeNode::getAlter()
{
    return Alter;
}

double TreeNode::getEinkommen()
{
    return Einkommen;
}

int TreeNode::getPLZ()
{
    return PLZ;
}

int TreeNode::getNodeID()
{
    return NodeID;
}

int TreeNode::getNodePosID()
{
    return NodePosID;
}

void TreeNode::setName(std::string name)
{
    Name = name;
}

void TreeNode::setAlter(int alter)
{
    Alter = alter;
}

void TreeNode::setEinkommen(double einkommen)
{
    Einkommen = einkommen;
}

void TreeNode::setPLZ(int plz)
{
    PLZ = plz;
}

void TreeNode::printData()
{
    std::cout << "Name: " << Name << " Alter: " << Alter << " Einkommen: " << Einkommen << " PLZ: " << PLZ << std::endl;
}

void TreeNode::setLinks(TreeNode *links)
{
    Links = links;
}

void TreeNode::setRechts(TreeNode *rechts)
{
    Rechts = rechts;
}

TreeNode * TreeNode::getLinks()
{
    return Links;
}

TreeNode * TreeNode::getRechts()
{
    return Rechts;
}
