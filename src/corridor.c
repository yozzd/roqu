#include "base.h"
#include "rng.h"
#include "map.h"

static int corridor_len[2] = {8, 10};
static int corridor_dir[4][3] = {{0, 1, 3}, {0, 1 ,2}, {1, 2, 3}, {0, 2, 3}};

static void set_door_candidate(uint8_t sy, uint8_t ey, uint8_t sx, uint8_t ex, uint8_t dr) {
  if (dr == 0) set_grid_door(sy, sx, 4, 0);
  else if (dr == 1) set_grid_door(ey, ex, 4, 1);
  else if (dr == 2) set_grid_door(ey, ex, 4, 2);
  else set_grid_door(sy, sx, 4, 3);
}

static void fill_corridor(uint8_t sy, uint8_t ey, uint8_t sx, uint8_t ex) {
  for (uint8_t y = sy; y <= ey; y++) {
    for (uint8_t x = sx; x <= ex; x++) {
      m->gr[y * WIDTH + x]->gv = 2;

      if (m->spt >= 2) m->pt = realloc(m->pt, sizeof(m->pt) * m->spt + 1);
      m->pt[m->spt] = y * WIDTH + x;
      m->spt++;
    }
  }
}

static bool is_valid_corridor(uint8_t sy, uint8_t ey, uint8_t sx, uint8_t ex, uint8_t len) {
  uint8_t c = 0;

  for (uint8_t y = sy; y <= ey; y++) {
    for (uint8_t x = sx; x <= ex; x++) {
      if (y * WIDTH + x > 0 && y * WIDTH + x < HEIGHT * WIDTH - 1) {
        if (m->gr[y * WIDTH + x]->gv == 0) c++;
      }
    }
  }

  if (c == len) return true;
  else return false;
}

void create_corridor(void) {
  uint16_t id;
  uint8_t len, idc, cd, dr, sy, ey, sx, ex;

  id = random_pick_grid(m->dr, m->sdr);
  len = get_uniform_bound(corridor_len[0], corridor_len[1]);

  if (m->gr[id]->drv == 4) {
    idc = get_uniform_bound(0, 3);

    if (m->gr[id]->drd == 0) cd = corridor_dir[0][idc];
    else if (m->gr[id]->drd == 1) cd = corridor_dir[1][idc];
    else if (m->gr[id]->drd == 2) cd = corridor_dir[2][idc];
    else cd = corridor_dir[3][idc];
  }

  dr = m->gr[id]->drv == 4 ? cd : m->gr[id]->drd;

  if (dr == 0) {
    sy = m->gr[id]->y + (len * dir[0][0]);
    ey = m->gr[id]->y + dir[0][0];
    sx = m->gr[id]->x + dir[0][1];
    ex = sx;
  } else if (dr == 1) {
    sy = m->gr[id]->y + dir[1][0];
    ey = sy;
    sx = m->gr[id]->x + dir[1][1];
    ex = m->gr[id]->x + (len * dir[1][1]);
  } else if (dr == 2) {
    sy = m->gr[id]->y + dir[2][0];
    ey = m->gr[id]->y + (len * dir[2][0]);
    sx = m->gr[id]->x + dir[2][1];
    ex = sx;
  } else {
    sy = m->gr[id]->y + dir[3][0];
    ey = sy;
    sx = m->gr[id]->x + (len * dir[3][1]);
    ex = m->gr[id]->x + dir[3][1];
  }

  if (is_valid_corridor(sy, ey, sx, ex, len)) {
    m->gr[id]->drv = 0;
    m->gr[id]->drd = 4;
    fill_corridor(sy, ey, sx, ex);
    set_door_candidate(sy, ey, sx, ex, dr);
  }
}
