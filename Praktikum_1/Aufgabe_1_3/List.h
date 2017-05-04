#ifndef _LIST_H
#define _LIST_H

#include "Node.h"
#include <string>
#include <iostream>

template<typename T>
class List
{
    /*
    Die Klasse List dient zur Verwaltung von Knoten (Node). Mit Hilfe der Klasse List
    kann ein Stapel oder Warteschlange realisiert werden.
    */
private:
    struct form
    {
        form() :
            start("<< "), zwischen(", "), ende(">>\n") {}
        std::string start;
        std::string zwischen;
        std::string ende;
    } _form;
    Node<T> *head, *tail;
    int _size;
public:
    List();
    ~List();

    // Copy Operator ueberladen
    List(List<T> &_list);

    // Einfuegen eines Knotens am Anfang
    void insertFront(T key);

    // Einfuegen eines Knotesn am Ende
    void insertBack(T key);

    // Entnehmen eines Knoten am Anfang
    bool getFront(T &key);

    // Entnehmen eines Knoten am Ende
    bool getBack(T &key);

    // loeschen eines Knotens [key]
    bool del(T key);

    // Suchen eines Knoten
    bool search(T key);

    // Knoten in der Liste vertauschen
    bool swap(T key1, T key2);

    // Groesse der Lise (Anzahl der Knoten)
    int size(void);

    // Ueberpruefen der Zeigerstruktur der Liste
    bool test(void);

    // Mit der format Methode kann die Ausgabe gesteuert werden: operator <<
    void format(const std::string &start, const std::string &zwischen, const std::string &ende);

    // Zuweisungsoperator definieren
    List<T>& operator=(const List<T> &List);

    // Zuweisungsoperator definieren
    List<T>& operator=(const List<T> *List);

    // Listen zusammenfuehren zu einer Liste
    List<T> operator+(const List<T> &List_Append) const;

    // Listen zusammenfuehren zu einer Liste
    List<T> operator+(const List<T> *List_Append) const;

    // Ausgabeoperator ueberladen
    template <typename S>
    friend std::ostream& operator<<(std::ostream & stream, List<S> const &Liste);
    template <typename S>
    friend std::ostream& operator<<(std::ostream & stream, List<S> const *Liste);
};

template<typename T>
List<T>::List()
{
    head = new Node<T>;
    tail = new Node<T>;
    head->next = tail;
    tail->prev = head;
    _size = 0;
}

// Jeder Knoten muss sequenziell gelöscht werden!
template<typename T>
List<T>::~List()
{
    // Vom Anfang bis Ende Laufen
    Node<T> *current = head;
    while (current->next != nullptr && current != tail)
    {
        Node<T>* tmp = current;
        // Weiterlaufen
        current = current->next;
        delete tmp;
    }

    // Es werden nur die Knoten bis vor tail gelöscht.
    // tail muss seperat gelöscht werden
    if (tail != nullptr)
        delete tail;
}

// Copykontruktor
template<typename T>
List<T>::List(List<T>& _list)
{
    // Muss immer initalisiert werden!
    head = new Node<T>;
    tail = new Node<T>;
    head->next = tail;
    tail->prev = head;
    _size = 0;

    if (_list.head->next == _list.tail) // Leere Liste, nichts zu tun!
        return;

    // Vom Anfang bis Ende Laufen
    Node<T> *current = _list.head->next;
    while (current->next != nullptr && current != _list.tail)
    {
        this->insertBack(current->key);
        current = current->next;
    }
}

