#include "rng.h"
#include "map.h"

static const u8 room_h[2] = {4, 6};
static const u8 room_w[2] = {6, 16};

static void set_door_candidate(u8 y1, u8 x1, u8 y2, u8 x2, u8 drd) {
  if (drd == 0) {
    set_grid_door(y1, get_uniform_bound(x1 + 1, x2 - 1), 3, 0);
    set_grid_door(get_uniform_bound(y1 + 1, y2 - 1), x2, 3, 1);
    set_grid_door(get_uniform_bound(y1 + 1, y2 - 1), x1, 3, 3);
  } else if (drd == 1) {
    set_grid_door(y1, get_uniform_bound(x1 + 1, x2 - 1), 3, 0);
    set_grid_door(get_uniform_bound(y1 + 1, y2 - 1), x2, 3, 1);
    set_grid_door(y2, get_uniform_bound(x1 + 1, x2 - 1), 3, 2);
  } else if (drd == 2) {
    set_grid_door(get_uniform_bound(y1 + 1, y2 - 1), x2, 3, 1);
    set_grid_door(y2, get_uniform_bound(x1 + 1, x2 - 1), 3, 2);
    set_grid_door(get_uniform_bound(y1 + 1, y2 - 1), x1, 3, 3);
  } else if (drd == 3) {
    set_grid_door(y1, get_uniform_bound(x1 + 1, x2 - 1), 3, 0);
    set_grid_door(y2, get_uniform_bound(x1 + 1, x2 - 1), 3, 2);
    set_grid_door(get_uniform_bound(y1 + 1, y2 - 1), x1, 3, 3);
  } else {
    set_grid_door(y1, get_uniform_bound(x1 + 1, x2 - 1), 3, 0);
    set_grid_door(get_uniform_bound(y1 + 1, y2 - 1), x2, 3, 1);
    set_grid_door(y2, get_uniform_bound(x1 + 1, x2 - 1), 3, 2);
    set_grid_door(get_uniform_bound(y1 + 1, y2 - 1), x1, 3, 3);
  }
}

static void fill_room(u8 y1, u8 x1, u8 y2, u8 x2) {
  for (u8 y = y1; y <= y2; y++) {
    for (u8 x = x1; x <= x2; x++) {
      set_grid_path(y, x, 2, 1);
    }
  }
}

static bool is_valid_room(i16 y1, i16 x1, i16 y2, i16 x2) {
  u8 t = 0;
  i8 c = 0;

  for (i16 y = y1; y <= y2; y++) {
    for (i16 x = x1; x <= x2; x++) {
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
  i16 n, y1, x1, y2, x2;
  u8 len, h, w;

  do {
    n = random_pick_grid(m->sdr);
  } while(m->gr[m->dr[n]]->drv == 3);

  h = get_uniform_bound(room_h[0], room_h[1]);
  w = get_uniform_bound(room_w[0], room_w[1]);

  if (m->gr[m->dr[n]]->drd == 0) {
    len = m->gr[m->dr[n]]->x - floor(get_uniform() * w);
    y1 = m->gr[m->dr[n]]->y - h;
    x1 = len;
    y2 = m->gr[m->dr[n]]->y - 1;
    x2 = len + w - 1;
  } else if (m->gr[m->dr[n]]->drd == 1) {
    len = m->gr[m->dr[n]]->y - floor(get_uniform() * h);
    y1 = len;
    x1 = m->gr[m->dr[n]]->x + 1;
    y2 = len + h - 1;
    x2 = m->gr[m->dr[n]]->x + w;
  } else if (m->gr[m->dr[n]]->drd == 2) {
    len = m->gr[m->dr[n]]->x - floor(get_uniform() * w);
    y1 = m->gr[m->dr[n]]->y + 1;
    x1 = len;
    y2 = m->gr[m->dr[n]]->y + h;
    x2 = len + w - 1;
  } else {
    len = m->gr[m->dr[n]]->y - floor(get_uniform() * h);
    y1 = len;
    x1 = m->gr[m->dr[n]]->x - w;
    y2 = len + h - 1;
    x2 = m->gr[m->dr[n]]->x - 1;
  }

  if (is_valid_room(y1, x1, y2, x2)) {
    fill_room(y1, x1, y2, x2);
    set_door_candidate(y1, x1, y2, x2, m->gr[m->dr[n]]->drd);
    delete_door_arr(n);
  }
}

void first_room(void) {
  u8 cy, cx, h, w, y1, x1, y2, x2;

  cy = floor(HEIGHT / 2);
  cx = floor(WIDTH / 2);

  h = get_uniform_bound(room_h[0], room_h[1]);
  w = get_uniform_bound(room_w[0], room_w[1]);

  y1 = cy - floor(get_uniform() * h);
  x1 = cx - floor(get_uniform() * w);
  y2 = y1 + h - 1;
  x2 = x1 + w - 1;

  fill_room(y1, x1, y2, x2);
  set_door_candidate(y1, x1, y2, x2, 4);
}
