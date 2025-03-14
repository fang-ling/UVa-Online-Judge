/*===----------------------------------------------------------------------===*/
/*                                                        ___   ___           */
/* RedBlackTree.h                                       /'___\ /\_ \          */
/*                                                     /\ \__/ \//\ \         */
/* Author: Fang Ling (fangling@fangl.ing)              \ \ ,__\  \ \ \        */
/* Date: March 1, 2025                                  \ \ \_/__ \_\ \_  __  */
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

#ifndef RedBlackTree_h
#define RedBlackTree_h

#include "_Foundation.h"

enum _RedBlackTreeColor {
  RED_BLACK_TREE_COLOR_RED,
  RED_BLACK_TREE_COLOR_BLACK
};

struct _RedBlackTreeNode {
  AnyObject key;
  AnyObject value;
  struct _RedBlackTreeNode* children[2];
  struct _RedBlackTreeNode* parent;
  Int64 count; /* Duplicate key counts */
  Int64 size; /* Subtree size. */
  enum _RedBlackTreeColor color;
};

/**
 * A sorted collection of key-value pairs.
 *
 * A ``RedBlackTree`` is a type of tree, providing efficient read and write
 * operations to the pairs it contains. Each pair in the tree is identified
 * using a key, which is a comparable type such as a string or number. You can
 * use that key to retrieve the associated value.
 *
 * TODO Add more summary
 */
struct RedBlackTree {
  struct _RedBlackTreeNode* _root;

  struct _RedBlackTreeNode* _nil;

  /**
   * The number of key-value pairs in the tree.
   */
  Int64 count;

  Int64 _key_width;

  Int64 _value_width;

  /**
   * The comparator used to maintain order in this tree. it must return a 32-bit
   * integer less than, equal to, or greater than zero if the first argument is
   * considered to be respectively less than, equal to, or greater than the
   * second.
   */
  Int32 (*_compare)(AnyConstantObject, AnyConstantObject);
};

/* MARK: - Creating and Destroying a Tree */

/**
 * Creates a new, empty tree.
 *
 * - Parameters:
 *   - key_width: The size of the key type of the tree.
 *   - value_width: The size of the value type of the tree.
 *   - compare: A predicate that returns a 32-bit integer less than, equal to,
 *              or greater than zero if the first argument is considered to be
 *              respectively less than, equal to, or greater than the second.
 *
 * - Returns: The newly created tree object, or NULL if memory allocation fails.
 *
 * > Warning: It is the caller's responsibility to deinitialize the tree using
 * ``red_black_tree_deinit`` when it is no longer needed to prevent memory
 * leaks.
 *
 * Here is an example to create a tree:
 *
 * ```c
 * Int32 compare(AnyConstantObject _lhs, AnyConstantObject _rhs) {
 *   var lhs = *(Int32*)_lhs;
 *   var rhs = *(Int32*)_rhs;
 *
 *   if (lhs < rhs) {
 *     return -1;
 *   } else if (lhs > rhs) {
 *     return 1;
 *   }
 *   return 0;
 * }
 *
 * var tree = red_black_tree_init(sizeof(Int32), sizeof(Int32), compare);
 * ```
 */
struct RedBlackTree*
red_black_tree_init(Int64 key_width,
                    Int64 value_width,
                    Int32 (*compare)(AnyConstantObject, AnyConstantObject));

/**
 * Destroys a tree.
 *
 * This function safely frees all the resources associated with the tree,
 * including its nodes and any dynamically allocated memory. After calling this
 * function, the tree should no longer be used, as all pointers to its nodes
 * will be invalidated.
 *
 * - Parameter tree: The tree object to be deinitialized.
 *
 * - Complexity: *O(n)*, where *n* is the number of key-value pairs in the tree.
 */
Void red_black_tree_deinit(struct RedBlackTree* tree);

/* MARK: - Accessing Keys and Values */

/**
 * Returns the minimum key and its associated value, if available.
 *
 * This function **copies** the minimum key and its associated value to the
 * provided key and value objects if they are not `NULL`.
 *
 * - Parameters:
 *   - tree: The tree object from which to retrieve the minimum key and its
 *           value.
 *   - key: The object to store the minimum key. If `NULL`, the key will not be
 *          written.
 *   - value: The object to store the value, If `NULL`, the value will not be
 *            written.
 *
 * - Complexity: *O(log n)*, where *n* is the number of key-value pairs in the
 *               tree.
 */
Void red_black_tree_min(struct RedBlackTree* tree,
                        AnyObject key,
                        AnyObject value);

/**
 * Returns the maximum key and its associated value, if available.
 *
 * This function **copies** the maximum key and its associated value to the
 * provided key and value objects if they are not `NULL`.
 *
 * - Parameters:
 *   - tree: The tree object from which to retrieve the maximum key and its
 *           value.
 *   - key: The object to store the maximum key. If `NULL`, the key will not be
 *          written.
 *   - value: The object to store the value, If `NULL`, the value will not be
 *            written.
 *
 * - Complexity: *O(log n)*, where *n* is the number of key-value pairs in the
 *               tree.
 */
Void red_black_tree_max(struct RedBlackTree* tree,
                        AnyObject key,
                        AnyObject value);

/* MARK: - Adding Keys and Values */

/**
 * Adds a new key-value pair if the key does not exist.
 *
 * - Parameters:
 *   - tree: The tree object where the key-value pair will be inserted.
 *   - key: The key to associate with value. If key already exists in the tree,
 *          no action is taken, and the tree remains unchanged.
 *   - value: The new value to add to the tree.
 *
 * - Complexity: *O(log n)*, where *n* is the number of key-value pairs in the
 *               tree.
 */
Void red_black_tree_insert(struct RedBlackTree* tree,
                           AnyObject key,
                           AnyObject value);

/* MARK: - Removing Keys and Values */

/**
 * Removes the given key and its associated value from the tree.
 *
 * If the key is found in the tree, this method copiess the removed key's
 * associated value to the given value object, if it is not `NULL`.
 *
 * - Parameters:
 *   - tree: The tree object from which to remove the key-value pair.
 *   - key: The key to remove along with its associated value.
 *   - value: An object to store the value of the removed key-value pair.
 *
 *  - Complexity: *O(log n)*, where *n* is the number of key-value pairs in the
 *                tree.
 */
Void red_black_tree_remove(struct RedBlackTree* tree,
                           AnyObject key,
                           AnyObject value);

#endif /* RedBlackTree_h */

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
