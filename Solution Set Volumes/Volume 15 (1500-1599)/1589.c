//
//  1589.c
//  hxy
//
//  Created by Fang Ling on 2024/1/16.
//

#include <stdio.h>
#include <stdbool.h>

/*===----------------------------------------------------------------------===*/
/*                                                        ___   ___           */
/* Array START                                          /'___\ /\_ \          */
/*                                                     /\ \__/ \//\ \         */
/* Author: Fang Ling (fangling@fangl.ing)              \ \ ,__\  \ \ \        */
/* Version: 1.6                                         \ \ \_/__ \_\ \_  __  */
/* Date: January 4, 2024                                 \ \_\/\_\/\____\/\_\ */
/*                                                        \/_/\/_/\/____/\/_/ */
/*===----------------------------------------------------------------------===*/

/*
 * This source file is part of the C Collections open source project
 *
 * Copyright (c) 2023 Fang Ling
 * Licensed under Apache License v2.0
 *
 * See https://github.com/fang-ling/C-Collections/blob/main/LICENSE for license
 * information
 */

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define var __auto_type

/*
 * Error code of Array:
 * 0: NO ERROR
 * 1: due to malloc, check `errno`
 * 2: Array index is out of range
 * 3: Negative Array index is out of range
 * 5: due to realloc, check `errno`
 * 6: Can't remove last element from an empty collection
 */

struct Array {
  void* _storage;
  
  /* The number of elements in the array. */
  int count;
  
  /*
   * The total number of elements that the array can contain without
   * allocating new storage.
   *
   * Every array reserves a specific amount of memory to hold its contents.
   * When you add elements to an array and that array begins to exceed its
   * reserved capacity, the array allocates a larger region of memory and
   * copies its elements into the new storage. The new storage is a multiple
   * of the old storage's size. This exponential growth strategy means that
   * appending an element happens in constant time, averaging the performance
   * of many append operations. Append operations that trigger reallocation
   * have a performance cost, but they occur less and less often as the array
   * grows larger.
   */
  int capacity;
  
  /* The size of stored Element type. */
  int element_size;
  
  /* A Boolean value indicating whether or not the array is empty. */
  bool is_empty;
};

/* MARK: - Creating and Destroying an Array */

static
int _array_init(struct Array* array, unsigned int count, int element_size) {
  /* Rounding up to next power of 2 */
  var capacity = count - 1;
  capacity |= capacity >> 1;
  capacity |= capacity >> 2;
  capacity |= capacity >> 4;
  capacity |= capacity >> 8;
  capacity |= capacity >> 16;
  capacity += 1;
  
  if (count == 0) {
    (*array)._storage = NULL;
  } else {
    (*array)._storage = malloc(capacity * element_size);
    if ((*array)._storage == NULL) {
      return 1;
    }
  }
  (*array).element_size = element_size;
  (*array).capacity = capacity;
  (*array).count = count;
  (*array).is_empty = count == 0 ? true : false;
  
  return 0;
}

/* Creates an empty array. */
static int array_init(struct Array* array, int element_size) {
  return _array_init(array, 0, element_size);
}

/* Destroys an array. */
static void array_deinit(struct Array* array) {
  free((*array)._storage);
  (*array).count = 0;
  (*array).element_size = 0;
  (*array).capacity = 0;
  (*array).is_empty = true;
}

/* MARK: - Accessing Elements */

/* Check that the specified `index` is valid, i.e. `0 ≤ index < count`. */
static int _check_index(struct Array* array, int index) {
  if (index >= (*array).count) {
    return 2;
  } else if (index < 0) {
    return 3;
  }
  return 0;
}

/* Returns the element at the specified position. */
static int array_get(struct Array* array, int index, void* element) {
  var err = _check_index(array, index);
  if (err != 0) {
    return err;
  }
  memcpy(
    element,
    (*array)._storage + (*array).element_size * index,
    (*array).element_size
  );
  return err;
}

