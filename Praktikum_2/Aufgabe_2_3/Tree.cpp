#include "Tree.h"
#include <iostream>
#include <iomanip>

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

bool Tree::deleteNode(int item)
{
	if (anker == nullptr) 
		return false;

	TreeNode *parent = nullptr;
	TreeNode *current = anker;
	while (current != nullptr && current->NodePosID != item)
	{
		parent = current;
		if (item > parent->NodePosID)
			current = current->Rechts;
		else
			current = current->Links;
	}

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
		TreeNode *minParent;
		// Kleinsten Knoten im Rechten Teilbaum suchen
		TreeNode *min = minNode(current->Rechts, minParent); 

		// Da minNode kein minParent zurückgibt muss der 
		// kleinste Knoten direkt unser Nachfolger vom zu
		// löschenden Knoten sein.
		if (minParent == nullptr)
			minParent = current;

		std::cout << "Zu loeschender Knoten hat zwei Nachfolger." << std::endl;
		std::cout << "Kleinster Knoten im Rechten Teilbaum ist: " << min->NodePosID << std::endl;
		std::cout << "Elternknoten von " << min->NodePosID << " ist " << minParent->NodePosID << std::endl;

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
	parent = nullptr;
	return k;
}

TreeNode * Tree::maxNode(TreeNode *k)
{
	while (k->Rechts != nullptr)
	{
		k = k->Rechts;
	}
	return k;
}

TreeNode * Tree::findNode(int item)
{
	return searchRecursive(anker, item);
}

TreeNode * Tree::searchRecursive(TreeNode * k, int key)
{
	// in: Wurzel k, x = zu suchender Schlüssel
	// out: Element mit gesuchtem Wert oder null
	if (k == nullptr)
		return nullptr;
	else if (key == k->NodePosID)
		return k;
	else if (key < k->NodePosID)
	{
		return searchRecursive(k->Links, key);
	}
	else
	{
		return searchRecursive(k->Rechts, key);
	}
}

void Tree::printPreorder(TreeNode * k)
{
	using namespace std;
	if (k != nullptr)
	{
		cout << setw(3) << k->NodeID  << "|"
			<< setw(12) << k->Name << "|"
			<< setw(7) << k->Alter << "|"
			<< setw(11) << k->Einkommen << "|"
			<< setw(9) << k->PLZ << "|"
			<< k->NodePosID << endl;
		printPreorder(k->Links);
		printPreorder(k->Rechts);
	}
}
