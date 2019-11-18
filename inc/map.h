#ifndef MAP_H
#define MAP_H

#include "base.h"

typedef struct grid {
  u16 gv;      //grid value
  u8 y, x;     //position
  bool vb;          //visible
  bool vt;          //visited
  u8 co;       //color
  u8 type;     //1:room, 2:corridor
  u8 drv, drd; //door value, door direction
} grid;

typedef struct map {
  grid **gr;
  u16 *pt;     //path arr
  u16 spt;     //path size
  u16 *dr;     //door arr
  u16 sdr;     //door size
} map;

void delete_door_arr(u16 id);
void set_grid_door(u8 y, u8 x, u8 drv, u8 drd);
void reset_grid_visibility(void);
wchar_t print_map(u8 y, u8 x);
u16 random_pick_grid(u16 size);
void free_map(void);
void init_map(void);

extern map *m;
extern u8 dir[8][2];

#endif
