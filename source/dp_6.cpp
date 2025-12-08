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


int count_N_01_without_K(int N, int K) {
    if (N < K) return pow(2, N);

    int i, ki, res;
    vector<int> dp;

    // fill start bounds, like full success combines on current level: 2^i
    for (ki = 0; ki < K; ki++) {
        dp.push_back(pow(2, ki));
    };     

    for (i = K; i <= N; i++) {
        res = 0;
        for (ki = 1; ki <= K; ki++) {
            res += dp[i - ki];
        }
        dp.push_back(res);
    }
    res = dp.back();
    print_array(dp);
    return res;
}


int max_true_sequence(vector<int> arr) {
    if (arr.size() <= 1) return 1;

    vector<int> max_contracts = {1};
    int r = 1;
    int last_r;
    int max_true = -1;

    for (auto i = 1; i < arr.size(); i++) {
        r = 1;
        
        last_r = max_contracts[i - 1];
        if (arr[i] >= arr[i - 1]) r += last_r;
        max_contracts.push_back(r);

        // Analogue of max(vector)
        if (max_true < max_contracts[i]) max_true = max_contracts[i];
    }
    return max_true;
}


void create_Pascal_triangle(int level) { 
    vector<vector<int>> Pascal_triangle;

    // Generate of memory for Pascal.
    int str, col, i, l, r;
    for (str = 1; str <= level; str++) {
        vector<int> string = {};
        for (i = 0; i < str; i++) {
            string.push_back(1);
        }
        Pascal_triangle.push_back(string);
        // cout << "l " << str << ": ";
        // print_array(string);
    }
    

    for (str = 0; str < level; str++) {     // start from 3rd because i can)
        auto size_str = Pascal_triangle[str].size();

        if (str >= 2) {
            for (col = 0; col < size_str; col++) {

                l = 0; r = 0;
                if (col -1 >= 0) l = Pascal_triangle[str -1][col -1];
                if (col + 1 < size_str) r = Pascal_triangle[str -1][col];

                Pascal_triangle[str][col] = l + r;
            }
        }
        print_array(Pascal_triangle[str]);
    }
}


int max_profit(vector<int> sequence) {

    int min_price = sequence[0];
    int max_price = 0;
    
    for (int i = 1; i < sequence.size(); i++) {
        min_price = min(min_price, sequence[i]);
        max_price = max(max_price, sequence[i] - max_price);
        // cout << "min: " << min_price << " max: " << max_price << endl;
    }
    return max_price;
}


int min_sum_comb(vector<int> coins, int sum) {

    vector<int> comb = {0};
    // vector<int> comb;

    int i;

    for (i = 0; i < sum; i++) comb.push_back(UINT16_MAX);

    for (auto c: coins) {       // work by columns

        i = 1;
        while (i <= sum) {    // work by strings
            if (i - c >= 0) {
                comb[i] = min(comb[i], comb[i - c] + 1);
        }
        i++;
    }
    cout << "Min of sum '" << i << "' on coins '" << c << "' is: '" << comb.back() << "'" << endl;

}
    return comb.back();
}


int main() {

    int N = 3;
    int K = 3;
    cout << "1) 0-1-0-...N sequences without 1-1-...K contract: " << endl;
    cout << "N: " <<  N << " K: " << K << endl;
    cout << "res: " << count_N_01_without_K(N, K) << endl << endl;


    vector<int> arr = {2, 2, 1, 3, 4, 2, 5};
    cout << "2) Len of max true sequence: "; print_array(arr);
    // cout << "arr: {2, 2, 1, 3, 4, 2, 5}" << endl;
    cout << "res: " << max_true_sequence(arr) << endl << endl;

    cout << "3) Create triange of Pascal (method of iterations): " << endl;
    create_Pascal_triangle(11);

    cout << endl << endl << "4) Search of max profit from sequence: "; print_array(arr);
    auto r = max_profit(arr);
    cout << "res: " << r << endl << endl;

    auto sum = 22;
    vector<int> coins = {1, 3, 5, 7};
    cout << endl << "5) Find min combs of coins {1, 3, 5, 7} for get sum '" << sum << "': " << endl;
    r = min_sum_comb(coins, sum);
    cout << "res: " << r << endl << endl;

    return 0;
}