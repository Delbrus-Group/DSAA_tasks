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
    string s;
    getline(fin, s);

    vector <int> cnt (26), curcnt(26);
    for(char c : s)
        if(c >= 'a' && c <= 'z')
            cnt[c - 'a'] ++;

    int64_t ans = 0;

    for(int i = 0; i < s.size(); ++ i) {
        if(s[i] >= 'a' && s[i] <= 'z') {
            cnt[s[i] - 'a']--;
            for (int j = 0; j < 26; ++j)
                ans += curcnt[j] * cnt[j];
            curcnt[s[i] - 'a']++;
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
