#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <ranges>
#include <algorithm>
#include <map>
#include <typeinfo>

// System funcs.
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

// template<typename T>
// void print_2d_vector(vector<vector<T>> vec);

template<typename T>
void print_2d_vector(vector<vector<T>> vec) {
    cout << "\n[\n";
    for (auto inner: vec) {
        cout << "  [";
        for (size_t i = 0; i < inner.size(); ++i) {
            cout << inner[i] << ' ';
        }
        cout << "\b]\n";
    }
    cout << "]\n";
}
//


int binary_sqrt(int target) {
    auto l = 0; auto r = target;

    while (l <= r) {
        // int m = r - (r + l) / 2;
        int m = (r + l) / 2;
        // cout << m << endl;
        if (m * m < target) l = m + 1;
        else if (m * m > target) r = m - 1;
        else return m;
    }
    return r;
}


int binary_print(int n, int x, int y) {
    int l, r, t;
    l = 0; r = (n - 1) * max(x,y);

    while (l+1 < r) {
        t = (r + l) / 2;
        if (t/x + t/y < n - 1) l = t;
        else r = t;
    }
    return r + min(x, y);
}

char hash_diff_strings(string a, string b) {
    map<char, int> hash_A;
    
    for (char c: a) {
        if (! hash_A.contains(c)) hash_A[c] = 0;
        hash_A[c]++;
    }

    for (char c: b) {
        if (! hash_A.contains(c)) return c;     // break if inoagent.
        hash_A[c]--;
        if (hash_A[c] < 0) return c;            // break if count of char > exist.
    }
    
    return ' ';
}

int how_many_animals_can_be_eat(vector<int> animals, vector<int> foods) {
    sort(animals.begin(), animals.end());
    sort(foods.begin(), foods.end());
    
    int a = 0, f = 0;
    int need, have, eated;
    while(a != animals.size() and f != foods.size()) {
        need = animals[a];
        have = foods[f];
        
        if (need <= have) {
            eated++; a++; f++;
        }
        else {
            f++;
        }
    }
    return eated;
}


vector<int> sum2element(vector<int> data, int target) {
    map<int, int> cash_data;

    int diff, i = 0;
    for (int v: data) cash_data[v] = i++;

    i = 0;
    for (int v: data) {
        diff = target - v;
        if (cash_data.contains(diff))
            return {i, cash_data[diff]};
        i++;
    }
    return {};
}


auto polynomical_hash(string str, bool collision = false) {
    long long hash = 0, mod = 1e9+7;
    int x, k, m = 1;

    if (collision) k = 1;
    else k = 32;

    for (char c: str) {
        x = (int) c - 'a' + 1;
        hash = (hash + x*m) % mod;
        m = m*k % mod;
    }
    // cout << "Hash for '" << str << "' is: " << hash << endl;
    return hash;
}


vector<vector<string>> group_how_anagrams(vector<string> data) {

    long long hash;
    bool with_collision = true;
    map<long long, vector<string>> hash_anagrams;
    
    for (string anagram: data) {
        hash = polynomical_hash(anagram, with_collision);
        hash_anagrams[hash].push_back(anagram);
    }

    vector<vector<string>> res = {};
    vector<string> grouped;
    for (auto iter = hash_anagrams.begin(); iter != hash_anagrams.end(); iter++) {
        grouped = iter->second;
        res.push_back(grouped);
    }
    return res;
}


vector<int> sort_shell(vector<int> arr) {
    int n = arr.size(), gap = (int) n / 2;
    int cur_pos, cur_gap;

    while (gap > 0) {
        for (cur_pos = gap; cur_pos < n; cur_pos++) {
            cur_gap = cur_pos;
            while (cur_gap >= gap and arr[cur_gap - gap] > arr[cur_gap]) {
                swap(arr[cur_gap - gap], arr[cur_gap]);
                cur_gap -= gap;
            }
        }
        gap = (int) gap / 2;
    }
    return arr;
}


int main() {
    int sqrt_x;

    cout << "Homework #3: binary searches, sortings." << endl;
    cout << "1) Binary search of f(x) = sqrt(x)" << endl;
    sqrt_x = 4;
    cout << "Sqrt of '" << sqrt_x << "' is: " << binary_sqrt(sqrt_x) << endl;
    sqrt_x = 300;
    cout << "Sqrt of '" << sqrt_x << "' is: " << binary_sqrt(sqrt_x);
    cout << endl << endl;

    int n, x_s, y_s;
    n = 5, x_s = 2, y_s = 3;
    cout << "2) For print '"  << n << "' on x_speed '" << x_s << "' & y_speed '" << y_s;
    cout << "', your need: " << binary_print(n, x_s, y_s) << "s";
    cout << endl << endl;

    string a = "abcdef", b = "xfedcba";
    cout << "3) First char in '" << b << "' what's not in '" << a << "': ";
    cout << hash_diff_strings(a, b) << endl;
    a = "abcdef", b = "bfedcba";
    cout << "3) First char in '" << b << "' what's not in '" << a << "': ";
    cout << hash_diff_strings(a, b);
    cout << endl << endl;

    vector<int> animals, foods;
    animals = {4, 3, 6, 1, 8, 6, 5, 8, 5};
    foods =   {1, 1, 1, 1, 8};
    cout << "4) Have animals: '" << animals.size() << "': "; print_array(animals);
    cout << "4) Have foods:   '" << foods.size() << "': "; print_array(foods);
    cout << "How many animals can be eat: ";
    cout << how_many_animals_can_be_eat(animals, foods);
    cout << endl << endl;

    vector<int> range, res;
    int target = 25;
    range = {7, 4, 3, 6, 1, 2, 9, 8, 5, 16};
    res = sum2element(range, target);
    cout << "5) Indices of 2 elements, what give: " << target << endl;
    cout << "from range: "; print_array(range);
    cout << "is: "; print_array(res); cout << endl;

    vector<string> anagrams = {"eat", "tan", "nat", "tea", "bat", "ate"};
    vector<vector<string>> grouped_anagrams;
    grouped_anagrams = group_how_anagrams(anagrams);
    cout << "6) Grouping anagrams: "; print_array(anagrams);
    cout << "is: "; print_2d_vector(grouped_anagrams); cout << endl;

    cout << "7) Sort by Shell of array: "; print_array(range);
    cout << "Res: "; print_array(sort_shell(range));

    return 0;
}