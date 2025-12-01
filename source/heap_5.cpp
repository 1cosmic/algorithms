#include <iostream>
#include <list>
#include <queue>
#include <random>
#include <ranges>
#include <algorithm>

using namespace std;


template<typename T>
void print_array(vector<T> array) {
    cout << "[ ";
    for (auto n : array)
        cout << n << ' ';
    cout << ']' << endl;
}


auto is_bunch(vector<int> arr, bool is_full=false) {

    int i, root, l, r;
    int v_root, v_l, v_r;
    for (i = 0; i < arr.size() / 2; i++) {
        root = i;
        l = 2*i + 1;
        r = 2*i + 2;

        if (!is_full) {
            if (arr[root] < arr[l] or arr[root] < arr[r]) return false;
        }

        else {
            v_root = arr[root];
            v_l = arr[l];
            v_r = arr[r];
            
            if ((v_l < 0 and v_r < 0) or (v_l > 0 and v_r > 0)) continue;
            else return false;
        }
    }
    return true;
}


vector <int> mergeKvector(vector<vector<int>> vectors, bool verbose=false) {
    vector<int> res;
    priority_queue<int, vector<int>, greater<int>> minHeap;
    
    for (auto vec: vectors) {
        for (auto elem: vec) {
            minHeap.push(elem);
        }
    }

    while (!minHeap.empty()) {
        res.push_back(minHeap.top());
        if (verbose) cout << "got root-element: " << minHeap.top() << endl;
        minHeap.pop();
    }
    return res;
}


class TreeNode {
    public:
        int v; TreeNode *l, *r;
        int balance_factor = NULL;

        TreeNode (int val = -1, TreeNode *left = nullptr, TreeNode *right = nullptr) {
            v = val;
            l = left; r = right;
        };

        bool search_BFS() {
            vector<int> res = {};
            queue<TreeNode *> breadth;

            int level = 1;
            int i = level;
            breadth.push(this);

            cout << "tree by levels: \n0: ";
            while (!breadth.empty()) {
                i--;

                TreeNode *root = breadth.front();
                if (root) {
                    TreeNode *l = root->l; if (l) breadth.push(l);
                    TreeNode *r = root->r; if (r) breadth.push(r);
                    cout << root->v  << ", ";
                    res.push_back(root->v);
                }
                breadth.pop();

                if (i <= 0 and !breadth.empty()) {
                    cout << "\n";
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
    if (arr[i] == -1) return nullptr;

    TreeNode* root = new TreeNode(arr[i]);
    root->v = arr[i];
    root->l = build(arr, 2*i + 1);
    root->r = build(arr, 2*i + 2);

    return root;
};


int K_extremum(TreeNode *root, int k, bool verbose=false) {
    static int counter = 0;
    static bool output = verbose;

    if (!root) return 0;

    auto left = K_extremum(root->l, k);
    if (left > 0) return left;          // extrude finded k-value.

    if (output) cout << "root: " << root->v << " count: " << counter << endl;

    // if not:
    counter++;    
    if (counter == k) return root->v;
    
    return K_extremum(root->r, k);
}


int compute_balance(TreeNode* root, bool verbose=false) {
    static bool output = verbose;


    if (!root) return NULL;
    
    auto l = compute_balance(root->l);
    auto r = compute_balance(root->r);
    auto h = max(l, r);

    root->balance_factor = h;
    if (output) cout << "root: " << root->v << " balance_f: " << h << endl;
    return 1 + h;
}


TreeNode* recurce_mirror_tree(TreeNode* root) {
    if (!root) return nullptr;
    
    swap(root->l, root->r);
    recurce_mirror_tree(root->r);
    recurce_mirror_tree(root->l);
}


int main() {
    bool verbose = false;

    vector<int> true_bunch, bad_bunch, full_binary_tree;
    vector<vector <int>> k_vectors;
    int r, k;

    true_bunch = {21, 19, 18, 11, 12, 15, 16, 9, 8, 10, -1};
    bad_bunch = {21, 19, 18, 11, 12, 15, 16, 12, 8, 10, -1};

    cout << "1) Check of array, what's true bunch: " << endl;
    cout << "true bunch: "; print_array(true_bunch);
    cout << "-> is true?: " << is_bunch(true_bunch) << endl << endl;
    cout << "bad bunch:  "; print_array(bad_bunch);
    cout << "-> is true?: " << is_bunch(bad_bunch) << endl << endl;


    full_binary_tree = {21, 15, 25, 9, 16, 22, 26,     7, 10, -1, 17, -1, -1, -1, -1};

    cout << endl;
    cout << "2) Check of tree, what's full binary tree: " << endl;
    cout << "full binary tree: "; print_array(full_binary_tree); 
    cout << "-> is true?: " << is_bunch(full_binary_tree, true) << endl << endl;
    cout << "not full binary tree: "; print_array(true_bunch); 
    cout << "-> is true?: " << is_bunch(true_bunch, true) << endl;

    cout << endl;
    cout << "3) Merge K-arrays:" << endl;
    k_vectors.push_back({1, 5, 7, 9, 10});
    k_vectors.push_back({2, 3, 3, 4, 6, 7, 9, 11});
    k_vectors.push_back({4, 6, 8, 13, 14, 15, 20, 30});
    print_array(mergeKvector(k_vectors, verbose)); cout << endl << endl;
    
    cout << endl;
    cout << "4) Get K min element:" << endl;
    TreeNode* tree = build(full_binary_tree);
    tree->search_BFS();
    k = 4;
    cout << endl;
    r = K_extremum(tree, k, verbose); 
    cout << "k: " << k << " res: " << r << endl << endl;

    cout << endl;
    cout << "4) compute balance_factor for previous tree:" << endl;
    compute_balance(tree, true); cout << endl << endl;

    cout << endl;
    cout << "5) Mirror previous tree:" << endl;
    recurce_mirror_tree(tree);
    tree->search_BFS();

    
    cout << endl << endl;
    return 0;
}