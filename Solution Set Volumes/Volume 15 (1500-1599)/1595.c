//
//  1595.c
//  hxy
//
//  Created by Fang Ling on 2024/4/23.
//

#include <stdio.h>

/*===----------------------------------------------------------------------===*/
/*                                                        ___   ___           */
/* Array START                                          /'___\ /\_ \          */
/*                                                     /\ \__/ \//\ \         */
/* Author: Fang Ling (fangling@fangl.ing)              \ \ ,__\  \ \ \        */
/* Version: 2.0                                         \ \ \_/__ \_\ \_  __  */
/* Date: April 22, 2024                                  \ \_\/\_\/\____\/\_\ */
/*                                                        \/_/\/_/\/____/\/_/ */
/*===----------------------------------------------------------------------===*/

/*
 * This source file is part of the C Collections open source project
 *
 * Copyright (c) 2024 Fang Ling
 * Licensed under Apache License v2.0
 *
 * See https://github.com/fang-ling/C-Collections/blob/main/LICENSE for license
 * information
 */

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include <stdio.h> /* For printing error messages */

#include <stddef.h> /* For size_t */

#include <stdlib.h>
#include <stdbool.h>

#include <stddef.h> /* For size_t */

#define INS_THR 64

/* Byte-wise swap two items of size SIZE. */
#define SWAP(a, b, size)      \
  do {                        \
    size_t __size = (size);   \
    char *__a = (a);          \
    char *__b = (b);          \
    do {                      \
      char __tmp = *__a;      \
      *__a++ = *__b;          \
      *__b++ = __tmp;         \
    } while (--__size > 0);   \
  } while (0);

/*===----------------------------------------------------------------------===*/
/*                                                        ___   ___           */
/* sort START                                           /'___\ /\_ \          */
/*                                                     /\ \__/ \//\ \         */
/* Author: Fang Ling (fangling@fangl.ing)              \ \ ,__\  \ \ \        */
/* Version: 1.0                                         \ \ \_/__ \_\ \_  __  */
/* Date: December 4, 2023                                \ \_\/\_\/\____\/\_\ */
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

#define var __auto_type

static int partition(
  void* base,
  size_t width,
  int p,
  int r,
  int (*compare)(const void*, const void*)
) {
  var x_ptr = base + width * r;
  var i = p - 1;
  var j = 0;
  for (j = p; j < r; j += 1) {
    if (compare(base + width * j, x_ptr) <= 0) {
      i += 1;
      SWAP(base + width * i, base + width * j, width);
    }
  }
  SWAP(base + width * (i + 1), base + width * r, width);
  return i + 1;
}

static int randomized_partition(
  void* base,
  size_t width,
  int p,
  int r,
  int (*compare)(const void*, const void*)
) {
  var i = p + random() % (r - p + 1);
  SWAP(base + width * r, base + width * i, width);
  return partition(base, width, p, r, compare);
}

static void _wkq_insertion_sort(
  void* base,
  size_t width,
  int p,
  int r,
  int (*compare)(const void*, const void*)
) {
  var j = p + 1;
  for (; j <= r; j += 1) {
    var i = j;
    while (i > 0 && compare(base + width * (i - 1), base + width * i) > 0) {
      SWAP(base + width * (i - 1), base + width * i, width);
      i -= 1;
    }
  }
}

static void _wkq_quicksort(
  void* base,
  size_t width,
  int p,
  int r,
  int (*compare)(const void*, const void*)
) {
  if (p < r) {
    var is_sorted = true;
    var i = 0;
    for (i = p + 1; i <= r; i += 1) {
      if (compare(base + width * i, base + width * (i - 1)) < 0) {
        is_sorted = false;
        break;
      }
    }

    var is_reverse_sorted = true;
    for (i = r; i > p; i -= 1) {
      if (compare(base + width * i, base + width * (i - 1)) > 0) {
        is_reverse_sorted = false;
      }
    }
    if (is_reverse_sorted) {
      i = p;
      var j = r;
      while (j > i) {
        SWAP(base + width * i, base + width * j, width);
        i += 1;
        j -= 1;
      }
    } else if (!is_sorted) {
      if (r - p + 1 <= INS_THR) {
        _wkq_insertion_sort(base, width, p, r, compare);
      } else {
        var q = randomized_partition(base, width, p, r, compare);
        _wkq_quicksort(base, width, p, q - 1, compare);
        _wkq_quicksort(base, width, q + 1, r, compare);
      }
    }
  }
}

void sort(
  void* base,
  size_t nel,
  size_t width,
  int (*compare)(const void*, const void*)
) {
  srandom(1935819342);
  _wkq_quicksort(base, width, (int)0, (int)nel - 1, compare);
}

/*===----------------------------------------------------------------------===*/
/*             ___                            ___                             */
/*           /'___\                          /\_ \    __                      */
/*          /\ \__/   __      ___      __    \//\ \  /\_\    ___      __      */
/*          \ \ ,__\/'__`\  /' _ `\  /'_ `\    \ \ \ \/\ \ /' _ `\  /'_ `\    */
/*           \ \ \_/\ \L\.\_/\ \/\ \/\ \L\ \    \_\ \_\ \ \/\ \/\ \/\ \L\ \   */
/*            \ \_\\ \__/.\_\ \_\ \_\ \____ \   /\____\\ \_\ \_\ \_\ \____ \  */
/*             \/_/ \/__/\/_/\/_/\/_/\/___L\ \  \/____/ \/_/\/_/\/_/\/___L\ \ */
/* sort END                            /\____/                        /\____/ */
/*                                     \_/__/                         \_/__/  */
/*===----------------------------------------------------------------------===*/


