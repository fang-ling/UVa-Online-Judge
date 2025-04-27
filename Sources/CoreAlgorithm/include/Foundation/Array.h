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
 * This source file is part of the CoreAlgorithm open source project.
 *
 * Copyright (c) 2024-2025 Fang Ling All Rights Reserved.
 *
 * Use of this source code is governed by the Apache License, Version 2.0
 * that can be found in the LICENSE file in the root of the source tree.
 * This source code may include problem descriptions from some online judges,
 * which have their own licensing terms.
 */

#ifndef Array_h
#define Array_h

#include "_Foundation.h"

/**
 * An ordered, random-access collection.
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
  Int64 _capacity;

  /**
   * The number of elements in the array.
   */
  Int64 count;

  /**
   * The size of the `Element` type of the array.
   */
  Int64 _width;

  AnyObject _buffer;
};

/* MARK: - Creating and Destroying an Array */

/**
 * Creates a new, empty array.
 *
 * - Parameter width: The size of the `Element` type of the array.
 *
 * - Returns: The newly created array object, or NULL if memory allocation
 *            fails.
 *
 * > Warning: It is the caller's responsibility to deinitialize the array using
 *            ``array_deinit`` when it is no longer needed to prevent memory
 *            leaks.
 *
 * Here is an example to create an array:
 *
 * ```c
 * var array = array_init(sizeof(Int32));
 *
 * if (array->count == 0) {
 *   // true
 * }
 * ```
 */
struct Array* array_init(Int64 width);

/**
 * Destroys an array.
 *
 * This function safely frees all the resources associated with the array. After
 * calling this function, the array should no longer be used, as all elements in
 * that array will be invalidated.
 *
 * - Parameter array: The array object to be deinitialized, if array is a `NULL`
 *                    pointer, no operation is performed.
 */
Void array_deinit(struct Array* array);

/* MARK: - Adding and Removing Elements */

/**
 * Adds an element to the end of the array.
 *
 * Use this function to append a single element to the end of a mutable array.
 *
 * ```c
 * var numbers = array_init(sizeof(Int32));
 *
 * var i = 0;
 * for (; i < 5; i += 1) {
 *   array_append(numbers, &i);
 * }
 *
 * // numbers = [0, 1, 2, 3, 4]
 * ```
 *
 * Because arrays increase their allocated capacity using an exponential
 * strategy, appending a single element to an array is an *O(1)* operation when
 * averaged over many calls to the `array_append` method. When an array has
 * additional capacity, appending an element is *O(1)*. When an array needs to
 * reallocate storage before appending, appending is *O(n)*, where n is the
 * length of the array.
 *
 * - Parameters:
 *   - array: The array object where the element will be appended.
 *   - new_element: The element to append to the array.
 *
 * - Complexity: *O(1)* on average, over many calls to `array_append` on the
 *               same array.
 */
Void array_append(struct Array* array, AnyObject new_element);

/**
 * Removes and returns the last element of the array.
 *
 * The array must not be empty.
 *
 * ```c
 * var numbers = array_init(sizeof(Int32));
 *
 * var i = 0;
 * for (; i < 5; i += 1) {
 *   array_append(numbers, &i);
 * }
 * // numbers = [0, 1, 2, 3, 4]
 *
 * array_remove_last(numbers, NULL); // numbers = [0, 1, 2, 3]
 *
 * var last_element = 0;
 * array_remove_last(numbers, &last_element);
 * // numbers = [0, 1, 2]
 * // last_element = 3
 * ```
 *
 * - Returns: The last element of the array. Passes `NULL` to `removed_element`
 *            if you want to ignore the return value.
 *
 * - Complexity: *O(1)* on average, over many calls to `remove_last` on the
 *               same array.
 */
Void array_remove_last(struct Array* array, AnyObject removed_element);

/**
 * Removes all elements from the array.
 *
 * - Parameter keep_capacity: Pass `true` to request that the collection avoid
 *                            releasing its storage. Retaining the collection's
 *                            storage can be a useful optimization when you're
 *                            planning to grow the collection again.
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
Void array_read(struct Array* array, Int64 index, AnyObject element);

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
Void array_write(struct Array* array, Int64 index, AnyObject element);

/* MARK: - Reordering an Array's Elements */

/**
 * Sorts the array in place, using the given predicate as the comparison between
 * elements.
 *
 * - Parameter compare: A predicate that returns an integer less than, equal to,
 *   or greater than zero if the first argument is considered to be respectively
 *   less than, equal to, or greater than the second.
 */
Void array_sort(struct Array* array, Comparable comparator);

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
