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

    int n, s;
    fin >> n >> s;

    vector<pair <pair <int, int> , int>> apples;
    vector<pair <pair <int, int> , int>> left;
    apples.reserve(n);
    left.reserve(n);

    for (int i = 0; i < n; ++i) {
        pair <int, int> a;
        fin >> a.first >> a.second;

        if(a.second > a.first)
            apples.push_back({a, i});
        else
            left.push_back({a, i});
    }

    sort(apples.begin(), apples.end());
    sort(left.begin(), left.end(), [](const pair <pair <int, int> , int> &a, const pair <pair <int, int> , int> &b) {
        return a.first.second - a.first.first < b.first.second - b.first.first;
    });

    vector <int> answer;

    for(auto &i : apples) {
        if(s >= i.first.first) {
            s += i.first.second - i.first.first;
            answer.push_back(i.second);
        } else {
            fout << "-1";
            return 0;
        }
    }

    for(auto &i : left) {
        if(s >= i.first.first) {
            s += i.first.second - i.first.first;
            answer.push_back(i.second);
        } else {
            fout << "-1";
            return 0;
        }
    }

    for(auto &i : answer)
        fout << i + 1 << " ";

    // ---- code ends here -----

    printTimeUse();
    printMemoryUse();

    fin.close();
    fout.close();
    return 0;
}
