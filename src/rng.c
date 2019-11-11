#include "base.h"
#include "rng.h"

// Define MT19937 constants (32-bit RNG)
enum {
  N = 624,
  M = 397,
  R = 31,
  A = 0x9908B0DF,

  F = 1812433253,

  U = 11,

  S = 7,
  B = 0x9D2C5680,

  T = 15,
  C = 0xEFC60000,

  L = 18,

  MASK_LOWER = (1ull << R) - 1,
  MASK_UPPER = (1ull << R)
};

static uint32_t mt[N];
static uint16_t idx;

void initialize(const uint32_t seed) {
  uint32_t i;

  mt[0] = seed;

  for (i = 1; i < N; i++) {
    mt[i] = (F * (mt[i - 1] ^ (mt[i - 1] >> 30)) + i);
  }

  idx = N;
}

static void twist() {
  uint32_t i, x, xA;

  for (i = 0; i < N; i++) {
    x = (mt[i] & MASK_UPPER) + (mt[(i + 1) % N] & MASK_LOWER);

    xA = x >> 1;

    if (x & 0x1) xA ^= A;

    mt[i] = mt[(i + M) % N] ^ xA;
  }

  idx = 0;
}

uint32_t extractU32() {
  uint32_t y;
  int i = idx;

  if (idx >= N) {
    twist();
    i = idx;
  }

  y = mt[i];
  idx = i + 1;

  y ^= (y >> U);
  y ^= (y << S) & B;
  y ^= (y << T) & C;
  y ^= (y >> L);

  return y;
}

double get_uniform(void) {
  return ldexp(extractU32(), -32);
}

uint16_t get_uniform_bound(uint16_t lower, uint16_t upper) {
  uint16_t min, max;

  max = MAX(lower, upper);
  min = MIN(lower, upper);

  return floor(get_uniform() * (max - min + 1)) + min;
}

