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

int isMaskGood(int curMask, int prevMask, int n) {
    for (int i = 1; i < n; ++ i) {
        int white = (((1 << (i - 1)) & (curMask)) > 0) +
                    (((1 << (i)) & (curMask)) > 0) +
                    (((1 << (i - 1)) & (prevMask)) > 0) +
                    (((1 << (i)) & (prevMask)) > 0);

        if (white == 4 || white == 0)
            return false;
    }
    return true;
}

int main() {
    getFirstTime();

    // ---- code starts here -----
    int n, m;
    fin >> n >> m;
    if (n > m)
        swap(n, m);

    int full = (1 << n);
    vector<vector<int64_t> > dp(32, vector<int64_t>(full, 0));
    for (int mask = 0; mask < full; mask++)
        dp[1][mask] = 1;

    for (int i = 2; i <= m; ++ i) {
        for (int curMask = 0; curMask < full; curMask++) {
            for (int prevMask = 0; prevMask < full; prevMask++) {
                if (isMaskGood(curMask, prevMask, n)) {
                    dp[i][curMask] += dp[i - 1][prevMask];
                }
            }
        }
    }

    int64_t ans = 0;
    for (int mask = 0; mask < full; mask++)
        ans += dp[m][mask];

    fout << ans;
    // ---- code ends here -----

    printTimeUse();
    printMemoryUse();

    fin.close();
    fout.close();
    return 0;
}
