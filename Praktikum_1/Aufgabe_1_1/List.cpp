#include "List.h"

/*
Anfangszustand der leeren Liste
Head          Tail
|-------|     |-------|
| 0 |   | --> | 0 |   |
|-------| <-- |-------|
Wenn Head == Tail, dann ist die Liste leer!
*/
List::List()
{
    head = new Node;
    tail = new Node;
    head->next = tail;
    tail->prev = head;
    _size = 0;
}

// Jeder Knoten muss sequenziell gelöscht werden!
List::~List()
{
    // Vom Anfang bis Ende Laufen
    Node *current = head;
    while (current->next != nullptr && current != tail)
    {
        Node* tmp = current;
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
List::List(List& _list)
{
    // Muss immer initalisiert werden!
    head = new Node;
    tail = new Node;
    head->next = tail;
    tail->prev = head;
    _size = 0;

    if (_list.head->next == _list.tail) // Leere Liste, nichts zu tun!
        return;

    // Vom Anfang bis Ende Laufen
    Node *current = _list.head->next;
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
void List::insertFront(int key)
{
    // Neuen Knoten erzeugen
    Node *new_node = new Node(key);

    // Nachfolgeknoten von Head sichern
    Node *tmp = head->next;

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
void List::insertBack(int key)
{
    // Neuen Knoten erzeugen
    Node *new_node = new Node(key);

    // Vorgänger von Tail sichern
    Node *tmp = tail->prev;

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
bool List::getFront(int &key)
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
bool List::getBack(int &key)
{
    key = 0;
    if (head != tail)
    {
        key = (tail->prev)->key;
        return true;
    }

    return false;
}

bool List::del(int key)
{
    // Startknoten = nachfolger von Head
    Node *current = head->next;

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

    Node* tmp = current->prev;

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
bool List::search(int key)
{
    // Startknoten = nachfolger von Head
    Node *current = head->next;

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
bool List::swap(int key1, int key2)
{
    Node* node1 = nullptr;
    Node* node2 = nullptr;
    Node *current = nullptr;

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
        Node* tmp1_prev = node1->prev;

        //Nachfolger von node2 sichern
        Node* tmp2_next = node2->next;

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
        Node* tmp2_prev = node2->prev;

        //Nachfolger von node1 sichern
        Node* tmp1_next = node1->next;

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
        Node* tmp1_prev = node1->prev;
        Node* tmp1_next = node1->next;

        // Vorgänger und Nachfolger von node2 sichern
        Node* tmp2_prev = node2->prev;
        Node* tmp2_next = node2->next;

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

int List::size(void)
{
    return _size;
}

bool List::test(void)
{
    if (head == nullptr || tail == nullptr) // Konstruktor Test
        return false;

    if (head->next == tail && tail->next == nullptr &&
        tail->prev == head && head->prev == nullptr)
    {
        // Leere Liste
        return true;
    }

    Node *current = nullptr;

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

void List::format(const std::string &start, const std::string &zwischen, const std::string &ende)
{
    _form.start = start;
    _form.zwischen = zwischen;
    _form.ende = ende;
}

List& List::operator=(const List &List)
{
    if (this == &List)
        return *this;

    // Eventuelle vorhandene Knoten löschen
    Node *current = head->next;

    while (current->next != nullptr && current != tail)
    {
        Node* tmp = current;
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

List& List::operator=(const List *List)
{
    if (this == List)
        return *this;

    // Eventuelle vorhandene Knoten löschen
    Node *current = head->next;

    while (current->next != nullptr && current != tail)
    {
        Node* tmp = current;
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

List List::operator+(const List &List_Append) const
{
    List tmp;

    Node *current = head->next;
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

List List::operator+(const List *List_Append) const
{
    List tmp;

    Node *current = head->next;
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

std::ostream& operator<<(std::ostream &stream, List const &Liste)
{
    stream << Liste._form.start;

    // Startknoten = nachfolger von Head
    Node *current = Liste.head->getNext();

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
std::ostream& operator<<(std::ostream &stream, List const *Liste)
{
    stream << Liste->_form.start;

    // Startknoten = nachfolger von Head
    Node *current = Liste->head->getNext();

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
