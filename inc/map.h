#ifndef MAP_H
#define MAP_H

typedef struct grid {
  uint16_t gv;    //grid value
  bool vb;        //visible
  bool vt;        //visited
} grid;

typedef struct map {
  grid **g;
} map;

void init_map(void);

#endif
