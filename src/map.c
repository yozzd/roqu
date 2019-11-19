#include "rng.h"
#include "map.h"
#include "room.h"
#include "corridor.h"
#include "charset.h"
#include "player.h"

map *m;
u8 dir[8][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}, {-1, 1}, {1, 1}, {1, -1}, {-1, -1}};
static u16 grcap = 10, ptcap = 10, drcap = 10;

void delete_door_arr(u16 id) {
  m->gr[m->dr[id]]->drv = 0;
  m->gr[m->dr[id]]->drd = 4;
  for(u16 i = 0; i < m->sdr; i++){
    m->dr[id + i] = m->dr[id + i + 1];
  }
  m->sdr = m->sdr - 1;
}

void set_grid_path(u8 y, u8 x, u8 gv, u8 type) {
  m->gr[y * WIDTH + x]->gv = gv;
  m->gr[y * WIDTH + x]->type = type;

  if (m->spt == ptcap) {
    ptcap *= 2;
    m->pt = realloc(m->pt, sizeof(m->pt) * ptcap);
  }
  m->pt[m->spt] = y * WIDTH + x;
  m->spt++;
}

void set_grid_door(u8 y, u8 x, u8 drv, u8 drd) {
  m->gr[y * WIDTH + x]->drv = drv;
  m->gr[y * WIDTH + x]->drd = drd;

  if (m->sdr == drcap) {
    drcap *= 2;
    m->dr = realloc(m->dr, sizeof(m->dr) * drcap);
  }
  m->dr[m->sdr] = y * WIDTH + x;
  m->sdr++;
}

void reset_grid_visibility(void) {
  for (u16 i = 0; i < HEIGHT * WIDTH; i++) {
    m->gr[i]->vb = 0;

    if (m->gr[i]->vb && m->gr[i]->vt && m->gr[i]->gv == 5) player_color(i);
    else if (m->gr[i]->vb && m->gr[i]->vt && m->gr[i]->gv != 5) m->gr[i]->co = 2;
    else if (!m->gr[i]->vb && m->gr[i]->vt && m->gr[i]->gv != 5) m->gr[i]->co = 3;
  }
}

wchar_t print_map(u8 y, u8 x) {
  if (y < 0 || x < 0 || y >= HEIGHT || x >= WIDTH) return charset[0];
  else return charset[m->gr[y * WIDTH + x]->gv];
}

u16 random_pick_grid(u16 size) {
  return get_uniform_bound(0, size - 1);
}

void new_map(void) {
  u16 n = 1;

  m = calloc(1, sizeof(map));

  m->gr = calloc(grcap, sizeof(grid));
  for (u16 i = 0; i < HEIGHT * WIDTH; i++) {
    if (i == grcap) {
      grcap *= 2;
      m->gr = realloc(m->gr, sizeof(m->gr) * grcap);
    }
    if (i == n * WIDTH) n++;
    m->gr[i] = calloc(1, sizeof(grid));
    m->gr[i]->y = n - 1;
    m->gr[i]->x = i - (n - 1) * WIDTH;
    m->gr[i]->gv = 0;
    m->gr[i]->vb = 1;
    m->gr[i]->vt = 1;
    m->gr[i]->co = 1;
    m->gr[i]->type = 0;
    m->gr[i]->drv = 0;
    m->gr[i]->drd = 4;

    if (m->gr[i]->y == 0 || m->gr[i]->y == HEIGHT - 1
        || m->gr[i]->x == 0 || m->gr[i]->x == WIDTH - 1) m->gr[i]->gv = 1;
    else m->gr[i]->gv = 0;
  }

  m->pt = calloc(ptcap, sizeof(int));
  m->spt = 0;

  m->dr = calloc(drcap, sizeof(int));
  m->sdr = 0;
}

static void create_walls(void) {
  for (u8 y = 0; y < HEIGHT; y++) {
    for (u8 x = 0; x < WIDTH; x++) {
      for (u8 i = 0; i < 8; i++) {
        u8 yy = y + dir[i][0], xx = x + dir[i][1];

        if (m->gr[y * WIDTH + x]->gv == 2 && m->gr[yy * WIDTH + xx]->gv == 0) {
          m->gr[yy * WIDTH + xx]->gv = 1;
        }
      }
    }
  }
}

void free_map(void) {
  for (u16 i = 0; i < HEIGHT * WIDTH; i++) {
    free(m->gr[i]);
  }

  free(m->pt);
  free(m->dr);
  free(m->gr);
  free(m);
}

void init_map(void) {
  u8 i = 0, attempt = 50, idx;

  new_map();
  first_room();

  do {
    i++;

    create_corridor();
    idx = get_uniform_bound(0, 1);
    if (idx == 0) create_corridor();
    else create_room();
  } while(i < attempt);

  create_walls();
}
