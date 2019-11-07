#ifndef RNG_H
#define RNG_H

void initialize(const uint32_t seed);
double get_uniform();
int get_uniform_bound(int lower, int upper);

#endif
