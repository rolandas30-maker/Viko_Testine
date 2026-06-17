#include <iostream>
#include <string>
#include <limits>
using namespace std;

const int MAX_MOKINIU = 100;
const int MAX_PAZYMIU = 10;

int main() {
    string vardai[MAX_MOKINIU];
    int pazymiai[MAX_MOKINIU][MAX_PAZYMIU];
    int pazymiuKiekis[MAX_MOKINIU];
    int mokiniuSkaicius = 0;
    int pasirinkimas;

    do {
        cout << "\n--- MOKINIU PAZYMIU SISTEMA ---\n";
        cout << "1 - Prideti mokini ir pazymius\n";
        cout << "2 - Rodyti visu mokiniu pazymius\n";
        cout << "3 - Rodyti vieno mokinio pazymius\n";
        cout << "4 - Atnaujinti pazymi\n";
        cout << "5 - Pasalinti mokini\n";
        cout << "0 - Baigti programa\n";
        cout << "Pasirinkite: ";

        cin >> pasirinkimas;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Klaida: iveskite skaiciu!\n";
            continue;
        }

        //1.Ivesti mokini
        if (pasirinkimas == 1) {
            if (mokiniuSkaicius >= MAX_MOKINIU) {
                cout << "Pasiektas maksimalus mokiniu skaicius.\n";
                continue;
            }

            cout << "Iveskite mokinio varda: ";
            cin >> vardai[mokiniuSkaicius];

            if (vardai[mokiniuSkaicius].empty()) {
                cout << "Klaida: vardas negali buti tuscias.\n";
                continue;
            }

            cout << "Kiek pazymiu (1-10): ";
            cin >> pazymiuKiekis[mokiniuSkaicius];

            if (cin.fail() || pazymiuKiekis[mokiniuSkaicius] < 1 || pazymiuKiekis[mokiniuSkaicius] > 10) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Klaida: neteisingas pazymiu kiekis.\n";
                continue;
            }

            for (int j = 0; j < pazymiuKiekis[mokiniuSkaicius]; j++) {
                cout << "Iveskite " << j + 1 << "-aji pazymi (1-10): ";
                cin >> pazymiai[mokiniuSkaicius][j];

                if (cin.fail() || pazymiai[mokiniuSkaicius][j] < 1 || pazymiai[mokiniuSkaicius][j] > 10) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Klaida: pazymys turi buti nuo 1 iki 10.\n";
                    j--;
                }
            }

            mokiniuSkaicius++;
            cout << "Mokinys sekmingai pridetas.\n";
        }

        //2.Rodyti visu mokiniu pazymius
        else if (pasirinkimas == 2) {
            if (mokiniuSkaicius == 0) {
                cout << "Mokiniu nera.\n";
                continue;
            }

            for (int i = 0; i < mokiniuSkaicius; i++) {
                cout << vardai[i] << ": ";
                for (int j = 0; j < pazymiuKiekis[i]; j++) {
                    cout << pazymiai[i][j] << " ";
                }
                cout << endl;
            }
        }

        //3.Rodyti vieno mokinio pazymius
        else if (pasirinkimas == 3) {
            string vardas;
            cout << "Iveskite mokinio varda: ";
            cin >> vardas;

            bool rastas = false;
            for (int i = 0; i < mokiniuSkaicius; i++) {
                if (vardai[i] == vardas) {
                    cout << "Pazymiai: ";
                    for (int j = 0; j < pazymiuKiekis[i]; j++) {
                        cout << pazymiai[i][j] << " ";
                    }
                    cout << endl;
                    rastas = true;
                }
            }

            if (!rastas)
                cout << "Mokinys nerastas.\n";
        }

        //4. Pakeisti pazymi
        else if (pasirinkimas == 4) {
            string vardas;
            cout << "Iveskite mokinio varda: ";
            cin >> vardas;

            for (int i = 0; i < mokiniuSkaicius; i++) {
                if (vardai[i] == vardas) {
                    int nr;
                    cout << "Kuri pazymi keisti (1-" << pazymiuKiekis[i] << "): ";
                    cin >> nr;

                    if (nr < 1 || nr > pazymiuKiekis[i]) {
                        cout << "Blogas numeris.\n";
                        break;
                    }

                    cout << "Iveskite nauja pazymi: ";
                    cin >> pazymiai[i][nr - 1];
                    cout << "Pazymys atnaujintas.\n";
                }
            }
        }

        //5.Pasalinti mokini
        else if (pasirinkimas == 5) {
            string vardas;
            cout << "Iveskite mokinio varda salinimui: ";
            cin >> vardas;

            for (int i = 0; i < mokiniuSkaicius; i++) {
                if (vardai[i] == vardas) {
                    for (int j = i; j < mokiniuSkaicius - 1; j++) {
                        vardai[j] = vardai[j + 1];
                        pazymiuKiekis[j] = pazymiuKiekis[j + 1];
                        for (int k = 0; k < pazymiuKiekis[j]; k++)
                            pazymiai[j][k] = pazymiai[j + 1][k];
                    }
                    mokiniuSkaicius--;
                    cout << "Mokinys pasalintas.\n";
                    break;
                }
            }
        }

    } while (pasirinkimas != 0);

    cout << "Programa baigta.\n";
    return 0;
}