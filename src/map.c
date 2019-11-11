#include "base.h"
#include "rng.h"
#include "map.h"
#include "room.h"
#include "charset.h"
#include "player.h"

map *m;

void reset_grid_visibility(void) {
  for (uint16_t i = 0; i < HEIGHT * WIDTH; i++) {
    m->gr[i]->vb = 0;

    if (m->gr[i]->vb && m->gr[i]->vt && m->gr[i]->gv == 5) player_color(i);
    else if (m->gr[i]->vb && m->gr[i]->vt && m->gr[i]->gv != 5) m->gr[i]->co = 2;
    else if (!m->gr[i]->vb && m->gr[i]->vt && m->gr[i]->gv != 5) m->gr[i]->co = 3;
  }
}

wchar_t print_map(uint8_t y, uint8_t x) {
  if (y < 0 || x < 0 || y >= HEIGHT || x >= WIDTH) return charset[0];
  else return charset[m->gr[y * WIDTH + x]->gv];
}

uint16_t random_pick_path(void) {
  uint16_t id;

  id = get_uniform_bound(0, m->spt - 1);
  return m->pt[id];
}

void new_map(void) {
  uint16_t n = 1;

  m = malloc(sizeof(map));

  m->gr = malloc(sizeof(grid) * HEIGHT * WIDTH * 2);
  for (uint16_t i = 0; i < HEIGHT * WIDTH; i++) {
    if (i == n * WIDTH) n++;
    m->gr[i] = malloc(sizeof(grid));
    m->gr[i]->y = n - 1;
    m->gr[i]->x = i - (n - 1) * WIDTH;
    m->gr[i]->gv = 0;
    m->gr[i]->vb = 0;
    m->gr[i]->vt = 0;
    m->gr[i]->co = 1;

    if (m->gr[i]->y == 0 || m->gr[i]->y == HEIGHT - 1
        || m->gr[i]->x == 0 || m->gr[i]->x == WIDTH - 1) m->gr[i]->gv = 1;
    else m->gr[i]->gv = 0;
  }

  m->pt = malloc(sizeof(int) * 2);
  m->spt = 0;
}

void free_map(void) {
  for (uint16_t i = 0; i < HEIGHT * WIDTH; i++) {
    free(m->gr[i]);
  }

  free(m->pt);
  free(m->gr);
  free(m);
}

void init_map(void) {
  new_map();
  first_room();
}
