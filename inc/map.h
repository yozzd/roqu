#ifndef MAP_H
#define MAP_H

typedef struct grid {
  uint16_t gv;      //grid value
  uint8_t y, x;     //position
  bool vb;          //visible
  bool vt;          //visited
  uint8_t co;       //color
  uint8_t type;     //1:room, 2:corridor
  uint8_t drv, drd; //door value, door direction
} grid;

typedef struct map {
  grid **gr;
  uint16_t *pt;     //path arr
  uint16_t spt;     //path size
  uint16_t *dr;     //door arr
  uint16_t sdr;     //door size
} map;

void set_grid_door(uint8_t y, uint8_t x, uint8_t drv, uint8_t drd);
void reset_grid_visibility(void);
wchar_t print_map(uint8_t y, uint8_t x);
uint16_t random_pick_grid(uint16_t *arr, uint16_t size);
void free_map(void);
void init_map(void);

extern map *m;
extern uint8_t dir[8][2];

#endif
