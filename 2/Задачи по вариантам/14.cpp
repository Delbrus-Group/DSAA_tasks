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
class TreeNode {
public:
    int val;
    TreeNode* left;
    TreeNode* right;
    int height;
    int index;
    TreeNode(int val, int i) {
        this->val = val;
        left = NULL;
        right = NULL;
        height = 1;
        index = i;
    }
};

struct Kek {
    int val;
    int left = -1;
    int right = -1;
};

class AVL_Tree {
public:
    TreeNode* insert(TreeNode* root, int key, int index) {
        if (!root) {
            return new TreeNode(key, index);
        }
        else if (key < root->val) {
            root->left = insert(root->left, key, index);
        }
        else {
            root->right = insert(root->right, key, index);
        }
        root->height = 1 + max(getHeight(root->left), getHeight(root->right));
        int balance = getBalance(root);
        if (balance > 1 && key < root->left->val) {
            return rightRotate(root);
        }
        if (balance < -1 && key > root->right->val) {
            return leftRotate(root);
        }
        if (balance > 1 && key > root->left->val) {
            root->left = leftRotate(root->left);
            return rightRotate(root);
        }
        if (balance < -1 && key < root->right->val) {
            root->right = rightRotate(root->right);
            return leftRotate(root);
        }
        return root;
    }

    void prepareTree(TreeNode* currentNode, int index, vector <Kek> &g) {
        if(g[index].left != -1) {
            currentNode->left = new TreeNode(g[g[index].left].val, g[index].left);
            prepareTree(currentNode->left, g[index].left, g);
        }
        if(g[index].right != -1) {
            currentNode->right = new TreeNode(g[g[index].right].val, g[index].right);
            prepareTree(currentNode->right, g[index].right, g);
        }
    }

    int getHeight(TreeNode* root) {
        if (!root) {
            return 0;
        }
        return root->height;
    }

    int getBalance(TreeNode* root) {
        if (!root) {
            return 0;
        }
        return getHeight(root->left) - getHeight(root->right);
    }

    TreeNode* leftRotate(TreeNode* z) {
        TreeNode* y = z->right;
        TreeNode* t = y->left;
        y->left = z;
        z->right = t;
        z->height = 1 + max(getHeight(z->left), getHeight(z->right));
        y->height = 1 + max(getHeight(y->left), getHeight(y->right));
        return y;
    }

    TreeNode* rightRotate(TreeNode* z) {
        TreeNode* y = z->left;
        TreeNode* t = y->right;
        y->right = z;
        z->left = t;
        z->height = 1 + max(getHeight(z->left), getHeight(z->right));
        y->height = 1 + max(getHeight(y->left), getHeight(y->right));
        return y;
    }

    void preOrder(TreeNode* root, int index, vector <Kek> &g) {
        g[index] = {root->val, -1, -1};

        if(root->left) {
            g[index].left = root->left->index;
            preOrder(root->left, root->left->index, g);
        }

        if(root->right) {
            g[index].right = root->right->index;
            preOrder(root->right, root->right->index, g);
        }

    }
};


int main() {
    getFirstTime();

    // ---- code starts here -----

    AVL_Tree myTree;
    TreeNode* root = NULL;
    int rootID = 0;

    int n;
    fin >> n;

    vector <Kek> g (n);
    vector <int> used (n);

    for(int i = 0; i < n; ++ i) {
        int k, l, r;
        fin >> k >> l >> r;

        g[i] = {k, l - 1, r - 1};
        used[l - 1] = 1;
        used[r - 1] = 1;
    }

    for(int i = 0; i < n; ++ i)
        if(!used[i]) {
            rootID = i;
            break;
        }

    root = new TreeNode(g[rootID].val, rootID);
    myTree.prepareTree(root, rootID, g);

    int x;
    fin >> x;

    root = myTree.insert(root, x, n);
    vector <Kek> ans (n + 1);
    myTree.preOrder(root, root->index, ans);

    for(int i = 0; i <= n; ++ i)
        fout << ans[i].val << ' ' << ans[i].left + 1 << ' ' << ans[i].right + 1 << '\n';


    // ---- code ends here -----

    printTimeUse();
    printMemoryUse();

    fin.close();
    fout.close();
    return 0;
}
