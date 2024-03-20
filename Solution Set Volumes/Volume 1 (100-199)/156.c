//
//  156.c
//  hxy
//
//  Created by Fang Ling on 2024/3/20.
//

#include <stdio.h>
#include <ctype.h>

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

/*
 * Replaces one subtree as a child of its parent with another subtree.
 * When transplant(tree, u, v) replaces the subtree rooted at node u with the
 * subtree rooted at node v, node u's parent becomes node v's parent, and u's
 * parent ends up having v as its appropriate child.
 */
static void _transplant(
  struct RedBlackTree* tree,
  struct RedBlackTreeNode* u,
  struct RedBlackTreeNode* v
) {
  if (u -> p == tree -> nil){
    tree -> root = v;
  } else {
    u -> p -> children[(u == u -> p -> children[0]) ? 0 : 1] = v;
  }
  v -> p = u -> p;
}

static struct RedBlackTreeNode* _minimum(
  struct RedBlackTree* tree,
  struct RedBlackTreeNode* x
) {
  while (x -> children[0] != tree -> nil) {
    x = x -> children[0];
  }
  return x;
}

/* Maintain the red black tree property violated by remove.
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

static void _delete_fixup(
  struct RedBlackTree* tree,
  struct RedBlackTreeNode* node
) {
  var x = node;
  struct RedBlackTreeNode* p;
  struct RedBlackTreeNode* w;
  var is_left = 0;
  while (x != tree -> root && x -> color == RBT_BLACK) {
    p = x -> p;
    is_left = x == x -> p -> children[0] ? 1 : 0;
    w = p -> children[is_left];
    if (w -> color == RBT_RED) { /* Case 1 */
      p -> color = RBT_RED;
      w -> color = RBT_BLACK;
      _rotate(tree, p, is_left ^ 1);
      w = p -> children[is_left];
    }
    if (
      w -> children[0] -> color == RBT_BLACK &&
      w -> children[1] -> color == RBT_BLACK
    ) { /* Case 2 */
      w -> color = RBT_RED;
      x = x -> p;
    } else {
      if (w -> children[is_left] -> color == RBT_BLACK) { /* Case 3 */
        w -> color = RBT_RED;
        w -> children[is_left ^ 1] -> color = RBT_BLACK;
        _rotate(tree, w, is_left);
        w = p -> children[is_left];
      }
      /* Case 4 */
      w -> color = p -> color;
      p -> color = RBT_BLACK;
      w -> children[is_left] -> color = RBT_BLACK;
      _rotate(tree, w -> p, is_left ^ 1);
      x = tree -> root;
    }
  }
  x -> color = RBT_BLACK;
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

/* MARK: - Removing Elements */

