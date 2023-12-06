//
//  232.c
//  hxy
//
//  Created by Fang Ling on 2023/12/6.
//

/*
 * Create a structute named Word to keep track of the index and word content.
 * Then, iterate through the entire crossword in row-major order to find all the
 * starting points of an answer. For each starting point, we find the answers in
 * two directions - vertical and horizontal.
 */

#include <stdio.h>
#include <stdbool.h>

#define var __auto_type

/*===----------------------------------------------------------------------===*/
/*                                                        ___   ___           */
/* Array START                                          /'___\ /\_ \          */
/*                                                     /\ \__/ \//\ \         */
/* Author: Fang Ling                                   \ \ ,__\  \ \ \        */
/* Version: 1.1                                         \ \ \_/__ \_\ \_  __  */
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

struct Word {
  int index;
  struct Array content;
};

void main_232(void) {
  char crossword[10 + 1][10 + 1];
  struct Array h_words;
  struct Array v_words;
  array_init(&h_words, sizeof(struct Word));
  array_init(&v_words, sizeof(struct Word));
  var is_first = true;
  var crossword_count = 1;

  var r = 0;
  var c = 0;
  while (true) {
    var i = 0;
    /* h_words & v_words clear, cannot call remove_all directly */
    for (i = 0; i < h_words.count; i += 1) {
      struct Word delta;
      array_get(&h_words, i, &delta);
      array_remove_all(&delta.content);
      array_deinit(&delta.content);
    }
    for (i = 0; i < v_words.count; i += 1) {
      struct Word delta;
      array_get(&v_words, i, &delta);
      array_remove_all(&delta.content);
      array_deinit(&delta.content);
    }
    array_remove_all(&h_words);
    array_remove_all(&v_words);

    scanf("%d", &r);
    if (r == 0) {
      break;
    }
    scanf("%d", &c);
    for (i = 0; i < r; i += 1) {
      scanf("%s", crossword[i]);
    }

    var index = 1; /* numbering */
    for (i = 0; i < r; i += 1) {
      var j = 0;
      for (j = 0; j < c; j += 1) {
        if (crossword[i][j] != '*') { /* non-blank */
          if (i < 1 || crossword[i - 1][j] == '*') { /* v */
            struct Array content;
            array_init(&content, sizeof(char));
            var k = 0;
            for (k = i; k < r && crossword[k][j] != '*'; k += 1) {
              array_append(&content, &crossword[k][j]);
            }
            struct Word word;
            word.index = index;
            word.content = content;
            array_append(&v_words, &word);
          }
          if (j < 1 || crossword[i][j - 1] == '*') { /* h */
            struct Array content;
            array_init(&content, sizeof(char));
            var k = 0;
            for (k = j; k < c && crossword[i][k] != '*'; k += 1) {
              array_append(&content, &crossword[i][k]);
            }
            struct Word word;
            word.index = index;
            word.content = content;
            array_append(&h_words, &word);
          }
          if ((i < 1 || crossword[i - 1][j] == '*') ||
              (j < 1 || crossword[i][j - 1] == '*')) {
            index += 1;
          }
        }
      }
    }

    if (!is_first) {
      printf("\n");
    }
    is_first = false;
    printf("puzzle #%d:\n", crossword_count);
    crossword_count += 1;
    printf("Across\n");
    for (i = 0; i < h_words.count; i += 1) {
      struct Word word;
      array_get(&h_words, i, &word);
      char eos = '\0';
      array_append(&word.content, &eos); /* Add end of string */
      printf("%3d.%s\n", word.index, (char*)word.content._storage);
    }
    printf("Down\n");
    for (i = 0; i < v_words.count; i += 1) {
      struct Word word;
      array_get(&v_words, i, &word);
      char eos = '\0';
      array_append(&word.content, &eos); /* Add end of string */
      printf("%3d.%s\n", word.index, (char*)word.content._storage);
    }
  }

  array_deinit(&h_words);
  array_deinit(&v_words);
}
