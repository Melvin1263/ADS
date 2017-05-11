#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "Tree.h"
#include "Ringbuffer.h"
using namespace std;

enum Auswahl
{
    PROGRAMM_BEENDEN,
    RING_BACKUP_EINFUEGEN,
    RING_BACKUP_SUCHEN,
    RING_ALLE_BACKUPS_AUSGEBEN,
    TREE_DATENSATZ_EINFUEGEN,
    TREE_EINFUEGEN_CSV,
    TREE_DATENSATZ_LOESCHEN,
    TREE_DATENSATZ_SUCHEN,
    TREE_ALLE_DATENSAETZE_ANZEIGEN
};

bool importCSV(Tree& baum)
{
    ifstream file("ExportZielanalyse.csv");
    if (!file.is_open())
    {
        cout << "+ Datei wurde nicht gefunden!" << endl;
        return false;
    }

    int i = 0;
    string line;
    while (getline(file, line))
    {
        stringstream stream(line);
        string Name;
        getline(stream, Name, ';');

        int Alter;
        string AlterSTR;
        getline(stream, AlterSTR, ';');
        Alter = stoi(AlterSTR);

        int Einkommen;
        string EinkommenSTR;
        getline(stream, EinkommenSTR, ';');
        Einkommen = stoi(EinkommenSTR);

        int PLZ;
        string PLZSTR;
        getline(stream, PLZSTR);
        PLZ = stoi(PLZSTR);

        if (baum.addNode(Name, Alter, PLZ, Einkommen))
            i++;
    }
    cout << "+ Es wurden " << i << " Eintraege hinzugefuegt!" << endl;
    return (i > 0);
}


int main()
{
    Tree baum;
    Ringbuffer buffer(6);

    cout << "====================================" << endl;
    cout << "DPDS v0.1, by Melvin Engelhardt" << endl;
    cout << "====================================" << endl;
    cout << "1) Backup einfuegen" << endl;
    cout << "2) Backup suchen" << endl;
    cout << "3) Alle Backups ausgeben" << endl;
    cout << "------------------------------------" << endl;
    cout << "Aktueller Baum" << endl;
    cout << "4) Datensatz einfuegen, manuell" << endl;
    cout << "5) Datensatz einfuegen, CSV Datei" << endl;
    cout << "6) Datensatz loeschen" << endl;
    cout << "7) Suchen" << endl;
    cout << "8) Datenstruktur anzeigen" << endl;

    Auswahl auswahl = PROGRAMM_BEENDEN;
    int auswahl_int;
    bool abbrechen = false;
    do
    {
        cout << "?> ";
        cin >> auswahl_int;
        auswahl = Auswahl(auswahl_int);
        cin.clear();
        cin.ignore(1, '\n');

        switch (auswahl)
        {
        case RING_BACKUP_EINFUEGEN:
        {
            cin.clear();
            string beschreibung, daten;
            cout << "+Neuen Datensatz einfuegen" << endl;
            cout << "Beschreibung ?>";
            getline(cin, beschreibung);

            buffer.addNode(beschreibung, baum);

            cout << "+Ihr Datensatz wurde hinzugefuegt." << endl;

            break;
        }
        case RING_BACKUP_SUCHEN:
        {
            string suche;
            cout << "+Nach welchen Daten soll gesucht werden?" << endl;
            getline(cin, suche);
            RingNode* s = buffer.search(suche);
            if (s != nullptr)
            {
                cout << "+ Gefunden in Backup: OldAge " << s->getAge() <<
                    ", Beschreibung: " << s->getDescription()
                    << ", Daten: " << endl;
                s->getData().print();
            }
            else
            {
                cout << "+ Kein passender Datensatz gefunden." << endl;
            }
            break;
        }
        case RING_ALLE_BACKUPS_AUSGEBEN:
        {
            buffer.print();
            break;
        }
        case TREE_DATENSATZ_EINFUEGEN:
        {
            string name;
            int alter, plz;
            double einkommen;
            cout << "+ Bitte geben Sie die den Datensatz ein" << endl;
            cout << "Name ?>";
            getline(cin, name);
            cout << "Alter ?>";
            cin >> alter;
            cout << "Einkommen ?>";
            cin >> einkommen;
            cout << "PLZ ?>";
            cin >> plz;

            if (baum.addNode(name, alter, plz, einkommen))
                cout << "+ Eintrag hinzugefuegt." << endl;
            else
                cout << "+ Eintrag wurde nicht hinzugefuegt! Fehler!" << endl;
            break;
        }
        case TREE_EINFUEGEN_CSV:
        {
            importCSV(baum);
            break;
        }
        case TREE_DATENSATZ_SUCHEN:
        {
            string suche;
            TreeNode* node = nullptr;
            cout << "+ Bitte geben Sie den zu suchenden Datensatz an" << endl;
            cout << "Name?> ";
            getline(cin, suche);
            node = baum.search(suche);
            if (node != nullptr)
            {
                cout << "+ Fundstellen: " << endl;
                cout << "NodeID: " << node->getNodePosID()
                    << ", Name: " << node->getName()
                    << ", Alter: " << node->getAlter()
                    << ", Einkommen: " << node->getEinkommen()
                    << ", PLZ: " << node->getPLZ()
                    << ", PosID: " << node->getNodePosID() << endl;
            }
            else
            {
                cout << "Kein Eintrag gefunden!" << endl;
            }
            break;
        }
        case TREE_DATENSATZ_LOESCHEN:
        {
            int pos_id;
            cout << "+ Bitte geben Sie den zu loeschenden Datensatz an" << endl;
            cout << "PosID: ";
            cin >> pos_id;
            if (baum.deleteNode(pos_id))
                cout << "+ Datensatz wurde geloescht." << endl;
            else
                cout << "+ Datensatz wurde NICHT geloescht!" << endl;
            break;
        }
        case TREE_ALLE_DATENSAETZE_ANZEIGEN:
        {
            baum.print();
            break;
        }
        case PROGRAMM_BEENDEN:
        {
            abbrechen = true;
            break;
        }
        default: break;
        }
    } while (!abbrechen);

    cin.get();
    return 0;
}