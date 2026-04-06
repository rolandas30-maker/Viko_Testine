#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

int main() {
    // Parodo du skaicius po kablelio
    cout << fixed << setprecision(2);

    char testi = 't';   // ar kartoti programą

    while (testi == 't') {

        int pasirinkimas;
        string valiuta;
        double kiekis;

    // Visu valiutu kursai
    double GBP_Bendras   = 0.8729;
    double GBP_Pirkti    = 0.8600;
    double GBP_Parduoti  = 0.9220;

    double USD_Bendras   = 1.1793;
    double USD_Pirkti    = 1.1460;
    double USD_Parduoti  = 1.2340;

    double INR_Bendras   = 104.6918;
    double INR_Pirkti    = 101.3862;
    double INR_Parduoti  = 107.8546;

    // Pagrindinis meniu
    cout << "1 - Palyginti valiutos kursa\n";
    cout << "2 - Pirkti valiuta (EUR -> kita valiuta)\n";
    cout << "3 - Parduoti valiuta (kita valiuta -> EUR)\n";
    cout << "Pasirinkite: ";
    cin >> pasirinkimas;

    // Patikrinimas
    if (pasirinkimas < 1 || pasirinkimas > 3) {
        cout << "Klaida: blogas pasirinkimas.\n";
        return 0;
    }

    // Valiutos įvedimas
    cout << "Iveskite valiuta (GBP, USD, INR): ";
    cin >> valiuta;

    // Palyginti
    if (pasirinkimas == 1) {
        if (valiuta == "GBP") {
            cout << "1 EUR = " << GBP_Bendras << " GBP\n";
            cout << "1 GBP = " << 1.0 / GBP_Bendras << " EUR\n";
        }
        else if (valiuta == "USD") {
            cout << "1 EUR = " << USD_Bendras << " USD\n";
            cout << "1 USD = " << 1.0 / USD_Bendras << " EUR\n";
        }
        else if (valiuta == "INR") {
            cout << "1 EUR = " << INR_Bendras << " INR\n";
            cout << "1 INR = " << 1.0 / INR_Bendras << " EUR\n";
        }
        else {
            cout << "Nezinoma valiuta.\n";
        }
    }
    // Valiutos pirkimas
    if (pasirinkimas == 2) {
        cout << "Kiek EUR norite isleisti? ";
        cin >> kiekis;

        if (kiekis <= 0) {
            cout << "Kiekis turi buti teigiamas.\n";
            return 0;
        }

        if (valiuta == "GBP") {
            cout << "Jus gausite: " << kiekis * GBP_Pirkti << " GBP\n";
        }
        else if (valiuta == "USD") {
            cout << "Jus gausite: " << kiekis * USD_Pirkti << " USD\n";
        }
        else if (valiuta == "INR") {
            cout << "Jus gausite: " << kiekis * INR_Pirkti << " INR\n";
        }
        else {
            cout << "Nezinoma valiuta.\n";
        }
    }

    // Padrduoti valiuta
    if (pasirinkimas == 3) {
        cout << "Kiek norite parduoti? ";
        cin >> kiekis;

        if (kiekis <= 0) {
            cout << "Kiekis turi buti teigiamas.\n";
            return 0;
        }

        if (valiuta == "GBP") {
            cout << "Jus gausite: " << kiekis / GBP_Parduoti << " EUR\n";
        }
        else if (valiuta == "USD") {
            cout << "Jus gausite: " << kiekis / USD_Parduoti << " EUR\n";
        }
        else if (valiuta == "INR") {
            cout << "Jus gausite: " << kiekis / INR_Parduoti << " EUR\n";
        }
        else {
            cout << "Nezinoma valiuta.\n";
        }
        // Ar kartoti
        cout << "\n Ar norite skaiciuoti dar karta? (t/n): ";
        cin >> testi;
    }
        cout << "\nSkaiciavimas atliktas\n";
    }
    return 0;
}
