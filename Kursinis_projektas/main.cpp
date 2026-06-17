#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <numeric>
#include <iomanip>
#include <random>

// ============================================================
//  Globalūs skaitikliai
// ============================================================
long long comparisons = 0;   // palyginimų skaičius
long long swaps       = 0;   // sukeitimų skaičius

// ============================================================
//  INSERTION SORT
// ============================================================
void insertionSort(std::vector<int>& arr) {
    int n = arr.size();
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;

        // Perkeliame elementus, kurie didesni už key, viena pozicija į dešinę
        while (j >= 0 && (++comparisons, arr[j] > key)) {
            arr[j + 1] = arr[j];
            swaps++;   // loginis perkėlimas
            j--;
        }
        arr[j + 1] = key;
    }
}

// ============================================================
//  MERGE SORT – pagalbinė funkcija: suliejimas
// ============================================================
void merge(std::vector<int>& arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    std::vector<int> L(arr.begin() + left, arr.begin() + left + n1);
    std::vector<int> R(arr.begin() + mid + 1, arr.begin() + mid + 1 + n2);

    int i = 0, j = 0, k = left;

    while (i < n1 && j < n2) {
        comparisons++;
        if (L[i] <= R[j]) {
            arr[k++] = L[i++];
        } else {
            arr[k++] = R[j++];
            swaps++;   // inversijų skaičius
        }
    }

    // Likusių elementų perkėlimas
    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];
}

// ============================================================
//  MERGE SORT – rekursinė funkcija
// ============================================================
void mergeSort(std::vector<int>& arr, int left, int right) {
    if (left >= right) return;

    int mid = left + (right - left) / 2;
    mergeSort(arr, left, mid);
    mergeSort(arr, mid + 1, right);
    merge(arr, left, mid, right);
}

// ============================================================
//  Duomenų generavimas
// ============================================================

// Atsitiktiniai duomenys
std::vector<int> generateRandom(int n) {
    std::vector<int> arr(n);
    std::mt19937 rng(42);   // fiksuota sėkla – tie patys duomenys abiem algoritmams
    std::uniform_int_distribution<int> dist(1, n * 10);
    for (int& x : arr) x = dist(rng);
    return arr;
}

// Atvirkščiai surikiuoti duomenys
std::vector<int> generateReverse(int n) {
    std::vector<int> arr(n);
    for (int i = 0; i < n; i++) arr[i] = n - i;
    return arr;
}

// Jau surikiuoti duomenys
std::vector<int> generateSorted(int n) {
    std::vector<int> arr(n);
    for (int i = 0; i < n; i++) arr[i] = i + 1;
    return arr;
}

// ============================================================
//  Matavimo funkcija – grąžina vidurkį iš REPEAT kartų
// ============================================================
const int REPEAT = 5;

struct Result {
    double avgTime;       // mikrosekundės
    long long avgComps;
    long long avgSwaps;
};

template<typename SortFunc>
Result measure(const std::vector<int>& original, SortFunc sortFunc) {
    std::vector<double> times(REPEAT);
    std::vector<long long> compsVec(REPEAT), swapsVec(REPEAT);

    for (int r = 0; r < REPEAT; r++) {
        std::vector<int> arr = original;   // kopija kiekvienam bandymui

        comparisons = 0;
        swaps       = 0;

        // Matuojame TIK rikiavimo laiką
        auto start = std::chrono::high_resolution_clock::now();
        sortFunc(arr);
        auto end   = std::chrono::high_resolution_clock::now();

        times[r]    = std::chrono::duration<double, std::micro>(end - start).count();
        compsVec[r] = comparisons;
        swapsVec[r] = swaps;
    }

    Result res;
    res.avgTime  = std::accumulate(times.begin(),    times.end(),    0.0) / REPEAT;
    res.avgComps = std::accumulate(compsVec.begin(), compsVec.end(), 0LL) / REPEAT;
    res.avgSwaps = std::accumulate(swapsVec.begin(), swapsVec.end(), 0LL) / REPEAT;
    return res;
}

// ============================================================
//  Lentelės spausdinimas
// ============================================================
void printHeader(std::ostream& out) {
    out << std::left
        << std::setw(12) << "Algoritmas"
        << std::setw(10) << "N"
        << std::setw(18) << "Duomenys"
        << std::setw(16) << "Laikas (us)"
        << std::setw(16) << "Palyginimai"
        << std::setw(16) << "Sukeitimai"
        << "\n";
    out << std::string(88, '-') << "\n";
}

void printRow(std::ostream& out,
              const std::string& algo, int n,
              const std::string& type, const Result& r) {
    out << std::left
        << std::setw(12) << algo
        << std::setw(10) << n
        << std::setw(18) << type
        << std::setw(16) << std::fixed << std::setprecision(2) << r.avgTime
        << std::setw(16) << r.avgComps
        << std::setw(16) << r.avgSwaps
        << "\n";
}

// ============================================================
//  MAIN
// ============================================================
int main() {
    std::vector<int> sizes = {5000, 10000, 50000};

    std::ofstream csvFile("rezultatai.csv");
    csvFile << "Algoritmas,N,Duomenys,Laikas_us,Palyginimai,Sukeitimai\n";

    std::cout << "\n=== Rikiavimo algoritmų lyginamoji analizė ===\n";
    std::cout << "Kartojimų skaičius: " << REPEAT << "\n\n";

    printHeader(std::cout);

    for (int n : sizes) {
        std::vector<std::pair<std::string, std::vector<int>>> datasets = {
            {"Atsitiktiniai", generateRandom(n)},
            {"Atvirksciai",   generateReverse(n)},
            {"Surikiuoti",    generateSorted(n)}
        };

        for (auto& [typeName, data] : datasets) {

            // --- Insertion sort ---
            Result insRes = measure(data, [](std::vector<int>& arr) {
                insertionSort(arr);
            });
            printRow(std::cout, "Insertion", n, typeName, insRes);
            csvFile << "Insertion," << n << "," << typeName << ","
                    << std::fixed << std::setprecision(2) << insRes.avgTime << ","
                    << insRes.avgComps << "," << insRes.avgSwaps << "\n";

            // --- Merge sort ---
            Result merRes = measure(data, [](std::vector<int>& arr) {
                mergeSort(arr, 0, (int)arr.size() - 1);
            });
            printRow(std::cout, "Merge", n, typeName, merRes);
            csvFile << "Merge," << n << "," << typeName << ","
                    << std::fixed << std::setprecision(2) << merRes.avgTime << ","
                    << merRes.avgComps << "," << merRes.avgSwaps << "\n";

            std::cout << "\n";
        }
        std::cout << std::string(88, '-') << "\n";
    }

    csvFile.close();
    std::cout << "\nRezultatai issaugoti: rezultatai.csv\n";
    return 0;
}