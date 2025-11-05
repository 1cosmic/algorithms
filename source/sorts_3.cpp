#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <ranges>
#include <algorithm>
#include <map>

using namespace std;

// System funcs.
void print_array(vector<int> array) {
  for (int n : array)
    cout << n << ' ';
  cout << endl;
}
// Forward declaration.
void print_array(vector<int> array);


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


    return 0;
}