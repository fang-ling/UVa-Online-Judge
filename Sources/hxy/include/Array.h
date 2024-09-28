/*===----------------------------------------------------------------------===*/
/*                                                        ___   ___           */
/* Array.h                                              /'___\ /\_ \          */
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

#ifndef Array_h
#define Array_h

#include "Foundation.h"

/**
 * An ordered, random-access collection.
 *
 * Arrays are one of the most commonly used data types in an app. You use
 * arrays to organize your app's data. Specifically, you use the `Array` type
 * to hold elements of a single type, the array's `Element` type. An array
 * can store any kind of elements---from integers to structures to pointers.
 */
struct Array {
  /**
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
  Int _capacity;
  
  /**
   * The number of elements in the array.
   */
  Int count;
  
  /**
   * The size of the `Element` type of the array.
   */
  Int _width;
  
  Void* _buffer;
};

/* MARK: - Creating and Destroying an Array */

/**
 * Creates a new, empty array.
 */
struct Array* array_init(Int width);

/**
 * Destroys an array.
 */
Void array_deinit(struct Array* array);

/* MARK: - Adding and Removing Elements */

/**
 * Adds an element to the end of the array.
 *
 * If the array does not have sufficient capacity for another element,
 * additional storage is allocated before appending `new_element`.
 *
 * - Parameter new_element: The element to append to the array.
 *
 * - Complexity: O(1) on average, over many calls to `append()` on the
 *   same array.
 */
Void array_append(struct Array* array, Void* new_element);

/**
 * Removes and returns the last element of the array.
 *
 * The array must not be empty.
 *
 * - Returns: The last element of the collection. Passes NULL to
 * `removed_element` if you want to ignore the return value.
 *
 * - Complexity: O(1) on average, over many calls to `remove_last()` on the
 *   same array.
 */
Void array_remove_last(struct Array* array, Void* removed_element);

/**
 * Removes all elements from the array.
 *
 * - Parameter keep_capacity: Pass `true` to request that the collection
 *   avoid releasing its storage. Retaining the collection's storage can
 *   be a useful optimization when you're planning to grow the collection
 *   again.
 *
 * - Complexity:
 *   - O(*n*), when `keep_capacity` is `false`, where *n* is the length of the
 *   array.
 *   - O(1), when `keep_capacity` is `true`.
 */
Void array_remove_all(struct Array* array, Bool keep_capacity);

/* MARK: - Accessing Elements */

/**
 * Reads the element at the specified position.
 *
 * - Parameter index: The position of the element to access. `index` must be
 *   greater than or equal to 0 and less than `count`.
 *
 * - Returns: The element at the specified position.
 *
 * - Complexity: O(1)
 */
Void array_read(struct Array* array, Int index, Void* element);

/**
 * Writes the element to the specified position.
 *
 * - Parameters:
 *   - index: The position of the element to access. `index` must be
 *   greater than or equal to 0 and less than `count`.
 *   - element: The element to be write.
 *
 * - Complexity: O(1)
 */
Void array_write(struct Array* array, Int index, Void* element);

#endif /* Array_h */

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
