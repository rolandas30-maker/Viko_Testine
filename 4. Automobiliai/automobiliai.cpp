#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <iomanip>
#include <limits>
#include <windows.h>

using namespace std;

// ===== 1. STRUKTÛRA =====
struct Automobilis {
    string marke;       // Markë, pvz. Toyota
    string modelis;     // Modelis, pvz. Corolla
    string numeris;     // Valstybinis numeris ES formatas: AAA000
    int    rida;        // Ridos kilometrai
    int    ta_metai;    // Techninës apþiûros metai
    int    ta_menuo;    // Techninës apþiûros mënuo (1–12)
};

// ===== 2. PAGALBINËS FUNKCIJOS =====

// Paverèia eilutæ á didþiàsias raides
string didziososRaides(string s) {
    transform(s.begin(), s.end(), s.begin(), ::toupper);
    return s;
}

// Tikrina ar simbolis yra raidë (A-Z)
bool yraRaide(char c) {
    return (c >= 'A' && c <= 'Z');
}

// Tikrina ar simbolis yra skaitmuo (0-9)
bool yraSkaitmuo(char c) {
    return (c >= '0' && c <= '9');
}

// Tikrina valstybiná numerá: lygiai 6 simboliai, 3 raidës + 3 skaitmenys (pvz. ABC123)
bool validusNumeris(const string& nr) {
    if (nr.length() != 6) return false;
    for (int i = 0; i < 3; ++i)
        if (!yraRaide(nr[i])) return false;
    for (int i = 3; i < 6; ++i)
        if (!yraSkaitmuo(nr[i])) return false;
    return true;
}

// Tikrina ar TA data logiðka (metai 2000–2030, mënuo 1–12)
bool validusMetai(int metai) { return metai >= 2000 && metai <= 2030; }
bool validusMenuo(int menuo) { return menuo >= 1  && menuo <= 12;   }

// Tikrina ar techninë apþiûra galioja.
// TA iðduodama datai, galioja 2 metus nuo tos datos.
// Galioja jei: TA pabaiga (ta_metai, ta_menuo) >= ðiandien (2026-06)
bool taGalioja(int ta_metai, int ta_menuo) {
    int dabMetai = 2026, dabMenuo = 6; // 2026 birþelis
    int dabTotal = dabMetai * 12 + dabMenuo;
    int taTotal  = ta_metai  * 12 + ta_menuo;
    return taTotal >= dabTotal; // TA data ateityje arba ðis mënuo = galioja
}

// Nuskaito sveikàjá skaièiø su klaidø tikrinimu
int nuskaitytiInt(const string& tekstas, int min, int max) {
    int reiksme;
    while (true) {
        cout << tekstas;
        if (cin >> reiksme && reiksme >= min && reiksme <= max) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return reiksme;
        }
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "  Klaida: áveskite skaièiø nuo " << min << " iki " << max << ".\n";
    }
}

// Nuskaito valstybiná numerá su validacija
string nuskaitytiNumeri(const string& tekstas) {
    string nr;
    while (true) {
        cout << tekstas;
        cin >> nr;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        nr = didziososRaides(nr);
        if (validusNumeris(nr)) return nr;
        cout << "  Klaida: numeris turi bûti AAA000 formatu (3 raidës 3 skaitmenys / be tarpo).\n";
    }
}

// Tikrina ar toks numeris jau egzistuoja sàraðe (gràþina indeksà arba -1)
int rastiPagalNumeri(const vector<Automobilis>& sarasas, const string& nr) {
    for (int i = 0; i < (int)sarasas.size(); ++i)
        if (sarasas[i].numeris == nr) return i;
    return -1;
}

// ===== 3. SPAUSDINIMAS =====

void spausdintiAntraste() {
    cout << string(78, '-') << "\n";
    cout << left
         << setw(4)  << "Valst. Nr."
         << setw(13) << "Marke"
         << setw(13) << "Modelis"
         << setw(9)  << "Numeris"
         << setw(11) << "Rida (km)"
         << setw(10) << "TA data"
         << setw(12) << "TA statusas"
         << "\n" << string(78, '-') << "\n";
}

void spausdintiEilute(const Automobilis& a, int nr) {
    string statusas = taGalioja(a.ta_metai, a.ta_menuo) ? "Galioja" : "PASIBAIGUSI";
    cout << left
         << setw(4)  << nr
         << setw(13) << a.marke
         << setw(13) << a.modelis
         << setw(9)  << a.numeris
         << setw(11) << a.rida
         << setw(2)  << a.ta_metai << "-" << setw(8) << (to_string(a.ta_menuo).length() == 1 ? "0"+to_string(a.ta_menuo) : to_string(a.ta_menuo))
         << setw(12) << statusas
         << "\n";
}

// ===== 4. FAILO OPERACIJOS =====

