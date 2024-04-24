//
//  12100.c
//  hxy
//
//  Created by Fang Ling on 2024/4/24.
//

#include <stdio.h>

/*===----------------------------------------------------------------------===*/
/*                                                        ___   ___           */
/* Deque START                                          /'___\ /\_ \          */
/*                                                     /\ \__/ \//\ \         */
/* Author: Fang Ling (fangling@fangl.ing)              \ \ ,__\  \ \ \        */
/* Version: 2.0                                         \ \ \_/__ \_\ \_  __  */
/* Date: April 24, 2024                                  \ \_\/\_\/\____\/\_\ */
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

#ifndef deque_h
#define deque_h

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


#include <string.h>

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


#include <stdlib.h>
#include <string.h>

#include <stdio.h> /* For printing error messages */

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

static void array_remove_last(struct Array* array) {
  if (array->is_empty) {
    fprintf(stderr, ARRAY_FATAL_ERR_REMEM);
    abort();
  }
  array->count -= 1;
  if (array->count == 0) {
    array->is_empty = true;
  }
  if (array->count * ARRAY_RESIZE_FACTOR <= array->_capacity) {
    array->_capacity /= ARRAY_MULTIPLE_FACTOR;
    var new_size = array->_capacity * array->_width;
    array->_storage = realloc(array->_storage, new_size);
    if (array->_storage == NULL && new_size != 0) { /* Linux fix */
      fprintf(stderr, ARRAY_FATAL_ERR_REALLO);
      abort();
    }
  }
}

