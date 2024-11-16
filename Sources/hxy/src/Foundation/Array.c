/*===----------------------------------------------------------------------===*/
/*                                                        ___   ___           */
/* Array.c                                              /'___\ /\_ \          */
/*                                                     /\ \__/ \//\ \         */
/* Author: Fang Ling (fangling@fangl.ing)              \ \ ,__\  \ \ \        */
/* Date: September 16, 2024                             \ \ \_/__ \_\ \_  __  */
/*                                                       \ \_\/\_\/\____\/\_\ */
/*                                                        \/_/\/_/\/____/\/_/ */
/*===----------------------------------------------------------------------===*/

/*
 * This source file is part of the hxy open source project.
 *
 * Copyright (c) 2024 Fang Ling All Rights Reserved.
 *
 * Use of this source code is governed by the Apache License, Version 2.0
 * that can be found in the LICENSE file in the root of the source tree.
 * This source code may include problem descriptions from some online judges,
 * which have their own licensing terms.
 */

#include "Foundation/Array.h"

/**
 * Check that the specified `index` is valid, i.e. `0 ≤ index < count`.
 */
#define _array_check_index(index, count)                                      \
        do {                                                                  \
          precondition((index) < (count), "Array index is out of range");     \
          precondition((index) >= 0, "Negative Array index is out of range"); \
        } while(0)

/* MARK: - Creating and Destroying an Array */

/**
 * Creates a new, empty array.
 */
struct Array* array_init(Int64 width) {
  struct Array* array;
  if ((array = malloc(sizeof(struct Array))) == NULL) {
    return NULL;
  }
  
  array->_buffer = NULL;
  array->_width = width;
  array->count = 0;
  array->_capacity = 0;
  
  return array;
}

/**
 * Destroys an array.
 */
Void array_deinit(struct Array* array) {
  if (array == NULL) {
    return;
  }
  
  free(array->_buffer);
  free(array);
}

/* MARK: - Adding and Removing Elements */

/**
 * Adds an element to the end of the array.
 */
Void array_append(struct Array* array, AnyObject new_element) {
  if (array->_capacity == 0) {
    /* Allocate buffer with 1 slot */
    array->_buffer = realloc(array->_buffer, 1 * array->_width);
    array->_capacity = 1;
  }
  
  if (array->count == array->_capacity) {
    /* Re-allocate buffer with 2 * capacity slots */
    array->_capacity *= 2;
    array->_buffer = realloc(array->_buffer, array->_capacity * array->_width);
  }
  
  memcpy(
    array->_buffer + array->count * array->_width, /* dst */
    new_element,                                   /* src */
    array->_width                                  /* width */
  );
  array->count += 1;
}

/**
 * Removes and returns the last element of the array.
 */
Void array_remove_last(struct Array* array, AnyObject removed_element) {
  precondition(
    array->count > 0,
    "Can't remove last element from an empty array"
  );
  
  if (removed_element != NULL) {
    memcpy(
      removed_element,                                     /* dst */
      array->_buffer + (array->count - 1) * array->_width, /* src */
      array->_width                                        /* width */
    );
  }
  
  array->count -= 1;
  if (array->count * 4 <= array->_capacity) {
    array->_capacity /= 4;
    array->_buffer = realloc(array->_buffer, array->_capacity * array->_width);
  }
}

/**
 * Removes all elements from the array.
 */
Void array_remove_all(struct Array* array, Bool keep_capacity) {
  if (keep_capacity) {
    array->count = 0;
  } else {
    free(array->_buffer);
    array->_buffer = NULL;
    array->count = 0;
    array->_capacity = 0;
  }
}

/* MARK: - Accessing Elements */

/**
 * Reads the element at the specified position.
 */
Void array_read(struct Array* array, Int64 index, AnyObject element) {
  _array_check_index(index, array->count);
  
  if (element != NULL) {
    memcpy(element, array->_buffer + index * array->_width, array->_width);
  }
}

/**
 * Writes the element to the specified position.
 */
Void array_write(struct Array* array, Int64 index, AnyObject element) {
  _array_check_index(index, array->count);
  
  if (element != NULL) {
    memcpy(array->_buffer + index * array->_width, element, array->_width);
  }
}

/*===----------------------------------------------------------------------===*/
/*         ___                            ___                                 */
/*       /'___\                          /\_ \    __                          */
/*      /\ \__/   __      ___      __    \//\ \  /\_\    ___      __          */
/*      \ \ ,__\/'__`\  /' _ `\  /'_ `\    \ \ \ \/\ \ /' _ `\  /'_ `\        */
/*       \ \ \_/\ \L\.\_/\ \/\ \/\ \L\ \    \_\ \_\ \ \/\ \/\ \/\ \L\ \       */
/*        \ \_\\ \__/.\_\ \_\ \_\ \____ \   /\____\\ \_\ \_\ \_\ \____ \      */
/*         \/_/ \/__/\/_/\/_/\/_/\/___L\ \  \/____/ \/_/\/_/\/_/\/___L\ \     */
/*                                 /\____/                        /\____/     */
/*                                 \_/__/                         \_/__/      */
/*===----------------------------------------------------------------------===*/
