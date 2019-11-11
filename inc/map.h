#ifndef MAP_H
#define MAP_H

typedef struct grid {
  uint16_t gv;    //grid value
  uint32_t y, x;  //position
  bool vb;        //visible
  bool vt;        //visited
} grid;

typedef struct map {
  grid **gr;
  uint32_t *pt;   //path
  uint32_t spt;   //path size
} map;

wchar_t print_map(uint8_t y, uint8_t x);
uint32_t random_pick_path(void);
void free_map(void);
void init_map(void);

extern map *m;

#endif
