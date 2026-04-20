#include <iostream>
#include <string>
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
//Ivesti mokini
        if (pasirinkimas == 1) {
            cout << "Iveskite mokinio varda: ";
            cin >> vardai[mokiniuSkaicius];

            cout << "Kiek pazymiu: ";
            cin >> pazymiuKiekis[mokiniuSkaicius];

            for (int j = 0; j < pazymiuKiekis[mokiniuSkaicius]; j++) {
                cout << "Iveskite pazymi: ";
                cin >> pazymiai[mokiniuSkaicius][j];
            }
            mokiniuSkaicius++;
        }
//Rodyti visus mokinius
        else if (pasirinkimas == 2) {
            for (int i = 0; i < mokiniuSkaicius; i++) {
                cout << vardai[i] << ": ";
                for (int j = 0; j < pazymiuKiekis[i]; j++)
                    cout << pazymiai[i][j] << " ";
                cout << endl;
            }
        }
//Rodyti vieno mokinio pazymius
        else if (pasirinkimas == 3) {
            string vardas;
            cout << "Iveskite mokinio varda: ";
            cin >> vardas;

            for (int i = 0; i < mokiniuSkaicius; i++) {
                if (vardai[i] == vardas) {
                    for (int j = 0; j < pazymiuKiekis[i]; j++)
                        cout << pazymiai[i][j] << " ";
                }
            }
            cout << endl;
        }
//Keisti pazymi
        else if (pasirinkimas == 4) {
            string vardas;
            cout << "Iveskite mokinio varda: ";
            cin >> vardas;

            for (int i = 0; i < mokiniuSkaicius; i++) {
                if (vardai[i] == vardas) {
                    int nr;
                    cout << "Kuri pazymi keisti: ";
                    cin >> nr;
                    cout << "Iveskite nauja pazymi: ";
                    cin >> pazymiai[i][nr - 1];
                }
            }
        }
//Trinti mokini
        else if (pasirinkimas == 5) {
            string vardas;
            cout << "Iveskite mokinio varda: ";
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
                }
            }
        }

    } while (pasirinkimas != 0);

    return 0;
}