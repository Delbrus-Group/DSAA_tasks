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

int f(int l, int r, vector<vector<int>> &dp, vector <vector<string>> &correct, string &s) {
    if(l > r) {
        return 0;
    }

    if(l == r)
        return 1;

    if(dp[l][r] != -1) {
        return dp[l][r];
    }

    dp[l][r] = INT_MAX;

    for(int k = l; k <= r; ++ k) {
        if(f(l, k, dp, correct, s) + f(k + 1, r, dp, correct, s) < dp[l][r]) {
            dp[l][r] = f(l, k, dp, correct, s) + f(k + 1, r, dp, correct, s);
            correct[l][r] = correct[l][k] + correct[k + 1][r];
        }
    }

    if(f(l + 1, r, dp, correct, s) + 1 < dp[l][r]) {
        dp[l][r] = f(l + 1, r, dp, correct, s) + 1;
        correct[l][r] = correct[l + 1][r];
    }

    if(f(l, r - 1, dp, correct, s) + 1 < dp[l][r]) {
        dp[l][r] = f(l, r - 1, dp, correct, s) + 1;
        correct[l][r] = correct[l][r - 1];
    }

    if((s[l] == '(' && s[r] == ')') || (s[l] == '[' && s[r] == ']') || (s[l] == '{' && s[r] == '}')) {
        if(f(l + 1, r - 1, dp, correct, s) < dp[l][r]) {
            dp[l][r] = f(l + 1, r - 1, dp, correct, s);
            correct[l][r] = s[l];
            correct[l][r] += s[r];
            if(l + 1 <= r - 1)
                correct[l][r] = s[l] + correct[l + 1][r - 1] + s[r];
        }
    }

    return dp[l][r];
}

int main() {
    getFirstTime();

    // ---- code starts here -----

    string s;
    fin >> s;

    vector<vector<int>> dp(s.size(), vector<int>(s.size(), -1));
    vector<vector<string>> correct(s.size(), vector<string>(s.size(), ""));

    f(0, s.size() - 1, dp, correct, s);
    fout << correct[0][s.size() - 1];
    // ---- code ends here -----

    printTimeUse();
    printMemoryUse();

    fin.close();
    fout.close();
    return 0;
}
