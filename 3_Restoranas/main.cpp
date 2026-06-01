#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <windows.h>

using namespace std;

// ===== STRUKTURA =====
struct menuItemType {
    string menuItem;
    double menuPrice;
};

// ===== NUSKAITO MENIU =====
void getData(menuItemType menuList[], int& size) {
    ifstream inFile("menu.txt");

    if (!inFile) {
        cout << "KLAIDA: Nepavyko atidaryti menu.txt\n";
        exit(1);
    }

    size = 0;

    while (getline(inFile, menuList[size].menuItem) &&
           inFile >> menuList[size].menuPrice) {
        inFile.ignore();
        size++;
    }

    inFile.close();
}

// ===== PARODO MENIU =====
void showMenu(menuItemType menuList[], int size) {
    cout << "===== Pusryčių meniu =====\n\n";
    cout << fixed << setprecision(2);

    for (int i = 0; i < size; i++) {
        cout << i + 1 << ". " << menuList[i].menuItem
             << " - " << menuList[i].menuPrice << " EUR\n";
    }

    cout << "\nPasirinkite patiekalą pagal numerį (0 - baigti)\n";
}

// ===== SPAUSDINA SĄSKAITĄ =====
void printCheck(menuItemType menuList[], int order[], int size) {
    ofstream outFile("receipt.txt");

    double suma = 0;
    cout << "\n===== SĄSKAITA =====\n\n";

    cout << fixed << setprecision(2);
    outFile << fixed << setprecision(2);

    bool tuscia = true;

    for (int i = 0; i < size; i++) {
        if (order[i] > 0) {
            tuscia = false;

            double kaina = order[i] * menuList[i].menuPrice;
            suma += kaina;

            cout << order[i] << " " << menuList[i].menuItem
                 << " " << kaina << " EUR\n";

            outFile << order[i] << " " << menuList[i].menuItem
                    << " " << kaina << " EUR\n";
        }
    }

    if (tuscia) {
        cout << "Nieko neužsakėte!\n";
        return;
    }

    double pvm = suma * 0.21;
    double galutine = suma + pvm;

    cout << "\nMokesčiai (21%): " << pvm << " EUR\n";
    cout << "Galutinė suma: " << galutine << " EUR\n";

    outFile << "\nMokesčiai (21%): " << pvm << " EUR\n";
    outFile << "Galutinė suma: " << galutine << " EUR\n";

    outFile.close();
}

// ===== MAIN =====
int main() {
    // UTF-8 kad veiktų lietuviškos raidės
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    menuItemType menuList[20];
    int size;

    getData(menuList, size);

    int order[20] = {0};

    showMenu(menuList, size);

    int pasirinkimas, kiekis;

    while (true) {
        cout << "Pasirinkimas: ";

        if (!(cin >> pasirinkimas)) {
            cout << "Klaida! Įveskite skaičių.\n";
            cin.clear();
            cin.ignore(1000, '\n');
            continue;
        }

        if (pasirinkimas == 0)
            break;

        if (pasirinkimas < 1 || pasirinkimas > size) {
            cout << "Neteisingas pasirinkimas!\n";
            continue;
        }

        cout << "Kiekis: ";

        if (!(cin >> kiekis)) {
            cout << "Klaida! Įveskite skaičių.\n";
            cin.clear();
            cin.ignore(1000, '\n');
            continue;
        }

        if (kiekis <= 0) {
            cout << "Kiekis turi būti > 0!\n";
            continue;
        }

        order[pasirinkimas - 1] += kiekis;
    }

    printCheck(menuList, order, size);

    return 0;
}