#include "base.h"
#include "map.h"
#include "room.h"

map *m;

void new_map(void) {
  m = malloc(sizeof(map));

  m->gr = malloc(sizeof(grid) * HEIGHT * WIDTH * 2);
  for (uint32_t i = 0; i < HEIGHT * WIDTH; i++) {
    m->gr[i] = malloc(sizeof(grid));
    m->gr[i]->gv = 0;
    m->gr[i]->vb = 0;
    m->gr[i]->vt = 0;
  }

  m->pt = malloc(sizeof(int) * 2);
  m->spt = 0;
}

void free_map(void) {
  for (int i = 0; i < HEIGHT * WIDTH; i++) {
    free(m->gr[i]);
  }

  free(m->pt);
  free(m->gr);
  free(m);
}

void init_map(void) {
  new_map();
  first_room(m);
}