#define var __auto_type

#define ARRAY_MULTIPLE_FACTOR 2
#define ARRAY_RESIZE_FACTOR   4

#define ARRAY_FATAL_ERR_MALLOC "malloc() return a NULL pointer, check errno"
#define ARRAY_FATAL_ERR_REALLO "realloc() return a NULL pointer, check errno"
#define ARRAY_FATAL_ERR_REMEM  "Can't remove last element from an empty array"

struct Array {
  void* _storage;
  
  /**
   * The number of elements in the array.
   */
  size_t count;
  
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
  size_t _capacity;
  
  /* The size of stored Element type. */
  size_t _width;
  
  /**
   * A Boolean value indicating whether the array is empty.
   *
   * When you need to check whether your array is empty, use the `is_empty`
   * property instead of checking that the `count` property is equal to zero.
   */
  bool is_empty;
};

static void _array_init(struct Array* array, size_t count, size_t width) {
  /* Rounding up to next power of 2 */
  var capacity = count - 1;
  capacity |= capacity >> 1;
  capacity |= capacity >> 2;
  capacity |= capacity >> 4;
  capacity |= capacity >> 8;
  capacity |= capacity >> 16;
  capacity += 1;
  
  if (count == 0) {
    array->_storage = NULL;
  } else {
    array->_storage = malloc(capacity * width);
    if (array->_storage == NULL) {
      fprintf(stderr, ARRAY_FATAL_ERR_MALLOC);
      abort();
    }
  }
  array->_width = width;
  array->_capacity = capacity;
  array->count = count;
  array->is_empty = count == 0 ? true : false;
}

/* MARK: - Creating and Destroying an Array */

static struct Array* array_init(size_t width) {
  struct Array* array;
  if ((array = malloc(sizeof(struct Array))) == NULL) {
    return NULL;
  }
  _array_init(array, 0, width);
  return array;
}

static void array_deinit(struct Array* array) {
  if (array == NULL) {
    return;
  }
  
  free(array->_storage);
  array->count = 0;
  array->_width = 0;
  array->_capacity = 0;
  array->is_empty = true;
  
  free(array);
}

/* MARK: - Adding Elements */

static void array_append(struct Array* array, void* new_element) {
  if (array->_capacity == 0) {
    array->_storage = realloc(array->_storage, 1 * array->_width);
    array->_capacity = 1;
  }
  if (array->count == array->_capacity) {
    array->_capacity *= ARRAY_MULTIPLE_FACTOR;
    var new_size = array->_capacity * array->_width;
    array->_storage = realloc(array->_storage, new_size);
    if (array->_storage == NULL) {
      fprintf(stderr, ARRAY_FATAL_ERR_REALLO);
      abort();
    }
  }
  array->count += 1;
  array->is_empty = false;
  memcpy(
    array->_storage + (array->count - 1) * array->_width,
    new_element,
    array->_width
  );
}

/* MARK: - Removing Elements */

static void array_remove_all(struct Array* array) {
  free(array->_storage);
  array->_storage = NULL;
  array->count = 0;
  array->_capacity = 0;
  array->is_empty = true;
}

/* MARK: - Reordering an Array’s Elements */

static
void array_sort(struct Array* array, int (*compare)(const void*, const void*)) {
  if (array->count <= 1) {
    return;
  }
  sort(array->_storage, array->count, array->_width, compare);
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

struct Point_1595 {
  int x;
  int y;
};

static int compare(const void* a, const void* b) {
  var _a = *(struct Point_1595*)a;
  var _b = *(struct Point_1595*)b;
  return _a.x == _b.x ? _a.y - _b.y : _a.x - _b.x;
}

static bool is_symmetric(struct Array* points) {
  /* Find 2 points with minimum / maximum x values */
  var max = -1;
  var unsafe = (struct Point_1595*)points->_storage;
  var i = 0;
  for (i = (int)points->count-1; i >= 0; i -= 1) {
    if (
      unsafe[i].x == unsafe[points->count-1].x &&
      unsafe[i].y == unsafe[0].y
    ) {
      max = (int)i;
      break;
    }
  }
  if (max == -1) {
    return false;
  }
  var sym_x_times_2 = unsafe[0].x + unsafe[max].x;
  struct Point_1595 new_p;
  for (i = 0; i < points->count; i += 1) {
    if (unsafe[i].x * 2 == sym_x_times_2) { /* on the symmetry axis */
      /* Do nothing */
    } else {
      new_p.x = sym_x_times_2 - unsafe[i].x;
      new_p.y = unsafe[i].y;
      var is_contains = false;
      var j = 0;
      for (j = 0; j < points->count; j += 1) {
        if (unsafe[j].x == new_p.x && unsafe[j].y == new_p.y) {
          is_contains = true;
          break;
        }
      }
      if (!is_contains) {
        return false;
      }
    }
  }
  return true;
}

void main_1595(void) {
  var points = array_init(sizeof(struct Point_1595));
  
  struct Point_1595 pt;
  
  var t = 0;
  scanf("%d", &t);
  while (t--) {
    array_remove_all(points);
    
    var n = 0;
    scanf("%d", &n);
    while (n--) {
      scanf("%d %d", &pt.x, &pt.y);
      array_append(points, &pt);
    }
    array_sort(points, compare);
    
    printf("%s\n", is_symmetric(points) ? "YES" : "NO");
  }
  
  array_deinit(points);
}
