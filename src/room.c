#include "base.h"
#include "rng.h"
#include "map.h"

static uint8_t room_h[2] = {4, 6};
static uint8_t room_w[2] = {6, 10};

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

static bool is_valid_room(int16_t y1, int16_t x1, int16_t y2, int16_t x2) {
  uint8_t t = 0;
  int8_t c = 0;

  for (int16_t y = y1; y <= y2; y++) {
    for (int16_t x = x1; x <= x2; x++) {
      t++;
      if (y * WIDTH + x > 0 && y * WIDTH + x < HEIGHT * WIDTH - 1) {
        if (m->gr[y * WIDTH + x]->gv == 0) c++;
      }
    }
  }

  if (t == c) return true;
  else return false;
}

void create_room(void) {
  uint16_t id;
  uint8_t len, h, w;
  int16_t y1, x1, y2, x2;

  do {
    id = random_pick_grid(m->dr, m->sdr);
  } while(m->gr[id]->drv == 3);

  h = get_uniform_bound(room_h[0], room_h[1]);
  w = get_uniform_bound(room_w[0], room_w[1]);

  if (m->gr[id]->drd == 0) {
    len = m->gr[id]->x - floor(get_uniform() * w);
    y1 = m->gr[id]->y - h;
    x1 = len;
    y2 = m->gr[id]->y - 1;
    x2 = len + w - 1;
  } else if (m->gr[id]->drd == 1) {
    len = m->gr[id]->y - floor(get_uniform() * h);
    y1 = len;
    x1 = m->gr[id]->x + 1;
    y2 = len + h - 1;
    x2 = m->gr[id]->x + w;
  } else if (m->gr[id]->drd == 2) {
    len = m->gr[id]->x - floor(get_uniform() * w);
    y1 = m->gr[id]->y + 1;
    x1 = len;
    y2 = m->gr[id]->y + h;
    x2 = len + w - 1;
  } else {
    len = m->gr[id]->y - floor(get_uniform() * h);
    y1 = len;
    x1 = m->gr[id]->x - w;
    y2 = len + h - 1;
    x2 = m->gr[id]->x - 1;
  }

  if (is_valid_room(y1, x1, y2, x2)) {
    m->gr[id]->drv = 0;
    m->gr[id]->drd = 4;
    fill_room(y1, x1, y2, x2);
    set_door_candidate(y1, x1, y2, x2);
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

  fill_room(y1, x1, y2, x2);
  set_door_candidate(y1, x1, y2, x2);
}
