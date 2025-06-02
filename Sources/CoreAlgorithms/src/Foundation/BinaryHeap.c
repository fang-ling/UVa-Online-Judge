/*===----------------------------------------------------------------------===*/
/*                                                        ___   ___           */
/* BinaryHeap.c                                         /'___\ /\_ \          */
/*                                                     /\ \__/ \//\ \         */
/* Author: Fang Ling (fangling@fangl.ing)              \ \ ,__\  \ \ \        */
/* Date: February 5, 2025                               \ \ \_/__ \_\ \_  __  */
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

#include "Foundation/BinaryHeap.h"

/* MARK: - Private methods */

#define binary_heap_parent(i) (((i) - 1) / 2)
#define binary_heap_left(i) (2 * (i) + 1)
#define binary_heap_right(i) (2 * (i) + 2)

/* Maintain the max heap property from node i all the way up to root. */
static Void binary_heap_max_heapify_up(struct BinaryHeap* heap, Int64 i) {
  if (i == 0) { /* We are at root node now. */
    return;
  }
  /* A[parent(i)] <= A[i] */
  var a_p_i = heap->_buffer + binary_heap_parent(i) * heap->_width;
  var a_i = heap->_buffer + i * heap->_width;
  if (heap->compare(a_p_i, a_i) <= 0) {
    /* Exchange i with parent(i) */
    _memswap(a_p_i, a_i, heap->_width);
    /*
     * Current node is satisfy max heap property, but maybe not its parent.
     * Fix this recursively.
     */
    binary_heap_max_heapify_up(heap, binary_heap_parent(i));
  }
}

/* Maintain the max heap property from node i all the way down to leaf. */
static Void binary_heap_max_heapify_down(struct BinaryHeap* heap, Int64 i) {
  if (i >= heap->count / 2) { /* No children, we are done */
    return;
  }

  var l_i = binary_heap_left(i);
  var r_i = binary_heap_right(i);
  var j = -1ll;
  /* Find i's largest children j. */
  if (l_i < heap->count && r_i < heap->count) {
    /* Both children exist */
    var left = heap->_buffer + l_i * heap->_width;
    var right = heap->_buffer + r_i * heap->_width;
    j = heap->compare(left, right) > 0 ? l_i : r_i;
  } else if (l_i < heap->count && r_i >= heap->count) {
    /* Left only */
    j = l_i;
  } else if (l_i >= heap->count && r_i < heap->count) {
    /* Right only */
    j = r_i;
  }
  /*
   * If i is smaller than j (i's largest child), we are violate the max
   * heap property. Fix it by swap i.key with j.key and then recur on j.
   */
  var a_i = heap->_buffer + i * heap->_width;
  var a_j = heap->_buffer + j * heap->_width;
  if (heap->compare(a_i, a_j) <= 0) {
    _memswap(a_i, a_j, heap->_width);
    binary_heap_max_heapify_down(heap, j);
  }
}

/* MARK: - Creating and Destroying a Heap */

/**
 * Creates a new, empty heap.
 */
struct BinaryHeap*
binary_heap_init(Int64 width,
                 Int32 (*compare)(AnyConstantObject, AnyConstantObject)) {
  struct BinaryHeap* heap;
  if ((heap = malloc(sizeof(struct BinaryHeap))) == NULL) {
    return NULL;
  }

  heap->_buffer = NULL;
  heap->_width = width;
  heap->count = 0;
  heap->_capacity = 0;
  heap->compare = compare;

  return heap;
}

/**
 * Destroys a heap.
 */
Void binary_heap_deinit(struct BinaryHeap* heap) {
  free(heap->_buffer);
  free(heap);
}

/* MARK: - Adding and Removing Elements */

/**
 * Inserts the given element into the heap.
 */
Void binary_heap_insert(struct BinaryHeap* heap, AnyObject new_element) {
  if (heap->_capacity == 0) {
    /* Allocate buffer with 1 slot */
    heap->_buffer = realloc(heap->_buffer, 1 * heap->_width);
    heap->_capacity = 1;
  }

  if (heap->count == heap->_capacity) {
    /* Re-allocate buffer with 2 * capacity slots */
    heap->_capacity *= 2;
    heap->_buffer = realloc(heap->_buffer, heap->_capacity * heap->_width);
  }

  memcpy(heap->_buffer + heap->count * heap->_width,
         new_element,
         heap->_width);

  heap->count += 1;

  binary_heap_max_heapify_up(heap, heap->count - 1);
}

/**
 * Removes and returns the element with the highest priority.
 */
Void binary_heap_pop_max(struct BinaryHeap* heap, AnyObject removed_element) {
  _precondition(heap->count > 0,
                "Can't remove last element from an empty heap");

  _memswap(heap->_buffer + 0 * heap->_width,
               heap->_buffer + (heap->count - 1) * heap->_width,
               heap->_width);


  if (removed_element != NULL) {
    memcpy(removed_element,
           heap->_buffer + (heap->count - 1) * heap->_width,
           heap->_width);
  }

  heap->count -= 1;
  if (heap->count * 4 <= heap->_capacity) {
    heap->_capacity /= 4;
    heap->_buffer = realloc(heap->_buffer, heap->_capacity * heap->_width);
  }

  binary_heap_max_heapify_down(heap, 0);
}

/* MARK: - Accessing Elements */

/**
 * Reads the element with the highest priority.
 */
Void binary_heap_max(struct BinaryHeap* heap, AnyObject element) {
  _precondition(heap->count > 0,
                "Can't access largest element from an empty heap");
  memcpy(element, heap->_buffer + 0 * heap->_width, heap->_width);
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
