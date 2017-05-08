#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "Tree.h"
using namespace std;

enum Auswahl
{
    DS_PROGRAMM_BEENDEN,
    DS_EINFUEGEN,
    DS_EINFUEGEN_CSV,
    DS_LOESCHEN,
    DS_SUCHEN,
    DS_DATENSTRUKTUR_ANZEIGEN
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

    cout << "====================================" << endl;
    cout << "Person Analyzer v19.84, by George Orwell" << endl;
    cout << "====================================" << endl;
    cout << "1) Datensatz einfuegen, manuell" << endl;
    cout << "2) Datensatz einfuegen, CSV Datei" << endl;
    cout << "3) Datensatz loeschen" << endl;
    cout << "4) Suchen" << endl;
    cout << "5) Datenstruktur anzeigen" << endl;

    Auswahl auswahl = DS_PROGRAMM_BEENDEN;
    int auswahl_int;
    bool abbrechen = false;
    do
    {
		cout << "?> ";
        cin >> auswahl_int;
        auswahl = Auswahl(auswahl_int);
        cin.clear();
        cin.ignore(1, '\n');

        switch(auswahl)
        {
        case DS_EINFUEGEN: 
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
        case DS_EINFUEGEN_CSV:
        {
            importCSV(baum);
            break;
        }
        case DS_SUCHEN:
        {
            string suche;
            TreeNode* node = nullptr;
            cout << "+ Bitte geben Sie den zu suchenden Datensatz an" << endl;
            cout << "Name?> ";
            getline(cin, suche);
            node = baum.search(suche);
            if(node != nullptr)
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
        case DS_LOESCHEN:
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
        case DS_DATENSTRUKTUR_ANZEIGEN:
        {
            baum.print();
            break;
        }
        case DS_PROGRAMM_BEENDEN:
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
