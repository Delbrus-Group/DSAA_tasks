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
struct node {
    int key;
    node *left, *right;
    node(int x) {
        key = x;
        left = right = NULL;
    }
};

node* insert(node* root, int key) {
    if (!root) {
        return new node(key);
    }
    if (key < root->key) {
        root->left = insert(root->left, key);
    } else if (key > root->key) {
        root->right = insert(root->right, key);
    }
    return root;
}

int get_min_greater(node* root, int x) {
    int min_greater = 0;
    while (root) {
        if (root->key > x) {
            min_greater = root->key;
            root = root->left;
        } else {
            root = root->right;
        }
    }
    return min_greater;
}


int main() {
    getFirstTime();

    // ---- code starts here -----

    node* root = NULL;
    string query;
    while (fin >> query) {
        int x;
        fin >> x;
        if (query == "+") {
            root = insert(root, x);
        } else if (query == ">") {
            fout << get_min_greater(root, x) << endl;
        }
    }

    // ---- code ends here -----

    printTimeUse();
    printMemoryUse();

    fin.close();
    fout.close();
    return 0;
}
