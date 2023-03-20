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

    const int mod = 1e9;

    int n;
    fin >> n;

    vector <int64_t> dp (10, 1);
    dp[8] = dp[0] = 0;

    for(int i = 1; i < n; ++ i) {
        vector <int64_t> new_dp (10, 0);
        new_dp[0] = (dp[4] + dp[6]) % mod;
        new_dp[1] = (dp[6] + dp[8]) % mod;
        new_dp[2] = (dp[7] + dp[9]) % mod;
        new_dp[3] = (dp[4] + dp[8]) % mod;
        new_dp[4] = (dp[0] + dp[3] + dp[9]) % mod;
        new_dp[6] = (dp[0] + dp[1] + dp[7]) % mod;
        new_dp[7] = (dp[2] + dp[6]) % mod;
        new_dp[8] = (dp[1] + dp[3]) % mod;
        new_dp[9] = (dp[2] + dp[4]) % mod;

        dp = new_dp;
    }

    int64_t ans = 0;
    for(int i = 0; i < 10; ++ i)
        ans = (ans + dp[i]) % mod;

    fout << ans << '\n';

    // ---- code ends here -----

    printTimeUse();
    printMemoryUse();

    fin.close();
    fout.close();
    return 0;
}
