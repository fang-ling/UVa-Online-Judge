//
//  511.c
//  hxy
//
//  Created by Fang Ling on 2024/5/7.
//

/*
 * This source file is part of the C Collections open source project
 *
 * Copyright (c) 2024 Fang Ling
 * Licensed under Apache License v2.0
 *
 * See https://github.com/fang-ling/C-Collections/blob/main/LICENSE for license
 * information
 */

#ifndef types_h
#define types_h

#include <stdint.h>
#include <stdbool.h>

typedef void Void;
typedef int8_t Int8;
typedef uint8_t UInt8;
typedef int32_t Int32;
typedef uint32_t UInt32;
typedef int64_t Int64;
typedef uint64_t UInt64;

typedef bool Bool;

typedef double Double;

#define var __auto_type

#endif /* types_h */

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

/*
 * This source file is part of the C Collections open source project
 *
 * Copyright (c) 2023 Fang Ling
 * Licensed under Apache License v2.0
 *
 * See https://github.com/fang-ling/C-Collections/blob/main/LICENSE for license
 * information
 */

#ifndef sort_h
#define sort_h

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

#endif /* sort_h */

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

static void sort(
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

/*
 * This source file is part of the C Collections open source project
 *
 * Copyright (c) 2024 Fang Ling
 * Licensed under Apache License v2.0
 *
 * See https://github.com/fang-ling/C-Collections/blob/main/LICENSE for license
 * information
 */

#ifndef array_h
#define array_h

#include <stdlib.h>
#include <string.h>

#include <stdio.h> /* For printing error messages */

#define ARRAY_MULTIPLE_FACTOR 2
#define ARRAY_RESIZE_FACTOR   4

#define ARRAY_FATAL_ERR_MALLOC "malloc() return a NULL pointer, check errno"
#define ARRAY_FATAL_ERR_REALLO "realloc() return a NULL pointer, check errno"
#define ARRAY_FATAL_ERR_REMEM  "Can't remove last element from an empty array"
#define ARRAY_FATAL_ERR_OUTOB  "Index out of range"

struct Array {
  void* _storage;
  
  /**
   * The number of elements in the array.
   */
  Int64 count;
  
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
  Int64 _capacity;
  
  /* The size of stored Element type. (in-bytes) */
  UInt32 _width;
  
  /**
   * A Boolean value indicating whether the array is empty.
   *
   * When you need to check whether your array is empty, use the `is_empty`
   * property instead of checking that the `count` property is equal to zero.
   */
  Bool is_empty;
};

#endif /* array_h */


/*
 * Error code of Array:
 * 0: NO ERROR
 * 1: due to malloc, check `errno`
 * 2: Array index is out of range
 * 3: Negative Array index is out of range
 * 5: due to realloc, check `errno`
 * 6: Can't remove last element from an empty collection
 */

static void _array_init(struct Array* array, Int64 count, UInt32 width) {
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

/* Check that the specified `index` is valid, i.e. `0 ≤ index < count`. */
static void _array_check_index(struct Array* array, Int64 index) {
  if (index >= array->count || index < 0) {
    fprintf(stderr, ARRAY_FATAL_ERR_OUTOB);
    abort();
  }
}

/* MARK: - Creating and Destroying an Array */

static struct Array* array_init(UInt32 width) {
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

/* MARK: - Accessing Elements */

/* Returns the element at the specified position. */
static void array_get(struct Array* array, Int64 index, void* element) {
  _array_check_index(array, index);
  
  memcpy(
    element,
    array->_storage + array->_width * index,
    array->_width
  );
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

/* MARK: - Reordering an Array’s Elements */

static void array_sort(
  struct Array* array,
  Int32 (*compare)(const void*, const void*)
) {
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
 * Returns a Boolean value indicating whether the sorted sequence contains the
 * given element.
 */
bool binary_search(
  const void* key,
  const void* base,
  int nel,
  int width,
  int (*compare)(const void*, const void*)
) {
  var i = _binary_search(key, base, nel, width, compare);
  return i != nel && compare(base + i * width, key) == 0;
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


#include <stdio.h>
#include <math.h>
#include <string.h>

struct Map {
  char name[128];
  Double x1;
  Double y1;
  Double x2;
  Double y2;
};

struct Location {
  char name[128];
  Double x;
  Double y;
};

/* Allow binary search on locations */
static Int32 compare(const void* a, const void* b) {
  var _a = *(struct Location*)a;
  var _b = *(struct Location*)b;
  return strcmp(_a.name, _b.name);
}

struct MapLocation {
  char name[128];
  Double x1;
  Double y1;
  Double x2;
  Double y2;
  /* Equal for whole batch */
  Double x;
  Double y;
};

static Void get_lowest_right(
  Double x1,
  Double y1,
  Double x2,
  Double y2,
  Double* x,
  Double* y
) {
  /*
   * Case 1:                  Case 2:
   *         1----+  x1<x2            2----+  x2<x1
   *         |    |  y2<y1            |    |  y1<y2
   *         +----2                   +----1
   *
   * Case 3:                  Case 4:
   *         +----1  x2<x1            +----2 x1<x2
   *         |    |  y2<y1            |    | y1<y2
   *         2----+                   1----+
   */
  if (x1 < x2 && y2 < y1) {
    *x = x2;
    *y = y2;
  } else if (x2 < x1 && y1 < y2) {
    *x = x1;
    *y = y1;
  } else if (x2 < x1 && y2 < y1) {
    *x = x1;
    *y = y2;
  } else if (x1 < x2 && y1 < y2) {
    *x = x2;
    *y = y1;
  } else {
    /* Debug use error, due to fp */
    abort();
  }
}

static Int32 compare2(const void* a, const void* b) {
  var _a = *(struct MapLocation*)a;
  var _b = *(struct MapLocation*)b;
  
  var a_a = fabs(_a.x1 - _a.x2) * fabs(_a.y1 - _a.y2);
  var a_b = fabs(_b.x1 - _b.x2) * fabs(_b.y1 - _b.y2);
  if (a_a == a_b) {
    var c_a_x = fabs(_a.x1 - _a.x2) / 2;
    var c_a_y = fabs(_a.y1 - _a.y2) / 2;
    var c_b_x = fabs(_b.x1 - _b.x2) / 2;
    var c_b_y = fabs(_b.y1 - _b.y2) / 2;
    var dis_a = (c_a_x-_a.x) * (c_a_x-_a.x) + (c_a_y-_a.y) * (c_a_y-_a.y);
    var dis_b = (c_b_x-_a.x) * (c_b_x-_a.x) + (c_b_y-_a.y) * (c_b_y-_a.y);
    if (dis_a == dis_b) {
      var ratio_a = fabs(_a.y1 - _a.y2) / fabs(_a.x1 - _a.x2) - 0.75;
      var ratio_b = fabs(_a.y1 - _a.y2) / fabs(_a.x1 - _a.x2) - 0.75;
      if (ratio_a == ratio_b) {
        var lr_a_x = 0.0;
        var lr_a_y = 0.0;
        var lr_b_x = 0.0;
        var lr_b_y = 0.0;
        get_lowest_right(_a.x1, _a.y1, _a.x2, _a.y2, &lr_a_x, &lr_a_y);
        get_lowest_right(_b.x1, _b.y1, _b.x2, _b.y2, &lr_b_x, &lr_b_y);
        var dislr_a = (_a.x-lr_a_x)*(_a.x-lr_a_x) + (_a.y-lr_a_y)*(_a.y-lr_a_y);
        var dislr_b = (_b.x-lr_b_x)*(_b.x-lr_b_x) + (_b.y-lr_b_y)*(_b.y-lr_b_y);
        if (dislr_a == dislr_b) {
          var min_ax = _a.x1 < _a.x2 ? _a.x1 : _a.x2;
          var min_bx = _b.x1 < _b.x2 ? _b.x1 : _b.x2;
          if (min_ax < min_bx) {
            return -1;
          } else {
            return 1;
          }
        } else {
          if (dislr_a > dislr_b) {
            return -1;
          } else {
            return 1;
          }
        }
      } else {
        if (ratio_a < ratio_b) {
          return -1;
        } else {
          return 1;
        }
      }
    } else {
      if (dis_a < dis_b) {
        return -1;
      } else {
        return 1;
      }
      /* no equal case here */
    }
  } else {
    if (a_a > a_b) {
      return -1;
    } else {
      return 1;
    }
    /* no equal case */
  }
}

static Bool is_in_rect(
  Double x, Double y,
  Double x1, Double y1,
  Double x2, Double y2
) {
  /*
   * Case 1:                  Case 2:
   *         1----+  x1<x2            2----+  x2<x1
   *         |    |  y2<y1            |    |  y1<y2
   *         +----2                   +----1
   *
   * Case 3:                  Case 4:
   *         +----1  x2<x1            +----2 x1<x2
   *         |    |  y2<y1            |    | y1<y2
   *         2----+                   1----+
   */
  if (x1 < x2 && y2 < y1) {
    return x1 <= x && x <= x2 && y2 <= y && y <= y1;
  } else if (x2 < x1 && y1 < y2) {
    return x2 <= x && x <= x1 && y1 <= y && y <= y2;
  } else if (x2 < x1 && y2 < y1) {
    return x2 <= x && x <= x1 && y2 <= y && y <= y1;
  } else if (x1 < x2 && y1 < y2) {
    return x1 <= x && x <= x2 && y1 <= y && y <= y2;
  } else {
    /* Debug use error, due to fp */
    abort();
  }
}

void main_511(void) {
  var maps = array_init(sizeof(struct Map));
  var locations = array_init(sizeof(struct Location));
  
  struct Map map;
  scanf("%s", map.name); /* Dummy read for MAPS */
  while (scanf("%s", map.name) == 1 && strcmp(map.name, "LOCATIONS") != 0) {
    scanf("%lf %lf %lf %lf", &map.x1, &map.y1, &map.x2, &map.y2);
    array_append(maps, &map);
  }
  
  struct Location location;
  while (
    scanf("%s", location.name) == 1 &&
    strcmp(location.name, "REQUESTS") != 0
  ) {
    scanf("%lf %lf", &location.x, &location.y);
    array_append(locations, &location);
  }
  
  /* Sort locations for binary search */
  array_sort(locations, compare);
  
  char buf[128];
  var level = 0;
  while (scanf("%s %d", buf, &level) == 2 && strcmp(buf, "END") != 0) {
    /* Create a dummy location just for binary search */
    strcpy(location.name, buf);
    var loc_i = _binary_search(
      &location,
      locations->_storage,
      (int)locations->count,
      locations->_width,
      compare
    );
    if (
      loc_i != locations->count &&
      compare(locations->_storage + loc_i * locations->_width, &location) == 0
    ) {
      array_get(locations, loc_i, &location);
      
      var maps_contains_location = array_init(sizeof(struct MapLocation));
      
      var i = 0;
      for (i = 0; i < maps->count; i += 1) {
        array_get(maps, i, &map);
        if (
          is_in_rect(location.x, location.y, map.x1, map.y1, map.x2, map.y2)
        ) {
          struct MapLocation ml;
          strcpy(ml.name, map.name);
          ml.x = location.x;
          ml.y = location.y;
          ml.x1 = map.x1;
          ml.y1 = map.y1;
          ml.x2 = map.x2;
          ml.y2 = map.y2;
          array_append(maps_contains_location, &ml);
        }
      }
      array_sort(maps_contains_location, compare2);
      
      if (maps_contains_location->is_empty) {
        printf(
          "%s at detail level %d no map contains that location\n",
          location.name,
          level
        );
      } else if (level > maps_contains_location->count) {
        struct MapLocation ml;
        array_get(maps_contains_location, maps_contains_location->count-1, &ml);
        printf(
          "%s at detail level %d no map at that detail level; using %s\n",
          location.name,
          level,
          ml.name
        );
      } else {
        struct MapLocation ml;
        array_get(maps_contains_location, level-1, &ml);
        printf(
          "%s at detail level %d using %s\n",
          location.name,
          level,
          ml.name
        );
      }
      
      array_deinit(maps_contains_location);
    } else { /* Not found */
      printf("%s at detail level %d unknown location\n", buf, level);
    }
  }
  
  array_deinit(maps);
  array_deinit(locations);
}
