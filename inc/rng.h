#ifndef RNG_H
#define RNG_H

#include "base.h"

i16 get_weighted_value(u8 m, u8 n, u8 arr[m][n]);
void initialize(const u32 seed);
double get_uniform();
u16 get_uniform_bound(u16 lower, u16 upper);

#endif
