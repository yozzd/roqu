#ifndef RNG_H
#define RNG_H

#include "base.h"

void initialize(const u32 seed);
double get_uniform();
u16 get_uniform_bound(u16 lower, u16 upper);

#endif
