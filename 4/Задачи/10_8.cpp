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

int main() {
    getFirstTime();

    // ---- code starts here -----
    string s;
    fin >> s;

    int n = s.size();
    vector <vector <int> > cnt (n + 1, vector <int> (26, 0));
    for(int i = 1; i <= n; ++ i) {
        cnt[i] = cnt[i - 1];
        cnt[i][s[i - 1] - 'a']++;
    }

    for(int length = n - 1; length >= 1; -- length) {
        for(int i = 0; i < n - length + 1; ++ i) {
            for(int j = 0; j < n - length + 1; ++ j) {
                if(i == j)
                    continue;

                bool ok = true;
                for(int z = 0; z < 26; ++ z)
                    if(cnt[j + length][z] - cnt[j][z] != cnt[i + length][z] - cnt[i][z]) {
                        ok = false;
                        break;
                    }

                if(ok) {
                    cout << length;
                    return 0;
                }
            }
        }
    }

    fout << 0;

    // ---- code ends here -----

    printTimeUse();
    printMemoryUse();

    fin.close();
    fout.close();
    return 0;
}
