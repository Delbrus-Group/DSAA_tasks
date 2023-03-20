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

const int p = 61;
const int m = 1e9 + 9;

int getCode(char c) {
    if(c >= 'a' && c <= 'z')
        return c - 'a';
    return c - 'A' + 26;
}

vector<int> rabin_karp(const string& pattern, const string& text) {
    int n = text.size(), cntM = pattern.size();
    vector<long long> p_pow(n);
    p_pow[0] = 1;
    for (int i = 1; i < n; i++) {
        p_pow[i] = (p_pow[i-1] * p) % m;
    }

    vector<long long> h(n+1, 0);
    for (int i = 0; i < n; i++) {
        h[i+1] = (h[i] + (getCode(text[i]) + 1) * p_pow[i]) % m;
    }

    long long h_pattern = 0;
    for (int i = 0; i < cntM; i++) {
        h_pattern = (h_pattern + (getCode(pattern[i]) + 1) * p_pow[i]) % m;
    }

    vector<int> occurences;
    for (int i = 0; i <= n - cntM; i++) {
        long long cur_h = (h[i+cntM] + m - h[i]) % m;
        if (cur_h == h_pattern * p_pow[i] % m) {
            occurences.push_back(i+1);
        }
    }
    return occurences;
}

//------------------------------------

int main() {
    getFirstTime();

    // ---- code starts here -----
    string pattern, text;
    fin >> pattern >> text;

    vector<int> occurences = rabin_karp(pattern, text);

    int count = occurences.size();
    fout << count << endl;
    for (int i = 0; i < count; i++) {
        fout << occurences[i] << " ";
    }
    // ---- code ends here -----

    printTimeUse();
    printMemoryUse();

    fin.close();
    fout.close();
    return 0;
}
