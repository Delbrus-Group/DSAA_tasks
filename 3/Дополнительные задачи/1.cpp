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
vector<vector<int>> g;
vector<bool> visited;

void dfs(int v, int p = -1) {
    if(visited[v])
        return;

    visited[v] = true;
    for(int u : g[v]) {
        if(u == p)
            continue;

        dfs(u, v);
    }
}

int main() {
    getFirstTime();

    // ---- code starts here -----

    int n, m;
    fin >> n >> m;

    g.assign(n, vector <int> ());
    visited.assign(n, false);
    for(int i = 0; i < m; ++ i) {
        int a, b;
        fin >> a >> b;

        -- a; -- b;
        g[a].push_back(b);
        g[b].push_back(a);
    }

    int u, v;
    fin >> u >> v;
    -- u; -- v;
    dfs(u);

    fout << visited[v];

    // ---- code ends here -----

    printTimeUse();
    printMemoryUse();

    fin.close();
    fout.close();
    return 0;
}
