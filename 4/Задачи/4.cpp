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

const int p = 31;
const int m = 1e9 + 9;

//------------------------------------

int main() {
    getFirstTime();

    // ---- code starts here -----
    string s;
    fin >> s;

    vector <int> pows (s.size() + 1);
    pows[0] = 1;
    for(int i = 1; i <= s.size(); ++ i) {
        pows[i] = (1ll * pows[i - 1] * p) % m;
    }
    vector <int> hashes (s.size() + 1, 0);
    hashes[s.size() - 1] = (s[s.size() - 1] - 'a' + 1);

    for(int i = s.size() - 2; i >= 0; -- i) {
        hashes[i] = (hashes[i + 1] + 1ll * (s[i] - 'a' + 1) * pows[s.size() - i - 1]) % m;
    }

    int q;
    fin >> q;

    while(q --) {
        int a, b, l;
        fin >> a >> b >> l;
        if(a > b)
            swap(a, b);

        int firsthash = (hashes[a] - hashes[a + l]),
            secondhash = (1ll * (hashes[b] - hashes[b + l]) * pows[b - a]) % m;

        if(firsthash == secondhash) {
            fout << "Yes\n";
        } else {
            fout << "No\n";
        }
    }
    // ---- code ends here -----

    printTimeUse();
    printMemoryUse();

    fin.close();
    fout.close();
    return 0;
}
