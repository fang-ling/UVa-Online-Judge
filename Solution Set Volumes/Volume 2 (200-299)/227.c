//
//  227.c
//  hxy
//
//  Created by Fang Ling on 2023/12/3.
//

/*
 * We define some helper functions:
 * - Find the position of the space character.
 * - The square around the empty position moves, if not possbile, return false.
 *
 * Be careful about the output format and getchar().
 */

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

#define var __auto_type

#define N 5

static void find_space_227(char puzzle[N][N], int* i, int* j) {
  for (*i = 0; *i < N; *i += 1) {
    for (*j = 0; *j < N; *j += 1) {
      if (puzzle[*i][*j] == ' ') {
        return;
      }
    }
  }
}

static bool above_move_227(char puzzle[N][N], int i, int j) {
  if (i < 1) {
    return false;
  }
  puzzle[i][j] = puzzle[i - 1][j];
  puzzle[i - 1][j] = ' ';
  return true;
}

static bool below_move_227(char puzzle[N][N], int i, int j) {
  if (i > (N - 1) - 1) {
    return false;
  }
  puzzle[i][j] = puzzle[i + 1][j];
  puzzle[i + 1][j] = ' ';
  return true;
}

static bool left_move_227(char puzzle[N][N], int i, int j) {
  if (j < 1) {
    return false;
  }
  puzzle[i][j] = puzzle[i][j - 1];
  puzzle[i][j - 1] = ' ';
  return true;
}

static bool right_move_227(char puzzle[N][N], int i, int j) {
  if (j > (N - 1) - 1) {
    return false;
  }
  puzzle[i][j] = puzzle[i][j + 1];
  puzzle[i][j + 1] = ' ';
  return true;
}

void main_227(void) {
  char delta[N + 1 + 1];
  char puzzle[N][N];
  var is_first = true;
  var puzzle_num = 0;

  while (true) {
    var is_ok = true;

    var i = 0;
    /* Read the puzzle */
    for (i = 0; i < N; i += 1) {
      var line_i = 0;
      while (true) {
        var c = getchar();
        delta[line_i] = c;
        line_i += 1;
        if (c == '\n') {
          break;
        }
      }
      if (delta[0] == 'Z') { /* we reach the end of input */
        return;
      }
      var j = 0;
      for (j = 0; j < N; j += 1) {
        puzzle[i][j] = delta[j];
      }
    }
    /* Read move instructions */
    while (true) {
      char inst;
      scanf("%c", &inst);

      if (inst == '0') {
        getchar(); /* Read the new line character */
        break;
      } else if (inst == '\n' || inst == 'A' || inst == 'B' || inst == 'L') {
        /* Do nothing. */
      } else if (inst == 'R') {
        /* Do nothing. */
      } else {
        is_ok = false; /* illegal move instruction */
      }

      if (is_ok) { /* Only perform move instructions when ok */
        /* find space character */
        var r = 0;
        var c = 0;
        find_space_227(puzzle, &r, &c);
        if (inst == 'A') {
          if (!above_move_227(puzzle, r, c)) {
            is_ok = false;
          }
        } else if (inst == 'B') {
          if (!below_move_227(puzzle, r, c)) {
            is_ok = false;
          }
        } else if (inst == 'L') {
          if (!left_move_227(puzzle, r, c)) {
            is_ok = false;
          }
        } else if (inst == 'R') {
          if (!right_move_227(puzzle, r, c)) {
            is_ok = false;
          }
        }
      }
    }

    if (!is_first) {
      printf("\n");
    }
    is_first = false;
    puzzle_num += 1;
    printf("Puzzle #%d:\n", puzzle_num);
    if (!is_ok) {
      printf("This puzzle has no final configuration.\n");
      continue;
    }
    for (i = 0; i < N; i += 1) {
      var j = 0;
      for (j = 0; j < N; j += 1) {
        printf("%c", puzzle[i][j]);
        printf(j == 4 ? "" : " ");
      }
      printf("\n");
    }
  }
}
