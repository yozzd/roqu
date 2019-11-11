#include "base.h"
#include "map.h"
#include "player.h"

player * p;

uint8_t border_y = (HEIGHT - (HEIGHT - W1_NLINES + 2)) / 2;
uint8_t border_x = (WIDTH - (WIDTH - W1_NCOLS + 2)) / 2;

static void put_player(void) {
  if (p->y < border_y) p->vy = border_y;
  else if (p->y >= HEIGHT - border_y) p->vy = HEIGHT - border_y;
  else p->vy = p->y;

  if (p->x <= border_x) p->vx = border_x;
  else if (p->x > WIDTH - border_x) p->vx = WIDTH - border_x;
  else p->vx = p->x;
}

void free_player(void) {
  free(p);
}

void init_player(void) {
  uint32_t id;

  p = malloc(sizeof(player));
  id = random_pick_path();

  m->gr[id]->gv = 5;

  p->name = "Orcbolg";
  p->y = m->gr[id]->y;
  p->x = m->gr[id]->x;
  p->hp = 100;
  p->vision = 4;
  p->quit = false;

  put_player();
}
