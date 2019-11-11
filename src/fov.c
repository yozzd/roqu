#include "base.h"
#include "map.h"

static int multipliers[4][8] = {
  {1, 0, 0, -1, -1, 0, 0, 1},
  {0, 1, -1, 0, 0, -1, 1, 0},
  {0, 1, 1, 0, 0, -1, -1, 0},
  {1, 0, 0, 1, -1, 0, 0, -1}
};

void cast_light(uint8_t x, uint8_t y, uint8_t radius, uint8_t row, float start_slope,
    float end_slope, int8_t xx, int8_t xy, int8_t yx, int8_t yy) {

  if (start_slope < end_slope) return;

  float next_start_slope = start_slope;
  for (uint8_t i = row; i <= radius; i++) {
    bool blocked = false;
    for (int8_t dx = -i, dy = -i; dx <= 0; dx++) {
      float l_slope = (dx - 0.5) / (dy + 0.5);
      float r_slope = (dx + 0.5) / (dy - 0.5);

      if (start_slope < r_slope) continue;
      else if (end_slope > l_slope) break;

      int8_t sax = dx * xx + dy * xy;
      int8_t say = dx * yx + dy * yy;

      if ((sax < 0 && (int8_t) abs(sax) > x) || (say < 0 && (int8_t) abs(say) > y)) continue;

      uint8_t ax = x + sax;
      uint8_t ay = y + say;

      if (ax >= WIDTH || ay >= HEIGHT) continue;

      uint8_t radius2 = radius * radius;
      if ((int8_t) (dx * dx + dy * dy) < radius2) {
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

void fov(uint8_t x, uint8_t y, uint8_t radius) {
  reset_grid_visibility();
  for (uint8_t i = 0; i < 8; i++) {
    cast_light(x, y, radius, 1, 1.0, 0.0, multipliers[0][i],
        multipliers[1][i], multipliers[2][i], multipliers[3][i]);
  }
}
