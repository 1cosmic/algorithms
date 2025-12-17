#include <iostream>
#include <list>
#include <queue>
#include <random>
#include <ranges>
#include <algorithm>
#include <vector>
#include <map>
using namespace std;

vector<int> component, used;

template<typename T>
void print_array(vector<T> array) {
    cout << "[ ";
    for (auto n : array)
        cout << n << ' ';
    cout << ']' << endl;
}


int max_sum_k(auto arr, int k) {
    if (arr.size() < 1) return 0;

    int cur_sum = 0;
    int max_sum;

    for (auto i = 0; i < k; i++) {
        cur_sum += arr[i];
    }
    max_sum = cur_sum;

    int d = 0;
    for (auto i = k; i < arr.size(); i++) {
        d = arr[i] - arr[i - k];
        cur_sum = cur_sum + d; 
        max_sum = max(cur_sum, max_sum);
    }

    return max_sum;
}


auto max_count_sums(auto arr, int k) {

    map<int, int> mapped_sums = {{0, 1}};
    auto count = 0;
    auto prefix_sum = 0;
    auto d = 0;

    for (auto v: arr) {
        prefix_sum += v;
        d = prefix_sum - k;
        
        if (mapped_sums.contains(d)) count += mapped_sums[d];
        mapped_sums[prefix_sum] = (mapped_sums[prefix_sum] || 0) +1;
    }

    return count;
}


int max_balance_length(auto arr) {

    map<int, int> indexMap = {{0, -1}};
    int prefSum = 0;
    int maxLen = 0;
    int n;
    
    for(int i = 0; i < arr.size(); i++) {

        n = arr[i];
        if (n) prefSum += 1; else prefSum += -1;
        if (indexMap.contains(prefSum)) {
            maxLen = max(maxLen, i - indexMap[prefSum]);
        }
        else {
            indexMap[prefSum] = i;
        }
    }

    return maxLen;
}


int pivotIndex(auto arr) {
    int totalSum = 0;
    int leftSum = 0;

    for (auto i = 0; i < arr.size(); i++) {
        totalSum += arr[i];
    }

    for (auto i = 0; i < arr.size(); i++) {
        if (leftSum == totalSum - leftSum - arr[i]) {
            return i;
        }
        leftSum += arr[i];
    }
    return -1;
}

int balanced_brackets(auto str, int k) {
    int balance = 0;
    int extra_closed_balance = 0;

    for (auto i = 0; i < str.size(); i++) {
        if (str[i] == '(') {
            balance += 1;
        }
        else {
            if (balance > 0) {
                balance -= 1;
            } else {
                extra_closed_balance += 1;
            }
        }
    }

    int total_needed = balance + extra_closed_balance;

    return total_needed <= k;
}


int main() {
    cout << "Homeworks of prefix sums." << endl;
    cout << "Created by Michael Kolobakhin" << endl << endl;

    vector<int> arr = {1, 2, 4, 5, 9, 1};
    vector<int> arr2 = {1,2,4,5,9,1,3,5,6,3,1,2,5,2,8,9,6,1,8,5,2,1,8};
    vector<int> arr3 = {0, 1, 1, 1, 1, 0, 1, 0, 0, 1, 1, 0, 0, 0, 1, 1, 1};
    vector<int> arr4 = {9, 4, 8, 7, 1, 11, 2, 6, 1};
    string str = "()((";
    
    cout << "1) Max sum of arr, where k=3:"; print_array(arr);
    cout << "res: " << max_sum_k(arr, 3) << endl << endl;

    cout << "2) Max count of prefix sums = 4:"; print_array(arr2);
    cout << "res: " << max_count_sums(arr2, 4) << endl << endl;

    cout << "3) Max length of balanced sequence:"; print_array(arr3);
    cout << "res: " << max_balance_length(arr3) << endl << endl;

    cout << "4) Index of rotation the sequence:"; print_array(arr4);
    cout << "res: " << pivotIndex(arr4) << endl << endl;

    cout << "5) Balance brackets of sequence: '()((' with k=3: " << endl;
    cout << "res: " << balanced_brackets(str, 3) << endl << endl;

    return 0;
}