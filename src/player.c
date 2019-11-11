#include "base.h"
#include "map.h"
#include "player.h"

player * p;

void free_player(void) {
  free(p);
}

void init_player(void) {
  p = malloc(sizeof(player));

  p->name = "Orcbolg";
  p->pos = random_pick_path();
  p->vpos = p->pos;
  p->hp = 100;
  p->vision = 4;
  p->quit = false;

  m->gr[p->pos]->gv = 5;
}
