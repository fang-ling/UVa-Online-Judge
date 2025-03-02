/*===----------------------------------------------------------------------===*/
/*                                                        ___   ___           */
/* RedBlackTree.c                                       /'___\ /\_ \          */
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

#include "Foundation/RedBlackTree.h"

/* MARK: - Private methods */

static struct RedBlackTreeNode*
red_black_tree_node_init(AnyObject key,
                         AnyObject value,
                         Int64 key_width,
                         Int64 value_width,
                         Int64 size,
                         Int64 count,
                         struct RedBlackTreeNode* left,
                         struct RedBlackTreeNode* right,
                         struct RedBlackTreeNode* parent,
                         enum RedBlackTreeColor color) {
  var node = (struct RedBlackTreeNode*)malloc(sizeof(struct RedBlackTreeNode));

  node->children[0] = left;
  node->children[1] = right;
  node->parent = parent;
  node->color = color;
  node->count = count;
  node->size = size;

  node->key = malloc(key_width);
  if (key != NULL) {
    memcpy(node->key, key, key_width);
  }

  node->value = malloc(value_width);
  if (value != NULL) {
    memcpy(node->value, value, value_width);
  }

  return node;
}

static Void red_black_tree_node_deinit(struct RedBlackTreeNode* node) {
  free(node->key);
  free(node->value);
  free(node);
}

/*
 * RedBlackTree Rotation: Modify tree structure without breaking binary search
 * tree property, i.e. x.left.key < x.key < x.right.key
 *
 *        |                               |
 *       [y]       left_rotate(x)        [x]
 *      /   \      <--------------      /   \
 *    [x]    c                         a    [y]
 *   /   \         -------------->         /   \
 *  a     b        right_rotate(y)        b     c
 */
static Void red_black_tree_rotate(struct RedBlackTree* tree,
                                  struct RedBlackTreeNode* x,
                                  Int32 is_right) {
  var y = x->children[is_right ^ 1];
  x->children[is_right ^ 1] = y->children[is_right];
  if (y->children[is_right] != tree->_nil) {
    y->children[is_right]->parent = x;
  }
  y->parent = x->parent;
  if (x->parent == tree->_nil) {
    tree->_root = y;
  } else {
    x->parent->children[x == x->parent->children[1] ? 1 : 0] = y;
  }
  y->children[is_right] = x;
  x->parent = y;
  /* Maintain augmented data */
  y->size = x->size;
  x->size = x->children[0]->size + x->children[1]->size + x->count;
}

/*
 * Maintain the RedBlackTree property violated by insert.
 *
 * Notes from CLRS 3e:
 * Case 1: z's uncle y is red, {[A]: red node, (A): black node}
 *
 *           |                                   |
 *          (C)                                 [z] <--~ {new z}
 *         /   \                               /   \
 *        /     \                             /     \
 *       /       \                           / _old z\
 *      /         \                         / /       \
 *    [A]         [y]    ------------>    (A) |       (y)
 *   /   \       /   \                   /   \|      /   \
 *  a    [z]    d     e                 a    [z]    d     e
 *      /   \                               /   \
 *     b     c                             b     c
 *
 * Because z.p.p (in here: C) is black, we can color both z.p (A) and y black,
 * thereby fixing the problem of z and z.p (A) both being red, and we can color
 * z.p.p (C) red, thereby maintaining property 5. We then repeat the while loop
 * with z.p.p (C) as the new node z. The pointer z moves up two levels in the
 * tree.
 *
 * Case 2: z's uncle y is black, and z is a right child.
 * Case 3: z's uncle y is black, and z is a left child.
 *
 *           |                                  |
 *          (C)                                (C)
 *         /   \                              /   \
 *        /     \       left-rotate(A)       /     \
 *       /       \      ------------->      /       \
 *      /         \                        /         \
 *    [A]          d y                   [B]          d y
 *   /   \                              /   \
 *  a    [B]z                         [A]z   c
 *      /   \                        /   \
 *     b     c                      a     b
 *              Case 2                        Case 3
 *
 *                                              |
 *                              right-rotate(C) |
 *                                              |
 *                                              V
 *
 *                                              |
 *                                             (C)
 *                                            /   \
 *                                           /     \
 *                                          /       \
 *                                         /         \
 *                                       [A]         [B]
 *                                      /   \       /   \
 *                                     a     b     c     d
 *
 * In case 2 and 3, the color of z's uncle y is black. We distinguish the two
 * cases according to whether z is a right or left child of z.p. In case 2,
 * node z is a right child of its parent. We immediately use a left rotation
 * to transform the situation into case 3, in which node z is a left child.
 * Because both z and z.p are red, the rotation affects neither the black-
 * height of nodes nor property 5. Whether we enter case 3 directly or through
 * case 2, z's uncle y is black, since otherwise we would have executed case 1.
 * Additionally, the node z.p.p exists. In case 3, we execute some color
 * changes and a right rotation, which preserve property 5, and then, since we
 * no longer have two red nodes in a row, we are done. The while loop does not
 * iterate another time, since z.p is now black.
 */
static Void red_black_tree_insert_fixup(struct RedBlackTree* tree,
                                        struct RedBlackTreeNode* node) {
  struct RedBlackTreeNode* parent;
  struct RedBlackTreeNode* grandparent;
  struct RedBlackTreeNode* y;
  var z = node;
  while (z->parent->color == RED_BLACK_TREE_COLOR_RED) {
    parent = z->parent;
    grandparent = parent->parent;
    var is_left = parent == grandparent->children[0] ? 1 : 0;
    y = grandparent->children[is_left];
    if (y->color == RED_BLACK_TREE_COLOR_RED) { /* Case 1 */
      y->color = RED_BLACK_TREE_COLOR_BLACK;
      parent->color = RED_BLACK_TREE_COLOR_BLACK;
      grandparent->color = RED_BLACK_TREE_COLOR_RED;
      z = grandparent;
    } else {
      if (z == parent->children[is_left]) { /* Case 2 */
        z = parent;
        red_black_tree_rotate(tree, z, is_left ^ 1);
      }
      /* Case 3 */
      z->parent->color = RED_BLACK_TREE_COLOR_BLACK;
      z->parent->parent->color = RED_BLACK_TREE_COLOR_RED;
      red_black_tree_rotate(tree, grandparent, is_left);
    }
  }
  tree->_root->color = RED_BLACK_TREE_COLOR_BLACK;
}

/*
 * Replaces one subtree as a child of its parent with another subtree.
 * When transplant(tree, u, v) replaces the subtree rooted at node u with the
 * subtree rooted at node v, node u's parent becomes node v's parent, and u's
 * parent ends up having v as its appropriate child.
 */
static Void red_black_tree_transplant(struct RedBlackTree* tree,
                                      struct RedBlackTreeNode* u,
                                      struct RedBlackTreeNode* v) {
  if (u->parent == tree->_nil){
    tree->_root = v;
  } else {
    u->parent->children[(u == u->parent->children[0]) ? 0 : 1] = v;
  }
  v->parent = u->parent;
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
