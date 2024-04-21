//
//  10391.c
//  hxy
//
//  Created by Fang Ling on 2024/4/19.
//

#include <stdio.h>

/*===----------------------------------------------------------------------===*/
/*                                                        ___   ___           */
/* RedBlackTree START                                   /'___\ /\_ \          */
/*                                                     /\ \__/ \//\ \         */
/* Author: Fang Ling (fangling@fangl.ing)              \ \ ,__\  \ \ \        */
/* Version: 1.0                                         \ \ \_/__ \_\ \_  __  */
/* Date: March 18, 2024                                  \ \_\/\_\/\____\/\_\ */
/*                                                        \/_/\/_/\/____/\/_/ */
/*===----------------------------------------------------------------------===*/

/*
 * This source file is part of the C Collections open source project
 *
 * Copyright (c) 2024 Fang Ling
 * Licensed under Apache License v2.0
 *
 * See https://github.com/fang-ling/C-Collections/blob/main/LICENSE for license
 * information
 */

#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

enum RedBlackTreeColor {
  RBT_RED,
  RBT_BLACK
};

struct RedBlackTreeNode {
  /* The key. (Element size is stored in RedBlackTree) */
  void* key;
  /* 2 pointers to its children. */
  struct RedBlackTreeNode* children[2];
  /* Pointer to its parent */
  struct RedBlackTreeNode* p;
  /* Duplicate element count for the key. */
  int count;
  /* Subtree size */
  int size;
  /* Color of the node */
  enum RedBlackTreeColor color;
};

struct RedBlackTree {
  struct RedBlackTreeNode* root;
  struct RedBlackTreeNode* nil;
  
  int element_size;
  /* The number of elements in the tree */
  int count;
  /* A Boolean value indicating whether the tree is empty. */
  bool is_empty;
  /*
   * A Boolean value indicating whether a RedBlackTree allows duplicate
   * elements.
   */
  bool allow_duplicates;
  
  int (*compare)(const void* lhs, const void* rhs);
};

#define var __auto_type

static struct RedBlackTreeNode* _red_black_tree_node_init(
  const void* key,
  int element_size,
  int size,
  int count,
  struct RedBlackTreeNode* left,
  struct RedBlackTreeNode* right,
  struct RedBlackTreeNode* p,
  enum RedBlackTreeColor color
) {
  var node = (struct RedBlackTreeNode*)malloc(sizeof(struct RedBlackTreeNode));
  
  node -> children[0] = left;
  node -> children[1] = right;
  node -> p = p;
  node -> color = color;
  node -> count = count;
  node -> size = size;
  
  node -> key = malloc(element_size); /* allocate space for key */
  if (key == NULL) {
    /*
     * If either dest or src is a null pointer,
     * the behavior is undefined, even if count is zero.
     * See: https://en.cppreference.com/w/cpp/string/byte/memcpy
     */
    node -> key = NULL;
  } else {
    memcpy(node -> key, key, element_size);
  }
  
  return node;
}

static void _red_black_tree_node_deinit(struct RedBlackTreeNode* node) {
  free(node -> key);
  free(node);
}

/*
 * Red Black Tree Rotation: Modify tree structure without breaking binary
 * search tree property, i.e. x.left.key < x.key < x.right.key
 *
 *        |                               |
 *       [y]       left_rotate(x)        [x]
 *      /   \      <--------------      /   \
 *    [x]    c                         a    [y]
 *   /   \         -------------->         /   \
 *  a     b        right_rotate(y)        b     c
 */
static void _rotate(
  struct RedBlackTree* tree,
  struct RedBlackTreeNode* x,
  int is_right
) {
  var y = x -> children[is_right ^ 1];
  x -> children[is_right ^ 1] = y -> children[is_right];
  if (y -> children[is_right] != tree -> nil) {
    y -> children[is_right] -> p = x;
  }
  y -> p = x -> p;
  if (x -> p == tree -> nil) {
    tree -> root = y;
  } else {
    x -> p -> children[x == x -> p -> children[1] ? 1 : 0] = y;
  }
  y -> children[is_right] = x;
  x -> p = y;
  /* Maintain augmented data */
  y -> size = x -> size;
  x -> size = x -> children[0] -> size + x -> children[1] -> size + x -> count;
}