void nuskaitytiIsFailo(vector<Automobilis>& sarasas, const string& failas) {
    ifstream f(failas);
    if (!f.is_open()) {
        cout << "Duomenø failas '" << failas << "' nerastas. Pradedama su tuðèiu sàraðu.\n";
        return;
    }
    int eiluteNr = 0;
    string eilute;
    while (getline(f, eilute)) {
        eiluteNr++;
        if (eilute.empty()) continue;
        stringstream ss(eilute);
        Automobilis a;
        string metaiStr, menuoStr, ridaStr;
        try {
            getline(ss, a.marke,   ';');
            getline(ss, a.modelis, ';');
            getline(ss, a.numeris, ';');
            getline(ss, ridaStr,   ';');
            getline(ss, menuoStr,  ';');  // faile: rida;menuo;metai
            getline(ss, metaiStr,  ';');
            a.rida     = stoi(ridaStr);
            a.ta_menuo = stoi(menuoStr);
            a.ta_metai = stoi(metaiStr);
            sarasas.push_back(a);
        } catch (...) {
            cout << "Áspëjimas: " << eiluteNr << " eilutës duomenys netinkami, praleista.\n";
        }
    }
    f.close();
    cout << "Uþkrauta " << sarasas.size() << " áraðø ið '" << failas << "'.\n";
}

void irasytiIFaila(const vector<Automobilis>& sarasas, const string& failas) {
    ofstream f(failas);
    if (!f.is_open()) {
        cout << "Klaida: nepavyko iðsaugoti á failà '" << failas << "'!\n";
        return;
    }
    for (const auto& a : sarasas)
        f << a.marke << ";" << a.modelis << ";" << a.numeris << ";"
          << a.rida  << ";" << a.ta_menuo << ";" << a.ta_metai << "\n";
    f.close();
    cout << "Duomenys sëkmingai iðsaugoti á '" << failas << "'.\n";
}

// ===== 5. CRUD OPERACIJOS =====

// CREATE
void pridetiNauja(vector<Automobilis>& sarasas) {
    cout << "\n--- Naujo automobilio pridëjimas ---\n";
    Automobilis a;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "Markë: "; getline(cin, a.marke);
    cout << "Modelis: "; getline(cin, a.modelis);

    if (a.marke.empty() || a.modelis.empty()) {
        cout << "Klaida: markë ir modelis negali bûti tuðti.\n";
        return;
    }

    // Numerio validacija + unikalumo patikrinimas
    while (true) {
        a.numeris = nuskaitytiNumeri("Valstybinis numeris (AAA000): ");
        if (rastiPagalNumeri(sarasas, a.numeris) != -1) {
            cout << "  Klaida: automobilis su numeriu '" << a.numeris << "' jau egzistuoja!\n";
        } else break;
    }

    a.rida     = nuskaitytiInt("Rida (km, 0-9999999): ", 0, 9999999);
    a.ta_metai = nuskaitytiInt("TA metai (2000-2030): ", 2000, 2030);
    a.ta_menuo = nuskaitytiInt("TA mënuo (1-12): ", 1, 12);

    sarasas.push_back(a);
    cout << "Áraðas sëkmingai iðsaugotas: " << a.marke << " " << a.modelis << " (" << a.numeris << ").\n";
}

// READ – visi
void rodytiVisus(const vector<Automobilis>& sarasas) {
    if (sarasas.empty()) { cout << "Sàraðas tuðèias.\n"; return; }
    cout << "\n--- Visi automobiliai (" << sarasas.size() << ") ---\n";
    spausdintiAntraste();
    for (int i = 0; i < (int)sarasas.size(); ++i)
        spausdintiEilute(sarasas[i], i + 1);
}

// READ – vienas pagal numerá
void ieskotiPagalNumeri(const vector<Automobilis>& sarasas) {
    string nr;
    cout << "Áveskite valstybiná numerá: "; cin >> nr;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    nr = didziososRaides(nr);
    int idx = rastiPagalNumeri(sarasas, nr);
    if (idx == -1) {
        cout << "Áraðas su numeriu '" << nr << "' nerastas.\n";
        return;
    }
    spausdintiAntraste();
    spausdintiEilute(sarasas[idx], idx + 1);
}

// UPDATE

