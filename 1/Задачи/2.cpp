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

    int d, m, n;
    fin >> d >> m >> n;

    vector<int> stops(n+2);
    for (int i = 1; i <= n; i++) {
        fin >> stops[i];
    }
    stops[0] = 0;
    stops[n+1] = d;

    int num_refills = 0, current_refill = 0;
    while (current_refill <= n) {
        int last_refill = current_refill;
        while (current_refill <= n && stops[current_refill+1] - stops[last_refill] <= m) {
            current_refill++;
        }
        if (current_refill == last_refill) {
            fout << "-1" << endl;
            return 0;
        }
        if (current_refill <= n) {
            num_refills++;
        }
    }

    fout << num_refills << endl;

    // ---- code ends here -----

    printTimeUse();
    printMemoryUse();

    fin.close();
    fout.close();
    return 0;
}
