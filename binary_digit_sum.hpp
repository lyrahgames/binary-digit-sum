#pragma once
#include <cstdint>

// The following namespace provide different implementations of the same
// routine.

namespace static_iterative {
constexpr uint32_t binary_digit_sum(uint32_t x) {
  uint32_t result = 0;
  for (size_t i = 0; i < 32; ++i)  //
    result += (x >> i) & 0b01;
  return result;
}
}  // namespace static_iterative

namespace dynamic_iterative {
constexpr uint32_t binary_digit_sum(uint32_t x) {
  uint32_t result = 0;
  // while (x) {
  //   result += x & 0b01;
  //   x >>= 1;
  // }
  do {
    result += x & 0b01;
  } while (x >>= 1);
  return result;
}
}  // namespace dynamic_iterative

namespace lookup_table {
struct lut {
  constexpr lut() {
    for (size_t i = 0; i < 256; ++i)  //
      counts[i] = static_iterative::binary_digit_sum(i);
  }
  constexpr uint8_t operator[](uint8_t x) const { return counts[x]; }
  uint8_t counts[256];
};
constexpr uint32_t binary_digit_sum(const lut& table, uint32_t x) {
  return table[x >> 24] + table[x >> 16] + table[x >> 8] + table[x];
}
}  // namespace lookup_table

namespace subtraction {
constexpr uint32_t binary_digit_sum(uint32_t x) {
  uint32_t result = x;
  for (size_t i = 1; i < 32; ++i) result -= x >> i;
  return result;
}
}  // namespace subtraction

namespace divide_and_conquer {
constexpr uint32_t binary_digit_sum(uint32_t x) {
  // x = (x & 0x55555555) + ((x >> 1) & 0x55555555);
  x = x - ((x >> 1) & 0x55555555);
  x = (x & 0x33333333) + ((x >> 2) & 0x33333333);
  // x = (x & 0x0f0f0f0f) + ((x >> 4) & 0x0f0f0f0f);
  x = (x + (x >> 4)) & 0x0f0f0f0f;
  // x = (x & 0x00ff00ff) + ((x >> 8) & 0x00ff00ff);
  x = (x + (x >> 8)) & 0x00ff00ff;
  // x = (x & 0x0000ffff) + ((x >> 16) & 0x0000ffff);
  x = (x + (x >> 16)) & 0x0000ffff;
  return x;
}
}  // namespace divide_and_conquer

namespace hakhem {
constexpr uint32_t binary_digit_sum(uint32_t x) {
  x = x                            //
      - ((x >> 1) & 033333333333)  //
      - ((x >> 2) & 011111111111);
  x = (x + (x >> 3)) & 030707070707;
  x = (x + (x >> 6)) & 007700770077;
  x = (x + (x >> 12)) & 077700007777;
  x = (x + (x >> 24)) & 000077777777;
  return x;
}
}  // namespace hakhem