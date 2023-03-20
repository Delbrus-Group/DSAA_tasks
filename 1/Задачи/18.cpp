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
    int ans, k1, k2;

    fin >> n;

    vector<int> a(n + 1);
    vector<vector<int> > b(n + 1, vector<int>(n + 1, -1));
    vector<vector<int> > p(n + 1, vector<int>(n + 1, -1));
    vector<int> r(n + 1);

    for (int i = 1; i <= n; i++) {
        fin >> a[i];
    }

    b[0][0] = 0;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= i; j++) {
            if (b[i][j] != -1) {
                if (j > 0) {
                    if (b[i + 1][j - 1] > b[i][j] || b[i + 1][j - 1] == -1) {
                        b[i + 1][j - 1] = b[i][j];
                        p[i + 1][j - 1] = j;
                    }
                }

                int k = (a[i + 1] > 100) ? 1 : 0;

                if (b[i + 1][j + k] > b[i][j] + a[i + 1] || b[i + 1][j + k] == -1) {
                    b[i + 1][j + k] = b[i][j] + a[i + 1];
                    p[i + 1][j + k] = j;
                }
            }
        }
    }

    ans = 1e9;
    for (int i = 0; i <= n; i++) {
        if (b[n][i] != -1 && b[n][i] <= ans) {
            ans = b[n][i];
            k1 = i;
        }
    }

    int j = k1;
    k2 = 0;
    for (int i = n; i >= 1; i--) {
        if (j + 1 == p[i][j]) {
            k2++;
            r[k2] = i;
        }
        
        j = p[i][j];
    }

    fout << ans << '\n' << k1 << " " << k2 << endl;
    for (int i = k2; i >= 1; i--) {
        fout << r[i] << endl;
    }

    // ---- code ends here -----

    printTimeUse();
    printMemoryUse();

    fin.close();
    fout.close();
    return 0;
}