static void array_remove_all(struct Array* array) {
  free(array->_storage);
  array->_storage = NULL;
  array->count = 0;
  array->_capacity = 0;
  array->is_empty = true;
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


#define DEQUE_FATAL_ERR_REMFT "Can't remove first element from an empty deque"
#define DEQUE_FATAL_ERR_OUTOB "Index out of range"

struct Deque {
  struct Array* _head;
  struct Array* _tail;

  /*
   * Let head.count = h, tail.count = t
   *
   *  h                               h-1       0
   *  +--------+--------+-...-+--------+--------+
   *  |//tail//|        |-...-|        |\\head\\|
   *  +--------+--------+-...-+--------+--------+
   *
   *  head stores items in reversed order.
   *
   *  deque.append() causes tail.append()
   *  deque.remove_last() causes tail.remove_last()
   *  deque.prepend() causes head.append()
   *  deque.remove_first() causes head.remove_last()
   *
   *  remove from empty head or tail causes reblance.
   */

  /**
   * The number of elements in the deque.
   */
  Int64 count;

  /* The size of stored Element type. */
  UInt32 _width;

  /**
   * A Boolean value indicating whether the deque is empty.
   *
   * When you need to check whether your deque is empty, use the `is_empty`
   * property instead of checking that the `count` property is equal to zero.
   */
  Bool is_empty;
};

#endif /* deque_h */

/*
 * This function assumes that either the head or the tail is empty, but not
 * both.
 */
static void _deque_rebalance(struct Array* empty, struct Array* full) {
  var count = empty->count + full->count;
  var half_count = count / 2;
  /* TODO: use memcpy */
  /* copy the first half to empty */
  var i = 0ll;
  for (i = half_count - 1; i >= 0; i -= 1) { /* Important: append backwords */
    array_append(empty, full->_storage + i * full->_width);
  }
  /* shift the second half to the front of full */
  memmove(
    full->_storage,
    full->_storage + half_count * full->_width,
    (count - half_count) * full->_width
  );
  full->count = count - half_count;
}

/* Check that the specified `index` is valid, i.e. `0 ≤ index < count`. */
static void _deque_check_index(struct Deque* deque, Int64 index) {
  if (index >= deque->count || index < 0) {
    fprintf(stderr, DEQUE_FATAL_ERR_OUTOB);
    abort();
  }
}

/* MARK: - Creating and Destroying an Array */

static struct Deque* deque_init(UInt32 width) {
  struct Deque* deque;
  if ((deque = malloc(sizeof(struct Deque))) == NULL) {
    return NULL;
  }
  
  deque->count = 0;
  deque->is_empty = true;
  deque->_width = width;

  deque->_head = array_init(width);
  deque->_tail = array_init(width);
  
  if (deque->_head == NULL || deque->_tail == NULL) {
    return NULL;
  }
  
  return deque;
}

static void deque_deinit(struct Deque* deque) {
  if (deque == NULL) {
    return;
  }
  
  array_deinit(deque->_head);
  array_deinit(deque->_tail);
  
  free(deque);
}

/* MARK: - Accessing Elements */

/* Returns the element at the specified position. */
static void deque_get(struct Deque* deque, Int64 index, void* element) {
  _deque_check_index(deque, index);
  
  /* Calculate real index */
  if (index >= deque->_head->count) { /* in tail */
    index -= deque->_head->count;
    memcpy(
      element,
      deque->_tail->_storage + deque->_width * index,
      deque->_width
    );
  } else { /* in head */
    index = deque->_head->count - 1 - index;
    memcpy(
      element,
      deque->_head->_storage + deque->_width * index,
      deque->_width
    );
  }
}

/* MARK: - Adding Elements */

static void deque_append(struct Deque* deque, void* new_element) {
  deque->count += 1;
  deque->is_empty = false;
  array_append(deque->_tail, new_element);
}

/* MARK: - Removing Elements */

/* Removes the first element of the collection. */
static void deque_remove_first(struct Deque* deque) {
  if (deque->is_empty) {
    fprintf(stderr, DEQUE_FATAL_ERR_REMFT);
    abort();
  }

  deque->count -= 1;
  if (deque->count == 0) {
    deque->is_empty = true;
  }

  /* Special fix for reblance */
  if (deque->count == 0) { /* either head or tail is empty */
    if (deque->_head->is_empty) {
      array_remove_last(deque->_tail);
      return;
    } else {
      array_remove_last(deque->_head);
      return;
    }
  }

  if (deque->_head->is_empty && deque->_tail->is_empty) {
    /* never happen */
  } else if (!deque->_head->is_empty) {
    /* Normal case */
  } else {
    /* Bad case: rebalance needed */
    _deque_rebalance(deque->_head, deque->_tail);
  }
  array_remove_last(deque->_head);
}

static void deque_remove_all(struct Deque* deque) {
  deque->count = 0;
  deque->is_empty = true;
  array_remove_all(deque->_head);
  array_remove_all(deque->_tail);
}

/*===----------------------------------------------------------------------===*/
/*             ___                            ___                             */
/*           /'___\                          /\_ \    __                      */
/*          /\ \__/   __      ___      __    \//\ \  /\_\    ___      __      */
/*          \ \ ,__\/'__`\  /' _ `\  /'_ `\    \ \ \ \/\ \ /' _ `\  /'_ `\    */
/*           \ \ \_/\ \L\.\_/\ \/\ \/\ \L\ \    \_\ \_\ \ \/\ \/\ \/\ \L\ \   */
/*            \ \_\\ \__/.\_\ \_\ \_\ \____ \   /\____\\ \_\ \_\ \_\ \____ \  */
/*             \/_/ \/__/\/_/\/_/\/_/\/___L\ \  \/____/ \/_/\/_/\/_/\/___L\ \ */
/* Deque END                           /\____/                        /\____/ */
/*                                     \_/__/                         \_/__/  */
/*===----------------------------------------------------------------------===*/

struct Job {
  Int32 id;
  Int32 priority;
};

void main_12100(void) {
  var queue = deque_init(sizeof(struct Job));
  struct Job j;
  struct Job delta;
  
  var t = 0;
  scanf("%d", &t);
  while (t--) {
    deque_remove_all(queue);
    
    var n = 0;
    var m = 0;
    scanf("%d %d", &n, &m);
    
    var i = 0;
    for (i = 0; i < n; i += 1) {
      j.id = i;
      scanf("%d", &j.priority);
      deque_append(queue, &j);
    }
    var ans = 0;
    while (true) {
      deque_get(queue, 0, &j);
      deque_remove_first(queue);
      var is_greater = false;
      for (i = 0; i < queue->count; i += 1) {
        deque_get(queue, i, &delta);
        if (delta.priority > j.priority) {
          is_greater = true;
          break;
        }
      }
      if (is_greater) {
        deque_append(queue, &j);
      } else {
        if (j.id == m) {
          break;
        }
        ans += 1;
      }
    }
    printf("%d\n", ans + 1);
  }
  
  deque_deinit(queue);
}
