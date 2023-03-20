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

const int MAXN = 5005;

char s[MAXN];


int main() {
    getFirstTime();

    // ---- code starts here -----
    int n;
    fin >> n;

    int K;
    fin >> K >> s;
    int ans = 0;

    for (int i = 0; i < n; i++) {
        int l = i, r = i;
        int diff = 0;
        while (l >= 0 && r < n && diff <= K) {
            if (s[l] != s[r]) diff++;
            if (diff > K) break;
            ans++;
            l--, r++;
        }
        l = i, r = i + 1, diff = 0;

        while (l >= 0 && r < n && diff <= K) {
            if (s[l] != s[r]) diff++;
            if (diff > K) break;
            ans++;
            l--, r++;
        }
    }

    fout << ans << endl;
    // ---- code ends here -----

    printTimeUse();
    printMemoryUse();

    fin.close();
    fout.close();
    return 0;
}