/*
Head          new_node      Tail = tmp
|-------|     |-------|     |-------|
| 0 |   | --> | X |   | --> | 0 |   |
|-------| <-- |-------| <-- |-------|
Hier Fügen Wir einen Knoten am Anfang der verketteten
Liste ein. Der Head-Knoten dient hier als Anker zum Einfügen.
Es muss lediglich die restliche Liste wieder zum neuen Knoten angefügt werden.

Der Aufwand ist hier Konstant O(1)
*/
template<typename T>
void List<T>::insertFront(T key)
{
    // Neuen Knoten erzeugen
    Node<T> *new_node = new Node<T>(key);

    // Nachfolgeknoten von Head sichern
    Node<T> *tmp = head->next;

    // Neuen Knoten als Nachfolger von Head setzen
    head->next = new_node;

    // Den vorherigen Knoten vom neuen Knoten auf Head setzen
    new_node->prev = head;

    // Rest der Liste zum neuen Knoten anfügen;
    new_node->next = tmp;

    // Den neuen Knoten zum Vorgänger des
    // ersten Knotens vom Rest der Liste machen
    tmp->prev = new_node;

    // Anzahl Elemente um eins erhöhen
    _size++;
}

/*
Head          tmp           new_node      Tail
|-------|     |-------|     |-------|     |-------|
| 0 |   | --> | 1 |   | --> | x |   | --> | 0 |   |
|-------| <-- |-------| <-- |-------| <-- |-------|
Hier fügen wir einen neuen Knoten zum Ende der Liste ein.
Dafür steht uns direkt der Tail-Knoten zur verfügung.
Alle Elemente die davor sind müssen dann zum neuen Knoten
davorgehangen werden

Der Aufwand ist hier Konstant O(1)
*/
template<typename T>
void List<T>::insertBack(T key)
{
    // Neuen Knoten erzeugen
    Node<T> *new_node = new Node<T>(key);

    // Vorgänger von Tail sichern
    Node<T> *tmp = tail->prev;

    // Der neuen Knoten wird nachfolger der restlichen Liste davor
    tmp->next = new_node;

    // Tail wird Folgeknoten vom neuen Knoten
    new_node->next = tail;

    // Die vorherige Liste wird zum vorgänger des neuen Knotens
    new_node->prev = tmp;

    // Der neue Knoten wird Vorgänger vom Tail
    tail->prev = new_node;

    // Anzahl Elemente um eins erhöhen
    _size++;
}

/*
Erstes Element nach Head auslesen
*/
template<typename T>
bool List<T>::getFront(T &key)
{
    key = 0;
    if (head != tail)
    {
        key = (head->next)->key;
        return true;
    }

    return false;
}

// Letztes Element vor Tail auslesen
template<typename T>
bool List<T>::getBack(T &key)
{
    key = 0;
    if (head != tail)
    {
        key = (tail->prev)->key;
        return true;
    }

    return false;
}

template<typename T>
bool List<T>::del(T key)
{
    // Startknoten = nachfolger von Head
    Node<T> *current = head->next;

    // Vom Anfang bis Ende Laufen
    while (current->next != nullptr && current != tail)
    {
        if (current->key == key)
            break; // Key gefunden

                   // Weiterlaufen
        current = current->next;
    }

    if (current == tail)
        return false;

    Node<T>* tmp = current->prev;

    tmp->next = current->next;
    current->next->prev = tmp;

    delete current;
    _size--;

    return true;
}

/*
Nach einem Element suchen.

Aufwand ist hier O(n)
*/
template<typename T>
bool List<T>::search(T key)
{
    // Startknoten = nachfolger von Head
    Node<T> *current = head->next;

    // Vom Anfang bis Ende Laufen
    while (current->next != nullptr && current != tail)
    {
        if (current->key == key)
            return true; // Key gefunden

                         // Weiterlaufen
        current = current->next;
    }

    return false;
}

