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

static struct _RedBlackTreeNode*
red_black_tree_node_init(AnyObject key,
                         AnyObject value,
                         Int64 key_width,
                         Int64 value_width,
                         Int64 size,
                         Int64 count,
                         struct _RedBlackTreeNode* left,
                         struct _RedBlackTreeNode* right,
                         struct _RedBlackTreeNode* parent,
                         enum _RedBlackTreeColor color) {
  let node_size = sizeof(struct _RedBlackTreeNode);
  var node = (struct _RedBlackTreeNode*)malloc(node_size);

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

static Void red_black_tree_node_deinit(struct _RedBlackTreeNode* node) {
  free(node->key);
  free(node->value);
  free(node);
}

/* Destroys a tree using post-tree travesal. */
static Void _red_black_tree_deinit(struct RedBlackTree* tree,
                                   struct _RedBlackTreeNode* node) {
  if (node != tree->_nil) {
    _red_black_tree_deinit(tree, node->children[0]);
    _red_black_tree_deinit(tree, node->children[1]);
    red_black_tree_node_deinit(node);
  }
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
                                  struct _RedBlackTreeNode* x,
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
                                        struct _RedBlackTreeNode* node) {
  struct _RedBlackTreeNode* parent;
  struct _RedBlackTreeNode* grandparent;
  struct _RedBlackTreeNode* y;
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

static struct _RedBlackTreeNode*
red_black_tree_minimum(struct RedBlackTree* tree, struct _RedBlackTreeNode* x) {
  while (x->children[0] != tree->_nil) {
    x = x->children[0];
  }
  return x;
}

static struct _RedBlackTreeNode*
red_black_tree_maximum(struct RedBlackTree* tree, struct _RedBlackTreeNode* x) {
  while (x->children[1] != tree->_nil) {
    x = x->children[1];
  }
  return x;
}

/*
 * Replaces one subtree as a child of its parent with another subtree.
 * When transplant(tree, u, v) replaces the subtree rooted at node u with the
 * subtree rooted at node v, node u's parent becomes node v's parent, and u's
 * parent ends up having v as its appropriate child.
 */
static Void red_black_tree_transplant(struct RedBlackTree* tree,
                                      struct _RedBlackTreeNode* u,
                                      struct _RedBlackTreeNode* v) {
  if (u->parent == tree->_nil){
    tree->_root = v;
  } else {
    u->parent->children[(u == u->parent->children[0]) ? 0 : 1] = v;
  }
  v->parent = u->parent;
}

/*
 * Maintain the red black tree property violated by remove.
 *
 * Notes from CLRS 3e:
 * Case 1: x's sibling w is red, {[A]: red node, (A): black node}
 *
 *           |                                   |
 *          (B)                                 (D)
 *         /   \                               /   \
 *        /     \                             /     \
 *       /       \                           /       \
 *      /         \ w                       /         \
 *  x (A)         [D]    ------------>    [B]         (E)
 *   /   \       /   \                   /   \new w  /   \
 *  a     b    (C)   (E)             x (A)   (C)    e     f
 *             / \   / \               / \   / \
 *            c   d e   f             a   b c   d
 *
 * Since w must have black children, we can switch the colors of w and x.p and
 * then perform a left-rotation on x.p without violating any of the red-black
 * properties. The new sibling of x, which is one of w's children prior to the
 * rotation, is now black, and thus we have converted case 1 into case 2, 3, or
 * 4.
 *
 * Case 2: x's sibling w is black, and both of w's children are black
 *
 *           |                                   | new x
 *         [(B)]                              c[(B)]
 *         /   \                               /   \
 *        /     \                             /     \
 *       /       \                           /       \
 *      /         \ w                       /         \
 *  x (A)         (D)    ------------>    (A)         [D]
 *   /   \       /   \                   /   \       /   \
 *  a     b    (C)   (E)                a     b    (C)   (E)
 *             / \   / \                           / \   / \
 *            c   d e   f                         c   d e   f
 *
 * Since w is also black, we take one black off both x and w, leaving x with
 * only one black and leaving w red. To compensate for removing one black from
 * x and w, we would like to add an extra black to x.p, which originally either
 * red or black. We do so by repeating the while loop with x.p as the new node
 * x.
 *
 * Case 3: x's sibling w is black, w's left child is red, and w's right child
 * is black
 *
 *           |                                   |
 *       c [(B)]                              c[(B)]
 *         /   \                               /   \
 *        /     \                             /     \
 *       /       \                           /       \
 *      /         \ w                       /         \ new w
 *  x (A)         (D)    ------------>  x (A)         (C)
 *   /   \       /   \                   /   \       /   \
 *  a     b    [C]   (E)                a     b     c    [D]
 *             / \   / \                                 / \
 *            c   d e   f                               d  (E)
 *                                                         / \
 *                                                        e   f
 *
 * We can switch the colors of w and its left child w.left and then perform a
 * right rotation on w without violating any of the red-black properties. The
 * new sibling w of x is now a black node with a red right child, and thus we
 * have transformed case 3 into case 4.
 *
 * Case 4: x's sibling w is black, and w's right child is red
 *
 *           |                                   |
 *       c [(B)]                              c[(D)]
 *         /   \                               /   \
 *        /     \                             /     \
 *       /       \                           /       \
 *      /         \ w                       /         \
 *  x (A)         (D)    ------------>    (B)         (E)
 *   /   \    c' /   \                   /   \  c'   /   \
 *  a     b   [(C)]  [E]               (A)  [(C)]    e     f
 *             / \   / \               / \   / \
 *            c   d e   f             a   b c   d    new x = T.root
 *
 * By making some color changes and performing a left rotation on x.p, we can
 * remove the extra black on x, making it singly black, without violating any
 * of the red-black properties. Setting x to be the root causes the while loop
 * to terminate when it tests the loop condition.
 */
static void red_black_tree_delete_fixup(struct RedBlackTree* tree,
                                        struct _RedBlackTreeNode* node) {
  var x = node;
  struct _RedBlackTreeNode* parent;
  struct _RedBlackTreeNode* w;
  var is_left = 0;
  while (x != tree->_root && x->color == RED_BLACK_TREE_COLOR_BLACK) {
    parent = x->parent;
    is_left = x == x->parent->children[0] ? 1 : 0;
    w = parent->children[is_left];
    if (w->color == RED_BLACK_TREE_COLOR_RED) { /* Case 1 */
      parent->color = RED_BLACK_TREE_COLOR_RED;
      w->color = RED_BLACK_TREE_COLOR_BLACK;
      red_black_tree_rotate(tree, parent, is_left ^ 1);
      w = parent->children[is_left];
    }
    if (w->children[0]->color == RED_BLACK_TREE_COLOR_BLACK &&
        w->children[1]->color == RED_BLACK_TREE_COLOR_BLACK) { /* Case 2 */
      w->color = RED_BLACK_TREE_COLOR_RED;
      x = x->parent;
    } else {
      if (w->children[is_left]->color == RED_BLACK_TREE_COLOR_BLACK) {
        /* Case 3 */
        w->color = RED_BLACK_TREE_COLOR_RED;
        w->children[is_left ^ 1]->color = RED_BLACK_TREE_COLOR_BLACK;
        red_black_tree_rotate(tree, w, is_left);
        w = parent->children[is_left];
      }
      /* Case 4 */
      w->color = parent->color;
      parent->color = RED_BLACK_TREE_COLOR_BLACK;
      w->children[is_left]->color = RED_BLACK_TREE_COLOR_BLACK;
      red_black_tree_rotate(tree, w->parent, is_left ^ 1);
      x = tree->_root;
    }
  }
  x->color = RED_BLACK_TREE_COLOR_BLACK;
}

/* MARK: - Creating and Destroying a Tree */

/* Creates a new, empty tree. */
struct RedBlackTree*
red_black_tree_init(Int64 key_width,
                    Int64 value_width,
                    Int32 (*compare)(AnyConstantObject, AnyConstantObject)) {
  struct RedBlackTree* tree;
  if ((tree = malloc(sizeof(struct RedBlackTree))) == NULL) {
    return NULL;
  }

  tree->_key_width = key_width;
  tree->_value_width = value_width;
  tree->count = 0;
  tree->_compare = compare;

  tree->_nil = red_black_tree_node_init(NULL, /* key */
                                        NULL, /* value */
                                        key_width,
                                        value_width,
                                        0, /* size */
                                        0, /* count */
                                        NULL, /* left */
                                        NULL, /* right */
                                        NULL, /* parent */
                                        RED_BLACK_TREE_COLOR_BLACK);

  tree->_root = tree->_nil;
  tree->_root->parent = tree->_nil;

  return tree;
}

/* Destroys a tree. */
Void red_black_tree_deinit(struct RedBlackTree* tree) {
  _red_black_tree_deinit(tree, tree->_root);
  red_black_tree_node_deinit(tree->_nil);

  free(tree);
}

/* MARK: - Accessing Keys and Values */

/* Returns the minimum key and its associated value, if available. */
Void red_black_tree_min(struct RedBlackTree* tree,
                        AnyObject key,
                        AnyObject value) {
  if (tree->count <= 0) {
    return;
  }
  var minimum = red_black_tree_minimum(tree, tree->_root);
  if (minimum->key != NULL && key != NULL) {
    memcpy(key, minimum->key, tree->_key_width);
  }
  if (minimum->value != NULL && value != NULL) {
    memcpy(value, minimum->value, tree->_value_width);
  }
}

/* Returns the maximum key and its associated value, if available. */
Void red_black_tree_max(struct RedBlackTree* tree,
                        AnyObject key,
                        AnyObject value) {
  if (tree->count <= 0) {
    return;
  }
  var maximum = red_black_tree_maximum(tree, tree->_root);
  if (maximum->key != NULL && key != NULL) {
    memcpy(key, maximum->key, tree->_key_width);
  }
  if (maximum->value != NULL && value != NULL) {
    memcpy(value, maximum->value, tree->_value_width);
  }
}

/* MARK: - Adding Keys and Values */

/* Adds a new key-value pair if the key does not exist. */
Void red_black_tree_insert(struct RedBlackTree* tree,
                           AnyObject key,
                           AnyObject value) {
  /*
   * This works by creating a new red node with the key to where it belongs
   * in the tree, using binary search and then fix red black tree property
   * by calling insert_fixup().
   */
  var x = tree->_root;
  var y = tree->_nil;
  var z = red_black_tree_node_init(key,
                                   value,
                                   tree->_key_width,
                                   tree->_value_width,
                                   1, /* size */
                                   1, /* count */
                                   tree->_nil, /* left */
                                   tree->_nil, /* right */
                                   tree->_nil, /* p */
                                   RED_BLACK_TREE_COLOR_RED);
  var is_key_exists = false;
  while (x != tree->_nil) { /* Find the position to insert */
    y = x;
    y->size += 1;
    if (tree->_compare(x->key, key) == 0) {
      is_key_exists = true;
      break;
    }
    x = x->children[(tree->_compare(x->key, key) < 0) ? 1 : 0];
  }
  if (is_key_exists) {
    /* Restore substree sizes */
    while (x != tree->_nil) {
      x->size -= 1;
      x = x->parent;
    }
    return;
  }
  z->parent = y;
  if (y == tree->_nil) {
    tree->_root = z;
  } else {
    y->children[(tree->_compare(y->key, key) < 0) ? 1 : 0] = z;
  }
  red_black_tree_insert_fixup(tree, z);
  /* Update tree size */
  tree->count += 1;
}

/* MARK: - Removing Keys and Values */

/* Removes the given key and its associated value from the tree. */
Void red_black_tree_remove(struct RedBlackTree* tree,
                           AnyObject key,
                           AnyObject value) {
  _precondition(tree->count > 0,
                "Can't remove key-value pair from an empty tree.");

  var z = tree->_root;
  var w = tree->_nil;
  struct _RedBlackTreeNode* y;
  struct _RedBlackTreeNode* x;
  struct _RedBlackTreeNode* delta;
  enum _RedBlackTreeColor old_color;
  while (z != tree->_nil) { /* Find a node z with the specific key. */
    w = z;
    w->size -= 1;
    if (tree->_compare(key, z->key) == 0) {
      break;
    }
    z = z->children[tree->_compare(z->key, key) < 0 ? 1 : 0];
  }
  if (z != tree->_nil) {
    if (z->count > 1) {
      tree->count -= 1;
      z->count -= 1;
      return;
    }
    y = z;
    old_color = y->color;
    if (z->children[0] == tree->_nil) {
      x = z->children[1];
      red_black_tree_transplant(tree, z, z->children[1]);
    } else if (z->children[1] == tree->_nil) {
      x = z->children[0];
      red_black_tree_transplant(tree, z, z->children[0]);
    } else {
      y = red_black_tree_minimum(tree, z->children[1]);
      old_color = y->color;
      x = y->children[1];
      if (y->parent == z) {
        x->parent = y;
      } else {
        delta = y;
        while (delta != z) {
          delta->size -= y->count;
          delta = delta->parent;
        }
        red_black_tree_transplant(tree, y, y->children[1]);
        y->children[1] = z->children[1];
        y->children[1]->parent = y;
      }
      red_black_tree_transplant(tree, z, y);
      y->children[0] = z->children[0];
      y->children[0]->parent = y;
      y->color = z->color;
      y->size =
        y->children[0]->size + y->children[1]->size + y->count;
    }
    if (old_color == RED_BLACK_TREE_COLOR_BLACK) {
      red_black_tree_delete_fixup(tree, x);
    }
    if (value != NULL && z->value != NULL) {
      memcpy(value, z->value, tree->_value_width);
    }
    red_black_tree_node_deinit(z);
    tree->count -= 1;
  } else { /* No such key, restore subtree sizes */
    while (w != tree->_nil) {
      w->size += 1;
      w = w->parent;
    }
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
