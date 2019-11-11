#ifndef RNG_H
#define RNG_H

void initialize(const uint32_t seed);
double get_uniform();
uint16_t get_uniform_bound(uint16_t lower, uint16_t upper);

#endif
