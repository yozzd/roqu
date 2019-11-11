#include "base.h"
#include "map.h"

map *m;

void new_map(void) {
  m = malloc(sizeof(map));

  m->g = malloc(sizeof(grid) * HEIGHT * WIDTH * 2);
  for (int i = 0; i < HEIGHT * WIDTH; i++) {
    m->g[i] = malloc(sizeof(grid));
    m->g[i]->gv = 0;
    m->g[i]->vb = 0;
    m->g[i]->vt = 0;
  }
}

void free_map(void) {
  for (int i = 0; i < HEIGHT * WIDTH; i++) {
    free(m->g[i]);
  }

  free(m->g);
  free(m);
}

void init_map(void) {
  new_map();

  free_map();
}
