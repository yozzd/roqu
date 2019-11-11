#include "base.h"
#include "rng.h"
#include "map.h"
#include "player.h"

int main(void) {
  initialize(time(NULL));

  init_map();
  init_player();

  free_player();
  free_map();
  return 0;
}
