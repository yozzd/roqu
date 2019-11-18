#include "colors.h"

void color_init(void) {
  start_color();

  init_color(10, 250, 250, 250); //grey

  init_pair(1, COLOR_BLACK, COLOR_BLACK);
  init_pair(2, COLOR_WHITE, COLOR_BLACK);
  init_pair(3, 10, COLOR_BLACK);
  init_pair(4, COLOR_GREEN, COLOR_BLACK);
}
