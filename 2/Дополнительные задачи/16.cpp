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
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;

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

vector <int> fenwick;
void add(int i, int val) {
    for(int j = i; j < fenwick.size(); j += j & -j)
        fenwick[j] += val;
}

int getsum(int i) {
    int sum = 0;
    for(int j = i; j > 0; j -= j & -j)
        sum += fenwick[j];
    return sum;
}

int main() {
    getFirstTime();

    // ---- code starts here -----

    int n;
    fin >> n;

    vector <pair <int, int> > requests (n);
    for(auto &i : requests)
        fin >> i.first >> i.second;

    set <int> allElements;
    for(auto &i : requests)
        allElements.insert(i.second);

    gp_hash_table <int, int> number;
    int j = 1;
    for(int i : allElements)
        number[i] = j ++;

    vector <int> elementByNumber (1e5 + 1);
    fenwick.assign(1e5 + 1, 0);
    for(int i : allElements) {
        elementByNumber[number[i]] = i;
    }

    int cnt = 0;

    for(auto& [type, value] : requests) {
        if(type == -1) {
            add(number[value], -1);
            -- cnt;
        } else if(type == 0) {
            int l = 1, r = 1e5 + 1;
            while(l < r) { // 1 0 1 1 0 0
                int m = (l + r + 1) >> 1;
                if(getsum(m - 1) > cnt - value) {
                    r = m - 1;
                } else l = m;
            }

            fout << elementByNumber[l] << '\n';


        } else {
            add(number[value], 1);
            ++ cnt;
        }
    }

    // ---- code ends here -----

    printTimeUse();
    printMemoryUse();

    fin.close();
    fout.close();
    return 0;
}
