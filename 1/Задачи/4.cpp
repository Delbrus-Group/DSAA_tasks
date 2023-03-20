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
    vector<pair<int, int>> segments(n);
    for (int i = 0; i < n; i++) {
        fin >> segments[i].first >> segments[i].second;
    }

    sort(segments.begin(), segments.end(), [](const auto& a, const auto& b) {
        return a.second < b.second;
    });

    vector<int> points;
    int rightmost = -1;

    for (const auto& [left, right] : segments) {
        if (left > rightmost) {
            points.push_back(right);
            rightmost = right;
        }
    }

    fout << points.size() << endl;

    for (int p: points) {
        fout << p << " ";
    }

    // ---- code ends here -----

    printTimeUse();
    printMemoryUse();

    fin.close();
    fout.close();
    return 0;
}
