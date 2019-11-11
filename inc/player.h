#ifndef PLAYER_H
#define PLAYER_H

typedef struct player {
  char *name;
  uint16_t y, x, hp, vision, vpy, vpx;
  bool quit;
} player;

void free_player(void);
void init_player(void);

extern player * p;

#endif
