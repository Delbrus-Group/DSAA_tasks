#include <iostream>
#include <fstream>
#include <map>
#include <iomanip>
#include <vector>
#include <math.h>
#include "windows.h"
#include "psapi.h"
#include <time.h>
#include <stdlib.h>
#include <algorithm>
#include <numeric>
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

void reverseString(string &a, int l, int r) {
    string tmp = a;
    for (int i = 0; i < r - l + 1; i++) {
        a[l + i] = tmp[r - i];
    }
}

int main() {
    getFirstTime();

    // ---- code starts here -----
    int n;
    fin >> n;

    vector<string> words(n);
    for (auto &i: words)
        fin >> i;

    int m;
    fin >> m;
    vector<string> patterns(m);
    for (auto &i: patterns)
        fin >> i;

    map<string, int> howmany;

    for (auto &i: words) {
        for (int length = 1; length <= i.size(); ++length) {
            string prefix = i.substr(0, length),
                    suffix = i.substr(i.size() - length, length);

            if (prefix != suffix)
                continue;

            howmany[prefix]++;
        }
    }

    for (auto &i: patterns)
        fout << howmany[i] << '\n';

    // ---- code ends here -----

    printTimeUse();
    printMemoryUse();

    fin.close();
    fout.close();
    return 0;
}
