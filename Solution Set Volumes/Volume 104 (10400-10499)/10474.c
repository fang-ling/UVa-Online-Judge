//
//  10474.c
//  hxy
//
//  Created by Fang Ling on 2024/2/15.
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

#include <stdlib.h>
#include <stdbool.h>

#define var __auto_type

#define INS_THR 64

/* Byte-wise swap two items of size SIZE. */
#define SWAP(a, b, size)      \
  do {                        \
    unsigned __size = (size); \
    char *__a = (a);          \
    char *__b = (b);          \
    do {                      \
      char __tmp = *__a;      \
      *__a++ = *__b;          \
      *__b++ = __tmp;         \
    } while (--__size > 0);   \
  } while (0);

static int partition(
  void* base,
  int width,
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
  int width,
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
  int width,
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
  int width,
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

static void sort(
  void* base,
  int nel,
  int width,
  int (*compare)(const void*, const void*)
) {
  srandom(1935819342);
  _wkq_quicksort(base, width, 0, nel - 1, compare);
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

/* MARK: - Finding Elements */

/* MARK: - Reordering an Array’s Elements */

/* Sorts the collection in place. */
static
void array_sort(struct Array* array, int (*compare)(const void*, const void*)) {
  if ((*array).count <= 1) {
    return;
  }
  sort((*array)._storage, (*array).count, (*array).element_size, compare);
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

/*===----------------------------------------------------------------------===*/
/*                                                        ___   ___           */
/* binary_search START                                  /'___\ /\_ \          */
/*                                                     /\ \__/ \//\ \         */
/* Author: Fang Ling (fangling@fangl.ing)              \ \ ,__\  \ \ \        */
/* Version: 1.1                                         \ \ \_/__ \_\ \_  __  */
/* Date: December 25, 2023                               \ \_\/\_\/\____\/\_\ */
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

#define var __auto_type

/*
 * The _binary_search() function searches an array of nel objects, the initial
 * member of which is pointed to by base, for a member that matches the
 * object pointed to by key.  The size (in bytes) of each member of the
 * array is specified by width.
 *
 * The contents of the array should be in ascending sorted order according
 * to the comparison function referenced by compare.  The compare routine is
 * expected to have two arguments which point to the key object and to an
 * array member, in that order.  It should return an integer which is less
 * than, equal to, or greater than zero if the key object is found,
 * respectively, to be less than, to match, or be greater than the array
 * member.
 *
 * The _binary_search() functions returns the first position in which the new
 * element cloud be inserted without changing the ordering.
 */
static int _binary_search(
  const void* key,
  const void* base,
  int nel,
  int width,
  int (*compare)(const void*, const void*)
) {
  var low = 0;
  var high = nel;
  while (low < high) {
    var mid = (low + high) / 2;
    if (compare(base + mid * width, key) < 0) {
      low = mid + 1;
    } else {
      high = mid;
    }
  }
  return low;
}

/*
 * Returns the first position in which the new element cloud be inserted without
 * changing the ordering, or nel if no such element is found.
 */
static int lower_bound(
  const void* key,
  const void* base,
  int nel,
  int width,
  int (*compare)(const void*, const void*)
) {
  return _binary_search(key, base, nel, width, compare);
}

/*===----------------------------------------------------------------------===*/
/*             ___                            ___                             */
/*           /'___\                          /\_ \    __                      */
/*          /\ \__/   __      ___      __    \//\ \  /\_\    ___      __      */
/*          \ \ ,__\/'__`\  /' _ `\  /'_ `\    \ \ \ \/\ \ /' _ `\  /'_ `\    */
/*           \ \ \_/\ \L\.\_/\ \/\ \/\ \L\ \    \_\ \_\ \ \/\ \/\ \/\ \L\ \   */
/*            \ \_\\ \__/.\_\ \_\ \_\ \____ \   /\____\\ \_\ \_\ \_\ \____ \  */
/*             \/_/ \/__/\/_/\/_/\/_/\/___L\ \  \/____/ \/_/\/_/\/_/\/___L\ \ */
/* binary_search END                   /\____/                        /\____/ */
/*                                     \_/__/                         \_/__/  */
/*===----------------------------------------------------------------------===*/


static int cmp_10474(const void* a, const void* b) {
  if (*(int*)a < *(int*)b) {
    return -1;
  } else if (*(int*)a > *(int*)b) {
    return 1;
  }
  return 0;
}

void main_10474(void) {
  struct Array nums;
  array_init(&nums, sizeof(int));
  
  var case_count = 1;
  
  var n = 0;
  var q = 0;
  while (scanf("%d %d", &n, &q) == 2 && n != 0 && q != 0) {
    array_remove_all(&nums);
    
    var i = 0;
    for (i = 0; i < n; i += 1) {
      var delta = 0;
      scanf("%d", &delta);
      array_append(&nums, &delta);
    }
    array_sort(&nums, cmp_10474);
    printf("CASE# %d:\n", case_count);
    case_count += 1;
    for (i = 0; i < q; i += 1) {
      var x = 0;
      scanf("%d", &x);
      var pos = lower_bound(
        &x, 
        nums._storage,
        nums.count,
        sizeof(int),
        cmp_10474
      );
      if (pos == nums.count || ((int*)nums._storage)[pos] != x) { /* 404 */
        printf("%d not found\n", x);
      } else {
        printf("%d found at %d\n", x, pos + 1);
      }
    }
  }
  
  array_deinit(&nums);
}
