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

int main() {
    getFirstTime();

    // ---- code starts here -----

    int n;
    vector <int> a (7);
    fin >> n;
    for (int i = 0; i < 7; i++) {
        fin >> a[i];
    }

    for(int i = 1; i < 7; ++ i) {
        a[i] = min(a[i], a[i - 1] * 10);
    }

    int cur = 0;
    long long ans = 0;
    int copyn = n;

    while(copyn) {
        ans += a[cur] * (copyn % 10);
        copyn /= 10;
        ++ cur;
    }

    int nowPower = 1;
    for(int i = 0; i < 7; ++ i) {
        if(nowPower >= n && a[i] < ans) {
            ans = a[i];
        }
        nowPower *= 10;
    }

    fout << ans << endl;

    // ---- code ends here -----

    printTimeUse();
    printMemoryUse();

    fin.close();
    fout.close();
    return 0;
}
