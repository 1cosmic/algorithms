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

            // cout << v_root << ' ' << v_l << ' ' << v_r << endl;
            
            if ((v_l < 0 and v_r < 0) or (v_l > 0 and v_r > 0)) continue;
            else return false;
        }
    }
    return true;
}



int main() {

    vector<int> true_bunch, bad_bunch, full_binary_tree;

    true_bunch = {21, 19, 18, 11, 12, 15, 16, 9, 8, 10, -1};
    bad_bunch = {21, 19, 18, 11, 12, 15, 16, 12, 8, 10, -1};

    cout << "1) Check of array, what's true bunch: " << endl;
    cout << "true bunch: "; print_array(true_bunch);
    cout << "-> is true?: " << is_bunch(true_bunch) << endl << endl;
    cout << "bad bunch:  "; print_array(bad_bunch);
    cout << "-> is true?: " << is_bunch(bad_bunch) << endl << endl;


    full_binary_tree = {21, 19, 18, 11, 12, 15, 16, 9, 8,   -1, -1, 10, 11, -1, -1};

    cout << endl;
    cout << "2) Check of tree, what's full binary tree: " << endl;
    cout << "full binary tree: "; print_array(full_binary_tree); 
    cout << "-> is true?: " << is_bunch(full_binary_tree, true) << endl << endl;
    cout << "not full binary tree: "; print_array(true_bunch); 
    cout << "-> is true?: " << is_bunch(true_bunch, true) << endl;


    cout << endl << endl;
    return 0;
}