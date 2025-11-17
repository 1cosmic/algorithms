#include <iostream>
#include <list>
#include <queue>
#include <random>
#include <ranges>
#include <algorithm>

using namespace std;


template<typename T>
void print_array(vector<T> array);  // forward declaration.

template<typename T>
void print_array(vector<T> array) {
    cout << "[";
    for (auto n : array)
        cout << n << ' ';
    cout << "\b]" << endl;
}


class TreeNode {
    public:
        int v; TreeNode *l, *r;

        TreeNode (int val = -1, TreeNode *left = nullptr, TreeNode *right = nullptr) {
            v = val;
            l = left; r = right;
        };

        void print_BFS() {
            queue<TreeNode *> breadth;
            breadth.push(this);

            int level = 1;
            int i = level;

            cout << "tree by levels: \n0: ";
            while (!breadth.empty()) {
                i--;

                TreeNode *root = breadth.front();
                if (root) {
                    TreeNode *l = root->l; if (l) breadth.push(l);
                    TreeNode *r = root->r; if (r) breadth.push(r);
                    cout << root->v  << ", ";
                }
                breadth.pop();

                if (i <= 0 and !breadth.empty()) {
                    cout << "\b\b \n";
                    cout << level << ": ";
                    i = pow(2, level);
                    level += 1;
                };
            }
            cout << endl;
        };
};


TreeNode* build(vector<int> arr, int i = 0) {
    if (i > arr.size() -1) return nullptr;

    TreeNode* root = new TreeNode(arr[i]);
    root->v = arr[i];
    root->l = build(arr, 2*i + 1);
    root->r = build(arr, 2*i + 2);

    return root;
};



int main() {
    cout << "HOMEWORK #4: binary trees and its algorithms." << endl << endl;
    vector<int> data2tree = {8, 9, 11, 7, 16, 3, 1};

    cout << endl << "1) Revert binary tree u array." << endl;
    cout << "arr: "; print_array(data2tree); cout << endl;
    TreeNode *tree1 = build(data2tree, 0);
    tree1->print_BFS(); cout << endl;

    cout << endl << "2) ..." << endl;


    cout << endl << endl;
    cout << "Homeworks was made by Michael Kolobakhin." << endl;
    return 0;
}