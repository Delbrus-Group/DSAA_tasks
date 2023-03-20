#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <math.h>
#include "windows.h"
#include "psapi.h"
#include <time.h>
#include <stdlib.h>
#include <algorithm>
#include <type_traits>

using namespace std;

//------------------------------------

ifstream fin("input.txt");
ofstream fout("output.txt");

clock_t start;

void printMemoryUse() {
    PROCESS_MEMORY_COUNTERS_EX pmc;
    GetProcessMemoryInfo(GetCurrentProcess(), (PROCESS_MEMORY_COUNTERS *) &pmc, sizeof(pmc));
    SIZE_T virtualMemUsedByMe = pmc.PrivateUsage;

    cerr << fixed << setprecision(6);
    cerr << "Memory used: " << double(virtualMemUsedByMe) / (1024. * 1024) << " MB\n";
}

void getFirstTime() {
    start = clock();
}

void printTimeUse() {
    cerr << fixed << setprecision(6);
    cerr << "Time used: " << (double) (clock() - start) / CLOCKS_PER_SEC << " sec\n";
}

//------------------------------------

int ReadRank() {
    const string kRanks = "6789TJQKA";
    char rank;
    fin >> rank;
    return static_cast<int>(kRanks.find(rank));
}

int ReadSuit() {
    const string kSuits = "SCDH";
    char suit;
    fin >> suit;
    return static_cast<int>(kSuits.find(suit));
}

int main() {
    getFirstTime();

    // ---- code starts here -----
    int num_cards, num_tricks;
    fin >> num_cards >> num_tricks;
    int trump_suit = ReadSuit();
    vector<vector<bool>> available_ranks(9, vector<bool>(4, false));

    for (int i = 0; i < num_cards; ++i) {
        int rank = ReadRank();
        int suit = ReadSuit();
        available_ranks[rank][suit] = true;
    }

    for (int i = 0; i < num_tricks; ++i) {
        int rank = ReadRank();
        int suit = ReadSuit();
        bool found = false;

        for (int r = rank + 1; r <= 8; ++r) {
            if (available_ranks[r][suit]) {
                available_ranks[r][suit] = false;
                found = true;
                break;
            }
        }

        if (!found && suit != trump_suit) {
            for (int r = 0; r <= 8; ++r) {
                if (available_ranks[r][trump_suit]) {
                    available_ranks[r][trump_suit] = false;
                    found = true;
                    break;
                }
            }
        }

        if (!found) {
            fout << "NO";
            return 0;
        }
    }

    fout << "YES";
    // ---- code ends here -----

    printTimeUse();
    printMemoryUse();

    fin.close();
    fout.close();
    return 0;
}
