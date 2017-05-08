#include "Tree.h"
#include <iostream>
#include <iomanip>

Tree::Tree(): letzte_id(0)
{
    anker = new TreeNode(nullptr, nullptr);
}

Tree::~Tree()
{
    traversePostorder(anker, [](TreeNode* k)
    {
        delete k;
    });
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

bool Tree::deleteNode(int item)
{
    if (anker == nullptr) 
        return false;

    TreeNode *parent = anker;
    TreeNode *current = anker->Rechts;
    while (current != nullptr && current->NodePosID != item)
    {
        parent = current;
        if (item > parent->NodePosID)
            current = current->Rechts;
        else
            current = current->Links;
    }
    
    if(current == nullptr)
        return false;

    std::cout << "Zu loeschender Knoten: " << current->NodePosID << std::endl;
    std::cout << "Elternknoten ist: " << parent->NodePosID << std::endl;

    if (current->Links == nullptr && current->Rechts == nullptr) // Knoten ist Blatt, einfachster Fall
    {
        std::cout << "Zu loeschender Knoten ist ein Blatt." << std::endl;

        // Ueberpruefen ob current linker oder rechter Knoten ist.
        if (parent->Links == current)
            parent->Links = nullptr;
        else
            parent->Rechts = nullptr;

        // Knoten löschen
        delete current;
    }
    else if (current->Links != nullptr && current->Rechts == nullptr) // Ein Nachfolgeknoten Links
    {
        std::cout << "Zu loeschender Knoten hat Nachfolger links." << std::endl;

        // Ueberpruefen ob current linker oder rechter Knoten ist.
        if (parent->Links == current)
            parent->Links = current->Links;
        else
            parent->Rechts = current->Links;

        // Knoten löschen
        delete current;
    }
    else if (current->Links == nullptr && current->Rechts != nullptr) // Ein Nachfolgeknoten Rechts
    {
        std::cout << "Zu loeschender Knoten hat Nachfolger rechts." << std::endl;

        // Ueberpruefen ob current linker oder rechter Knoten ist.
        if (parent->Links == current)
            parent->Links = current->Rechts;
        else
            parent->Rechts = current->Rechts;

        // Knoten löschen
        delete current;
    }
    else // sonst zwei Nachfolger
    {
        // Pointer auf Elternknoten vom kleinsten Knoten im rechten Teilbaum
        TreeNode *minParent = current;
        // Kleinsten Knoten im Rechten Teilbaum suchen
        TreeNode *min = minNode(current->Rechts, minParent); 

        std::cout << "Zu loeschender Knoten hat zwei Nachfolger." << std::endl;
        std::cout << "Kleinster Knoten im Rechten Teilbaum ist: " << min->NodePosID << std::endl;
        std::cout << "Elternknoten von " << min->NodePosID << " ist " << minParent->NodePosID << std::endl;

        // Der kleinste Knoten kann noch einen Rechten Nachfolgeknoten haben     
        if (current->Rechts != min)
        {
            if (min->Rechts != nullptr)
                minParent->Links = min->Rechts;

            minParent->Links = nullptr;
        }
        
        // Der kleinste Knoten wird Nachfolger vom Elternknoten
        if (parent->Rechts == current)
            parent->Rechts = min;
        else
            parent->Links = min;

        // Alten Nachfolgeknoten von current umbiegen 
        // auf neuen Nachfolger vom Elternknoten
        if (current->Links != min)
            min->Links = current->Links;
        if (current->Rechts != min)
            min->Rechts = current->Rechts;

        // Knoten löschen
        delete current;
    }

    return true;
}

TreeNode * Tree::search(std::string name)
{
    TreeNode* result = nullptr;
    traverseInorder(anker->Rechts, [name, &result](TreeNode* k)
    {
        if (k->Name == name) 
            result = k;
    });
    return result;
}

void Tree::print()
{
    //std::cout << "ID | Name       | Alter | Einkommen | PLZ     | Pos" << std::endl;
    std::cout << std::setw(3) << std::left << "ID" << '|' 
        << std::setw(12) << "Name" << '|' 
        << std::setw(7) << "Alter" << '|'
        << std::setw(11) << "Einkommen" << '|'
        << std::setw(9) << "PLZ" << '|'
        << std::left << "Pos"
        << std::endl;
    std::cout << "--------------------------------------------------------" << std::endl;
    printPreorder(anker->Rechts);
}

TreeNode * Tree::minNode(TreeNode *k, TreeNode*&parent)
{
    while (k->Links != nullptr)
    {
        parent = k;
        k = k->Links;
    }
    return k;
}

TreeNode * Tree::maxNode(TreeNode *k)
{
    while (k->Rechts != nullptr)
        k = k->Rechts;
    return k;
}

TreeNode * Tree::findNode(int item)
{
    return nullptr;
}

void Tree::printPreorder(TreeNode *k)
{
    using namespace std;
    if (k == nullptr)
        return;

    traversePreorder(k, [&](TreeNode *ks)->void
    {
        cout << setw(3) << ks->NodeID << "|"
            << setw(12) << ks->Name << "|"
            << setw(7) << ks->Alter << "|"
            << setw(11) << ks->Einkommen << "|"
            << setw(9) << ks->PLZ << "|"
            << ks->NodePosID << endl;
    });
}

void Tree::traversePreorder(TreeNode *k, std::function<void(TreeNode *)> callback)
{
    if (k == nullptr)
        return;

    callback(k);
    traversePreorder(k->Links, callback);
    traversePreorder(k->Rechts, callback);
}

void Tree::traverseInorder(TreeNode *k, std::function<void(TreeNode*)> callback)
{
    if (k == nullptr)
        return;

    traverseInorder(k->Links, callback);
    callback(k);
    traverseInorder(k->Rechts, callback);
}

void Tree::traversePostorder(TreeNode *k, std::function<void(TreeNode*)> callback)
{
    if (k == nullptr)
        return;

    traversePostorder(k->Links, callback);
    traversePostorder(k->Rechts, callback);
    callback(k);
}