void redaguotiIrasa(vector<Automobilis>& sarasas) {
    rodytiVisus(sarasas);
    if (sarasas.empty()) return;
    int nr = nuskaitytiInt("Áveskite Nr. automobilio, kurio duomenis redaguoti (0 - atðaukti): ", 0, (int)sarasas.size());
    if (nr == 0) { cout << "Ðalinimas atðauktas.\n"; return; }
    Automobilis& a = sarasas[nr - 1];
    cout << "\nRedaguojamas: " << a.marke << " " << a.modelis << " (" << a.numeris << ")\n";
    cout << "(Enter - palikti esamà reikðmæ)\n\n";

    string tmp;

    cout << "Markë [" << a.marke << "]: ";
    getline(cin, tmp);
    if (!tmp.empty()) a.marke = tmp;

    cout << "Modelis [" << a.modelis << "]: ";
    getline(cin, tmp);
    if (!tmp.empty()) a.modelis = tmp;

    cout << "Numeris [" << a.numeris << "] (Enter - nekeisti): ";
    getline(cin, tmp);
    if (!tmp.empty()) {
        tmp = didziososRaides(tmp);
        if (!validusNumeris(tmp)) {
            cout << "  Netinkamas formatas – numeris nekeièiamas.\n";
        } else if (rastiPagalNumeri(sarasas, tmp) != -1 && tmp != a.numeris) {
            cout << "  Toks numeris jau egzistuoja – nekeièiamas.\n";
        } else {
            a.numeris = tmp;
        }
    }

    cout << "Rida [" << a.rida << "] (Enter - nekeisti): ";
    getline(cin, tmp);
    if (!tmp.empty()) {
        try { int r = stoi(tmp); if (r > 0) a.rida = r; }
        catch (...) { cout << "  Netinkama reikðmë – rida nekeièiama.\n"; }
    }

    cout << "TA metai [" << a.ta_metai << "] (Enter - nekeisti): ";
    getline(cin, tmp);
    if (!tmp.empty()) {
        try { int m = stoi(tmp); if (validusMetai(m)) a.ta_metai = m; }
        catch (...) { cout << "  Netinkama reikðmë – metai nekeièiami.\n"; }
    }

    cout << "TA mënuo [" << a.ta_menuo << "] (Enter - nekeisti): ";
    getline(cin, tmp);
    if (!tmp.empty()) {
        try { int m = stoi(tmp); if (validusMenuo(m)) a.ta_menuo = m; }
        catch (...) { cout << "  Netinkama reikðmë – mënuo nekeièiamas.\n"; }
    }

    cout << "Duomenys sëkmingai atnaujinti: " << a.marke << " " << a.modelis << " (" << a.numeris << ").\n";
}

// DELETE
void trintiIrasa(vector<Automobilis>& sarasas) {
    rodytiVisus(sarasas);
    if (sarasas.empty()) return;
    int nr = nuskaitytiInt("Áveskite Nr. automobilio, kurá paðalinti (0 - atðaukti): ", 0, (int)sarasas.size());
    if (nr == 0) { cout << "Redagavimas atðauktas.\n"; return; }
    const Automobilis& a = sarasas[nr - 1];
    cout << "Ar tikrai norite paðalinti " << a.marke << " " << a.modelis << " (" << a.numeris << ")? (y/n): ";
    char patvirtinimas; cin >> patvirtinimas;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    if (patvirtinimas == 'y' || patvirtinimas == 'Y') {
        sarasas.erase(sarasas.begin() + nr - 1);
        cout << "Áraðas sëkmingai paðalintas.\n";
    } else {
        cout << "Ðalinimas atðauktas.\n";
    }
}

// ===== 6. PAPILDOMOS FUNKCIJOS =====

// Filtravimas pagal TA statusà
void filtruotiPagalTA(const vector<Automobilis>& sarasas) {
    cout << "\n1. Galiojanti TA\n2. Pasibaigusi TA\nPasirinkite: ";
    int p; cin >> p;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    if (p != 1 && p != 2) { cout << "Neteisingas pasirinkimas.\n"; return; }

    bool ieskotiGaliojancia = (p == 1);
    vector<Automobilis> rezultatai;
    for (const auto& a : sarasas)
        if (taGalioja(a.ta_metai, a.ta_menuo) == ieskotiGaliojancia)
            rezultatai.push_back(a);

    string pav = ieskotiGaliojancia ? "galiojanèia TA" : "pasibaigusia TA";
    if (rezultatai.empty()) {
        cout << "Áraðø su " << pav << " nerasta.\n";
        return;
    }
    cout << "\nAutomobiliai su " << pav << " (" << rezultatai.size() << "):\n";
    spausdintiAntraste();
    for (int i = 0; i < (int)rezultatai.size(); ++i)
        spausdintiEilute(rezultatai[i], i + 1);
}