static bool red_black_tree_remove(struct RedBlackTree* tree, const void* key) {
  if (tree -> is_empty) {
    return false; /* Can't remove from an empty red black tree */
  }
  var z = tree -> root;
  var w = tree -> nil;
  struct RedBlackTreeNode* y;
  struct RedBlackTreeNode* x;
  struct RedBlackTreeNode* delta;
  enum RedBlackTreeColor old_color;
  while (z != tree -> nil) { /* Find a node z with the specific key. */
    w = z;
    w -> size -= 1;
    if (tree -> compare(key, z -> key) == 0) {
      break;
    }
    z = z -> children[tree -> compare(z -> key, key) < 0 ? 1 : 0];
  }
  if (z != tree -> nil) {
    if (z -> count > 1) {
      tree -> count -= 1;
      z -> count -= 1;
      return true;
    }
    y = z;
    old_color = y -> color;
    if (z -> children[0] == tree -> nil) {
      x = z -> children[1];
      _transplant(tree, z, z -> children[1]);
    } else if (z -> children[1] == tree -> nil) {
      x = z -> children[0];
      _transplant(tree, z, z -> children[0]);
    } else {
      y = _minimum(tree, z -> children[1]);
      old_color = y -> color;
      x = y -> children[1];
      if (y -> p == z) {
        x -> p = y;
      } else {
        delta = y;
        while (delta != z) {
          delta -> size -= y -> count;
          delta = delta -> p;
        }
        _transplant(tree, y, y -> children[1]);
        y -> children[1] = z -> children[1];
        y -> children[1] -> p = y;
      }
      _transplant(tree, z, y);
      y -> children[0] = z -> children[0];
      y -> children[0] -> p = y;
      y -> color = z -> color;
      y -> size =
        y -> children[0] -> size + y -> children[1] -> size + y -> count;
    }
    if (old_color == RBT_BLACK) {
      _delete_fixup(tree, x);
    }
    _red_black_tree_node_deinit(z);
    tree -> count -= 1;
    tree -> is_empty = tree -> count == 0 ? true : false;
    return true;
  } else { /* No such keys, restore subtree sizes */
    while (w != tree -> nil) {
      w -> size += 1;
      w = w -> p;
    }
    return false;
  }
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

static void red_black_tree_get(struct RedBlackTree* tree, void* key) {
  var x = tree -> root;
  while (x != tree -> nil) { /* Find the node with key */
    if (tree -> compare(x -> key, key) == 0) {
      memcpy(key, x -> key, tree -> element_size);
    }
    x = x -> children[(tree -> compare(x -> key, key) < 0) ? 1 : 0];
  }
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

/*===----------------------------------------------------------------------===*/
/*                                                        ___   ___           */
/* Array START                                          /'___\ /\_ \          */
/*                                                     /\ \__/ \//\ \         */
/* Author: Fang Ling (fangling@fangl.ing)              \ \ ,__\  \ \ \        */
/* Version: 1.6                                         \ \ \_/__ \_\ \_  __  */
/* Date: January 4, 2024                                 \ \_\/\_\/\____\/\_\ */
/*                                                        \/_/\/_/\/____/\/_/ */
/*===----------------------------------------------------------------------===*/

/*
 * This source file is part of the C Collections open source project
 *
 * Copyright (c) 2023 Fang Ling
 * Licensed under Apache License v2.0
 *
 * See https://github.com/fang-ling/C-Collections/blob/main/LICENSE for license
 * information
 */

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

/*===----------------------------------------------------------------------===*/
/*                                                        ___   ___           */
/* sort START                                           /'___\ /\_ \          */
/*                                                     /\ \__/ \//\ \         */
/* Author: Fang Ling (fangling@fangl.ing)              \ \ ,__\  \ \ \        */
/* Version: 1.0                                         \ \ \_/__ \_\ \_  __  */
/* Date: December 4, 2023                                \ \_\/\_\/\____\/\_\ */
/*                                                        \/_/\/_/\/____/\/_/ */
/*===----------------------------------------------------------------------===*/

/*
 * This source file is part of the C Collections open source project
 *
 * Copyright (c) 2023 Fang Ling
 * Licensed under Apache License v2.0
 *
 * See https://github.com/fang-ling/C-Collections/blob/main/LICENSE for license
 * information
 */

#include <stdlib.h>
#include <stdbool.h>

#define var __auto_type

#define INS_THR 64

/* Byte-wise swap two items of size SIZE. */
#define SWAP(a, b, size)      \
  do {                        \
    unsigned __size = (size); \
    char *__a = (a);          \
    char *__b = (b);          \
    do {                      \
      char __tmp = *__a;      \
      *__a++ = *__b;          \
      *__b++ = __tmp;         \
    } while (--__size > 0);   \
  } while (0);

static int partition(
  void* base,
  int width,
  int p,
  int r,
  int (*compare)(const void*, const void*)
) {
  var x_ptr = base + width * r;
  var i = p - 1;
  var j = 0;
  for (j = p; j < r; j += 1) {
    if (compare(base + width * j, x_ptr) <= 0) {
      i += 1;
      SWAP(base + width * i, base + width * j, width);
    }
  }
  SWAP(base + width * (i + 1), base + width * r, width);
  return i + 1;
}

static int randomized_partition(
  void* base,
  int width,
  int p,
  int r,
  int (*compare)(const void*, const void*)
) {
  var i = p + random() % (r - p + 1);
  SWAP(base + width * r, base + width * i, width);
  return partition(base, width, p, r, compare);
}

static void _wkq_insertion_sort(
  void* base,
  int width,
  int p,
  int r,
  int (*compare)(const void*, const void*)
) {
  var j = p + 1;
  for (; j <= r; j += 1) {
    var i = j;
    while (i > 0 && compare(base + width * (i - 1), base + width * i) > 0) {
      SWAP(base + width * (i - 1), base + width * i, width);
      i -= 1;
    }
  }
}

static void _wkq_quicksort(
  void* base,
  int width,
  int p,
  int r,
  int (*compare)(const void*, const void*)
) {
  if (p < r) {
    var is_sorted = true;
    var i = 0;
    for (i = p + 1; i <= r; i += 1) {
      if (compare(base + width * i, base + width * (i - 1)) < 0) {
        is_sorted = false;
        break;
      }
    }

    var is_reverse_sorted = true;
    for (i = r; i > p; i -= 1) {
      if (compare(base + width * i, base + width * (i - 1)) > 0) {
        is_reverse_sorted = false;
      }
    }
    if (is_reverse_sorted) {
      i = p;
      var j = r;
      while (j > i) {
        SWAP(base + width * i, base + width * j, width);
        i += 1;
        j -= 1;
      }
    } else if (!is_sorted) {
      if (r - p + 1 <= INS_THR) {
        _wkq_insertion_sort(base, width, p, r, compare);
      } else {
        var q = randomized_partition(base, width, p, r, compare);
        _wkq_quicksort(base, width, p, q - 1, compare);
        _wkq_quicksort(base, width, q + 1, r, compare);
      }
    }
  }
}

static void sort(
  void* base,
  int nel,
  int width,
  int (*compare)(const void*, const void*)
) {
  srandom(1935819342);
  _wkq_quicksort(base, width, 0, nel - 1, compare);
}

/*===----------------------------------------------------------------------===*/
/*             ___                            ___                             */
/*           /'___\                          /\_ \    __                      */
/*          /\ \__/   __      ___      __    \//\ \  /\_\    ___      __      */
/*          \ \ ,__\/'__`\  /' _ `\  /'_ `\    \ \ \ \/\ \ /' _ `\  /'_ `\    */
/*           \ \ \_/\ \L\.\_/\ \/\ \/\ \L\ \    \_\ \_\ \ \/\ \/\ \/\ \L\ \   */
/*            \ \_\\ \__/.\_\ \_\ \_\ \____ \   /\____\\ \_\ \_\ \_\ \____ \  */
/*             \/_/ \/__/\/_/\/_/\/_/\/___L\ \  \/____/ \/_/\/_/\/_/\/___L\ \ */
/* sort END                            /\____/                        /\____/ */
/*                                     \_/__/                         \_/__/  */
/*===----------------------------------------------------------------------===*/


#define var __auto_type

/*
 * Error code of Array:
 * 0: NO ERROR
 * 1: due to malloc, check `errno`
 * 2: Array index is out of range
 * 3: Negative Array index is out of range
 * 5: due to realloc, check `errno`
 * 6: Can't remove last element from an empty collection
 */

struct Array {
  void* _storage;
  
  /* The number of elements in the array. */
  int count;
  
  /*
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
  int capacity;
  
  /* The size of stored Element type. */
  int element_size;
  
  /* A Boolean value indicating whether or not the array is empty. */
  bool is_empty;
};

/* MARK: - Creating and Destroying an Array */

static
int _array_init(struct Array* array, unsigned int count, int element_size) {
  /* Rounding up to next power of 2 */
  var capacity = count - 1;
  capacity |= capacity >> 1;
  capacity |= capacity >> 2;
  capacity |= capacity >> 4;
  capacity |= capacity >> 8;
  capacity |= capacity >> 16;
  capacity += 1;
  
  if (count == 0) {
    (*array)._storage = NULL;
  } else {
    (*array)._storage = malloc(capacity * element_size);
    if ((*array)._storage == NULL) {
      return 1;
    }
  }
  (*array).element_size = element_size;
  (*array).capacity = capacity;
  (*array).count = count;
  (*array).is_empty = count == 0 ? true : false;
  
  return 0;
}

/* Creates an empty array. */
static int array_init(struct Array* array, int element_size) {
  return _array_init(array, 0, element_size);
}

/* Destroys an array. */
static void array_deinit(struct Array* array) {
  free((*array)._storage);
  (*array).count = 0;
  (*array).element_size = 0;
  (*array).capacity = 0;
  (*array).is_empty = true;
}

/* MARK: - Accessing Elements */

/* Check that the specified `index` is valid, i.e. `0 ≤ index < count`. */
static int _check_index(struct Array* array, int index) {
  if (index >= (*array).count) {
    return 2;
  } else if (index < 0) {
    return 3;
  }
  return 0;
}

/* Returns the element at the specified position. */
static int array_get(struct Array* array, int index, void* element) {
  var err = _check_index(array, index);
  if (err != 0) {
    return err;
  }
  memcpy(
    element,
    (*array)._storage + (*array).element_size * index,
    (*array).element_size
  );
  return err;
}

/* Replaces the element at the specified position. */
static int array_set(struct Array* array, int index, void* element) {
  var err = _check_index(array, index);
  if (err != 0) {
    return err;
  }
  memcpy(
    (*array)._storage + (*array).element_size * index,
    element,
    (*array).element_size
  );
  return err;
}

/* MARK: - Adding Elements */

/* Adds a new element at the end of the array. */
static int array_append(struct Array* array, void* element) {
  var q = 2; /* multiple factor = 2 */
  
  if ((*array).capacity == 0) {
    (*array)._storage = realloc((*array)._storage, 1 * (*array).element_size);
    (*array).capacity = 1;
  }
  if ((*array).count == (*array).capacity) {
    (*array).capacity *= q;
    var new_size = (*array).capacity * (*array).element_size;
    (*array)._storage = realloc((*array)._storage, new_size);
    if ((*array)._storage == NULL) {
      /* FIXME: memory leak will happen if realloc failed */
      return 5;
    }
  }
  (*array).count += 1;
  (*array).is_empty = false;
  array_set(array, (*array).count - 1, element);
  
  return 0;
}

/* MARK: - Reordering an Array’s Elements */

/* Sorts the collection in place. */
static
void array_sort(struct Array* array, int (*compare)(const void*, const void*)) {
  if ((*array).count <= 1) {
    return;
  }
  sort((*array)._storage, (*array).count, (*array).element_size, compare);
}

/*===----------------------------------------------------------------------===*/
/*             ___                            ___                             */
/*           /'___\                          /\_ \    __                      */
/*          /\ \__/   __      ___      __    \//\ \  /\_\    ___      __      */
/*          \ \ ,__\/'__`\  /' _ `\  /'_ `\    \ \ \ \/\ \ /' _ `\  /'_ `\    */
/*           \ \ \_/\ \L\.\_/\ \/\ \/\ \L\ \    \_\ \_\ \ \/\ \/\ \/\ \L\ \   */
/*            \ \_\\ \__/.\_\ \_\ \_\ \____ \   /\____\\ \_\ \_\ \_\ \____ \  */
/*             \/_/ \/__/\/_/\/_/\/_/\/___L\ \  \/____/ \/_/\/_/\/_/\/___L\ \ */
/* Array END                           /\____/                        /\____/ */
/*                                     \_/__/                         \_/__/  */
/*===----------------------------------------------------------------------===*/

struct String {
  char s[32];
};

static int char_compare(const void* a, const void* b) {
  if (*(char*)a < *(char*)b) {
    return -1;
  } else if (*(char*)a > *(char*)b) {
    return 1;
  }
  return 0;
}

static void normalize(struct String* s) {
  var i = 0;
  for (i = 0; (*s).s[i] != '\0'; i += 1) {
    (*s).s[i] = tolower((*s).s[i]);
  }
  sort((*s).s, (int)strlen((*s).s), sizeof(char), char_compare);
}

struct Entry {
  struct String key;
  int value;
};

static int compare(const void* a, const void* b) {
  var _a = *(struct Entry*)a;
  var _b = *(struct Entry*)b;
  return strcmp(_a.key.s, _b.key.s);
}

static int str_compare(const void* a, const void* b) {
  var _a = *(struct String*)a;
  var _b = *(struct String*)b;
  return strcmp(_a.s, _b.s);
}

void main_156(void) {
  struct Array words;
  array_init(&words, sizeof(struct String));
  struct RedBlackTree freq;
  red_black_tree_init(&freq, sizeof(struct Entry), false, compare);
  
  struct Entry delta;
  struct String buf;
  while (scanf("%s", buf.s) == 1) {
    if (buf.s[0] == '#') {
      break;
    }
    array_append(&words, &buf);
    
    normalize(&buf);
    delta.key = buf;
    if (!red_black_tree_contains(&freq, &delta)) { /* First time */
      delta.value = 1;
      /* red_black_tree_insert(&freq, &delta); */
    } else {
      red_black_tree_get(&freq, &delta);
      red_black_tree_remove(&freq, &delta);
      delta.value += 1;
    }
    red_black_tree_insert(&freq, &delta);
  }
  
  struct String buf2;
  array_sort(&words, str_compare);
  var i = 0;
  for (i = 0; i < words.count; i += 1) {
    array_get(&words, i, &buf);
    buf2 = buf;
    normalize(&buf);
    delta.value = -1;
    delta.key = buf;
    red_black_tree_get(&freq, &delta);
    if (delta.value == 1) {
      printf("%s\n", buf2.s);
    }
  }
  
  array_deinit(&words);
  red_black_tree_deinit(&freq);
}
