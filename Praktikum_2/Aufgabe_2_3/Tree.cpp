#include "Tree.h"

Tree::Tree(): letzte_id(0)
{
    anker = new TreeNode(nullptr, nullptr);
}

Tree::~Tree()
{
}

bool Tree::addNode(std::string name, int alter, int plz, double einkommen)
{
    TreeNode* node = new TreeNode();
    node->setName(name);
    node->setAlter(alter);
    node->setPLZ(plz);
    node->setEinkommen(einkommen);

    // Alter(int) + PLZ(int) + Einkommen(double) = Positionsindikator(int)
    int pos = node->Alter + node->PLZ + int(node->Einkommen);
    node->NodePosID = pos;
    node->NodeID = letzte_id++;

    TreeNode* parent = anker;
    TreeNode* child = anker->Rechts; // child ist Wurzelknoten

    while(child != nullptr)
    {
        parent = child;
        int key = child->NodePosID;
        if (pos == key)
            return false; // Knoten schon vorhanden!
        else if (pos > key)
            child = child->Rechts;
        else
            child = child->Links;
    }

    if(pos > parent->NodePosID)
        parent->Rechts = node;
    else
        parent->Links = node;
    return true;
}

bool Tree::deleteNode(int id)
{
    return false;
}
