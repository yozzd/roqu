#include "base.h"
#include "map.h"

map_s *m;

void new_map(void) {
  m = malloc(sizeof(map_s));

  m->grid = malloc(sizeof(grid_s) * HEIGHT * WIDTH * 2);
  for (int i = 0; i < HEIGHT * WIDTH; i++) {
    m->grid[i] = malloc(sizeof(grid_s));
    m->grid[i]->value = 0;
    m->grid[i]->visible = 0;
    m->grid[i]->visited = 0;
  }
}

void free_map(void) {
  for (int i = 0; i < HEIGHT * WIDTH; i++) {
    free(m->grid[i]);
  }

  free(m->grid);
  free(m);
}

void init_map(void) {
  new_map();

  free_map();
}
