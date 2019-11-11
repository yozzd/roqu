#ifndef PLAYER_H
#define PLAYER_H

typedef struct player {
  char *name;
  uint8_t y, x;        //position
  uint16_t hp;
  uint8_t vision;
  uint8_t vy, vx;      //viewport
  bool quit;
} player;

void player_color(uint16_t id);
void move_player(uint8_t y, uint8_t x, uint8_t cy, uint8_t cx);
void free_player(void);
void init_player(void);

extern player * p;

#endif
