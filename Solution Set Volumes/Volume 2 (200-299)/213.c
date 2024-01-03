//
//  213.c
//  hxy
//
//  Created by Fang Ling on 2024/1/3.
//

/*===----------------------------------------------------------------------===*/
/*                                                        ___   ___           */
/* Deque START                                          /'___\ /\_ \          */
/*                                                     /\ \__/ \//\ \         */
/* Author: Fang Ling (fangling@fangl.ing)              \ \ ,__\  \ \ \        */
/* Version: 1.1                                         \ \ \_/__ \_\ \_  __  */
/* Date: December 11, 2023                               \ \_\/\_\/\____\/\_\ */
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
#include <string.h>

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

/*
 * Error code of Deque:
 * 0: NO ERROR
 * 1: due to malloc, check `errno`
 * 2: Array index is out of range
 * 3: Negative Array index is out of range
 * 5: due to realloc, check `errno`
 * 6: Can't remove last element from an empty collection
 */

struct Deque {
  struct Array _head;
  struct Array _tail;

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

  /* The number of elements in the array. */
  int count;

  /* The size of stored Element type. */
  int element_size;

  /* A Boolean value indicating whether or not the array is empty. */
  bool is_empty;
};

/* MARK: - Creating and Destroying an Array */

/* Creates an empty deque. */
static int deque_init(struct Deque* deque, int element_size) {
  (*deque).count = 0;
  (*deque).is_empty = true;
  (*deque).element_size = element_size;

  var err = 0;
  if ((err = array_init(&(*deque)._head, element_size)) != 0) {
    return err;
  }
  if ((err = array_init(&(*deque)._tail, element_size)) != 0) {
    return err;
  }
  return err;
}

/* Destroys a deque. */
static void deque_deinit(struct Deque* deque) {
  array_deinit(&(*deque)._head);
  array_deinit(&(*deque)._tail);
}

/* MARK: - Accessing Elements */

/* Check that the specified `index` is valid, i.e. `0 ≤ index < count`. */
static int _deque_check_index(struct Deque* deque, int index) {
  if (index >= (*deque).count) {
    return 2;
  } else if (index < 0) {
    return 3;
  }
  return 0;
}

/* Returns the element at the specified position. */
static int deque_get(struct Deque* deque, int index, void* element) {
  var err = _deque_check_index(deque, index);
  if (err != 0) {
    return err;
  }
  /* Calculate real index */
  if (index >= (*deque)._head.count) { /* in tail */
    index -= (*deque)._head.count;
    memcpy(
      element,
      (*deque)._tail._storage + (*deque).element_size * index,
      (*deque).element_size
    );
  } else { /* in head */
    index = (*deque)._head.count - 1 - index;
    memcpy(
      element,
      (*deque)._head._storage + (*deque).element_size * index,
      (*deque).element_size
    );
  }

  return err;
}

/* MARK: - Adding Elements */

/* Adds a new element at the end of the deque. */
static int deque_append(struct Deque* deque, void* element) {
  (*deque).count += 1;
  (*deque).is_empty = false;
  return array_append(&(*deque)._tail, element);
}

/* MARK: - Removing Elements */

/*
 * This function assumes that either the head or the tail is empty, but not
 * both.
 */
static int _rebalance(struct Array* empty, struct Array* full) {
  var count = (*empty).count + (*full).count;
  var half_count = count / 2;
  var err = 0;
  /* TODO: use memcpy */
  /* copy the first half to empty */
  var i = 0;
  for (i = half_count - 1; i >= 0; i -= 1) { /* Important: append backwords */
    err = array_append(empty, (*full)._storage + i * (*full).element_size);
  }
  /* shift the second half to the front of full */
  memmove(
    (*full)._storage,
    (*full)._storage + half_count * (*full).element_size,
    (count - half_count) * (*full).element_size
  );
  (*full).count = count - half_count;
  return err;
}

