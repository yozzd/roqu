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

uint32_t random_pick_path(void);
void free_map(void);
void init_map(void);

extern map *m;

#endif
