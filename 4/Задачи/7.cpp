#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <math.h>
#include "windows.h"
#include "psapi.h"
#include <time.h>
#include <stdlib.h>
#include <chrono>
#include <algorithm>
#include <type_traits>
#include <ext/pb_ds/assoc_container.hpp>

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
#define int int64_t
int64_t binpow(int64_t a, int64_t b, int64_t mod) {
    int64_t res = 1;

    while(b) {
        if(b & 1)
            res = res * a % mod;
        a = a * a % mod;
        b /= 2;
    }

    return res;
}

vector<int> compute_hash(string s, int p, int mod, vector <int> &hash, vector <int> &inv_mod) {
    int n = s.size();
    int p_pow = 1, hash_value = 0;

    for (int i = 0; i < n; i++) {
        int c = s[i] - 'a' + 1;
        hash_value = (hash_value + c * p_pow) % mod;
        hash[i] = hash_value;
        inv_mod[i] = binpow(p_pow, mod - 2, mod);
        p_pow = (p_pow * p) % mod;
    }

    return hash;
}

int get_hash(vector<int>& hash, vector<int>& inv_mod, int l, int r, int mod) {
    if (l == 0) {
        return hash[r];
    }

    int window = (hash[r] - hash[l - 1] + mod) % mod;
    return (window * inv_mod[l]) % mod;
}

const int RANDOM = chrono::high_resolution_clock::now().time_since_epoch().count();
struct chash {
    int operator()(pair <int, int> x) const { return x.first * 31 + x.second; }
};

pair <int, pair <int, int>> longest_common_substr(string X, string Y, int n, int m) {
    int p1 = 31, p2 = 37;
    int m1 = 1e9 + 9, m2 = 1e9 + 7;
    vector <int> inv_for_p1, inv_for_p2, hash1, hash2, hash3, hash4;
    inv_for_p1.assign(max(n, m), 0);
    inv_for_p2.assign(max(n, m), 0);
    hash1.assign(n, 0);
    hash2.assign(n, 0);
    hash3.assign(m, 0);
    hash4.assign(m, 0);
    compute_hash(X, p1, m1, hash1, inv_for_p1);
    compute_hash(X, p2, m2, hash2, inv_for_p2);
    compute_hash(Y, p1, m1, hash3, inv_for_p1);
    compute_hash(Y, p2, m2, hash4, inv_for_p2);

    auto exists = [&](int k) -> pair <int, int> {
        if (k == 0) {
            return {0, 0};
        }
        __gnu_pbds::gp_hash_table <pair<int, int>, int, chash> st;
        for (int i = 0; i < n - k + 1; i++) {
            int h1 = get_hash(hash1, inv_for_p1, i, i + k - 1, m1);
            int h2 = get_hash(hash2, inv_for_p2, i, i + k - 1, m2);
            st[{h1, h2}] = i;
        }
        for (int i = 0; i < m - k + 1; i++) {
            int h1 = get_hash(hash3, inv_for_p1, i, i + k - 1, m1);
            int h2 = get_hash(hash4, inv_for_p2, i, i + k - 1, m2);
            if (st.find({h1, h2}) != st.end()) {
                return {st[{h1, h2}], i};
            }
        }
        return {-1, -1};
    };

    int answer = 0;
    int low = 0, high = min(n, m);

    pair <int, int> curAns;

    while (low <= high) {
        int mid = (low + high) / 2;
        auto ans = exists(mid);
        if (ans.first != -1) {
            answer = mid;
            curAns = ans;
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }

    return {answer, curAns};
}

signed main() {
    getFirstTime();

    // ---- code starts here -----
    string f, s;
    while(fin >> f >> s) {
        auto ans = longest_common_substr(f, s, f.size(), s.size());
        fout << ans.second.first + 1 << ' ' << ans.second.second + 1 << ' ' << ans.first << '\n';
    }
    // ---- code ends here -----

    printTimeUse();
    printMemoryUse();

    fin.close();
    fout.close();
    return 0;
}
