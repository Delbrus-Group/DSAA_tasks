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
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        fin >> a[i];
    }
    sort(a.begin(), a.end(), greater<int>());
    int sum = 0;
    for (int i = 0; i < n; i++) {
        sum += a[i];
    }
    if (sum % 2 == 1) {
        fout << "-1";
        return 0;
    }

    vector <int> aswecan;
    int sum1, sum2;
    sum1 = sum2 = 0;

    for(int i = 0; i < n; ++ i) {
        if(sum1 <= sum2) {
            sum1 += a[i];
            aswecan.push_back(a[i]);
        } else {
            sum2 += a[i];
        }
    }

    fout << aswecan.size() << '\n';
    for(int i = 0; i < aswecan.size(); ++ i) {
        fout << aswecan[i] << ' ';
    }


    // ---- code ends here -----

    printTimeUse();
    printMemoryUse();

    fin.close();
    fout.close();
    return 0;
}