/* Replaces the element at the specified position. */
static int array_set(struct Array* array, int index, void* element) {
  var err = _check_index(array, index);
  if (err != 0) {
    return err;
  }
  memcpy(
    (*array)._storage + (*array).element_size * index,
    element,
    (*array).element_size
  );
  return err;
}

/* MARK: - Adding Elements */

/* Adds a new element at the end of the array. */
static int array_append(struct Array* array, void* element) {
  var q = 2; /* multiple factor = 2 */
  
  if ((*array).capacity == 0) {
    (*array)._storage = realloc((*array)._storage, 1 * (*array).element_size);
    (*array).capacity = 1;
  }
  if ((*array).count == (*array).capacity) {
    (*array).capacity *= q;
    var new_size = (*array).capacity * (*array).element_size;
    (*array)._storage = realloc((*array)._storage, new_size);
    if ((*array)._storage == NULL) {
      /* FIXME: memory leak will happen if realloc failed */
      return 5;
    }
  }
  (*array).count += 1;
  (*array).is_empty = false;
  array_set(array, (*array).count - 1, element);
  
  return 0;
}

/* MARK: - Removing Elements */

/* Removes all the elements. */
static int array_remove_all(struct Array* array) {
  free((*array)._storage);
  (*array)._storage = NULL;
  (*array).count = 0;
  (*array).capacity = 0;
  (*array).is_empty = true;
  
  return 0;
}

/*===----------------------------------------------------------------------===*/
/*             ___                            ___                             */
/*           /'___\                          /\_ \    __                      */
/*          /\ \__/   __      ___      __    \//\ \  /\_\    ___      __      */
/*          \ \ ,__\/'__`\  /' _ `\  /'_ `\    \ \ \ \/\ \ /' _ `\  /'_ `\    */
/*           \ \ \_/\ \L\.\_/\ \/\ \/\ \L\ \    \_\ \_\ \ \/\ \/\ \/\ \L\ \   */
/*            \ \_\\ \__/.\_\ \_\ \_\ \____ \   /\____\\ \_\ \_\ \_\ \____ \  */
/*             \/_/ \/__/\/_/\/_/\/_/\/___L\ \  \/____/ \/_/\/_/\/_/\/___L\ \ */
/* Array END                           /\____/                        /\____/ */
/*                                     \_/__/                         \_/__/  */
/*===----------------------------------------------------------------------===*/


#define var __auto_type
#define ROW 10
#define COL 9

static void init_board_1589(char* board) {
  var count = ROW * COL;
  var i = 0;
  for (i = 0; i < count; i += 1) {
    board[i] = ' ';
  }
}

