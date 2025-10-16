#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <ranges>
#include <algorithm>

using namespace std;

// Forward declaration
void print_array(vector<int> array);

// System funcs.

void print_array(vector<int> array) {
  for (int n : array)
    cout << n << ' ';
  cout << endl;
}

auto generate_array(int count, int variation) {
  vector<int> array;

    for (int i = 0; i < count; i++) {
      auto random_value = rand() % variation;
      array.push_back(random_value);
    }
  return array;
}

// ==============================


auto two_sum(vector<int> array, int target) {

  int l = 0;
  int r = array.size() -1;

  int res;
  cout << "Searching indexes of array, what's sum give: " << target << endl;
  while (l < r) {
    res = array[l] + array[r];
    if (target < res)
      r--;
    else if (target > res)
      l++;
    else {
      cout << "finded values: " << l << " & " << r << endl;
      l++;
    }
  }
  cout << "Finished." << endl << endl;

  return 0;
}


auto reverse_array(vector<int> array, int l, int r) {

  cout << "Starting reversing array..." << endl; print_array(array); 
  while(l < r) {
    swap(array[l], array[r]);
    l++; r--;
  }
  cout << "Result: " << endl;
  print_array(array);
  cout << endl;

  return array;
}


auto merge2array(vector<int> arr1, vector<int> arr2) {

  int i = 0;
  int i2 = 0;
  int s1 = arr1.size() -1;
  int s2 = arr2.size() -1;
  int v;

  cout << "Merge 2 arrays: " << endl;
  print_array(arr1);
  print_array(arr2);

  // Не работает, следует идти с конца?

//   while (i < s1 or i2 < s2) {
//     if (arr1[i] < arr2[i2]) {
//       swap(arr1[i], arr2[i2]);
//       i2++;
//     }
//     (i < s1) i++;
// }
  cout << "Result: " << endl;
  print_array(arr1); print_array(arr2);
  cout << endl;
}


auto binary_sort(vector<int> arr) {
  int l = 0; int r = arr.size() -1;
  int buf;

  cout << "Starting binary sort of array..." << endl;
  print_array(arr);

  while (l < r) {
    if (arr[l] > arr[r] or arr[l] == 1) {
      swap(arr[l], arr[r]);
      r--;
    }
    else {
      l++;
    }
  }
  cout << "Result:" << endl;
  print_array(arr);
  cout << endl;
}


auto thirdy_sort(vector<int> arr) {
  /* l, r - extremums, m - cursor */
  int l, m, r;
  l = m = 0;
  r = arr.size() -1;

  cout << "Starting thirdy sort of array..." << endl; print_array(arr);
  while(m <= r) {
    if (arr[m] == 0) {
      swap(arr[l], arr[m]);
      l++;
    }
    else if (arr[m] == 2) {
      swap(arr[m], arr[r]);
      r--;
    }
    else if (arr[m] == 1)
      m++;
  }
  cout << "Result:" << endl;
  print_array(arr);
  cout << endl;
}


auto first_even(vector<int> arr) {
  
  int l = 0;
  int r = 0;

  cout << "Starting swap all even to first..." << endl;
  while (r < arr.size()) {
    if (arr[r] % 2 == 0) {
      swap(arr[l], arr[r]); l++;
    }
    else r++;
    // print_array(arr);
  }
  cout << "Result: " << endl;
  print_array(arr);
  cout << endl;
}


auto last_zero(vector<int> arr) {
  
  int l = 0;
  int r = 0;

  cout << "Starting swap all zero to last..." << endl;
  print_array(arr);
  while (r < arr.size() and l < arr.size()) {
    if (arr[r] == 0) {
      swap(arr[l], arr[r]); l++;
    }
    else r++;
  }
  cout << "Result: " << endl;
  print_array(arr);
  cout << endl;
}


auto main() -> int
{

  vector<int> array = {6, 8, 9, 11, 16, 18, 19, 21};
  int target = 25;
  two_sum(array, target);   // #1

  // # 2 & 3
  array = {1, 2, 3, 4, 5, 6, 7};
  auto k = 3;
  auto end = array.size() -1;
  array = reverse_array(array, 0, end);
  array = reverse_array(array, 0, k -1);
  array = reverse_array(array, k, end);

  // # 4
  // auto arr1 = {3, 8, 10, 11, 0, 0, 0};
  // auto arr2 = {1, 7, 9};
  // merge2array(arr1, arr2);

  // # 5
  auto arr = {0, 1, 1, 0, 1, 0, 1, 0};
  binary_sort(arr);

  // # 6
  // arr = {2, 0, 2, 1, 1, 0};
  auto arr3 = generate_array(10, 3);
  thirdy_sort(arr3);

  // # 7
  arr = {7, 3, 2, 4, 1, 11, 8, 9};
  first_even(arr);

  // # 8
  arr = {0, 33, 57, 88, 0, 0, 1};
  last_zero(arr);
}