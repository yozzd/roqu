#ifndef MAP_H
#define MAP_H

typedef struct grid_s {
  uint16_t value;
  bool visible, visited;
} grid_s;

typedef struct map_s {
  grid_s **grid;
} map_s;

void init_map(void);

#endif
