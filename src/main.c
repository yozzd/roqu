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
  update_ui();

  while(p->quit != true) {
    keymap();
    update_ui();
  }
  shutdown_ui();

  return 0;
}
