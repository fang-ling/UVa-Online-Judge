//
//  508.c
//  hxy
//
//  Created by Fang Ling on 2024/1/21.
//

#include <stdio.h>
#include <math.h>

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


struct ContextWord {
  int id;
  char plain[128];
  char morse[128];
};

static void get_morse_508(char morse_table[256][8], struct ContextWord* word) {
  var i = 0;
  var count = 0;
  var plain_count = (int)strlen((*word).plain);
  for (i = 0; i < plain_count; i += 1) {
    strcpy((*word).morse + count, morse_table[(*word).plain[i]]);
    count += strlen(morse_table[(*word).plain[i]]);
  }
  (*word).morse[count] = '\0';
}

static bool string_starts(char* a, char* b) {
  return strncmp(a, b, strlen(a)) == 0;
}

void main_508(void) {
  struct Array array;
  array_init(&array, sizeof(struct ContextWord));
  
  char morse_table[256][8];
  char read_buf[128];
  struct ContextWord context_words[128];
  struct ContextWord delta;
  
  /* Read the Morse code table */
  while (scanf("%s", read_buf) == 1 && read_buf[0] != '*') {
    var digit = read_buf[0];
    scanf("%s", morse_table[digit]);
  }
  /* Read the context section */
  var cw_count = 0;
  while (
    scanf("%s", context_words[cw_count].plain) == 1 &&
    context_words[cw_count].plain[0] != '*'
  ) {
    context_words[cw_count].id = cw_count;
    get_morse_508(morse_table, &context_words[cw_count]);
    cw_count += 1;
  }
  /* Read morse words and process */
  while (scanf("%s", read_buf) == 1 && read_buf[0] != '*') {
    /* Find perfect match */
    array_remove_all(&array);
    var i = 0;
    for (i = 0; i < cw_count; i += 1) {
      if (strcmp(read_buf, context_words[i].morse) == 0) { /* Perfect match */
        array_append(&array, &context_words[i]);
      }
    }
    if (!array.is_empty) {
      printf("%s", ((struct ContextWord*)array._storage)[0].plain);
      if (array.count != 1) { /* Multiple matches */
        printf("!");
      }
      printf("\n");
    } else { /* matches the longest prefix */
      var min_len = 0x7fffffff;
      i = 0;
      for (i = 0; i < cw_count; i += 1) {
        if (
          string_starts(context_words[i].morse, read_buf) ||
          string_starts(read_buf, context_words[i].morse)
        ) {
          var count = abs(
            (int)strlen(context_words[i].morse) -
            (int)strlen(read_buf)
          );
          if (min_len >= count) {
            min_len = count;
            delta = context_words[i];
          }
        }
      }
      printf("%s?\n", delta.plain);
    }
  }
  
  array_deinit(&array);
}