void main_1589(void) {
  char board[ROW * COL];
  char p[2];
  struct Array layer;
  array_init(&layer, sizeof(char*));
  
  while (true) {
    var n = 0;
    scanf("%d", &n);
    var bg_x = 0;
    var bg_y = 0;
    scanf("%d %d", &bg_x, &bg_y);
    bg_x -= 1;
    bg_y -= 1;
    if (n == 0 && bg_x == -1 && bg_y == -1) {
      break;
    }
    var i = 0;
    for (i = 0; i < layer.count; i += 1) {
      char* delta;
      array_get(&layer, i, &delta);
      free(delta);
    }
    /* Init board & layer */
    array_remove_all(&layer);
    init_board_1589(board);
    
    for (i = 0; i < n; i += 1) {
      scanf("%s", p);
      var x = 0;
      var y = 0;
      scanf("%d %d", &x, &y);
      board[(x - 1) * COL + (y - 1)] = p[0];
    }
    /* Mark forbidden region */
    var is_win = true;
    for (i = 0; i < ROW; i += 1) {
      var j = 0;
      for (j = 0; j < COL; j += 1) {
        if (board[i * COL + j] == 'G') {
          var is_piece_between_gens = false;
          /* Check if there is a piece between two generals */
          var k = 0;
          for (k = i; k > bg_x; k -= 1) {
            if (
              board[k * COL + j] != ' ' && board[k * COL + j] != 'X' &&
              board[k * COL + j] != 'B' && board[k * COL + j] != 'G'
            ) {
              is_piece_between_gens = true;
              var ll = (char*)malloc(ROW * COL);
              init_board_1589(ll);
              var kk = 0;
              for (kk = i; kk >= k; kk -= 1) {
                ll[kk * COL + j] = 'X';
              }
              array_append(&layer, &ll);
              break;
            }
          }
          if (!is_piece_between_gens) {
            /* Special case: if two generals can see each other */
            if (bg_y == j) {
              is_win = false;
              break;
            }
            var ll = (char*)malloc(ROW * COL);
            init_board_1589(ll);
            for (k = i; k >= 0; k -= 1) {
              ll[k * COL + j] = 'X';
            }
            array_append(&layer, &ll);
          }
        } else if (board[i * COL + j] == 'R') {
          var ll = (char*)malloc(ROW * COL);
          init_board_1589(ll);
          /* From chariot down */
          var k = 0;
          for (k = i + 1; k < ROW; k += 1) {
            if (board[k * COL + j] == ' ') {
              ll[k * COL + j] = 'X';
            } else if (
              board[k * COL + j] == 'G' || board[k * COL + j] == 'R' ||
              board[k * COL + j] == 'C' || board[k * COL + j] == 'H'
            ) {
              ll[k * COL + j] = 'X';
              break;
            }
          }
          /* From chariot up */
          for (k = i - 1; k >= 0; k -= 1) {
            if (board[k * COL + j] == ' ') {
              ll[k * COL + j] = 'X';
            } else if (
              board[k * COL + j] == 'G' || board[k * COL + j] == 'R' ||
              board[k * COL + j] == 'C' || board[k * COL + j] == 'H'
            ) {
              ll[k * COL + j] = 'X';
              break;
            }
          }
          /* From chariot left */
          for (k = j - 1; k >= 0; k -= 1) {
            if (board[i * COL + k] == ' ') {
              ll[i * COL + k] = 'X';
            } else if (
              board[i * COL + k] == 'G' || board[i * COL + k] == 'R' ||
              board[i * COL + k] == 'C' || board[i * COL + k] == 'H'
            ) {
              ll[i * COL + k] = 'X';
              break;
            }
          }
          /* From chariot right */
          for (k = j + 1; k < COL; k += 1) {
            if (board[i * COL + k] == ' ') {
              ll[i * COL + k] = 'X';
            } else if (
              board[i * COL + k] == 'G' || board[i * COL + k] == 'R' ||
              board[i * COL + k] == 'C' || board[i * COL + k] == 'H'
            ) {
              ll[i * COL + k] = 'X';
              break;
            }
          }
          array_append(&layer, &ll);
        } else if (board[i * COL + j] == 'H') {
          var ll = (char*)malloc(ROW * COL);
          init_board_1589(ll);
          if (
            j + 2 < COL &&
            (board[i * COL + j + 1] == ' ' || board[i * COL + j + 1] == 'X')
          ) {
            if (i - 1 >= 0) {
              ll[(i - 1) * COL + j + 2] = 'X';
            }
            if (i + 1 < ROW) {
              ll[(i + 1) * COL + j + 2] = 'X';
            }
          }
          if (
            i - 2 >= 0 &&
            (board[(i - 1) * COL + j] == ' ' || board[(i - 1) * COL + j] == 'X')
          ) {
            if (j - 1 >= 0) {
              ll[(i - 2) * COL + j - 1] = 'X';
            }
            if (j + 1 < COL) {
              ll[(i - 2) * COL + j + 1] = 'X';
            }
          }
          if (
            j - 2 >= 0 &&
            (board[i * COL + j - 1] == ' ' || board[i * COL + j - 1] == 'X')
          ) {
            if (i - 1 >= 0) {
              ll[(i - 1) * COL + j - 2] = 'X';
            }
            if (i + 1 < ROW) {
              ll[(i + 1) * COL + j - 2] = 'X';
            }
          }
          if (
            i + 2 < ROW &&
            (board[(i + 1) * COL + j] == ' ' || board[(i + 1) * COL + j] == 'X')
          ) {
            if (j - 1 >= 0) {
              ll[(i + 2) * COL + j - 1] = 'X';
            }
            if (j + 1 < COL) {
              ll[(i + 2) * COL + j + 1] = 'X';
            }
          }
          array_append(&layer, &ll);
        } else if (board[i * COL + j] == 'C') {
          var ll = (char*)malloc(ROW * COL);
          init_board_1589(ll);
          /* Down */
          var is_behind_cannon = false;
          var bet_x = 0;
          var bet_y = 0;
          var k = 0;
          for (k = i + 1; k < ROW; k += 1) {
            if (board[k * COL + j] != ' ' && board[k * COL + j] != 'X') {
              bet_x = k;
              bet_y = j;
              is_behind_cannon = true;
              break;
            }
          }
          var bet2_x = 0;
          var bet2_y = 0;
          var is_behind_behind_cannon = false;
          for (k = bet_x + 1; k < ROW; k += 1) {
            if (board[k * COL + j] != ' ' && board[k * COL + j] != 'X') {
              bet2_x = k;
              bet2_y = j;
              is_behind_behind_cannon = true;
              break;
            }
          }
          if (is_behind_cannon && is_behind_behind_cannon) {
            for (k = bet_x + 1; k < bet2_x; k += 1) {
              if (board[k * COL + j] == ' ') {
                ll[k * COL + j] = 'X';
              }
            }
          }
          if (is_behind_cannon && !is_behind_behind_cannon) {
            for (k = bet_x + 1; k < ROW; k += 1) {
              if (board[k * COL + j] == ' ') {
                ll[k * COL + j] = 'X';
              }
            }
          }
          /* Up */
          is_behind_cannon = false;
          for (k = i - 1; k >= 0; k -= 1) {
            if (board[k * COL + j] != ' ' && board[k * COL + j] != 'X') {
              bet_x = k;
              bet_y = j;
              is_behind_cannon = true;
              break;
            }
          }
          is_behind_behind_cannon = false;
          for (k = bet_x - 1; k >= 0; k -= 1) {
            if (board[k * COL + j] != ' ' && board[k * COL + j] != 'X') {
              bet2_x = k;
              bet2_y = j;
              is_behind_behind_cannon = true;
              break;
            }
          }
          if (is_behind_cannon && is_behind_behind_cannon) {
            for (k = bet_x - 1; k > bet2_x; k -= 1) {
              if (board[k * COL + j] == ' ') {
                ll[k * COL + j] = 'X';
              }
            }
          }
          if (is_behind_cannon && !is_behind_behind_cannon) {
            for (k = bet_x - 1; k >= 0; k -= 1) {
              if (board[k * COL + j] == ' ') {
                ll[k * COL + j] = 'X';
              }
            }
          }
          /* Right */
          is_behind_cannon = false;
          for (k = j + 1; k < COL; k += 1) {
            if (board[i * COL + k] != ' ' && board[i * COL + k] != 'X') {
              bet_x = i;
              bet_y = k;
              is_behind_cannon = true;
              break;
            }
          }
          is_behind_behind_cannon = false;
          for (k = bet_y + 1; k < COL; k += 1) {
            if (board[i * COL + k] != ' ' && board[i * COL + k] != 'X') {
              bet2_x = i;
              bet2_y = k;
              is_behind_behind_cannon = true;
              break;
            }
          }
          if (is_behind_cannon && is_behind_behind_cannon) {
            for (k = bet_y + 1; k < bet2_y; k += 1) {
              if (board[i * COL + k] == ' ') {
                ll[i * COL + k] = 'X';
              }
            }
          }
          if (is_behind_cannon && !is_behind_behind_cannon) {
            for (k = bet_y + 1; k < COL; k += 1) {
              if (board[i * COL + k] == ' ') {
                ll[i * COL + k] = 'X';
              }
            }
          }
          /* Left */
          is_behind_cannon = false;
          for (k = j - 1; k >= 0; k -= 1) {
            if (board[i * COL + k] != ' ' && board[i * COL + k] != 'X') {
              bet_x = i;
              bet_y = k;
              is_behind_cannon = true;
              break;
            }
          }
          is_behind_behind_cannon = false;
          for (k = bet_y - 1; k >= 0; k -= 1) {
            if (board[i * COL + k] != ' ' && board[i * COL + k] != 'X') {
              bet2_x = i;
              bet2_y = k;
              is_behind_behind_cannon = true;
              break;
            }
          }
          if (is_behind_cannon && is_behind_behind_cannon) {
            for (k = bet_y - 1; k > bet2_y; k -= 1) {
              if (board[i * COL + k] == ' ') {
                ll[i * COL + k] = 'X';
              }
            }
          }
          if (is_behind_cannon && !is_behind_behind_cannon) {
            for (k = bet_y - 1; k >= 0; k -= 1) {
              if (board[i * COL + k] == ' ') {
                ll[i * COL + k] = 'X';
              }
            }
          }
          array_append(&layer, &ll);
        }
      }
    }
    if (!is_win) {
      printf("NO\n");
    } else {
      is_win = false;
      if (bg_x == 1 - 1 && bg_y == 4 - 1) {
        char* l;
        var li = 0;
        for (li = 0; li < layer.count; li += 1) {
          array_get(&layer, li, &l);
          if (l[(2 - 1) * COL + (4 - 1)] == 'X') {
            char* j;
            var ji = 0;
            for (ji = 0; ji < layer.count; ji += 1) {
              array_get(&layer, ji, &j);
              if (j[(1 - 1) * COL + (5 - 1)] == 'X') {
                is_win = true;
              }
            }
          }
        }
      } else if (bg_x == 2 - 1 && bg_y == 4 - 1) {
        char* l;
        var li = 0;
        for (li = 0; li < layer.count; li += 1) {
          array_get(&layer, li, &l);
          if (l[(3 - 1) * COL + (4 - 1)] == 'X') {
            char* j;
            var ji = 0;
            for (ji = 0; ji < layer.count; ji += 1) {
              array_get(&layer, ji, &j);
              if (j[(2 - 1) * COL + (5 - 1)] == 'X') {
                char* k;
                var ki = 0;
                for (ki = 0; ki < layer.count; ki += 1) {
                  array_get(&layer, ki, &k);
                  if (k[(1 - 1) * COL + (4 - 1)] == 'X') {
                    is_win = true;
                  }
                }
              }
            }
          }
        }
      } else if (bg_x == 3 - 1 && bg_y == 4 - 1) {
        char* l;
        var li = 0;
        for (li = 0; li < layer.count; li += 1) {
          array_get(&layer, li, &l);
          if (l[(2 - 1) * COL + (4 - 1)] == 'X') {
            char* j;
            var ji = 0;
            for (ji = 0; ji < layer.count; ji += 1) {
              array_get(&layer, ji, &j);
              if (j[(3 - 1) * COL + (5 - 1)] == 'X') {
                is_win = true;
              }
            }
          }
        }
      } else if (bg_x == 1 - 1 && bg_y == 5 - 1) {
        char* l;
        var li = 0;
        for (li = 0; li < layer.count; li += 1) {
          array_get(&layer, li, &l);
          if (l[(1 - 1) * COL + (4 - 1)] == 'X') {
            char* j;
            var ji = 0;
            for (ji = 0; ji < layer.count; ji += 1) {
              array_get(&layer, ji, &j);
              if (j[(1 - 1) * COL + 6 - 1] == 'X') {
                char* k;
                var ki = 0;
                for (ki = 0; ki < layer.count; ki += 1) {
                  array_get(&layer, ki, &k);
                  if (k[(2 - 1) * COL + 5 - 1] == 'X') {
                    is_win = true;
                  }
                }
              }
            }
          }
        }
      } else if (bg_x == 2 - 1 && bg_y == 5 - 1) {
        char* l;
        var li = 0;
        for (li = 0; li < layer.count; li += 1) {
          array_get(&layer, li, &l);
          if (l[(2 - 1) * COL + 4 - 1] == 'X') {
            char* j;
            var ji = 0;
            for (ji = 0; ji < layer.count; ji += 1) {
              array_get(&layer, ji, &j);
              if (j[(2 - 1) * COL + 6 - 1] == 'X') {
                char* k;
                var ki = 0;
                for (ki = 0; ki < layer.count; ki += 1) {
                  array_get(&layer, ki, &k);
                  if (k[(3 - 1) * COL + 5 - 1] == 'X') {
                    char* m;
                    var mi = 0;
                    for (mi = 0; mi < layer.count; mi += 1) {
                      array_get(&layer, mi, &m);
                      if (m[(1 - 1) * COL + 5 - 1] == 'X') {
                        is_win = true;
                      }
                    }
                  }
                }
              }
            }
          }
        }
      } else if (bg_x == 3 - 1 && bg_y == 5 - 1) {
        char* l;
        var li = 0;
        for (li = 0; li < layer.count; li += 1) {
          array_get(&layer, li, &l);
          if (l[(3 - 1) * COL + 4 - 1] == 'X') {
            char* j;
            var ji = 0;
            for (ji = 0; ji < layer.count; ji += 1) {
              array_get(&layer, ji, &j);
              if (j[(3 - 1) * COL + 6 - 1] == 'X') {
                char* k;
                var ki = 0;
                for (ki = 0; ki < layer.count; ki += 1) {
                  array_get(&layer, ki, &k);
                  if (k[(2 - 1) * COL + 5 - 1] == 'X') {
                    is_win = true;
                  }
                }
              }
            }
          }
        }
      } else if (bg_x == 1 - 1 && bg_y == 6 - 1) {
        char* l;
        var li = 0;
        for (li = 0; li < layer.count; li += 1) {
          array_get(&layer, li, &l);
          if (l[(1 - 1) * COL + 5 - 1] == 'X') {
            char* j;
            var ji = 0;
            for (ji = 0; ji < layer.count; ji += 1) {
              array_get(&layer, ji, &j);
              if (j[(2 - 1) * COL + 6 - 1] == 'X') {
                is_win = true;
              }
            }
          }
        }
      } else if (bg_x == 2 - 1 && bg_y == 6 - 1) {
        char* l;
        var li = 0;
        for (li = 0; li < layer.count; li += 1) {
          array_get(&layer, li, &l);
          if (l[(1 - 1) * COL + 6 - 1] == 'X') {
            char* j;
            var ji = 0;
            for (ji = 0; ji < layer.count; ji += 1) {
              array_get(&layer, ji, &j);
              if (j[(2 - 1) * COL + 5 - 1] == 'X') {
                char* k;
                var ki = 0;
                for (ki = 0; ki < layer.count; ki += 1) {
                  array_get(&layer, ki, &k);
                  if (k[(3 - 1) * COL + 6 - 1] == 'X') {
                    is_win = true;
                  }
                }
              }
            }
          }
        }
      } else if (bg_x == 3 - 1 && bg_y == 6 - 1) {
        char* l;
        var li = 0;
        for (li = 0; li < layer.count; li += 1) {
          array_get(&layer, li, &l);
          if (l[(2 - 1) * COL + 6 - 1] == 'X') {
            char* j;
            var ji = 0;
            for (ji = 0; ji < layer.count; ji += 1) {
              array_get(&layer, ji, &j);
              if (j[(3 - 1) * COL + 5 - 1] == 'X') {
                is_win = true;
              }
            }
          }
        }
      }
      if (is_win) {
        printf("YES\n");
      } else {
        printf("NO\n");
      }
    }
  }
  
  array_deinit(&layer);
}
