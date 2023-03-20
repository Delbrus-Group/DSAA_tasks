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
    fin >> n;

    vector <vector <int>> a(n, vector <int>(n));
    for(int i = 0; i < n; ++ i)
        for(int j = 0; j < n; ++ j)
            fin >> a[i][j];

    vector <vector <int> > dp ((1ll << n), vector <int> (n, 1e9));
    vector <vector <int> > parent ((1ll << n), vector <int> (n, -1));
    for(int i = 0; i < n; ++ i)
        dp[(1 << i)][i] = 0;

    for(int i = 0; i < (1ll << n); ++ i) {
        for(int j = 0; j < n; ++ j) {
            if(!(i & (1ll << j)))
                continue;

            for(int k = 0; k < n; ++ k) {
                if((i & (1 << k)))
                    continue;

                dp[i | (1 << k)][k] = min(dp[i | (1 << k)][k], dp[i][j] + a[j][k]);
                if(dp[i | (1 << k)][k] == dp[i][j] + a[j][k])
                    parent[i | (1 << k)][k] = j;
            }
        }
    }

    int minimum = 1e9, lastparent = -1, curmask = (1 << n) - 1;
    vector <int> ans;
    for(int i = 0; i < n; ++ i) {
        if(dp[curmask][i] < minimum) {
            minimum = dp[curmask][i];
            lastparent = i;
        }
    }

    while(lastparent != -1) {
        ans.push_back(lastparent);
        int newmask = curmask ^ (1 << lastparent);
        lastparent = parent[curmask][lastparent];
        curmask = newmask;
    }

    fout << minimum << '\n';
    for(int i = ans.size() - 1; i >= 0; -- i)
        fout << " " << ans[i] + 1;
    // ---- code ends here -----

    printTimeUse();
    printMemoryUse();

    fin.close();
    fout.close();
    return 0;
}
