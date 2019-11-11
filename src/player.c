#include "base.h"
#include "map.h"
#include "player.h"
#include "fov.h"

player * p;

uint8_t border_y = (HEIGHT - (HEIGHT - W1_NLINES + 2)) / 2;
uint8_t border_x = (WIDTH - (WIDTH - W1_NCOLS + 2)) / 2;

void player_color(uint16_t id) {
  m->gr[id]->co = 2;
}

static void scroll_map(void) {
  if (p->y < p->vy - (W1_NLINES / 2 - 3)) {
    if (p->y < border_y) p->vy = border_y;
    else p->vy = p->y;
  } else if (p->y >= p->vy + (W1_NLINES / 2 - 3)) {
    if (p->y >= HEIGHT - border_y) p->vy = HEIGHT - border_y;
    else p->vy = p->y;
  }

  if (p->x < p->vx - (W1_NCOLS / 2 - 3)) {
    if (p->x <= border_x) p->vx = border_x;
    else p->vx = p->x;
  } else if (p->x >= p->vx + (W1_NCOLS / 2 - 3)) {
    if (p->x > WIDTH - border_x) p->vx = WIDTH - border_x;
    else p->vx = p->x;
  }
}

void move_player(uint8_t y, uint8_t x, uint8_t cy, uint8_t cx) {
  uint8_t yy, xx;

  yy = y + cy;
  xx = x + cx;

  if (m->gr[yy * WIDTH + xx]->gv == 2) {
    m->gr[yy * WIDTH + xx]->gv = m->gr[y * WIDTH + x]->gv;
    m->gr[y * WIDTH + x]->gv = 2;

    p->y += cy;
    p->x += cx;
  }

  fov(p->x, p->y, p->vision);
  scroll_map();
}

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
  uint16_t id;

  p = malloc(sizeof(player));

  do {
    id = random_pick_grid(m->pt, m->spt);
  } while (m->gr[id]->gv != 2);

  p->name = "Orcbolg";
  p->y = m->gr[id]->y;
  p->x = m->gr[id]->x;
  p->hp = 100;
  p->vision = 4;
  p->quit = false;

  m->gr[id]->gv = 5;

  put_player();
  player_color(id);
  fov(p->x, p->y, p->vision);
}
