#include "base.h"
#include "map.h"
#include "rng.h"

int main(void) {
  initialize(time(NULL));

  init_map();

  return 0;
}
