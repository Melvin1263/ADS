#include <iostream>
#include <string>
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

int main()
{
    Tree baum;

    cout << "====================================" << endl;
    cout << "Person Analyzer v19.84, by George Orwell" << endl;
    cout << "====================================" << endl;
    cout << "1) Datensatz einfuegen, manuell" << endl;
    cout << "2) Datensatz einfuegen, CSV Datei" << endl;
    cout << "3) Datensatz loeschen" << endl;
    cout << "4) Suchen" << endl;
    cout << "5) Datenstruktur anzeigen" << endl;

    Auswahl auswahl = DS_PROGRAMM_BEENDEN;
    int auswahl_int;
    bool abbrechen = false;
    do
    {
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

            baum.addNode(name, alter, plz, einkommen);

            break;
        }
        case DS_EINFUEGEN_CSV:
        {
            break;
        }
        case DS_SUCHEN:
        {
            break;
        }
        case DS_LOESCHEN:
        {
            int pos_id;
            cout << "+ Bitte geben Sie den zu loschenden Datensatz an" << endl;
            cout << "PosID: ";
            cin >> pos_id;
            if (baum.deleteNode(pos_id))
                cout << "+ Datensatz wurde geloscht." << endl;
            else
                cout << "+ Datensatz wurde NICHT geloescht!" << endl;
            break;
        }
        case DS_DATENSTRUKTUR_ANZEIGEN:
        {
            break;
        }
        case DS_PROGRAMM_BEENDEN:
        {
            break;
        }
        default: break;
        }
    } while (!abbrechen);

    cin.get();
    return 0;
} 
