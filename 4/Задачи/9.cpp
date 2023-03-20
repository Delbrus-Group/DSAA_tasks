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
vector<int> prefixFunction(string s, int offset) {
    int n = s.length();
    vector<int> p(n - offset, 0);

    for (int i = 1, j = 0; offset + i < n; ++i) {
        while (j > 0 && s[offset + i] != s[offset + j])
            j = p[j - 1];
        if (s[offset + i] == s[offset + j]) {
            ++j;
            p[i] = j;
        }
    }

    return p;
}

pair<int, int> findRepeatingPrefix(string s, int offset) {
    vector<int> p = prefixFunction(s, offset);
    int n = s.length() - offset;
    int max = p[0], maxIdx = 0;

    for (int i = 1; i < n; ++i) {
        if (p[i] > max && (i + 1) % (i + 1 - p[i]) == 0) {
            max = p[i];
            maxIdx = i;
        }
    }

    if (max > 0) {
        int l = maxIdx + 1 - max;
        return make_pair(l, (maxIdx + 1) / l);
    } else {
        return make_pair(1, 1);
    }
}

int cntDigitsInNumber(int num) {
    return (1 + log10(num));
}

string decomposeString(const string &s) {
    const int n = s.length();

    vector<int> minimum_join(n + 1), minimum_prefix(n + 1, 10000);
    vector<pair<int, int>> p(n);

    for (int i = n - 1; i >= 0; --i) {
        minimum_join[i] = 1 + min(minimum_join[i + 1], 1 + minimum_prefix[i + 1]);

        auto [l, k] = findRepeatingPrefix(s, i);
        p[i] = {l, k};

        const int minSuffixLen = min(minimum_join[i + l * k], minimum_prefix[i + l * k]);
        minimum_prefix[i] = l + 1 + cntDigitsInNumber(k) + (minSuffixLen > 0 ? 1 : 0) + minSuffixLen;
    }

    vector<string> answer;

    int i = 0;
    bool needPlus = false;
    while (i < n) {
        if (minimum_join[i] <= minimum_prefix[i]) {
            if (needPlus) {
                answer.push_back("+");
            }
            answer.push_back(s.substr(i, 1));
            i += 1;
            needPlus = false;
        } else {
            const auto [l, k] = p[i];
            if (i > 0) {
                answer.push_back("+");
            }
            answer.push_back(s.substr(i, l) + "*" + to_string(k));
            i += l * k;
            needPlus = true;
        }
    }

    return accumulate(answer.begin(), answer.end(), string(""));
}

int main() {
    getFirstTime();

    // ---- code starts here -----
    string s;
    fin >> s;

    fout << decomposeString(s);

    // ---- code ends here -----

    printTimeUse();
    printMemoryUse();

    fin.close();
    fout.close();
    return 0;
}
