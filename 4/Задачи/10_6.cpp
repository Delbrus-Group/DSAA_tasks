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

int main() {
    getFirstTime();

    // ---- code starts here -----
    int cnt;
    string s, s1, t;
    fin >> t >> s1;
    cnt = t.size();

    s = t + ' ' + s1 + s1;
    int l = 0, r = 0;
    int n = s.size();

    vector <int> z (n);
    for(int i = 0; i < n; i ++)
        z[i] = 0;

    int id = 0;

    for(int i = 1; i < n; i ++) {
        if(i <= r)
            z[i] = min(z[i - l], r - i + 1);
        while(i + z[i] < n && s[z[i]] == s[i + z[i]])
            z[i] ++;
        if(i + z[i] - 1 > r) {
            l = i;
            r = i + z[i] - 1;
        }
        if(z[i] > z[id])
            id = i;
    }

    if(z[id] != t.length())
        fout << -1;
    else fout << (id - cnt - 1);

    // ---- code ends here -----

    printTimeUse();
    printMemoryUse();

    fin.close();
    fout.close();
    return 0;
}
