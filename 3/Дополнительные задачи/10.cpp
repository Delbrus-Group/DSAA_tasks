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
const int INF = numeric_limits<int>::max();

struct Edge {
    int a, b, cost;
};

vector<int> bellman_ford(int n, int s, const vector<Edge> &edges) {
    vector<int> d(n, INF);
    d[s] = 0;
    vector<int> p(n, -1);
    int x;
    for (int i = 0; i < n; ++i) {
        x = -1;
        for (int j = 0; j < edges.size(); ++j)
            if (d[edges[j].a] < INF)
                if (d[edges[j].b] > d[edges[j].a] + edges[j].cost) {
                    d[edges[j].b] = max(-INF, d[edges[j].a] + edges[j].cost);
                    p[edges[j].b] = edges[j].a;
                    x = edges[j].b;
                }
    }

    if (x != -1) {
        int y = x;
        for (int i = 0; i < n; ++i)
            y = p[y];

        vector<int> path;
        for (int cur = y;; cur = p[cur]) {
            path.push_back(cur);
            if (cur == y && path.size() > 1)
                break;
        }
        reverse(path.begin(), path.end());

        for (size_t i = 0; i < path.size(); ++i)
            d[path[i]] = -INF;
    }

    return d;
}


int main() {
    getFirstTime();

    // ---- code starts here -----

    int n, m, s;
    fin >> n >> m;

    vector<Edge> edges(m);
    for (int i = 0; i < m; i++) {
        int u, v, w;
        fin >> u >> v >> w;
        edges[i] = {u - 1, v - 1, w}; // 0-based indexing
    }

    fin >> s;

    vector<int> dist = bellman_ford(n, s - 1, edges);

    for (int i = 0; i < n; i++) {
        if (dist[i] == INF) {
            fout << "*" << endl;
        } else if (dist[i] == -INF) {
            fout << "-" << endl;
        } else {
            fout << dist[i] << endl;
        }
    }

    // ---- code ends here -----

    printTimeUse();
    printMemoryUse();

    fin.close();
    fout.close();
    return 0;
}
