#include "map.h"
#include "player.h"
#include "fov.h"

player * p;

u8 border_y = (HEIGHT - (HEIGHT - W1_NLINES + 2)) / 2;
u8 border_x = (WIDTH - (WIDTH - W1_NCOLS + 2)) / 2;

void player_color(u16 id) {
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

void move_player(u8 y, u8 x, u8 cy, u8 cx) {
  u8 yy, xx;

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
  u16 n;

  p = malloc(sizeof(player));

  do {
    n = random_pick_grid(m->spt);
  } while (m->gr[m->pt[n]]->gv != 2);

  p->name = "Orcbolg";
  p->y = m->gr[m->pt[n]]->y;
  p->x = m->gr[m->pt[n]]->x;
  p->hp = 100;
  p->vision = 4;
  p->quit = false;

  m->gr[m->pt[n]]->gv = 5;

  put_player();
  player_color(m->pt[n]);
  fov(p->x, p->y, p->vision);
}
