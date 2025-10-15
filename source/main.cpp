#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <ranges>
#include <algorithm>

using namespace std;

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


auto reverse_array(vector<int> array) {
  int buf;
  vector<int> res = array;
  int l = 0; int r = res.size() -1;

  cout << "Starting reversing array..." << endl; print_array(array); 
  while(l < r) {
    buf = res[r];
    res[r] = array[l];
    res[l] = buf;

    l++; r--;
  }
  cout << "Result: " << endl;
  print_array(res);
  cout << endl;

  return res;
}


auto merge2array(vector<int> arr1, vector<int> arr2) {
  vector<int> res;

  int i = 0;
  int i2 = 0;
  int s1 = arr1.size() -1;
  int s2 = arr2.size() -1;
  int v;

  cout << "Merge 2 arrays: " << endl;
  print_array(arr1);
  print_array(arr2);

  while (i < s1 or i2 < s2) {
    if (arr1[i] < arr2[i2] or i2 >= s2) {
      v = arr1[i];
      if (i < s1) i++;

    } else {
      v = arr2[i2];
      if (i2 < s2) i2++;
    }
    res.push_back(v);
  }

  cout << "Result: " << endl;
  print_array(res);
  cout << endl;
}


auto binary_sort(vector<int> arr) {
  int l = 0; int r = arr.size() -1;
  int buf;

  cout << "Starting binary sort of array:" << endl;
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

  cout << "Starting thirdy sort of array:" << endl; print_array(arr);
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


auto main() -> int
{

  vector<int> array = {6, 8, 9, 11, 16, 18, 19, 21};
  int target = 25;
  two_sum(array, target);   // #1
  reverse_array(array);     // #2

  // # 3
  // k_reverse_arr();

  // # 4
  auto arr1 = {3, 8, 10, 11};
  auto arr2 = {1, 7, 9};
  merge2array(arr1, arr2);

  // # 5
  auto arr = {0, 1, 1, 0, 1, 0, 1, 0};
  binary_sort(arr);

  // # 6
  // arr = {2, 0, 2, 1, 1, 0};
  auto arr3 = generate_array(10, 3);
  thirdy_sort(arr3);
}