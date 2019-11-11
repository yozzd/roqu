#include "base.h"
#include "map.h"

static int multipliers[4][8] = {
  {1, 0, 0, -1, -1, 0, 0, 1},
  {0, 1, -1, 0, 0, -1, 1, 0},
  {0, 1, 1, 0, 0, -1, -1, 0},
  {1, 0, 0, 1, -1, 0, 0, -1}
};

void cast_light(int x, int y, int radius, int row, float start_slope,
    float end_slope, int xx, int xy, int yx, int yy) {

  if (start_slope < end_slope) return;

  float next_start_slope = start_slope;
  for (int i = row; i <= radius; i++) {
    bool blocked = false;
    for (int dx = -i, dy = -i; dx <= 0; dx++) {
      float l_slope = (dx - 0.5) / (dy + 0.5);
      float r_slope = (dx + 0.5) / (dy - 0.5);

      if (start_slope < r_slope) continue;
      else if (end_slope > l_slope) break;

      int sax = dx * xx + dy * xy;
      int say = dx * yx + dy * yy;

      if ((sax < 0 && (int) abs(sax) > x) || (say < 0 && (int) abs(say) > y)) continue;

      int ax = x + sax;
      int ay = y + say;

      if (ax >= WIDTH || ay >= HEIGHT) continue;

      int radius2 = radius * radius;
      if ((int) (dx * dx + dy * dy) < radius2) {
        m->gr[ay * WIDTH + ax]->vb = 1;
        m->gr[ay * WIDTH + ax]->vt = 1;
        m->gr[ay * WIDTH + ax]->co = 2;
      }

      if (blocked) {
        if (m->gr[ay * WIDTH + ax]->gv == 1) {
          next_start_slope = r_slope;
          continue;
        } else {
          blocked = false;
          start_slope = next_start_slope;
        }
      } else if (m->gr[ay * WIDTH + ax]->gv == 1) {
        blocked = true;
        next_start_slope = r_slope;
        cast_light(x, y, radius, i + 1, start_slope, l_slope, xx, xy, yx, yy);
      }
    }

    if (blocked) break;
  }
}

void fov(int x, int y, int radius) {
  reset_grid_visibility();
  for (int i = 0; i < 8; i++) {
    cast_light(x, y, radius, 1, 1.0, 0.0, multipliers[0][i],
        multipliers[1][i], multipliers[2][i], multipliers[3][i]);
  }
}
