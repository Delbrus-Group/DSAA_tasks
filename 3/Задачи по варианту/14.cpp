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
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <queue>

using namespace std;
using namespace __gnu_pbds;

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
vector<vector<pair <int, int> >> g;

int main() {
    getFirstTime();

    // ---- code starts here -----

    int n, s, f, m;
    fin >> n >> s >> f >> m;

    struct Info {
        int a, b, c, d;
    };

    vector <Info> g(m);

    for (int i = 0; i < m; i++) {
        int s, t, e, l;
        fin >> s >> t >> e >> l;
        g[i] = {s, t, e, l};
    }

    vector <int> d (n, INT_MAX);

    d[s - 1] = 0;
    for(int i = 0; i < n - 1; ++ i)
        for(int j = 0; j < m; ++ j)
            if(d[g[j].c - 1] > g[j].d && d[g[j].a - 1] != INT_MAX && g[j].b >= d[g[j].a - 1])
                d[g[j].c - 1] = g[j].d;

    fout << (d[f - 1] == INT_MAX ? -1 : d[f - 1]);

    // ---- code ends here -----

    printTimeUse();
    printMemoryUse();

    fin.close();
    fout.close();
    return 0;
}
