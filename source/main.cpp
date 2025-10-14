#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <ranges>

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
  if (mode == "random")
    for (int i = 0; i < count; i++) {
      auto random_value = rand() % 10;
      array.push_back(random_value);
    }
  else 
    exit(-1);
  
  print_array(array);
  return array;
}

// ==============================


auto two_sum(vector<int> array) {
  uint64_t res = 0;

  for

  return res;
}


auto main() -> int
{
  auto array = generate_array(10, "random");

  print_res(two_sum(array), "2sum");
}