//
//  101.c
//  hxy
//
//  Created by Fang Ling on 2024/2/25.
//

#include <stdio.h>

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

/* Removes the last element of the collection. */
static int array_remove_last(struct Array* array) {
  var q1 = 4;
  var q2 = 2;

  if ((*array).is_empty) {
    return 6;
  }
  (*array).count -= 1;
  if ((*array).count == 0) {
    (*array).is_empty = true;
  }
  if ((*array).count * q1 <= (*array).capacity) {
    (*array).capacity /= q2;
    var new_size = (*array).capacity * (*array).element_size;
    (*array)._storage = realloc((*array)._storage, new_size);
    if ((*array)._storage == NULL) {
      /* FIXME: memory leak will happen if realloc failed */
      return 5;
    }
  }

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

/* res[0] = position, res[1] = height */
static void find_block(struct Array* table, int n, int block, int* res) {
  var i = 0;
  for (i = 0; i < n; i += 1) {
    var j = 0;
    for (j = 0; j < table[i].count; j += 1) {
      if (((int*)table[i]._storage)[j] == block) {
        res[0] = i;
        res[1] = j;
        return;
      }
    }
  }
}

/* Move any blocks that are stacked on top of block to its initial position. */
static void clean_up(struct Array* table, int n, int block) {
  int res[2]; /* res[0] = position, res[1] = height */
  find_block(table, n, block, res);
  struct Array removed;
  array_init(&removed, sizeof(int));
  
  var i = 0;
  var count = table[res[0]].count;
  for (i = res[1] + 1; i < count; i += 1) {
    var a = -1;
    array_get(&table[res[0]], table[res[0]].count - 1, &a);
    array_remove_last(&table[res[0]]);
    array_append(&removed, &a);
  }
  
  for (i = 0; i < removed.count; i += 1) {
    var a = -1;
    array_get(&removed, i, &a);
    array_append(&table[a], &a);
  }
  
  array_deinit(&removed);
}

/* Move a and any blocks that are stacked on top of a to the top of b. */
static void move_on_top_of(struct Array* table, int n, int a, int b) {
  int res[2]; /* res[0] = position, res[1] = height */
  find_block(table, n, a, res);
  struct Array removed;
  array_init(&removed, sizeof(int));
  
  var i = 0;
  var count = table[res[0]].count;
  for (i = res[1]/* + 1*/; i < count; i += 1) {
    var delta = -1;
    array_get(&table[res[0]], i, &delta);
    array_append(&removed, &delta);
  }
  for (i = res[1]; i < count; i += 1) {
    array_remove_last(&table[res[0]]);
  }
  
  find_block(table, n, b, res);
  for (i = 0; i < removed.count; i += 1) {
    var delta = -1;
    array_get(&removed, i, &delta);
    array_append(&table[res[0]], &delta);
  }
  
  array_deinit(&removed);
}

void main_101(void) {
  char cmd[8];
  char pl[8];
  int res[2][2];
  struct Array table[25];
  
  var n = 0;
  scanf("%d", &n);
  
  var i = 0;
  for (i = 0; i < n; i += 1) {
    array_init(&table[i], sizeof(int));
    array_append(&table[i], &i);
  }
  
  while (scanf("%s", cmd) == 1 && cmd[0] != 'q') {
    var a = 0;
    var b = 0;
    scanf("%d %s %d", &a, pl, &b);
    if (a == b) {
      continue;
    }
    find_block(table, n, a, res[0]);
    find_block(table, n, b, res[1]);
    if (res[0][0] == res[1][0]) {
      continue;
    }
    if (cmd[0] == 'm' && cmd[1] == 'o') {
      clean_up(table, n, a);
      if (pl[0] == 'o' && pl[1] == 'n') {
        clean_up(table, n, b);
      }
    } else {
      if (pl[0] == 'o' && pl[1] == 'n') {
        clean_up(table, n, b);
      }
    }
    move_on_top_of(table, n, a, b);
  }
  
  for (i = 0; i < n; i += 1) {
    printf("%d:", i);
    var j = 0;
    for (j = 0; j < table[i].count; j += 1) {
      var a = 0;
      array_get(&table[i], j, &a);
      printf(" %d", a);
    }
    printf("\n");
  }
  
  for (i = 0; i < n; i += 1) {
    array_deinit(&table[i]);
  }
}