/* Maintain the red black tree property violated by insert.
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
static void _insert_fixup(
  struct RedBlackTree* tree,
  struct RedBlackTreeNode* node
) {
  struct RedBlackTreeNode* p;
  struct RedBlackTreeNode* gp;
  struct RedBlackTreeNode* y;
  var z = node;
  int is_left;
  while (z -> p -> color == RBT_RED) {
    p = z -> p;
    gp = p -> p;
    is_left = p == gp -> children[0] ? 1 : 0;
    y = gp -> children[is_left];
    if (y -> color == RBT_RED) { /* Case 1 */
      y -> color = RBT_BLACK;
      p -> color = RBT_BLACK;
      gp -> color = RBT_RED;
      z = gp;
    } else {
      if (z == p -> children[is_left]) { /* Case 2 */
        z = p;
        _rotate(tree, z, is_left ^ 1);
      }
      /* Case 3 */
      z -> p -> color = RBT_BLACK;
      z -> p -> p -> color = RBT_RED;
      _rotate(tree, gp, is_left);
    }
  }
  tree -> root -> color = RBT_BLACK;
}

static void _red_black_tree_deinit(
  struct RedBlackTree* tree,
  struct RedBlackTreeNode* node
) {
  if (node != tree -> nil) {
    _red_black_tree_deinit(tree, node -> children[0]);
    _red_black_tree_deinit(tree, node -> children[1]);
    _red_black_tree_node_deinit(node);
  }
}

/* MARK: - Creating and Destroying a RedBlackTree */

/* Creates a new, empty tree. */
static void red_black_tree_init(
  struct RedBlackTree* tree,
  int element_size,
  bool allow_duplicates,
  int (*compare)(const void* lhs, const void* rhs)
) {
  (*tree).element_size = element_size;
  (*tree).count = 0;
  (*tree).is_empty = true;
  (*tree).allow_duplicates = allow_duplicates;
  (*tree).compare = compare;
  
  (*tree).nil = _red_black_tree_node_init(
    NULL,         /* key */
    element_size, /* e_size */
    0,            /* size */
    0,            /* count */
    NULL,         /* left */
    NULL,         /* right */
    NULL,         /* p */
    RBT_BLACK     /* color */
  );
  tree -> root = tree -> nil;
  tree -> root -> p = tree -> nil;
}

/* Destroys a RedBlackTree. (postorder tree traversal) */
static void red_black_tree_deinit(struct RedBlackTree* tree) {
  _red_black_tree_deinit(tree, tree -> root);
  _red_black_tree_node_deinit(tree -> nil);
}

/* MARK: - Adding Elements */

static void red_black_tree_insert(struct RedBlackTree* tree, const void* key) {
  /*
   * This works by creating a new red node with the key to where it belongs
   * in the tree, using binary search and then fix red black tree property
   * by calling insert_fixup().
   */
  var x = tree -> root;
  var y = tree -> nil;
  var z = _red_black_tree_node_init(
    key,                  /* key */
    tree -> element_size, /* e_size */
    1,                    /* size */
    1,                    /* count */
    tree -> nil,          /* left */
    tree -> nil,          /* right */
    tree -> nil,          /* p */
    RBT_RED /* color */
  );
  while (x != tree -> nil) { /* Find the position to insert */
    y = x;
    y -> size += 1;
    /* If exists, add `count` by 1. */
    if (tree -> compare(x -> key, key) == 0) {
      if (tree -> allow_duplicates) {
        x -> count += 1;
        tree -> count += 1;
      }
      return;
    }
    x = x -> children[(tree -> compare(x -> key, key) < 0) ? 1 : 0];
  }
  z -> p = y;
  if (y == tree -> nil) {
    tree -> root = z;
  } else {
    y -> children[(tree -> compare(y -> key, key) < 0) ? 1 : 0] = z;
  }
  _insert_fixup(tree, z);
  /* Update tree size */
  tree -> count += 1;
  tree -> is_empty = false;
}

