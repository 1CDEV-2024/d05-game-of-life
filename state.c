#include <stdlib.h>
#include <time.h>

#include "gol.h"

static char NEXT_STATE[MATRIX_Y][MATRIX_X] = {{0}};

static void set_alive(vector2d_t pos) {
  cell_t *cell = &(GRID[pos.y][pos.x]);

  if (cell->state == STATE_LIVE)
    return;
  cell->state = STATE_LIVE;

  for (size_t y = pos.y - !!pos.y; y < MATRIX_Y && y < pos.y + 2; y += 1)
    for (size_t x = pos.x - !!pos.x; x < MATRIX_X && x < pos.x + 2; x += 1) {
      if (x == pos.x && y == pos.y)
        continue;
      GRID[y][x].neighbours += 1;
    }
}

static void set_dead(vector2d_t pos) {
  cell_t *cell = &(GRID[pos.y][pos.x]);

  if (cell->state == STATE_DEAD)
    return;
  cell->state = STATE_DEAD;

  for (size_t y = pos.y - !!pos.y; y < MATRIX_Y && y < pos.y + 2; y += 1)
    for (size_t x = pos.x - !!pos.x; x < MATRIX_X && x < pos.x + 2; x += 1) {
      if (x == pos.x && y == pos.y)
        continue;
      GRID[y][x].neighbours -= 1;
    }
}

void set_next_state(void) {
  vector2d_t pos = {0};
  cell_t *cell = NULL;
  char *state = NULL;

  for (pos.y = 0; pos.y < MATRIX_Y; pos.y += 1)
    for (pos.x = 0; pos.x < MATRIX_X; pos.x += 1) {
      cell = &(GRID[pos.y][pos.x]);
      state = &(NEXT_STATE[pos.y][pos.x]);

      if (cell->state == STATE_LIVE) {
        if (cell->neighbours < 2)
          *state = STATE_DEAD;
        else if (cell->neighbours <= 3)
          continue;
        else
          *state = STATE_DEAD;
      } else if (cell->neighbours == 3)
        *state = STATE_LIVE;
    }
}

void apply_next_state(void) {
  vector2d_t pos = {0};

  for (pos.y = 0; pos.y < MATRIX_Y; pos.y += 1)
    for (pos.x = 0; pos.x < MATRIX_X; pos.x += 1) {
      ((NEXT_STATE[pos.y][pos.x] == STATE_LIVE) ? set_alive : set_dead)(pos);
    }
}

void init_first_state() {
  srand(time(NULL));
  for (size_t y = 0; y < MATRIX_Y; y += 1)
    for (size_t x = 0; x < MATRIX_X; x += 1)
      NEXT_STATE[y][x] = rand() % 2;
}
