#include "rng.h"
#include "map.h"

static const u8 corridor_len[2] = {2, 8};
static const u8 corridor_dir[4][3] = {{0, 1, 3}, {0, 1, 2}, {1, 2, 3}, {0, 2, 3}};

static void set_door_candidate(u8 sy, u8 ey, u8 sx, u8 ex, u8 dr) {
  if (dr == 0) set_grid_door(sy, sx, 4, 0);
  else if (dr == 1) set_grid_door(ey, ex, 4, 1);
  else if (dr == 2) set_grid_door(ey, ex, 4, 2);
  else set_grid_door(sy, sx, 4, 3);
}

static void fill_corridor(u8 sy, u8 ey, u8 sx, u8 ex) {
  for (u8 y = sy; y <= ey; y++) {
    for (u8 x = sx; x <= ex; x++) {
      m->gr[y * WIDTH + x]->gv = 2;
      m->gr[y * WIDTH + x]->type = 2;

      if (m->spt >= 2) m->pt = realloc(m->pt, sizeof(m->pt) * m->spt + 1);
      m->pt[m->spt] = y * WIDTH + x;
      m->spt++;
    }
  }
}

static bool is_valid_corridor(u8 sy, u8 ey, u8 sx, u8 ex, u8 len) {
  u8 c = 0;

  for (u8 y = sy; y <= ey; y++) {
    for (u8 x = sx; x <= ex; x++) {
      if (y * WIDTH + x > 0 && y * WIDTH + x < HEIGHT * WIDTH - 1) {
        if (m->gr[y * WIDTH + x]->gv == 0) c++;
      }
    }
  }

  if (c == len) return true;
  else return false;
}

void create_corridor(void) {
  u16 n;
  u8 len, idc, cd, dr, sy, ey, sx, ex;

  n = random_pick_grid(m->sdr);
  len = get_uniform_bound(corridor_len[0], corridor_len[1]);

  if (m->gr[m->dr[n]]->drv == 4) {
    idc = get_uniform_bound(0, 3);

    if (m->gr[m->dr[n]]->drd == 0) cd = corridor_dir[0][idc];
    else if (m->gr[m->dr[n]]->drd == 1) cd = corridor_dir[1][idc];
    else if (m->gr[m->dr[n]]->drd == 2) cd = corridor_dir[2][idc];
    else cd = corridor_dir[3][idc];

    dr = cd;
  } else dr = m->gr[m->dr[n]]->drd;

  if (dr == 0) {
    sy = m->gr[m->dr[n]]->y + (len * dir[0][0]);
    ey = m->gr[m->dr[n]]->y + dir[0][0];
    sx = m->gr[m->dr[n]]->x + dir[0][1];
    ex = sx;
  } else if (dr == 1) {
    sy = m->gr[m->dr[n]]->y + dir[1][0];
    ey = sy;
    sx = m->gr[m->dr[n]]->x + dir[1][1];
    ex = m->gr[m->dr[n]]->x + (len * dir[1][1]);
  } else if (dr == 2) {
    sy = m->gr[m->dr[n]]->y + dir[2][0];
    ey = m->gr[m->dr[n]]->y + (len * dir[2][0]);
    sx = m->gr[m->dr[n]]->x + dir[2][1];
    ex = sx;
  } else {
    sy = m->gr[m->dr[n]]->y + dir[3][0];
    ey = sy;
    sx = m->gr[m->dr[n]]->x + (len * dir[3][1]);
    ex = m->gr[m->dr[n]]->x + dir[3][1];
  }

  if (is_valid_corridor(sy, ey, sx, ex, len)) {
    fill_corridor(sy, ey, sx, ex);
    set_door_candidate(sy, ey, sx, ex, dr);
    delete_door_arr(n);
  } else create_corridor();
}
