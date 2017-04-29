#ifndef _LIST_H
#define _LIST_H

#include "Node.h"
#include <string>
#include <iostream>

class List
{
    /*
    Die Klasse List dient zur Verwaltung von Knoten (Node). Mit Hilfe der Klasse List
    kann ein Stapel oder Warteschlange realisiert werden.
    */
private:
    struct form
    {
        std::string start = "<< ";
        std::string zwischen = ", ";
        std::string ende = " >>\n";
    } _form;
    Node *head, *tail;
    int _size;
public:
    List();
    ~List();

    // Copy Operator ueberladen
    List(List &_list);

    // Einfuegen eines Knotens am Anfang
    void insertFront(int key);

    // Einfuegen eines Knotesn am Ende
    void insertBack(int key);

    // Entnehmen eines Knoten am Anfang
    bool getFront(int &key);

    // Entnehmen eines Knoten am Ende
    bool getBack(int &key);

    // loeschen eines Knotens [key]
    bool del(int key);

    // Suchen eines Knoten
    bool search(int key);

    // Knoten in der Liste vertauschen
    bool swap(int key1, int key2);

    // Groesse der Lise (Anzahl der Knoten)
    int size(void);

    // Ueberpruefen der Zeigerstruktur der Liste
    bool test(void);

    // Mit der format Methode kann die Ausgabe gesteuert werden: operator <<
    void format(const std::string &start, const std::string &zwischen, const std::string &ende);

    // Zuweisungsoperator definieren
    List& operator=(const List &List);

    // Zuweisungsoperator definieren
    List& operator=(const List *List);

    // Listen zusammenfuehren zu einer Liste
    List operator+(const List &List_Append) const;

    // Listen zusammenfuehren zu einer Liste
    List operator+(const List *List_Append) const;

    // Ausgabeoperator ueberladen
    friend std::ostream& operator<<(std::ostream & stream, List const &Liste);
    friend std::ostream& operator<<(std::ostream & stream, List const *Liste);

	friend class List;
};

#endif
