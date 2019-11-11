#ifndef MAP_H
#define MAP_H

typedef struct grid {
  uint16_t gv;    //grid value
  uint8_t y, x;   //position
  bool vb;        //visible
  bool vt;        //visited
  uint8_t co;     //color
} grid;

typedef struct map {
  grid **gr;
  uint16_t *pt;   //path
  uint16_t spt;   //path size
} map;

void reset_grid_visibility(void);
wchar_t print_map(uint8_t y, uint8_t x);
uint16_t random_pick_path(void);
void free_map(void);
void init_map(void);

extern map *m;

#endif
