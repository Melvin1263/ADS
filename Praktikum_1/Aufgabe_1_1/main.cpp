#include <iostream>
#include "List.h"

void listeAusgeben(List& liste)
{
    if (liste.test())
        std::cout << liste;
    else
        std::cout << "Ausgabe nicht moeglich, da Zeigerstruktur defekt!" << std::endl;
}

int main()
{
    List liste;

    listeAusgeben(liste);

    /*
    Head                        Tail
    |-------|     |-------|     |-------|
    | 0 |   | --> | 1 |   | --> | 0 |   |
    |-------| <-- |-------| <-- |-------|
    */
    liste.insertFront(1);

    liste.swap(1, 0); // Darf nicht funktionieren, da wir nur ein Element bisher haben.
    listeAusgeben(liste);

    /*
    Head                                      Tail
    |-------|     |-------|     |-------|     |-------|
    | 0 |   | --> | 2 |   | --> | 1 |   | --> | 0 |   |
    |-------| <-- |-------| <-- |-------| <-- |-------|
    */
    liste.insertFront(2);

    listeAusgeben(liste);
    liste.swap(1, 2);
    listeAusgeben(liste);

    liste.swap(1, 1);
    listeAusgeben(liste);

    /*
    Head                                                    Tail
    |-------|     |-------|     |-------|     |-------|     |-------|
    | 0 |   | --> | 3 |   | --> | 2 |   | --> | 1 |   | --> | 0 |   |
    |-------| <-- |-------| <-- |-------| <-- |-------| <-- |-------|
    */
    liste.insertFront(3);
    /*
    Head                                                                  Tail
    |-------|     |-------|     |-------|     |-------|     |-------|     |-------|
    | 0 |   | --> | 4 |   | --> | 3 |   | --> | 2 |   | --> | 1 |   | --> | 0 |   |
    |-------| <-- |-------| <-- |-------| <-- |-------| <-- |-------| <-- |-------|
    */
    liste.insertFront(4);

    listeAusgeben(liste);
    /*
    Head                                                                                Tail
    |-------|     |-------|     |-------|     |-------|     |-------|     |-------|     |-------|
    | 0 |   | --> | 4 |   | --> | 3 |   | --> | 2 |   | --> | 1 |   | --> | 5 |   | --> | 0 |   |
    |-------| <-- |-------| <-- |-------| <-- |-------| <-- |-------| <-- |-------| <-- |-------|
    */
    liste.insertBack(5);

    std::cout << "Groesse der Liste: " << liste.size() << std::endl;

    listeAusgeben(liste);

    int font_key;
    liste.getFront(font_key);
    std::cout << "Erstes Element: | " << font_key << " |" << std::endl;

    int back_key;
    liste.getBack(back_key);
    std::cout << "Letztes Element: | " << back_key << " |" << std::endl;

    std::cout << "Suche Element mit Key: 5" << std::endl;
    if (liste.search(5))
        std::cout << "Element gefunden!" << std::endl;
    else
        std::cout << "Element NICHT gefunden!" << std::endl;

    std::cout << "Suche Element mit Key: 8" << std::endl;
    if (liste.search(8))
        std::cout << "Element gefunden!" << std::endl;
    else
        std::cout << "Element NICHT gefunden!" << std::endl;

    listeAusgeben(liste);

    liste.swap(3, 1);
    listeAusgeben(liste);

    liste.swap(2, 3);
    listeAusgeben(liste);

    liste.del(4);
    listeAusgeben(liste);

    liste.del(5);
    listeAusgeben(liste);

    liste.del(9);
    listeAusgeben(liste);

    liste.del(1);
    listeAusgeben(liste);

    liste.del(3);
    listeAusgeben(liste);

    liste.del(2);
    listeAusgeben(liste);

    for (int i = 0; i<10; i++)
    {
        liste.insertFront(i);
    }
    listeAusgeben(liste);

    List liste2(liste);
    listeAusgeben(liste2);

    List liste3;
    liste3.insertFront(1);
    liste3.insertFront(2);
    listeAusgeben(liste3);

    List liste4;
    liste4.insertFront(3);
    liste4.insertFront(4);
    liste4.insertFront(5);
    listeAusgeben(liste4);

    liste4 = liste3 + liste4;
    listeAusgeben(liste4);

    std::cin.get();
    return 0;
}
