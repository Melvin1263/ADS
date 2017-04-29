#include <iostream>
#include "Ringbuffer.h"
using namespace std;

int main()
{
    Ringbuffer buffer(6);

    cout << "==================================" << endl;
    cout << " OneRingToRuleThemAll v0.1, by Melvin Engelhardt" << endl;
    cout << "==================================" << endl;

    cout << "1) Backup einfuegen" << endl;
    cout << "2) Backup suchen" << endl;
    cout << "3) Alle Backups ausgeben" << endl;

    int auswahl = 0;
    bool abbrechen = false;
    do
    {
        cin >> auswahl;
        cin.clear();
        cin.ignore(1, '\n');

        switch(auswahl)
        {
        case 1:
        {
            cin.clear();
            string beschreibung, daten;
            cout << "+Neuen Datensatz einfuegen" << endl;
            cout << "Beschreibung ?>";
            getline(cin, beschreibung);
            cout << "Daten ?>";
            getline(cin, daten);

            buffer.addNode(beschreibung, daten);

            cout << "+Ihr Datensatz wurde hinzugefuegt." << endl;

            break;
        }
        case 2:
        {
            string suche;
            cout << "+Nach welchen Daten soll gesucht werden?" << endl;
            getline(cin, suche);
            RingNode* s = buffer.search(suche);
            if(s != nullptr)
            {
                cout << "+ Gefunden in Backup: OldAge " << s->getAge() << 
                    ", Beschreibung: " << s->getDescription() 
                    << ", Daten: " << s->getData() << endl;
            }
            else
            {
                cout << "+ Kein passender Datensatz gefunden." << endl;
            }
            break;
        }
        case 3:
        {
            buffer.print();
            break;
        }
        default:
            abbrechen = true;
        }
    } while (!abbrechen);


    cin.get();
    return 0;
}
