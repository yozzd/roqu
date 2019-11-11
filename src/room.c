#include "base.h"
#include "map.h"
#include "rng.h"

static uint8_t room_h[2] = {4, 5};
static uint8_t room_w[2] = {4, 9};

static void set_door_candidate(uint8_t y1, uint8_t x1, uint8_t y2, uint8_t x2) {
  set_grid_door(y1, get_uniform_bound(x1 + 1, x2 - 1), 3, 0);
  set_grid_door(get_uniform_bound(y1 + 1, y2 - 1), x2, 3, 1);
  set_grid_door(y2, get_uniform_bound(x1 + 1, x2 - 1), 3, 2);
  set_grid_door(get_uniform_bound(y1 + 1, y2 - 1), x1, 3, 3);
}

static void fill_room(uint8_t y1, uint8_t x1, uint8_t y2, uint8_t x2) {
  for (uint8_t y = y1; y <= y2; y++) {
    for (uint8_t x = x1; x <= x2; x++) {
      m->gr[y * WIDTH + x]->gv = 2;
      m->gr[y * WIDTH + x]->type = 1;

      if (m->spt >= 2) m->pt = realloc(m->pt, sizeof(m->pt) * m->spt + 1);
      m->pt[m->spt] = y * WIDTH + x;
      m->spt++;
    }
  }
}

void first_room(void) {
  uint8_t cy, cx, h, w, y1, x1, y2, x2;

  cy = floor(HEIGHT / 2);
  cx = floor(WIDTH / 2);

  h = get_uniform_bound(room_h[0], room_h[1]);
  w = get_uniform_bound(room_w[0], room_w[1]);

  y1 = cy - floor(get_uniform() * h);
  x1 = cx - floor(get_uniform() * w);
  y2 = y1 + h - 1;
  x2 = x1 + w - 1;
  //y1 = 1;
  //x1 = 1;
  //y2 = 64;
  //x2 = 196;

  fill_room(y1, x1, y2, x2);
  set_door_candidate(y1, x1, y2, x2);
}
