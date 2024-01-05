//
//  512.c
//  hxy
//
//  Created by Fang Ling on 2024/1/4.
//

#include <stdio.h>

#define var __auto_type

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

/*
 * Inserts a new element at the specified position.
 *
 * - Complexity:
 *   O(n), where n is the length of the array.
 */
static int array_insert(struct Array* array, void* element, int i) {
  if (i == (*array).count) { /* this method is equivalent to append(_:) */
    return array_append(array, element);
  }
  var err = _check_index(array, i);
  if (err != 0) {
    return err;
  }
  /* Dumb append to make room for the new element. Update is_empty & count. */
  if ((err = array_append(array, element)) != 0) {
    return err;
  }
  /*
   * [1, 2, 3, 4, 5]  <----- insert(100, at: 3)
   *
   *  0  1  2  3  4    5
   * [1, 2, 3, 4, 5, 100]  <---- after append, count = 6
   *           \--/  <---- shift right by one (i ..< count - 1)
   *                                          (move length = count - 1 - i)
   *
   * Then copy new_element at index 3.
   *
   *    0  1  2    3  4  5
   * = [1, 2, 3, 100, 4, 5]
   */
  memmove(
    (*array)._storage + (i + 1) * (*array).element_size,
    (*array)._storage + i * (*array).element_size,
    ((*array).count - 1 - i) * (*array).element_size
  );
  memcpy(
    (*array)._storage + i * (*array).element_size,
    element,
    (*array).element_size
  );
  return err;
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

/*
 * Removes the element at the specified position.
 *
 * - Complexity:
 *   O(n), where n is the length of the array.
 */
static int array_remove_at(struct Array* array, int i) {
  var err = 0;
  if ((err = _check_index(array, i)) != 0) {
    return err;
  }

  if (i == (*array).count - 1) {
    return array_remove_last(array);
  }

  /*
   *    0    1    2    3    4    5    6
   * [1.1, 1.5, 2.9, 1.2, 1.5, 1.3, 1.2]   <---  remove(at: 2)
   *                 \----------------/  <---  shift left by one (i+1 ..< count)
   *                                     <--- move length = count - i - 1
   * [1.1, 1.5, 1.2, 1.5, 1.3, 1.2, 1.2]
   *
   * then, call remove_last()
   *
   * [1.1, 1.5, 1.2, 1.5, 1.3, 1.2]
   */
  memmove(
    (*array)._storage + i * (*array).element_size,
    (*array)._storage + (i + 1) * (*array).element_size,
    ((*array).count - i - 1) * (*array).element_size
  );
  return array_remove_last(array);
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

static void delete_row_512(struct Array* tbl, int row) {
  struct Array temp;
  array_get(tbl, row, &temp);
  array_deinit(&temp); /* Free elem at row */
  array_set(tbl, row, &temp);
  array_remove_at(tbl, row);
}

static void delete_col_512(struct Array* tbl, int col) {
  struct Array temp;
  var row = 0;
  for (row = 0; row < (*tbl).count; row += 1) {
    array_get(tbl, row, &temp);
    array_remove_at(&temp, col);
    array_set(tbl, row, &temp);
  }
}

static void insert_row_512(struct Array* tbl, int row) {
  struct Array new_row;
  array_init(&new_row, sizeof(int));
  var i = 0;
  var count = ((struct Array*)(*tbl)._storage)[0].count;
  var buf = -1;
  for (i = 0; i < count; i += 1) {
    array_append(&new_row, &buf);
  }
  array_insert(tbl, &new_row, row);
}

static void insert_col_512(struct Array* tbl, int col) {
  struct Array temp;
  var buf = -1;
  var row = 0;
  for (row = 0; row < (*tbl).count; row += 1) {
    array_get(tbl, row, &temp);
    array_insert(&temp, &buf, col);
    array_set(tbl, row, &temp);
  }
}

static void swap_at_512(struct Array* tbl, int pos[]) {
  /* Beautiful ;-) */
  var delta =
    ((int*)((struct Array*)(*tbl)._storage)[pos[0]]._storage)[pos[1]];
  var delta2 =
    ((int*)((struct Array*)(*tbl)._storage)[pos[2]]._storage)[pos[3]];
  struct Array temp;
  array_get(tbl, pos[0], &temp);
  array_set(&temp, pos[1], &delta2);
  array_set(tbl, pos[0], &temp);

  array_get(tbl, pos[2], &temp);
  array_set(&temp, pos[3], &delta);
  array_set(tbl, pos[2], &temp);
}

static int compare(const void* a, const void* b) {
  if (*(int*)a < *(int*)b) {
    return -1;
  } else if (*(int*)a > *(int*)b) {
    return 1;
  }
  return 0;
}

void main_512(void) {
  char op_delta[2 + 1];
  int pos[4];

  struct Array tbl;
  array_init(&tbl, sizeof(struct Array));
  struct Array op_buf;
  array_init(&op_buf, sizeof(int));

  var is_first = true;
  var seq = 1;
  var r = 0;
  var c = 0;
  while (scanf("%d %d", &r, &c) == 2 && r != 0 && c != 0) {
    var i = 0;
    for (i = 0; i < tbl.count; i += 1) {
      struct Array temp;
      array_get(&tbl, i, &temp);
      array_deinit(&temp);
      array_set(&tbl, i, &temp);
    }
    array_remove_all(&tbl);

    if (!is_first) {
      printf("\n");
    }
    is_first = false;

    /* Construct the table */
    for (i = 0; i < r; i += 1) {
      struct Array row;
      array_init(&row, sizeof(int));
      var j = 0;
      for (j = 0; j < c; j += 1) {
        var temp = (i << 8) + j;
        array_append(&row, &temp);
      }
      array_append(&tbl, &row);
    }

    var ops = 0;
    var A = 0;
    var j = 0;
    var delta = 0;
    scanf("%d", &ops);
    while (ops--) {
      array_remove_all(&op_buf);
      scanf("%s", op_delta);
      if (op_delta[0] == 'D' && op_delta[1] == 'R') {
        scanf("%d", &A);
        for (j = 0; j < A; j += 1) {
          scanf("%d", &delta);
          delta -= 1;
          array_append(&op_buf, &delta);
        }
        array_sort(&op_buf, compare);
        for (j = 0; j < A; j += 1) {
          delete_row_512(&tbl, ((int*)op_buf._storage)[j] - j);
        }
      } else if (op_delta[0] == 'D' && op_delta[1] == 'C') {
        scanf("%d", &A);
        for (j = 0; j < A; j += 1) {
          scanf("%d", &delta);
          delta -= 1;
          array_append(&op_buf, &delta);
        }
        array_sort(&op_buf, compare);
        for (j = 0; j < A; j += 1) {
          delete_col_512(&tbl, ((int*)op_buf._storage)[j] - j);
        }
      } else if (op_delta[0] == 'I' && op_delta[1] == 'R') {
        scanf("%d", &A);
        for (j = 0; j < A; j += 1) {
          scanf("%d", &delta);
          delta -= 1;
          array_append(&op_buf, &delta);
        }
        array_sort(&op_buf, compare);
        for (j = 0; j < A; j += 1) {
          insert_row_512(&tbl, ((int*)op_buf._storage)[j] + j);
        }
      } else if (op_delta[0] == 'I' && op_delta[1] == 'C') {
        scanf("%d", &A);
        for (j = 0; j < A; j += 1) {
          scanf("%d", &delta);
          delta -= 1;
          array_append(&op_buf, &delta);
        }
        array_sort(&op_buf, compare);
        for (j = 0; j < A; j += 1) {
          insert_col_512(&tbl, ((int*)op_buf._storage)[j] + j);
        }
      } else if (op_delta[0] == 'E' && op_delta[1] == 'X') {
        scanf("%d %d %d %d", &pos[0], &pos[1], &pos[2], &pos[3]);
        pos[0] -= 1;
        pos[1] -= 1;
        pos[2] -= 1;
        pos[3] -= 1;
        swap_at_512(&tbl, pos);
      }
    }

    var q = 0;
    scanf("%d", &q);
    printf("Spreadsheet #%d\n", seq);
    seq += 1;
    while (q--) {
      scanf("%d %d", &ops, &A); /* Reuse ops, A, delta */
      ops -= 1;
      A -= 1;
      delta = (ops << 8) + A;
      var is_gone = true;
      for (i = 0; i < tbl.count; i += 1) {
        var count = ((struct Array*)tbl._storage)[i].count;
        for (j = 0; j < count; j += 1) {
          var delta2 = ((int*)(((struct Array*)tbl._storage)[i])._storage)[j];
          if (delta == delta2) {
            is_gone = false;
            r = i;
            c = j;
            break;
          }
        }
        if (is_gone == false) {
          break;
        }
      }
      if (is_gone) {
        printf("Cell data in (%d,%d) GONE\n", ops + 1, A + 1);
      } else {
        printf(
          "Cell data in (%d,%d) moved to (%d,%d)\n", 
          ops + 1, A + 1, r + 1, c + 1
        );
      }
    }
  }

  array_deinit(&op_buf);
  array_deinit(&tbl);
}
