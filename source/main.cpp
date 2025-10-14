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
  cout << endl << endl;
}


void print_res(uint64_t res, string type) {
  cout << "Result of " << type << ": " << res << endl;
}


auto generate_array(int count, string mode) {
  vector<int> array;

  cout << "Generating array by mode: " << mode << endl;
  if (mode == "sorted_random") {
    for (int i = 0; i < count; i++) {
      auto random_value = rand() % 10;
      array.push_back(random_value);
    }
   std::ranges::sort(array);
  }
  else 
    exit(-1);
  
  print_array(array);
  return array;
}

// ==============================


auto two_sum(vector<int> array, int target) {

  int l = 0;
  int r = array.size() -1;

  int res;
  while (l < r) {
    res = array[l] + array[r];
    if (target < res)
      r--;
    else if (target > res)
      l++;
    else
      cout << "Finded values, what give " << target << ". Its: " << l << " & " << r << endl;
      break;
  }

  return 0;
}


auto main() -> int
{
  // auto array = generate_array(10, "random");

  vector<int> array = {3, 8, 9, 11, 16, 18, 19, 21};
  int target = 25;
  print_res(two_sum(array, target), "2sum");
}