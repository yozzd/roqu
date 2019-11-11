#include "base.h"
#include "map.h"
#include "rng.h"

static uint8_t room_h[2] = {4, 5};
static uint8_t room_w[2] = {4, 9};

static void fill_room(map *m, uint16_t y1, uint16_t x1, uint16_t y2, uint16_t x2) {
  for (uint16_t y = y1; y <= y2; y++) {
    for (uint16_t x = x1; x <= x2; x++) {
      m->gr[y * WIDTH + x]->gv = 2;

      if (m->spt >= 2) m->pt = realloc(m->pt, sizeof(m->pt) * m->spt + 1);
      m->pt[m->spt] = y * WIDTH + x;
      m->spt++;
    }
  }
}

void first_room(map *m) {
  uint16_t cy, cx, h, w, y1, x1, y2, x2;

  cy = floor(HEIGHT / 2);
  cx = floor(WIDTH / 2);

  h = get_uniform_bound(room_h[0], room_h[1]);
  w = get_uniform_bound(room_w[0], room_w[1]);

  y1 = cy - floor(get_uniform() * h);
  x1 = cx - floor(get_uniform() * w);
  y2 = y1 + h - 1;
  x2 = x1 + w - 1;

  fill_room(m, y1, x1, y2, x2);
}