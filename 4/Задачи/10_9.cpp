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

void reverseString(string &a, int l, int r) {
    string tmp = a;
    for (int i = 0; i < r - l + 1; i++) {
        a[l + i] = tmp[r - i];
    }
}

int main() {
    getFirstTime();

    // ---- code starts here -----
    string s, f;
    fin >> s >> f;

    int n = s.size();
    vector<pair<int, int> > ans;
    for (int i = 0; i < n - 1; ++i) {
        for (int j = i + 1; j < n; ++j) {
            if (s[j] == f[i]) {
                ans.emplace_back(i + 1, j + 1);
                reverseString(s, i, j);
                break;
            }
        }
    }

    fout << ans.size() << '\n';
    for (auto i: ans)
        fout << i.first << ' ' << i.second << '\n';

    // ---- code ends here -----

    printTimeUse();
    printMemoryUse();

    fin.close();
    fout.close();
    return 0;
}
