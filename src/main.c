#include "base.h"
#include "rng.h"
#include "map.h"
#include "player.h"
#include "ui.h"

int main(void) {
  initialize(time(NULL));

  init_map();
  init_player();

  init_ui();

  free_player();
  free_map();
  return 0;
}
