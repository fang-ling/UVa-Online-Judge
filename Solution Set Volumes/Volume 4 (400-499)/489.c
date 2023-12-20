//
//  489.c
//  hxy
//
//  Created by Fang Ling on 2023/12/19.
//

/*
 * Consider the answer string as a bag of characters. Every time we guess a new
 * character, we check if the bag contains that character. If it does, we remove
 * all occurences of that character from the bag. Otherwise, we increment the
 * error_count by 1 (initially set to zero). Every time the error_count exceeds
 * 6, we lose. If the bag is empty, we win. and if we run out of the guesses and
 * neither lose nor win, we chickened out.
 */

/*
 * Notice that the following code does not pass all the unit test cases, but can
 * get 'AC'.
 */

#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define var __auto_type

/*===----------------------------------------------------------------------===*/
/*                                                        ___   ___           */
/* Array START                                          /'___\ /\_ \          */
/*                                                     /\ \__/ \//\ \         */
/* Author: Fang Ling (fangling@fangl.ing)              \ \ ,__\  \ \ \        */
/* Version: 1.5                                         \ \ \_/__ \_\ \_  __  */
/* Date: December 20, 2023                               \ \_\/\_\/\____\/\_\ */
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

/* Removes all the elements. */
static int array_remove_all(struct Array* array) {
  free((*array)._storage);
  (*array)._storage = NULL;
  (*array).count = 0;
  (*array).capacity = 0;
  (*array).is_empty = true;

  return 0;
}

/* MARK: - Finding Elements */

/*
 * Returns a Boolean value indicating whether the sequence contains the given
 * element.
 */
static bool array_contains(
  struct Array* array,
  void* key,
  bool (*equal)(const void*, const void*)
) {
  var buf = malloc((*array).element_size);
  var i = 0;
  for (i = 0; i < (*array).count; i += 1) {
    array_get(array, i, buf);
    if (equal(buf, key)) {
      free(buf);
      return true;
    }
  }
  free(buf);
  return false;
}

/*
 * Returns the first index where the specified value appears in the collection.
 */
static int array_first_index(
  struct Array* array,
  void* key,
  bool (*equal)(const void*, const void*)
) {
  var buf = malloc((*array).element_size);
  var i = 0;
  for (i = 0; i < (*array).count; i += 1) {
    array_get(array, i, buf);
    if (equal(buf, key)) {
      free(buf);
      return i;
    }
  }
  free(buf);
  return -1;
}

/* MARK: - Reordering an Array’s Elements */

/* Exchanges the values at the specified indices of the collection. */
static int array_swap_at(struct Array* array, int i, int j) {
  var err = 0;
  if ((err = _check_index(array, i)) != 0) {
    return err;
  }
  if ((err = _check_index(array, j)) != 0) {
    return err;
  }
  if (i == j) {
    return 0;
  }
  var width = (*array).element_size;
  var buf = malloc(width);
  memcpy(buf, (*array)._storage + i * width, width);
  memcpy((*array)._storage + i * width, (*array)._storage + j * width, width);
  memcpy((*array)._storage + j * width, buf, width);
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

static bool equal(const void* a, const void* b) {
  return *(char*)a == *(char*)b;
}

void main_489(void) {
  struct Array answer;
  array_init(&answer, sizeof(char));
  char delta[1024];
  bool unique[256];

  var round = 0;
  while (scanf("%d", &round) == 1 && round != -1) {
    array_remove_all(&answer);
    var i = 0;
    for (i = 0; i < 256; i += 1) {
      unique[i] = false;
    }

    scanf("%s", delta); /* Read answer */
    var count = strlen(delta);
    for (i = 0; i < count; i += 1) {
      array_append(&answer, &delta[i]);
    }
    scanf("%s", delta); /* Read guess */
    count = strlen(delta);

    printf("Round %d\n", round);
    var error_count = 0;
    for (i = 0; i < count; i += 1) {
      if (array_contains(&answer, &delta[i], equal)) {
        while (array_contains(&answer, &delta[i], equal)) {
          /* Remove all the matched char */
          var j = array_first_index(&answer, &delta[i], equal);
          array_swap_at(&answer, j, answer.count - 1);
          array_remove_last(&answer);
        }
      } else {
        if (unique[delta[i]] == false) {
          error_count += 1;
          unique[delta[i]] = true;
        }
      }
      if (error_count > 6) {
        printf("You lose.\n");
        break;
      }
      if (answer.is_empty) {
        printf("You win.\n");
        break;
      }
      if (i == count - 1) {
        printf("You chickened out.\n");
      }
    }
  }

  array_deinit(&answer);
}