/* MARK: - Finding Elements */

/* Returns a Boolean value indicating whether the tree contains the given
 * element.
 */
static bool red_black_tree_contains(struct RedBlackTree* tree, void* key) {
  var x = tree -> root;
  while (x != tree -> nil) { /* Find the node with key */
    if (tree -> compare(x -> key, key) == 0) {
      return true;
    }
    x = x -> children[(tree -> compare(x -> key, key) < 0) ? 1 : 0];
  }
  return false;
}

/* Returns the i-th smallest key in a tree */
void red_black_tree_select(struct RedBlackTree* tree, int i, void* result) {
  var x = tree -> root;
  while (x != tree -> nil) {
    if (x -> children[0] -> size + 1 <= i &&
        x -> children[0] -> size + x -> count >= i) {
      memcpy(result, x -> key, (*tree).element_size);
      return;
    } else {
      if (x -> children[0] -> size + x -> count < i) {
        i -= x -> children[0] -> size + x -> count;
        x = x -> children[1];
      } else {
        x = x -> children[0];
      }
    }
  }
  result = NULL; /* i.e. invalid i */
}

/*===----------------------------------------------------------------------===*/
/*             ___                            ___                             */
/*           /'___\                          /\_ \    __                      */
/*          /\ \__/   __      ___      __    \//\ \  /\_\    ___      __      */
/*          \ \ ,__\/'__`\  /' _ `\  /'_ `\    \ \ \ \/\ \ /' _ `\  /'_ `\    */
/*           \ \ \_/\ \L\.\_/\ \/\ \/\ \L\ \    \_\ \_\ \ \/\ \/\ \/\ \L\ \   */
/*            \ \_\\ \__/.\_\ \_\ \_\ \____ \   /\____\\ \_\ \_\ \_\ \____ \  */
/*             \/_/ \/__/\/_/\/_/\/_/\/___L\ \  \/____/ \/_/\/_/\/_/\/___L\ \ */
/* RedBlackTree END                    /\____/                        /\____/ */
/*                                     \_/__/                         \_/__/  */
/*===----------------------------------------------------------------------===*/

struct String {
  char _[32];
};

static int compare(const void* a, const void* b) {
  return strcmp(a, b);
}

void main_10391(void) {
  struct RedBlackTree words;
  red_black_tree_init(&words, sizeof(struct String), false, compare);
  
  struct String delta;
  while (scanf("%s", delta._) == 1) {
    red_black_tree_insert(&words, &delta);
  }
  
  struct String alpha;
  struct String beta;
  
  var i = 0;
  for (i = 0; i < words.count; i += 1) {
    red_black_tree_select(&words, i + 1, &delta);
    
    
    /*printf("%s\n", delta._);*/
    var count = (int)strlen(delta._);
    var j = 0;
    for (j = 1; j < count; j += 1) {
      var k = 0;
      for (k = 0; k < j; k += 1) {
        alpha._[k] = delta._[k];
      }
      alpha._[k] = '\0';
      for (k = j; k < count; k += 1) {
        beta._[k - j] = delta._[k];
      }
      beta._[k - j] = '\0';
      /*printf("%s|%s\n", alpha._, beta._);*/
      if (
        red_black_tree_contains(&words, &alpha) &&
        red_black_tree_contains(&words, &beta)
      ) {
        printf("%s\n", delta._);
        break;
      }
    }
    /*printf("\n");*/
  }
  red_black_tree_deinit(&words);
}
