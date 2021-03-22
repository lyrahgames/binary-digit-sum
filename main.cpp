#include <bitset>
#include <cassert>
#include <chrono>
#include <iomanip>
#include <iostream>
#include <random>
//
#include <binary_digit_sum.hpp>

using namespace std;

int main() {
  lookup_table::lut table{};

  mt19937 rng{random_device{}()};

  for (size_t i = 0; i < 10; ++i) {
    const auto rnd = rng();
    cout << setw(35) << bitset<32>{rnd} << setw(8)
         << static_iterative::binary_digit_sum(rnd) << '\n';
  }

  for (size_t i = 0; i < 100'000; ++i) {
    const auto rnd = rng();
    assert(static_iterative::binary_digit_sum(rnd) ==
           dynamic_iterative::binary_digit_sum(rnd));
    assert(static_iterative::binary_digit_sum(rnd) ==
           lookup_table::binary_digit_sum(table, rnd));
    assert(static_iterative::binary_digit_sum(rnd) ==
           subtraction::binary_digit_sum(rnd));
    assert(static_iterative::binary_digit_sum(rnd) ==
           divide_and_conquer::binary_digit_sum(rnd));
    assert(static_iterative::binary_digit_sum(rnd) ==
           hakhem::binary_digit_sum(rnd));
  }

  const auto start = chrono::high_resolution_clock::now();
  volatile uint32_t do_not_optimize_away;
  for (size_t i = 0; i < 1'000'000'000ull; ++i)
    do_not_optimize_away = divide_and_conquer::binary_digit_sum(rng());
  const auto end = chrono::high_resolution_clock::now();
  const auto time = chrono::duration<double>(end - start).count();
  cout << "time = " << time << " s\n";
}