#include "Node.h"

Node::Node()
{
    key = 0;
    next = nullptr;
    prev = nullptr;
}

Node::Node(int key, Node * next, Node * prev)
{
    this->key = key;
    this->prev = prev;
    this->next = next;
}

Node::~Node()
{
}

Node* Node::getNext()
{
	return next;
}

Node* Node::getPrev()
{
	return prev;
}

int Node::getKey()
{
	return key;
}
