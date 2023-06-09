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
int dfs(int i, vector <vector <int> > &g, int d = 1, int p = -1) {
    int maxDepth = d;
    for(int j : g[i]) {
        if(j == p)
            continue;

        maxDepth = max(dfs(j, g, d + 1, i), maxDepth);
    }

    return maxDepth;
}


int main() {
    getFirstTime();

    // ---- code starts here -----

    int n;
    fin >> n;

    vector <vector <int> > g(n, vector <int> ());

    for(int i = 0; i < n; ++ i) {
        int k, l, r;
        fin >> k >> l >> r;

        if(l)
            g[i].push_back(l - 1);
        if(r)
            g[i].push_back(r - 1);
    }

    fout << dfs(0, g);

    // ---- code ends here -----

    printTimeUse();
    printMemoryUse();

    fin.close();
    fout.close();
    return 0;
}
