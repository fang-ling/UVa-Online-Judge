/*===----------------------------------------------------------------------===*/
/*                                                        ___   ___           */
/* BinaryHeap.h                                         /'___\ /\_ \          */
/*                                                     /\ \__/ \//\ \         */
/* Author: Fang Ling (fangling@fangl.ing)              \ \ ,__\  \ \ \        */
/* Date: February 5, 2025                               \ \ \_/__ \_\ \_  __  */
/*                                                       \ \_\/\_\/\____\/\_\ */
/*                                                        \/_/\/_/\/____/\/_/ */
/*===----------------------------------------------------------------------===*/

/*
 * This source file is part of the hxy open source project.
 *
 * Copyright (c) 2024-2025 Fang Ling All Rights Reserved.
 *
 * Use of this source code is governed by the Apache License, Version 2.0
 * that can be found in the LICENSE file in the root of the source tree.
 * This source code may include problem descriptions from some online judges,
 * which have their own licensing terms.
 */

#ifndef BinaryHeap_h
#define BinaryHeap_h

#include "CFoundation.h"
#include "Number.h"

/**
 * A container type implementing a priority queue. Heap is a container of
 * Comparable elements that provides immediate access to its maximal members,
 * and supports removing these items or inserting arbitrary new items in
 * (amortized) logarithmic complexity.
 */
struct BinaryHeap {
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
   * The number of elements in the heap.
   */
  Int64 count;

  /**
   * The size of the `Element` type of the heap.
   */
  Int64 _width;

  /**
   * The predicate that returns an integer less than, equal to, or greater than
   * zero if the first argument is considered to be respectively less than,
   * equal to, or greater than the second.
   */
  Int32 (*compare)(AnyConstantObject, AnyConstantObject);

  AnyObject _buffer;
};

/* MARK: - Creating and Destroying a Heap */

/**
 * Creates a new, empty heap.
 */
struct BinaryHeap*
binary_heap_init(Int64 width,
                 Int32 (*compare)(AnyConstantObject, AnyConstantObject));

/**
 * Destroys a heap.
 */
Void binary_heap_deinit(struct BinaryHeap* heap);

/* MARK: - Adding and Removing Elements */

/**
 * Inserts the given element into the heap.
 *
 * If the heap does not have sufficient capacity for another element,
 * additional storage is allocated before inserting `new_element`.
 *
 * - Parameter new_element: The element to append to the array.
 *
 * - Complexity: O(log(count)) element comparisons on average, over many calls
 *   to `insert()` on the same heap.
 */
Void binary_heap_insert(struct BinaryHeap* heap, AnyObject new_element);

/**
 * Removes and returns the element with the highest priority.
 *
 * The heap must not be empty.
 *
 * - Returns: The last element of the collection. Passes NULL to
 *   `removed_element` if you want to ignore the return value.
 *
 * - Complexity: O(log(count)) element comparisons on average, over many calls
 *   to `pop_max()` on the same heap.
 */
Void binary_heap_pop_max(struct BinaryHeap* heap, AnyObject removed_element);

/* MARK: - Accessing Elements */

/**
 * Reads the element with the highest priority.
 *
 * - Returns: The element with the highest priority.
 *
 * - Complexity: O(1)
 */
Void binary_heap_max(struct BinaryHeap* heap, AnyObject element);

#endif /* BinaryHeap_h */

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
