#include "base.h"
#include "player.h"

player * p;

void free_player(void) {
  free(p);
}

void init_player(void) {
  p = malloc(sizeof(player));

  p->name = "Orcbolg";
  p->hp = 100;
  p->vision = 4;
  p->quit = false;
}
