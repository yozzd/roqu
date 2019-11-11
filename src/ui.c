#include "base.h"
#include "map.h"
#include "player.h"

WINDOW * win[3];
int offset_y, offset_x;

static void viewport_ui(int cy, int cx) {
  uint32_t vy, vx;

  vy = cy - ((W1_NLINES - 2) / 2);

  for (uint8_t dy = 1; dy < (W1_NLINES - 1); dy++) {
    vx = cx - ((W1_NCOLS - 2) / 2);
    for (uint8_t dx = 1; dx < (W1_NCOLS - 1); dx++) {
      mvwprintw(win[0], dy, dx, "%lc", print_map(vy, vx));
      vx++;
    }
    vy++;
  }
}

void update_ui(void) {
  werase(win[0]);
  werase(win[1]);
  werase(win[2]);

  wborder(win[0], 0, 0, 0, 0, 0, 0, 0, 0);
  wborder(win[1], 0, 0, 0, 0, 0, 0, 0, 0);
  wborder(win[2], 0, 0, 0, 0, 0, 0, 0, 0);
  mvwprintw(win[2], 1, 1, "Log");

  viewport_ui(p->vy, p->vx);

  wrefresh(win[0]);
  wrefresh(win[1]);
  wrefresh(win[2]);
}

void init_ui(void) {
  setlocale(LC_ALL, "");
  initscr();
  cbreak();
  noecho();
  curs_set(0);
  nonl();

  offset_y = (LINES - NLINES) / 2;
  offset_x = (COLS - NCOLS) / 2;

  win[0] = newwin(W1_NLINES, W1_NCOLS, offset_y, offset_x);
  win[1] = newwin(W2_NLINES, W2_NCOLS, offset_y, offset_x + W1_NCOLS);
  win[2] = newwin(W3_NLINES, W3_NCOLS, offset_y + W1_NLINES, offset_x);

  keypad(win[0], true);
}
