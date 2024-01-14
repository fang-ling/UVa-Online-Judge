//
//  12412.c
//  hxy
//
//  Created by Fang Ling on 2024/1/11.
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

/* Sorts the collection in place. */
static
void array_sort(struct Array* array, int (*compare)(const void*, const void*)) {
  if ((*array).count <= 1) {
    return;
  }
  sort((*array)._storage, (*array).count, (*array).element_size, compare);
}

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

/* MARK: - Comparing Arrays */

/*
 * Returns a Boolean value indicating whether two arrays contain the same
 * elements in the same order.
 */
static bool array_equal(
  struct Array* lhs,
  struct Array* rhs/*,
  int (*elem_compare)(const void*, const void*)*/
) {
  if ((*lhs).count != (*rhs).count) {
    return false;
  }
  if (
    memcmp(
      (*lhs)._storage,
      (*rhs)._storage,
      (*lhs).count * (*lhs).element_size
    ) != 0
  ) {
    return false;
  }
  return true;
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

typedef long long int64;

struct Student {
  int order;
  int64 sid;
  int cid;
  char name[11];
  int scores[4];
};

static bool equals_12412(const void* a, const void* b) {
  var sa = *(struct Student*)a;
  var sb = *(struct Student*)b;
  return sa.sid == sb.sid;
}

static void add_student_12412(struct Array* db, struct Student s) {
  if (array_contains(db, &s, equals_12412)) {
    printf("Duplicated SID.\n");
  } else {
    array_append(db, &s);
  }
}

static void remove_student_12412(struct Array* db, char* name) {
  var count = 0;
  var i = 0;
  struct Student delta;
  for (i = 0; i < (*db).count; i += 1) {
    array_get(db, i, &delta);
    if (strcmp(name, delta.name) == 0) {
      count += 1;
      array_remove_at(db, i);
      i -= 1;
    }
  }
  printf("%d student(s) removed.\n", count);
}

static void remove_student_2_12412(struct Array* db, int64 sid) {
  var count = 0;
  var i = 0;
  struct Student delta;
  for (i = 0; i < (*db).count; i += 1) {
    array_get(db, i, &delta);
    if (sid == delta.sid) {
      count += 1;
      array_remove_at(db, i);
      i -= 1;
    }
  }
  printf("%d student(s) removed.\n", count);
}

static int int_compare_reversed_12412(const void* a, const void* b) {
  if (*(int*)a > *(int*)b) {
    return 1;
  } else if (*(int*)a < *(int*)b) {
    return -1;
  }
  return 0;
}

static void _get_rank_list_12412(struct Array* db, struct Array* result) {
  /* Assume result is initialized and is empty. */
  struct Array total_score;
  array_init(&total_score, sizeof(int));
  
  var unsafe_cast = (struct Student*)(*db)._storage;
  var i = 0;
  for (i = 0; i < (*db).count; i += 1) {
    var delta = unsafe_cast[i].scores[0] + 
                unsafe_cast[i].scores[1] +
                unsafe_cast[i].scores[2] +
                unsafe_cast[i].scores[3];
    array_append(&total_score, &delta);
  }
  /* Biggest at front */
  array_sort(&total_score, int_compare_reversed_12412);
  var len = ((int*)total_score._storage)[0] + 1;
  var delta = 0;
  for (i = 0; i < len; i += 1) {
    array_append(result, &delta);
  }
  for (i = 0; i < total_score.count; i += 1) {
    var I = 0;
    array_get(&total_score, i, &I);
    array_get(result, I, &delta);
    if (delta == 0) { /* First insert */
      array_set(result, I, &i);
    }
  }
  
  array_deinit(&total_score);
}

static void select_student_12412(struct Array* db, char* name) {
  struct Array rank;
  array_init(&rank, sizeof(int));
  
  struct Student delta;
  
  var total_score = 0;
  var i = 0;
  for (i = 0; i < (*db).count; i += 1) {
    array_get(db, i, &delta);
    if (strcmp(delta.name, name)) {
      total_score = delta.scores[0] +
                    delta.scores[1] +
                    delta.scores[2] +
                    delta.scores[3];
      var rnk = 0;
      array_get(&rank, total_score, &rnk);
      printf(
        "%d %010lld %d %s %d %d %d %d %d %.2f\n",
        rnk + 1,
        delta.sid,
        delta.cid,
        delta.name,
        delta.scores[0],
        delta.scores[1],
        delta.scores[2],
        delta.scores[3],
        total_score,
        (double)total_score / 4.000000000000
      );
    }
  }
  
  array_deinit(&rank);
}

static void select_student_2_12412(struct Array* db, int64 sid) {
  struct Array rank;
  array_init(&rank, sizeof(int));
  
  struct Student delta;
  
  var total_score = 0;
  var i = 0;
  for (i = 0; i < (*db).count; i += 1) {
    array_get(db, i, &delta);
    if (delta.sid == sid) {
      total_score = delta.scores[0] +
                    delta.scores[1] +
                    delta.scores[2] +
                    delta.scores[3];
      var rnk = 0;
      array_get(&rank, total_score, &rnk);
      printf(
        "%d %010lld %d %s %d %d %d %d %d %.2f\n",
        rnk + 1,
        delta.sid,
        delta.cid,
        delta.name,
        delta.scores[0],
        delta.scores[1],
        delta.scores[2],
        delta.scores[3],
        total_score,
        (double)total_score / 4.000000000000
      );
    }
  }
  
  array_deinit(&rank);
}

static void stat_student_12412(struct Array* db, int cid) {
  char subjects[5][12] = {
    "Chinese", "Mathematics", "English", "Programming", "Overall:"
  };
  
  struct Student delta;
  
  var i = 0;
  for (i = 0; i < 4; i += 1) {
    var total = 0;
    var passed = 0;
    var size = 0;
    var j = 0;
    for (j = 0; j < (*db).count; j += 1) {
      array_get(db, j, &delta);
      if (cid == 0 || delta.cid == cid) {
        total += delta.scores[i];
        if (delta.scores[i] >= 60) {
          passed += 1;
        }
        size += 1;
      }
    }
    printf("%s\n", subjects[i]);
    printf("Average Score: %.2f\n", (double)total / size);
    printf("Number of passed students: %d\n", passed);
    printf("Number of failed students: %d\n", size - passed);
    printf("\n");
  }
  /* Overall.    0  1  2  3  4 */
  int pass[5] = {0, 0, 0, 0, 0};
  for (i = 0; i < (*db).count; i += 1) {
    var num_pass = 0;
    array_get(db, i, &delta);
    if (!(cid == 0 || delta.cid == cid)) {
      continue;
    }
    var j = 0;
    for (j = 0; j < 4; j += 1) {
      if (delta.scores[j] >= 60) {
        num_pass += 1;
      }
    }
    pass[num_pass] += 1;
  }
  printf("%s\n", subjects[4]);
  printf("Number of students who passed all subjects: %d\n", pass[4]);
  printf("Number of students who passed 3 or more subjects: %d\n", pass[3]);
  printf("Number of students who passed 2 or more subjects: %d\n", pass[2]);
  printf("Number of students who passed 1 or more subjects: %d\n", pass[1]);
  printf("Number of students who failed all subjects: %d\n", pass[0]);
  printf("\n");
}

void main_12412(void) {
  
}
