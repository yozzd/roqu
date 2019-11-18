#ifndef PLAYER_H
#define PLAYER_H

#include "base.h"

typedef struct player {
  char *name;
  u8 y, x;        //position
  u16 hp;
  u8 vision;
  u8 vy, vx;      //viewport
  bool quit;
} player;

void player_color(u16 id);
void move_player(u8 y, u8 x, u8 cy, u8 cx);
void free_player(void);
void init_player(void);

extern player * p;

#endif
