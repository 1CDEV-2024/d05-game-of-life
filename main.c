#include <stdio.h>
#include <threads.h>
#include <unistd.h>

#include "gol.h"

cell_t GRID[MATRIX_Y][MATRIX_X] = {{0}};

static void print(void) {
  static char buffer[MATRIX_Y][MATRIX_X + 1] = {0};

  clrscr();
  for (size_t y = 0; y < MATRIX_Y; y += 1) {
    for (size_t x = 0; x < MATRIX_X; x += 1)
      buffer[y][x] = GRID[y][x].state == STATE_LIVE ? CHAR_LIVE : CHAR_DEAD;
    buffer[y][MATRIX_X] = '\0';
    printf("%s\n", buffer[y]);
  }
}

int main(void) {
  init_first_state();
  while (1) {
    apply_next_state();
    print();
    set_next_state();
    sleep(1);
  }
}
