#ifndef MAP_H
#define MAP_H

typedef struct grid {
  uint16_t gv;    //grid value
  bool vb;        //visible
  bool vt;        //visited
} grid;

typedef struct map {
  grid **gr;
  uint32_t *pt;   //path
  uint32_t spt;   //path size
} map;

void init_map(void);

#endif
