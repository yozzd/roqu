#include "base.h"
#include "rng.h"
#include "map.h"
#include "room.h"
#include "corridor.h"
#include "charset.h"
#include "player.h"

map *m;
uint8_t dir[8][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1},
                    {-1, 1}, {1, 1}, {1, -1}, {-1, -1}};

void set_grid_door(uint8_t y, uint8_t x, uint8_t drv, uint8_t drd) {
  m->gr[y * WIDTH + x]->drv = drv;
  m->gr[y * WIDTH + x]->drd = drd;

  if (m->sdr >= 2) m->dr = realloc(m->dr, sizeof(m->dr) * m->sdr + 1);
  m->dr[m->sdr] = y * WIDTH + x;
  m->sdr++;
}

void reset_grid_visibility(void) {
  for (uint16_t i = 0; i < HEIGHT * WIDTH; i++) {
    m->gr[i]->vb = 0;

    if (m->gr[i]->vb && m->gr[i]->vt && m->gr[i]->gv == 5) player_color(i);
    else if (m->gr[i]->vb && m->gr[i]->vt && m->gr[i]->gv != 5) m->gr[i]->co = 2;
    else if (!m->gr[i]->vb && m->gr[i]->vt && m->gr[i]->gv != 5) m->gr[i]->co = 3;
  }
}

wchar_t print_map(uint8_t y, uint8_t x) {
  if (y < 0 || x < 0 || y >= HEIGHT || x >= WIDTH) return charset[0];
  else return charset[m->gr[y * WIDTH + x]->gv];
}

uint16_t random_pick_grid(uint16_t *arr, uint16_t size) {
  uint16_t id;

  id = get_uniform_bound(0, size - 1);
  return arr[id];
}

void new_map(void) {
  uint16_t n = 1;

  m = malloc(sizeof(map));

  m->gr = malloc(sizeof(grid) * HEIGHT * WIDTH * 2);
  for (uint16_t i = 0; i < HEIGHT * WIDTH; i++) {
    if (i == n * WIDTH) n++;
    m->gr[i] = malloc(sizeof(grid));
    m->gr[i]->y = n - 1;
    m->gr[i]->x = i - (n - 1) * WIDTH;
    m->gr[i]->gv = 0;
    m->gr[i]->vb = 0;
    m->gr[i]->vt = 0;
    m->gr[i]->co = 1;
    m->gr[i]->type = 0;
    m->gr[i]->drv = 0;
    m->gr[i]->drd = 4;

    if (m->gr[i]->y == 0 || m->gr[i]->y == HEIGHT - 1
        || m->gr[i]->x == 0 || m->gr[i]->x == WIDTH - 1) m->gr[i]->gv = 1;
    else m->gr[i]->gv = 0;
  }

  m->pt = malloc(sizeof(int) * 2);
  m->spt = 0;

  m->dr = malloc(sizeof(int) * 2);
  m->sdr = 0;
}

static void make_walls(void) {
  for (uint8_t y = 0; y < HEIGHT; y++) {
    for (uint8_t x = 0; x < WIDTH; x++) {
      for (uint8_t i = 0; i < 8; i++) {
        uint8_t yy = y + dir[i][0], xx = x + dir[i][1];

        if (m->gr[y * WIDTH + x]->gv == 2 && m->gr[yy * WIDTH + xx]->gv == 0) {
          m->gr[yy * WIDTH + xx]->gv = 1;
        }
      }
    }
  }
}

void free_map(void) {
  for (uint16_t i = 0; i < HEIGHT * WIDTH; i++) {
    free(m->gr[i]);
  }

  free(m->pt);
  free(m->dr);
  free(m->gr);
  free(m);
}

void init_map(void) {
  new_map();
  first_room();
  create_corridor();
  create_corridor();
  create_corridor();

  make_walls();
}
