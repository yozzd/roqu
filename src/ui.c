#include "base.h"

WINDOW * win[3];
int offset_y, offset_x;

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