/* Removes the first element of the collection. */
static int deque_remove_first(struct Deque* deque) {
  if ((*deque).is_empty) {
    return 6;
  }

  (*deque).count -= 1;
  if ((*deque).count == 0) {
    (*deque).is_empty = true;
  }

  /* Special fix for reblance */
  if ((*deque).count == 0) { /* either head or tail is empty */
    if ((*deque)._head.is_empty) {
      return array_remove_last(&(*deque)._tail);
    } else {
      return array_remove_last(&(*deque)._head);
    }
  }

  var err = 0;
  if ((*deque)._head.is_empty && (*deque)._tail.is_empty) {
    /* never happen */
  } else if (!(*deque)._head.is_empty) {
    /* Normal case */
  } else {
    /* Bad case: rebalance needed */
    _rebalance(&(*deque)._head, &(*deque)._tail);
  }
  err = array_remove_last(&(*deque)._head);

  return err;
}

/* Removes all the elements. */
static int deque_remove_all(struct Deque* deque) {
  (*deque).count = 0;
  (*deque).is_empty = true;
  array_remove_all(&(*deque)._head);
  array_remove_all(&(*deque)._tail);

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
/* Deque END                           /\____/                        /\____/ */
/*                                     \_/__/                         \_/__/  */
/*===----------------------------------------------------------------------===*/


#include <stdio.h>

#define var __auto_type

void main_213(void) {
  /*
   * code[i] contains the length i+1 key.
   * Example:                                            kcount = 2**(i+1)-1
   *   code[0]: 0  <------------------------------ 1 keys 2**1 - 1
   *   code[1]: 00 01 10  <----------------------- 3 keys 2**2 - 1
   *   code[2]: 000 001 010 011 100 101 110  <---- 7 keys 2**3 - 1
   *    ...
   *   code[6]: ...........................  <---- 127 keys 2**7 - 1
   *
   *   Header: TNM AEIOU
   *
   */
  char code[7][1 << 7];
  char c[7];

  struct Deque deque;
  deque_init(&deque, sizeof(char));

  char* line = NULL;
  size_t linecap = 0;
  var linelen = 0;
  while ((linelen = (int)getline(&line, &linecap, stdin)) > 1) {
    /* line[0..<linelen] now contains the header. Parse header: */
    /* linelen also include \n char */
    linelen -= 1;
    var i = 0;
    var k = 0;
    for (i = 0; i < 7; i += 1) { /* 1 ≤ key_len ≤ 7 */
      var j = 0;
      var len = (1 << (i + 1)) - 1;
      for (j = 0; j < len; j += 1) {
        if (k >= linelen) { /* Out of header */
          break;
        }

        code[i][j] = line[k];
        k += 1;
      }
    }

    /* Use a deque to help us read the cipher. */
    deque_remove_all(&deque);
    while ((linelen = (int)getline(&line, &linecap, stdin)) > 0) {
      linelen -= 1;
      for (i = 0; i < linelen; i += 1) {
        if (line[i] == '0' || line[i] == '1') {
          deque_append(&deque, &line[i]);
        }
      }

/*      deque_get(&deque, deque.count - 1, &c[0]);
      deque_get(&deque, deque.count - 2, &c[1]);
      deque_get(&deque, deque.count - 3, &c[2]);*/
      if (
        line[linelen - 1] == '0' &&
        line[linelen - 2] == '0' &&
        line[linelen - 3] == '0'
      ) { /* End of cipher */
        break;
      }
    }

    /* Parse the cipher */
    while (!deque.is_empty) {
      var len = 0;
      /* c1c2c3 */
      deque_get(&deque, 0, &c[0]);
      deque_remove_first(&deque);
      deque_get(&deque, 0, &c[1]);
      deque_remove_first(&deque);
      deque_get(&deque, 0, &c[2]);
      deque_remove_first(&deque);
      len = (c[2] - '0') + (c[1] - '0') * (1 << 1) + (c[0] - '0') * (1 << 2);
      if (len == 0) { /* End of cipher */
        break;
      }

      while (true) {
        for (i = 0; i < len; i += 1) {
          deque_get(&deque, 0, &c[i]);
          deque_remove_first(&deque);
        }
        var key = 0;
        for (i = len - 1; i >= 0; i -= 1) {
          key += (c[i] - '0') * (1 << (len - i - 1));
        }
        /*
         * 1 2 3
         * 1 3 7
         */
        if (key == (1 << len) - 1) {
          break;
        }
        printf("%c", code[len - 1][key]);
      }
    }
    printf("\n");
  }

  deque_deinit(&deque);
}