/*
Aus ...
Head          key1          key2          Tail
|-------|     |-------|     |-------|     |-------|
| 0 |   | --> | 1 |   | --> | 2 |   | --> | 0 |   |
|-------| <-- |-------| <-- |-------| <-- |-------|
... soll ...
Head          key1          key2          Tail
|-------|     |-------|     |-------|     |-------|
| 0 |   | --> | 2 |   | --> | 1 |   | --> | 0 |   |
|-------| <-- |-------| <-- |-------| <-- |-------|
... werden
*/
template<typename T>
bool List<T>::swap(T key1, T key2)
{
    Node<T>* node1 = nullptr;
    Node<T>* node2 = nullptr;
    Node<T> *current = nullptr;

    if (_size < 2) // Liste muss mehr als ein Element haben!
        return false;

    // Vom Anfang bis Ende Laufen
    current = head->next;
    while (current->next != nullptr && current != tail)
    {
        if (current->key == key1)
        {
            node1 = current; // Knoten 1 gefunden
            break;
        }
        // Weiterlaufen
        current = current->next;
    }

    // Vom Anfang bis Ende Laufen
    current = head->next;
    while (current->next != nullptr && current != tail)
    {
        if (current->key == key2)
        {
            node2 = current; // Knoten 1 gefunden
            break;
        }
        // Weiterlaufen
        current = current->next;
    }

    // leere Liste
    if (head->next == tail)
        return false;

    // Fallunterscheidung wenn node1->next = node2
    if (node1->next == node2)
    {
        // Vorgänger von node1 sichern
        Node<T>* tmp1_prev = node1->prev;

        //Nachfolger von node2 sichern
        Node<T>* tmp2_next = node2->next;

        // Vorgänger von node1 wird Vorgänger von node2
        tmp1_prev->next = node2;
        node2->prev = tmp1_prev;

        // Nachfolger von node2 wird Nachfolger von node1
        node1->next = tmp2_next;
        tmp2_next->prev = node1;

        // node1 wird Nachfolger von node2
        node2->next = node1;
        node1->prev = node2;
    }
    // Fallunterscheidung wenn node2->next = node1
    else if (node2->next == node1)
    {
        // Vorgänger von node2 sichern
        Node<T>* tmp2_prev = node2->prev;

        //Nachfolger von node1 sichern
        Node<T>* tmp1_next = node1->next;

        // Vorgänger von node2 wird Vorgänger von node1
        tmp2_prev->next = node1;
        node1->prev = tmp2_prev;

        // Nachfolger von node1 wird Nachfolger von node2
        node2->next = tmp1_next;
        tmp1_next->prev = node2;

        // node2 wird Nachfolger von node1
        node1->next = node2;
        node2->prev = node1;
    }
    // Wenn nicht nebeneinander
    else
    {
        // Vorgänger und Nachfolger von node1 sichern
        Node<T>* tmp1_prev = node1->prev;
        Node<T>* tmp1_next = node1->next;

        // Vorgänger und Nachfolger von node2 sichern
        Node<T>* tmp2_prev = node2->prev;
        Node<T>* tmp2_next = node2->next;

        // node2 zwischen Vorgänger und Nachfolger von node1 setzen
        node2->next = tmp1_next;
        tmp1_next->prev = node2;
        tmp1_prev->next = node2;
        node2->prev = tmp1_prev;

        // node1 zwischen Vorgänger und Nachfolger von node2 setzen
        node1->next = tmp2_next;
        tmp2_next->prev = node1;
        tmp2_prev->next = node1;
        node1->prev = tmp2_prev;
    }

    return false;
}

template<typename T>
int List<T>::size(void)
{
    return _size;
}

template<typename T>
bool List<T>::test(void)
{
    if (head == nullptr || tail == nullptr) // Konstruktor Test
        return false;

    if (head->next == tail && tail->next == nullptr &&
        tail->prev == head && head->prev == nullptr)
    {
        // Leere Liste
        return true;
    }

    Node<T> *current = nullptr;

    // Startknoten = nachfolger von Head
    current = head->next;

    // von Anfang bis Ende
    int i = 0;
    while (current->next != nullptr && current != tail)
    {
        i++;

        if (i > _size)
            return false; // Struktur kaputt, Endlosschleife!

                          // Weiterlaufen
        current = current->next;
    }

    if (i != _size || current != tail)
        return false;

    // von Ende bis Anfang
    current = tail->prev;
    while (current->prev != nullptr && current != head)
    {
        i--;

        if (i < 0)
            return false; // Struktur kaputt, Endlosschleife!

                          // Weiterlaufen
        current = current->prev;
    }

    if (i != 0 || current != head)
        return false;

    return true;
}

