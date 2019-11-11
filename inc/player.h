#ifndef PLAYER_H
#define PLAYER_H

typedef struct player {
  char *name;
  uint32_t y, x;        //position
  uint16_t hp, vision;
  uint32_t vy, vx;      //viewport
  bool quit;
} player;

void free_player(void);
void init_player(void);

extern player * p;

#endif
