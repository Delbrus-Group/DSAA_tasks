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
    string s, f;
    fin >> s >> f;

    vector<int> cnt1(26), cnt2(26);
    for (char i: s) {
        cnt1[i - 'a']++;
    }

    for (char i: f) {
        cnt2[i - 'a']++;
    }

    string ans;
    pair<int, int> curPos = {0, 0};
    for (int i = 25; i >= 0; --i) {
        while (cnt1[i] && cnt2[i] && curPos.first < s.size() && curPos.second < f.size()) {
            while (s[curPos.first] != ('a' + i)) {
                cnt1[s[curPos.first] - 'a'] --;
                curPos.first++;
            }

            while (f[curPos.second] != ('a' + i)) {
                cnt2[f[curPos.second] - 'a'] --;
                curPos.second++;
            }

            ans += ('a' + i);
            cnt1[i]--;
            cnt2[i]--;
            curPos.first ++;
            curPos.second ++;
        }
    }

    fout << ans;

    // ---- code ends here -----

    printTimeUse();
    printMemoryUse();

    fin.close();
    fout.close();
    return 0;
}
