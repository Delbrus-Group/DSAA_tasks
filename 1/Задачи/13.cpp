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

    vector <int> a (n);
    for(auto &i : a)
        fin >> i;

    int sum = 0;
    for(auto &i : a)
        sum += i;

    if(sum % 3) {
        fout << 0;
        return 0;
    }

    vector <int> test (2 * sum / 3);

    for(int i = 0; i < (1ll << n); i++) {
        int sum1 = 0;
        for (int j = 0; j < n; ++j) {
            if (i & (1ll << j))
                sum1 += a[j];
        }

        if (sum1 == sum / 3) {
            int cur = 0;
            for (int j = 0; j < n; ++j) {
                if (!(i & (1ll << j)))
                    test[cur++] = a[j];
            }

            for (int j = 0; j < (1ll << cur); j++) {
                int sum2 = 0;
                for (int k = 0; k < cur; ++k) {
                    if (j & (1ll << k))
                        sum2 += test[k];
                }

                if (sum2 == sum / 3) {
                    fout << 1;
                    printTimeUse();
                    printMemoryUse();
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