// Rikiavimas
void rikiuoti(vector<Automobilis>& sarasas) {
    cout << "\n1. Rida maþëjanèia\n2. Rida didëjanèia\n3. TA data (artimiausiai baigiasi pirmas)\n";
    cout << "Pasirinkite: ";
    int p; cin >> p;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    switch (p) {
        case 1: sort(sarasas.begin(), sarasas.end(),
                    [](const Automobilis& a, const Automobilis& b){ return a.rida > b.rida; });
                cout << "Surikiuota pagal ridà (maþëjanèiai).\n"; break;
        case 2: sort(sarasas.begin(), sarasas.end(),
                    [](const Automobilis& a, const Automobilis& b){ return a.rida < b.rida; });
                cout << "Surikiuota pagal ridà (didëjanèiai).\n"; break;
        case 3: sort(sarasas.begin(), sarasas.end(),
                    [](const Automobilis& a, const Automobilis& b){
                        return a.ta_metai*12+a.ta_menuo < b.ta_metai*12+b.ta_menuo; });
                cout << "Surikiuota pagal TA datà.\n"; break;
        default: cout << "Neteisingas pasirinkimas.\n"; return;
    }
    rodytiVisus(sarasas);
}

// Statistika
void statistika(const vector<Automobilis>& sarasas) {
    if (sarasas.empty()) { cout << "Sàraðas tuðèias.\n"; return; }
    long long suma = 0;
    int maxR = sarasas[0].rida, minR = sarasas[0].rida;
    string maxA, minA;
    int galioja = 0, pasibaige = 0;
    for (const auto& a : sarasas) {
        suma += a.rida;
        if (a.rida > maxR) { maxR = a.rida; maxA = a.marke+" "+a.modelis+" ("+a.numeris+")"; }
        if (a.rida < minR) { minR = a.rida; minA = a.marke+" "+a.modelis+" ("+a.numeris+")"; }
        taGalioja(a.ta_metai, a.ta_menuo) ? galioja++ : pasibaige++;
    }
    if (sarasas.size() == 1) maxA = minA = sarasas[0].marke+" "+sarasas[0].modelis;
    cout << "\n===== STATISTIKA =====\n";
    cout << "Ið viso automobiliø : " << sarasas.size() << "\n";
    cout << "Galiojanti TA       : " << galioja << "\n";
    cout << "Pasibaigusi TA      : " << pasibaige << "\n";
    cout << fixed << setprecision(0);
    cout << "Vidutinë rida       : " << (double)suma/sarasas.size() << " km\n";
    cout << "Didþiausia rida     : " << maxR << " km – " << maxA << "\n";
    cout << "Maþiausia rida      : " << minR << " km – " << minA << "\n";
    cout << "======================\n";
}

// ===== 7. MENIU =====

void spausdintiMeniu() {
    cout << "\n=== AUTOMOBILIØ DUOMENØ VALDYMAS ===\n";
    cout << "--- ÁRAÐØ VALDYMAS ---\n";
    cout << "1. Perþiûrëti visus automobilius (Read)\n";
    cout << "2. Paieðka pagal valstybiná numerá (Read)\n";
    cout << "3. Pridëti naujà automobilá (Create)\n";
    cout << "4. Redaguoti automobilio duomenis (Update)\n";
    cout << "5. Paðalinti automobilá (Delete)\n";
    cout << "--- PAPILDOMOS FUNKCIJOS ---\n";
    cout << "6. Filtruoti pagal TA statusà\n";
    cout << "7. Rikiuoti sàraðà\n";
    cout << "8. Statistika\n";
    cout << "0. Iðeiti ir iðsaugoti duomenis\n";
    cout << "Pasirinkite veiksmà: ";
}

// ===== 8. MAIN =====

int main() {
    vector<Automobilis> baze;
    const string FAILAS = "duomenys.txt";
    SetConsoleOutputCP(1257);  // Lietuviðka koduotë iðvedimui
    SetConsoleCP(1257);        // Lietuviðka koduotë ávedimui
    nuskaitytiIsFailo(baze, FAILAS);

    int pasirinkimas;
    do {
        spausdintiMeniu();
        // Skaièiaus nuskaitymas su klaidø tikrinimu
        if (!(cin >> pasirinkimas)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            pasirinkimas = -1;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (pasirinkimas) {
            case 1: rodytiVisus(baze);         break;
            case 2: ieskotiPagalNumeri(baze);  break;
            case 3: pridetiNauja(baze);        break;
            case 4: redaguotiIrasa(baze);      break;
            case 5: trintiIrasa(baze);         break;
            case 6: filtruotiPagalTA(baze);    break;
            case 7: rikiuoti(baze);            break;
            case 8: statistika(baze);          break;
         	case 0:
    			cout << "Issaugoti duomenis pries isejima? (y/n): ";
    			char ats; cin >> ats;
    			if (ats == 'y' || ats == 'Y')
        			irasytiIFaila(baze, FAILAS);
    			else
        			cout << "Pakeitimai neissaugoti.\n";
    			cout << "Viso gero!\n";
    			break;
            default:
                cout << "Neteisingas pasirinkimas! Bandykite dar karta.\n";
        }
    } while (pasirinkimas != 0);

    return 0;
}
