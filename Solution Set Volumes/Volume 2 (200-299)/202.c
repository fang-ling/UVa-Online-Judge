//
//  202.c
//  hxy
//
//  Created by Fang Ling on 2023/12/8.
//

/*
 * 1. Perform long division to find the quotient and remainder.
 * 2. Keep track of the remainders and the corresponding digits in the decimal
 *    representation.
 */

#include <stdio.h>

#define var __auto_type

/*===----------------------------------------------------------------------===*/
/*                                                        ___   ___           */
/* Array START                                          /'___\ /\_ \          */
/*                                                     /\ \__/ \//\ \         */
/* Author: Fang Ling (fangling@fangl.ing)              \ \ ,__\  \ \ \        */
/* Version: 1.2                                         \ \ \_/__ \_\ \_  __  */
/* Date: December 8, 2023                                \ \_\/\_\/\____\/\_\ */
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

/* MARK: - Finding Elements */

/*
 * Returns a Boolean value indicating whether the sequence contains an element
 * that satisfies the given predicate.
 *
 * Parameters:
 *   where: A function pointer that takes an element of the sequence as its
 *          argument and returns a Boolean value that indicates whether the
 *          passed element represents a match.
 *
 * Discussion:
 *   This example shows how you can check an array for an expense less than $59.
 *
 *   ```
 *   bool where(const void* elem) {
 *     if (*(int*)elem < 59) {
 *       return true;
 *     }
 *     return false;
 *   }
 *
 *   struct Array array;
 *   array_init(&array, sizeof(int));
 *
 *   int expenses[] = {19358, 12333, 19348, 19306, 19306, 58};
 *   for (var i = 0; i < 6; i += 1) {
 *     array_append(&array, &expenses[i]);
 *   }
 *   array_contains(&array, where); // Returnes true
 *
 *   array_deinit(&array);
 *   ```
 */
static bool array_contains(struct Array* array, bool (*where)(const void*)) {
  var buf = malloc((*array).element_size);
  var i = 0;
  for (i = 0; i < (*array).count; i += 1) {
    array_get(array, i, buf);
    if (where(buf)) {
      free(buf);
      return true;
    }
  }
  free(buf);
  return false;
}

/*
 * Returns the first index in which an element of the collection satisfies the
 * given predicate.
 *
 * Parameters:
 *   where: A function pointer that takes an element of the sequence as its
 *          argument and returns a Boolean value that indicates whether the
 *          passed element represents a match.
 *
 * Return Value:
 *  The index of the first element for which `where` returns true. If no
 *  elements in the collection satisfy the given predicate, returns -1.
 *
 * Disscussion:
 *   Here’s an example that finds a number that ends with the digit `3`:
 *
 *   ```
 *   bool where(const void* elem) {
 *     if (*(int*)elem % 10 == 3) {
 *       return true;
 *     }
 *     return false;
 *   }
 *
 *   struct Array array;
 *   array_init(&array, sizeof(int));
 *
 *   int input[] = {19358, 12333, 19348, 19306, 19306, 58};
 *   for (var i = 0; i < 6; i += 1) {
 *     array_append(&array, &input[i]);
 *   }
 *   array_first_index(&array, where_3); // Returns 1
 *
 *   array_deinit(&array);
 *   ```
 */
static int array_first_index(struct Array* array, bool (*where)(const void*)) {
  var buf = malloc((*array).element_size);
  var i = 0;
  for (i = 0; i < (*array).count; i += 1) {
    array_get(array, i, buf);
    if (where(buf)) {
      free(buf);
      return i;
    }
  }
  free(buf);
  return -1;
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

int a_202;

bool where_202(const void* elem) {
  if (*(int*)elem == a_202) {
    return true;
  }
  return false;
}

void main_202(void) {
  struct Array quo;
  struct Array rem;
  array_init(&quo, sizeof(int));
  array_init(&rem, sizeof(int));

  var a = 0;
  var b = 0;
  while (scanf("%d %d", &a, &b) == 2) {
    array_remove_all(&quo);
    array_remove_all(&rem);

    var A = a; /* copy of a */
    var B = b; /* copy of b */
    /* When remainder repeats, quotient repeats */
    while (a / b > 0) {
      a %= b;
    }
    if (a == 0) { /* Special case like 7 / 7 */
      printf("%d/%d = %d.(0)\n", A, B, A / B);
      printf("   1 = number of digits in repeating cycle\n\n");
      continue;
    }
    array_append(&rem, &a);
    var begin = 0;
    var end = 0;
    while (true) {
      a *= 10;
      var delta = a / b;
      array_append(&quo, &delta);
      a %= b;
      if (a == 0) {
        begin = rem.count;
        end = begin;
        break;
      }
      a_202 = a;
      if (array_contains(&rem, where_202)) {
        begin = array_first_index(&rem, where_202);
        end = rem.count - 1;
        break;
      }
      array_append(&rem, &a);
    }
    printf("%d/%d = %d.", A, B, A / B);
    var i = 0;
    for (i = 0; i < quo.count; i += 1) {
      if (i == begin) {
        printf("(");
      }
      var delta = 0;
      array_get(&quo, i, &delta);
      printf("%d", delta);
      if (i == end && end <= 49) {
        printf(")\n");
        break;
      }
      if (i >= 49) {
        printf("...)\n");
        break;
      }
    }
    if (begin == end && begin >= quo.count) {
      printf("(0)\n");
    }
    printf("   %d = number of digits in repeating cycle\n\n", end - begin + 1);
  }

  array_deinit(&quo);
  array_deinit(&rem);
}
