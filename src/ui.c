#include "base.h"
#include "map.h"
#include "player.h"
#include "colors.h"

WINDOW * win[3];
uint8_t offset_y, offset_x;


void keymap(void) {
  int c = wgetch(win[0]);

  if (c == 'q') p->quit = true;
  else if(c =='j') move_player(p->y, p->x, 1, 0);
  else if(c =='k') move_player(p->y, p->x, -1, 0);
  else if(c =='h') move_player(p->y, p->x, 0, -1);
  else if(c =='l') move_player(p->y, p->x, 0, 1);
}

void shutdown_ui(void) {
  free_player();
  free_map();

  delwin(win[0]);
  delwin(win[1]);
  delwin(win[2]);

  endwin();
}

static void viewport_ui(int cy, int cx) {
  uint8_t vy, vx;

  vy = cy - ((W1_NLINES - 2) / 2);

  for (uint8_t dy = 1; dy < (W1_NLINES - 1); dy++) {
    vx = cx - ((W1_NCOLS - 2) / 2);
    for (uint8_t dx = 1; dx < (W1_NCOLS - 1); dx++) {
      wattron(win[0], COLOR_PAIR(m->gr[vy * WIDTH + vx]->co));
      mvwprintw(win[0], dy, dx, "%lc", print_map(vy, vx));
      wattroff(win[0], COLOR_PAIR(m->gr[vy * WIDTH + vx]->co));
      vx++;
    }
    vy++;
  }
}

void update_ui(void) {
  werase(win[0]);
  werase(win[1]);
  werase(win[2]);

  color_init();

  mvwprintw(win[2], 1, 1, "y=%d,x=%d",p->y,p->x);

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
