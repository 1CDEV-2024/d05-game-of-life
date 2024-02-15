#ifndef GOL_H
#define GOL_H

#include <stddef.h>

#ifdef _WIN32
#include <conio.h>
#else
#include <stdio.h>
#define clrscr() printf("\e[1;1H\e[2J")
#endif

typedef enum {
  STATE_DEAD = 0,
  STATE_LIVE = 1,
} state_t;

typedef enum {
  CHAR_DEAD = ' ',
  CHAR_LIVE = 'o',
} char_t;

typedef struct {
  state_t state;
  size_t neighbours;
} cell_t;

typedef struct {
  size_t x;
  size_t y;
} vector2d_t;

#define Vector2D(...) ((vector2d_t){__VA_ARGS__})

#define MAX_NEIGHBOURS 8

#define MATRIX_Y 30
#define MATRIX_X MATRIX_Y * 4

extern cell_t GRID[MATRIX_Y][MATRIX_X];

void set_next_state(void);
void apply_next_state(void);
void init_first_state(void);

#endif // GOL_H
