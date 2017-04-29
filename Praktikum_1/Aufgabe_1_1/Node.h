#ifndef _NODE_H
#define _NODE_H

class Node
{
private:
    int key;
    Node *next, *prev;
public:
    Node();
    Node(int key, Node *next = nullptr, Node *prev = nullptr);
    ~Node();

	Node* getNext();
	Node* getPrev();

	int getKey();

	friend class List;
};

#endif