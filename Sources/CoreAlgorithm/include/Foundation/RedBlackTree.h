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

#include "CFoundation.h"
#include "Number.h"

enum RedBlackTreeColor {
  RED_BLACK_TREE_COLOR_RED,
  RED_BLACK_TREE_COLOR_BLACK
};

struct RedBlackTreeNode {
  AnyObject key;
  AnyObject value;
  struct RedBlackTreeNode* children[2];
  struct RedBlackTreeNode* parent;
  Int64 count; /* Duplicate key counts */
  Int64 size; /* Subtree size. */
  enum RedBlackTreeColor color;
};

/**
 * An ordered collection of key-value pairs.
 *
 * A RedBlackTree is a type of tree, providing efficient read and write
 * operations to the entries it contains. Each entry in the sorted dictionary is
 * identified using a key, which is a comparable type such as a string or
 * number. You can use that key to retrieve the corresponding value.
 */
struct RedBlackTree {
  struct RedBlackTreeNode* _root;

  struct RedBlackTreeNode* _nil;

  /**
   * The number of key-value pairs in the tree.
   */
  Int64 count;

  /**
   * The size of the `Key` type of the tree.
   */
  Int64 _key_width;

  /**
   * The size of the `Value` type of the tree.
   */
  Int64 _value_width;

  /**
   * The predicate that returns an integer less than, equal to, or greater than
   * zero if the first argument is considered to be respectively less than,
   * equal to, or greater than the second.
   */
  Int32 (*compare)(AnyConstantObject, AnyConstantObject);

  /**
   * A Boolean value indicating whether a tree allows duplicate keys.
   */
  Bool allow_duplicates;
};

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
