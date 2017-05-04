#ifndef _NODE_H
#define _NODE_H

template<typename T>
class Node
{
private:
    T key;
    Node *next, *prev;
public:
    Node();
    Node(T key, Node *next = nullptr, Node *prev = nullptr);
    ~Node();

	Node* getNext();
	Node* getPrev();

	T getKey();

	template <typename S>
	friend class List;
};

template<typename T>
Node<T>::Node()
{
    key = 0;
    next = nullptr;
    prev = nullptr;
}

template<typename T>
Node<T>::Node(T key, Node * next, Node * prev)
{
    this->key = key;
    this->prev = prev;
    this->next = next;
}

template<typename T>
Node<T>::~Node()
{
}

template<typename T>
Node<T>* Node<T>::getNext()
{
	return next;
}

template<typename T>
Node<T>* Node<T>::getPrev()
{
	return prev;
}

template<typename T>
T Node<T>::getKey()
{
	return key;
}



#endif