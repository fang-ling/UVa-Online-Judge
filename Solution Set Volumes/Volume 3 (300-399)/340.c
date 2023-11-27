//
//  340.c
//  hxy
//
//  Created by Fang Ling on 2023/11/27.
//

/*
 * To solve the MasterMind problem and determine the hint, you compare the
 * secret code and the guess element by element. If they match in both value
 * and position, you count it as a strong match. If they match in value but not
 * position, you count it as a weak match. By iterating through the code and
 * guess and tracking the number of strong and weak matches, you can calculate
 * the hint.
 */

/*===----------------------------------------------------------------------===*/
/*                                                        ___   ___           */
/* Array START                                          /'___\ /\_ \          */
/*                                                     /\ \__/ \//\ \         */
/* Author: Fang Ling                                   \ \ ,__\  \ \ \        */
/* Version: 1.0                                         \ \ \_/__ \_\ \_  __  */
/* Date: November 27, 2023                               \ \_\/\_\/\____\/\_\ */
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

#include <stdio.h>

#define var __auto_type

int count_correct_position_340(struct Array* target, struct Array* array) {
  var result = 0;
  var alpha = 0;
  var beta = 0;
  
  var i = 0;
  for (; i < (*target).count; i += 1) {
    array_get(target, i, &alpha);
    array_get(array, i, &beta);
    if (alpha == beta) {
      result += 1;
    }
  }
  
  return result;
}

int count_appreance_340(struct Array* target, struct Array* array) {
  var result = 0;
  var result_t = 0;
  var result_a = 0;
  var alpha = 0;
  
  var i = 0;
  for (i = 1; i <= 9; i += 1) {
    result_t = 0;
    result_a = 0;
    
    var j = 0;
    for (; j < (*target).count; j += 1) {
      array_get(target, j, &alpha);
      if (i == alpha) {
        result_t += 1;
      }
    }
    for (j = 0; j < (*array).count; j += 1) {
      array_get(array, j, &alpha);
      if (i == alpha) {
        result_a += 1;
      }
    }
    result += result_t < result_a ? result_t : result_a;
  }
  
  return result;
}

void main_340(void) {
  struct Array array;
  struct Array target;
  array_init(&array, sizeof(int));
  array_init(&target, sizeof(int));
  
  var n = 0;
  var game_cnt = 1;
  var delta = 0;
  var i = 0;
  while (true) {
    array_remove_all(&target);
    scanf("%d", &n);
    if (n == 0) {
      break;
    }
    for (i = 0; i < n; i += 1) {
      scanf("%d", &delta);
      array_append(&target, &delta);
    }
    
    printf("Game %d:\n", game_cnt);
    game_cnt += 1;
    
    while (true) {
      array_remove_all(&array);
      for (i = 0; i < n; i += 1) {
        scanf("%d", &delta);
        array_append(&array, &delta);
      }
      if (delta == 0) { /* all-zero */
        break;
      }
      delta = count_correct_position_340(&target, &array);
      printf(
        "    (%d,%d)\n", 
        delta,
        count_appreance_340(&target, &array) - delta
      );
    }
  }
  
  array_deinit(&array);
  array_deinit(&target);
}
