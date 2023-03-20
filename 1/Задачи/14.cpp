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

int f(int i, int j, const string &s, bool isMax = true) {
    if (i == j) {
        return s[i] - '0';
    }

    if(isMax) {
        int ans = -1e9;

        for (int k = i; k < j; ++k) {
            if (s[k] == '+')
                ans = max(ans, f(i, k - 1, s) + f(k + 1, j, s));
            else if (s[k] == '-')
                ans = max(ans, f(i, k - 1, s) - f(k + 1, j, s, 0));
            else if(s[k] == '*')
                ans = max(ans, f(i, k - 1, s) * f(k + 1, j, s));
        }

        return ans;
    } else {
        int ans = 1e9;

        for (int k = i; k < j; ++k) {
            if (s[k] == '+')
                ans = min(ans, f(i, k - 1, s, 0) + f(k + 1, j, s, 0));
            else if (s[k] == '-')
                ans = min(ans, f(i, k - 1, s, 0) - f(k + 1, j, s, 1));
            else if(s[k] == '*')
                ans = min(ans, f(i, k - 1, s, 0) * f(k + 1, j, s, 0));
        }

        return ans;
    }
}


int main() {
    getFirstTime();

    // ---- code starts here -----

    string s;
    fin >> s;

    fout << f(0, s.size() - 1, s);

    // ---- code ends here -----

    printTimeUse();
    printMemoryUse();

    fin.close();
    fout.close();
    return 0;
}