template<typename T>
void List<T>::format(const std::string &start, const std::string &zwischen, const std::string &ende)
{
    _form.start = start;
    _form.zwischen = zwischen;
    _form.ende = ende;
}

template<typename T>
List<T>& List<T>::operator=(const List<T> &List)
{
    if (this == &List)
        return *this;

    // Eventuelle vorhandene Knoten löschen
    Node<T> *current = head->next;

    while (current->next != nullptr && current != tail)
    {
        Node<T>* tmp = current;
        current = current->next;
        delete tmp;
    }

    head->next = tail;
    tail->prev = head;
    _size = 0;

    // Knoten aus anderer Liste eintragen
    current = List.head->next;
    while (current->next != nullptr && current != List.tail)
    {
        this->insertBack(current->key);
        current = current->next;
    }

    return *this;
}

template<typename T>
List<T>& List<T>::operator=(const List<T> *List)
{
    if (this == List)
        return *this;

    // Eventuelle vorhandene Knoten löschen
    Node<T> *current = head->next;

    while (current->next != nullptr && current != tail)
    {
        Node<T>* tmp = current;
        current = current->next;
        delete tmp;
    }

    head->next = tail;
    tail->prev = head;
    _size = 0;

    // Knoten aus anderer Liste eintragen
    current = List->head->next;
    while (current->next != nullptr && current != List->tail)
    {
        this->insertBack(current->key);
        current = current->next;
    }

    return *this;
}

template<typename T>
List<T> List<T>::operator+(const List<T> &List_Append) const
{
    List tmp;

    Node<T> *current = head->next;
    while (current->next != nullptr && current != tail)
    {
        tmp.insertBack(current->key);
        current = current->next;
    }

    if (!List_Append._size)
        return tmp;

    current = List_Append.head->next;
    while (current->next != nullptr && current != List_Append.tail)
    {
        tmp.insertBack(current->key);
        current = current->next;
    }

    return tmp;
}

template<typename T>
List<T> List<T>::operator+(const List<T> *List_Append) const
{
    List tmp;

    Node<T> *current = head->next;
    while (current->next != nullptr && current != tail)
    {
        tmp.insertBack(current->key);
        current = current->next;
    }

    if (!List_Append->_size)
        return tmp;

    current = List_Append->head->next;
    while (current->next != nullptr && current != List_Append->tail)
    {
        tmp.insertBack(current->key);
        current = current->next;
    }

    return tmp;
}

template<typename T>
std::ostream& operator<<(std::ostream &stream, List<T> const &Liste)
{
	stream << Liste._form.start;

	// Startknoten = nachfolger von Head
	Node<T> *current = Liste.head->getNext();

	// von Anfang bis Ende
	int i = 0;
	while (current->getNext() != nullptr && current != Liste.tail)
	{
		stream << current->getKey();

		if (current->getNext() != Liste.tail)
			stream << Liste._form.zwischen;

		// Weiterlaufen
		current = current->getNext();
	}

	stream << Liste._form.ende;

	return stream;
}

template<typename T>
std::ostream& operator<<(std::ostream &stream, List<T> const *Liste)
{
	stream << Liste->_form.start;

	// Startknoten = nachfolger von Head
	Node<T> *current = Liste->head->getNext();

	// von Anfang bis Ende
	int i = 0;
	while (current->getNext() != nullptr && current != Liste->tail)
	{
		stream << current->getKey();

		if (current->getNext() != Liste->tail)
			stream << Liste->_form.zwischen;

		// Weiterlaufen
		current = current->getNext();
	}

	stream << Liste->_form.ende;

	return stream;
}

#endif
