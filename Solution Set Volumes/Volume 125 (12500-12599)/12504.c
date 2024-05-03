//
//  12504.c
//  hxy
//
//  Created by Fang Ling on 2024/5/3.
//

#include <stdio.h>

/*
 * This source file is part of the C Collections open source project
 *
 * Copyright (c) 2024 Fang Ling
 * Licensed under Apache License v2.0
 *
 * See https://github.com/fang-ling/C-Collections/blob/main/LICENSE for license
 * information
 */

#ifndef types_h
#define types_h

#include <stdint.h>
#include <stdbool.h>

typedef int8_t Int8;
typedef uint8_t UInt8;
typedef int32_t Int32;
typedef uint32_t UInt32;
typedef int64_t Int64;
typedef uint64_t UInt64;

typedef bool Bool;

typedef double Double;

#define var __auto_type

#endif /* types_h */

/*===----------------------------------------------------------------------===*/
/*                                                        ___   ___           */
/* Array START                                          /'___\ /\_ \          */
/*                                                     /\ \__/ \//\ \         */
/* Author: Fang Ling (fangling@fangl.ing)              \ \ ,__\  \ \ \        */
/* Version: 2.0                                         \ \ \_/__ \_\ \_  __  */
/* Date: April 22, 2024                                  \ \_\/\_\/\____\/\_\ */
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

/*
 * This source file is part of the C Collections open source project
 *
 * Copyright (c) 2024 Fang Ling
 * Licensed under Apache License v2.0
 *
 * See https://github.com/fang-ling/C-Collections/blob/main/LICENSE for license
 * information
 */

#ifndef array_h
#define array_h

#include <stdlib.h>
#include <string.h>

#include <stdio.h> /* For printing error messages */

#define ARRAY_MULTIPLE_FACTOR 2
#define ARRAY_RESIZE_FACTOR   4

#define ARRAY_FATAL_ERR_MALLOC "malloc() return a NULL pointer, check errno"
#define ARRAY_FATAL_ERR_REALLO "realloc() return a NULL pointer, check errno"
#define ARRAY_FATAL_ERR_REMEM  "Can't remove last element from an empty array"
#define ARRAY_FATAL_ERR_OUTOB  "Index out of range"

struct Array {
  void* _storage;
  
  /**
   * The number of elements in the array.
   */
  Int64 count;
  
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
  Int64 _capacity;
  
  /* The size of stored Element type. (in-bytes) */
  UInt32 _width;
  
  /**
   * A Boolean value indicating whether the array is empty.
   *
   * When you need to check whether your array is empty, use the `is_empty`
   * property instead of checking that the `count` property is equal to zero.
   */
  Bool is_empty;
};

#endif /* array_h */


/*
 * Error code of Array:
 * 0: NO ERROR
 * 1: due to malloc, check `errno`
 * 2: Array index is out of range
 * 3: Negative Array index is out of range
 * 5: due to realloc, check `errno`
 * 6: Can't remove last element from an empty collection
 */

static void _array_init(struct Array* array, Int64 count, UInt32 width) {
  /* Rounding up to next power of 2 */
  var capacity = count - 1;
  capacity |= capacity >> 1;
  capacity |= capacity >> 2;
  capacity |= capacity >> 4;
  capacity |= capacity >> 8;
  capacity |= capacity >> 16;
  capacity += 1;
  
  if (count == 0) {
    array->_storage = NULL;
  } else {
    array->_storage = malloc(capacity * width);
    if (array->_storage == NULL) {
      fprintf(stderr, ARRAY_FATAL_ERR_MALLOC);
      abort();
    }
  }
  array->_width = width;
  array->_capacity = capacity;
  array->count = count;
  array->is_empty = count == 0 ? true : false;
}

/* Check that the specified `index` is valid, i.e. `0 ≤ index < count`. */
static void _array_check_index(struct Array* array, Int64 index) {
  if (index >= array->count || index < 0) {
    fprintf(stderr, ARRAY_FATAL_ERR_OUTOB);
    abort();
  }
}

/* MARK: - Creating and Destroying an Array */

static struct Array* array_init(UInt32 width) {
  struct Array* array;
  if ((array = malloc(sizeof(struct Array))) == NULL) {
    return NULL;
  }
  _array_init(array, 0, width);
  return array;
}

static void array_deinit(struct Array* array) {
  if (array == NULL) {
    return;
  }
  
  free(array->_storage);
  array->count = 0;
  array->_width = 0;
  array->_capacity = 0;
  array->is_empty = true;
  
  free(array);
}

/* MARK: - Accessing Elements */

/* Returns the element at the specified position. */
static void array_get(struct Array* array, Int64 index, void* element) {
  _array_check_index(array, index);
  
  memcpy(
    element,
    array->_storage + array->_width * index,
    array->_width
  );
}

/* MARK: - Adding Elements */

static void array_append(struct Array* array, void* new_element) {
  if (array->_capacity == 0) {
    array->_storage = realloc(array->_storage, 1 * array->_width);
    array->_capacity = 1;
  }
  if (array->count == array->_capacity) {
    array->_capacity *= ARRAY_MULTIPLE_FACTOR;
    var new_size = array->_capacity * array->_width;
    array->_storage = realloc(array->_storage, new_size);
    if (array->_storage == NULL) {
      fprintf(stderr, ARRAY_FATAL_ERR_REALLO);
      abort();
    }
  }
  array->count += 1;
  array->is_empty = false;
  memcpy(
    array->_storage + (array->count - 1) * array->_width,
    new_element,
    array->_width
  );
}

/* MARK: - Removing Elements */

static void array_remove_all(struct Array* array) {
  free(array->_storage);
  array->_storage = NULL;
  array->count = 0;
  array->_capacity = 0;
  array->is_empty = true;
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

/*===----------------------------------------------------------------------===*/
/*                                                        ___   ___           */
/* string        START                                  /'___\ /\_ \          */
/*                                                     /\ \__/ \//\ \         */
/* Author: Fang Ling (fangling@fangl.ing)              \ \ ,__\  \ \ \        */
/* Version: 1.0                                         \ \ \_/__ \_\ \_  __  */
/* Date: April 15, 2024                                  \ \_\/\_\/\____\/\_\ */
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

/*
 * This source file is part of the C Collections open source project
 *
 * Copyright (c) 2024 Fang Ling
 * Licensed under Apache License v2.0
 *
 * See https://github.com/fang-ling/C-Collections/blob/main/LICENSE for license
 * information
 */

#ifndef string_h
#define string_h

#define WKQ_INT64_MAX       0x7fffffffffffffffLL      /* max signed long long */
#define WKQ_INT64_MIN       (-0x7fffffffffffffffLL-1) /* min signed long long */

#include <stdlib.h>
#include <ctype.h>

struct String {
  /*
   * A buffer for storing UTF-8 string as an array of uint32 numbers.
   * In UTF-8 encoding, characters are represented by variable-length code
   * units. The code units for a single character are "concatenated" together to
   * form a single uint32 number. This allows easy implementation of functions
   * for manipulating multi-language strings.
   */
  UInt32* _utf8;
  
  /* The length of each unicode character. */
  Int32* _utf8_length;
  
  Int64 _utf8_capacity;
  
  /* The number of (unicode) characters in a string. */
  Int64 count;
  
  /* A Boolean value indicating whether a string has no characters. */
  Bool is_empty;
};

#endif /* string_h */


static char const WKQ_UTF8_LEN[] = {
/* 0  1  2  3  4  5  6  7  8  9  A  B  C  D  E  F */
   1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 2, 2, 3, 4
};
#define WKQUTF8LEN(c) WKQ_UTF8_LEN[((c) & 0xFF) >> 4]

static struct String* _string_init(
  UInt32* _utf8,
  Int32* _utf8_length,
  Int64 count
) {
  struct String* string;
  if ((string = malloc(sizeof(struct String))) == NULL) {
    return NULL;
  }
  
  string->_utf8_capacity = count;
  string->count = count;
  
  string->is_empty = true; /* set initial value */
  if (string->_utf8_capacity > 0) {
    string->is_empty = false;
  }
  
  string->_utf8 = malloc(sizeof(UInt32) * string->_utf8_capacity);
  string->_utf8_length = malloc(sizeof(Int32) * string->_utf8_capacity);
  
  memcpy(string->_utf8, _utf8, sizeof(UInt32) * count);
  memcpy(string->_utf8_length, _utf8_length, sizeof(Int32) * count);
  
  return string;
}

/* MARK: - Creating and Destroying a String */

static struct String* string_init(const char* s) {
  struct String* string;
  if ((string = malloc(sizeof(struct String))) == NULL) {
    return NULL;
  }
  
  /* Calculate capacity & is_empty */
  string->is_empty = true;
  string->_utf8_capacity = 0;
  var _s = s;
  while (*_s != '\0') {
    string->_utf8_capacity += 1;
    _s += WKQUTF8LEN(*_s);
  }
  if (string->_utf8_capacity > 0) {
    string->is_empty = false;
  }
  
  string->_utf8 = malloc(sizeof(UInt32) * string->_utf8_capacity);
  string->_utf8_length = malloc(sizeof(UInt32) * string->_utf8_capacity);
  
  _s = s;
  string->count = 0;
  while (*_s != '\0') {
    var len = WKQUTF8LEN(*_s);
    string->_utf8[string->count] = 0;
    string->_utf8_length[string->count] = len;
    var i = 0;
    for (i = 0; i < len; i += 1) {
      string->_utf8[string->count] |= (((UInt32)(UInt8)*_s) << (i * 8));
      _s += 1;
    }
    string->count += 1;
  }

  return string;
}

static void string_deinit(struct String* string) {
  free(string->_utf8);
  free(string->_utf8_length);
  free(string);
}

/* MARK: - Getting Substrings */

/*
 * Returns a new contiguous substring of the string.
 *
 * It's caller's responsibility to free the returned value.
 *
 * Returns NULL if the start is negative, or end is larger than the length of
 * this string object, or start is larger than end.
 */
static struct String* string_substring(
  struct String* string,
  Int64 start,
  Int64 end
) {
  if (start < 0 || end > string->count || start > end) {
    return NULL;
  }
  
  var _utf8 = string->_utf8 + start;
  var _utf8_length = string->_utf8_length + start;
  return _string_init(_utf8, _utf8_length, end - start);
}

/* MARK: - Splitting a String */

/*
 * Returns an array containing substrings from the string that have been divided
 * by the given separator.
 * It's caller's responsibility to free the strings stored in the result.
 */
/* Example:
 *                    1                 2    3             4
 * Assuming: str = "#zyy#jasdjq2n3oasd#zyy##zyy#adn972929#zyy#"
 *           separator = "#zyy#"
 *      will return 5 substrings.
 */
static void string_components(
  struct String* string,
  struct String* separator,
  struct Array* result
) {
  var last_index = 0ll;
  
  if (separator->count != 0) {
    var i = 0;
    var length = string->count - separator->count + 1;
    for (i = 0; i < length; i += 1) {
      var j = 0;
      while (
        j < separator->count &&
        string->_utf8[i + j] == separator->_utf8[j]
      ) {
        j += 1;
      }
      if (j == separator->count) { /* Find a match at i */
        var substring = string_substring(string, last_index, i);
        array_append(result, &substring);
        last_index += separator->count + substring->count;
      }
    }
  }
  /* Add the remaining substring */
  var substring = string_substring(string, last_index, string->count);
  array_append(result, &substring);
}

/* MARK: - Getting C Strings */

static void string_c_string(struct String* string, char* result) {
  var i = 0;
  for (i = 0; i < string->count; i += 1) {
    var j = 0;
    for (j = 0; j < string->_utf8_length[i]; j += 1) {
      *result = (UInt8)(string->_utf8[i] >> (j * 8));
      result += 1;
    }
  }
  *result = '\0';
}

/* MARK: - Comparing Strings */

/*
 * Returns an integer greater than, equal to, or less than 0, according as the
 * string lhs is greater than, equal to, or less than the string rhs.
 */
static Int32 string_compare_ascii(const void* lhs, const void* rhs) {
  var a = *(struct String**)lhs;
  var b = *(struct String**)rhs;
  
  var lim = a->count < b->count ? a->count : b->count;
  
  /* Find the first mismatch */
  var i = 0;
  for (i = 0; i < lim; i += 1) {
    if (a->_utf8[i] != b->_utf8[i]) {
      break;
    }
  }
  if (i == lim) { /* no mismatch founded */
    return (Int32)(a->count - b->count);
  } else {
    return ((Int32)a->_utf8[i]) - ((Int32)b->_utf8[i]);
  }
}

/* MARK: - Accessing Elements */

/*===----------------------------------------------------------------------===*/
/*             ___                            ___                             */
/*           /'___\                          /\_ \    __                      */
/*          /\ \__/   __      ___      __    \//\ \  /\_\    ___      __      */
/*          \ \ ,__\/'__`\  /' _ `\  /'_ `\    \ \ \ \/\ \ /' _ `\  /'_ `\    */
/*           \ \ \_/\ \L\.\_/\ \/\ \/\ \L\ \    \_\ \_\ \ \/\ \/\ \/\ \L\ \   */
/*            \ \_\\ \__/.\_\ \_\ \_\ \____ \   /\____\\ \_\ \_\ \_\ \____ \  */
/*             \/_/ \/__/\/_/\/_/\/_/\/___L\ \  \/____/ \/_/\/_/\/_/\/___L\ \ */
/* string        END                   /\____/                        /\____/ */
/*                                     \_/__/                         \_/__/  */
/*===----------------------------------------------------------------------===*/

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

/*
 * This source file is part of the C Collections open source project
 *
 * Copyright (c) 2024 Fang Ling
 * Licensed under Apache License v2.0
 *
 * See https://github.com/fang-ling/C-Collections/blob/main/LICENSE for license
 * information
 */

#ifndef red_black_tree_h
#define red_black_tree_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define RBT_FATAL_ERR_REMEM "Can't remove from an empty red black tree."
#define RBT_FATAL_ERR_INDOB "Index out of range."

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
  Int64 count;
  /* Subtree size */
  Int64 size;
  /* Color of the node */
  enum RedBlackTreeColor color;
};

struct RedBlackTree {
  struct RedBlackTreeNode* root;
  struct RedBlackTreeNode* null;
  
  UInt32 _width;
  
  /* The number of elements in the tree */
  Int64 count;
  
  /* A Boolean value indicating whether the tree is empty. */
  Bool is_empty;
  
  /*
   * A Boolean value indicating whether a RedBlackTree allows duplicate
   * elements.
   */
  Bool allow_duplicates;
  
  Int32 (*compare)(const void* lhs, const void* rhs);
};

#endif /* red_black_tree_h */


static struct RedBlackTreeNode* _red_black_tree_node_init(
  const void* key,
  UInt32 element_size,
  Int64 size,
  Int64 count,
  struct RedBlackTreeNode* left,
  struct RedBlackTreeNode* right,
  struct RedBlackTreeNode* p,
  enum RedBlackTreeColor color
) {
  var node = (struct RedBlackTreeNode*)malloc(sizeof(struct RedBlackTreeNode));
  
  node->children[0] = left;
  node->children[1] = right;
  node->p = p;
  node->color = color;
  node->count = count;
  node->size = size;
  
  node->key = malloc(element_size); /* allocate space for key */
  if (key != NULL) {
    memcpy(node->key, key, element_size);
  }
  
  return node;
}

static void _red_black_tree_node_deinit(struct RedBlackTreeNode* node) {
  free(node->key);
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
static void _red_black_tree_rotate(
  struct RedBlackTree* tree,
  struct RedBlackTreeNode* x,
  Int32 is_right
) {
  var y = x->children[is_right ^ 1];
  x->children[is_right ^ 1] = y->children[is_right];
  if (y->children[is_right] != tree->null) {
    y->children[is_right]->p = x;
  }
  y->p = x->p;
  if (x->p == tree->null) {
    tree->root = y;
  } else {
    x->p->children[x == x->p->children[1] ? 1 : 0] = y;
  }
  y->children[is_right] = x;
  x->p = y;
  /* Maintain augmented data */
  y->size = x->size;
  x->size = x->children[0]->size + x->children[1]->size + x->count;
}

static void _red_black_tree_insert_fixup(
  struct RedBlackTree* tree,
  struct RedBlackTreeNode* node
) {
  struct RedBlackTreeNode* p;
  struct RedBlackTreeNode* gp;
  struct RedBlackTreeNode* y;
  var z = node;
  Int32 is_left;
  while (z->p->color == RBT_RED) {
    p = z->p;
    gp = p->p;
    is_left = p == gp->children[0] ? 1 : 0;
    y = gp->children[is_left];
    if (y->color == RBT_RED) { /* Case 1 */
      y->color = RBT_BLACK;
      p->color = RBT_BLACK;
      gp->color = RBT_RED;
      z = gp;
    } else {
      if (z == p->children[is_left]) { /* Case 2 */
        z = p;
        _red_black_tree_rotate(tree, z, is_left ^ 1);
      }
      /* Case 3 */
      z->p->color = RBT_BLACK;
      z->p->p->color = RBT_RED;
      _red_black_tree_rotate(tree, gp, is_left);
    }
  }
  tree->root->color = RBT_BLACK;
}

/*
 * Replaces one subtree as a child of its parent with another subtree.
 * When transplant(tree, u, v) replaces the subtree rooted at node u with the
 * subtree rooted at node v, node u's parent becomes node v's parent, and u's
 * parent ends up having v as its appropriate child.
 */
static void _red_black_tree_transplant(
  struct RedBlackTree* tree,
  struct RedBlackTreeNode* u,
  struct RedBlackTreeNode* v
) {
  if (u->p == tree->null){
    tree->root = v;
  } else {
    u->p->children[(u == u->p->children[0]) ? 0 : 1] = v;
  }
  v->p = u->p;
}

static struct RedBlackTreeNode* _red_black_tree_minimum(
  struct RedBlackTree* tree,
  struct RedBlackTreeNode* x
) {
  while (x->children[0] != tree->null) {
    x = x->children[0];
  }
  return x;
}

static void _red_black_tree_delete_fixup(
  struct RedBlackTree* tree,
  struct RedBlackTreeNode* node
) {
  var x = node;
  struct RedBlackTreeNode* p;
  struct RedBlackTreeNode* w;
  var is_left = 0;
  while (x != tree->root && x->color == RBT_BLACK) {
    p = x->p;
    is_left = x == x->p->children[0] ? 1 : 0;
    w = p->children[is_left];
    if (w->color == RBT_RED) { /* Case 1 */
      p->color = RBT_RED;
      w->color = RBT_BLACK;
      _red_black_tree_rotate(tree, p, is_left ^ 1);
      w = p->children[is_left];
    }
    if (
      w->children[0]->color == RBT_BLACK &&
      w->children[1]->color == RBT_BLACK
    ) { /* Case 2 */
      w->color = RBT_RED;
      x = x->p;
    } else {
      if (w->children[is_left]->color == RBT_BLACK) { /* Case 3 */
        w->color = RBT_RED;
        w->children[is_left ^ 1]->color = RBT_BLACK;
        _red_black_tree_rotate(tree, w, is_left);
        w = p->children[is_left];
      }
      /* Case 4 */
      w->color = p->color;
      p->color = RBT_BLACK;
      w->children[is_left]->color = RBT_BLACK;
      _red_black_tree_rotate(tree, w->p, is_left ^ 1);
      x = tree->root;
    }
  }
  x->color = RBT_BLACK;
}

static void _red_black_tree_deinit(
  struct RedBlackTree* tree,
  struct RedBlackTreeNode* node
) {
  if (node != tree->null) {
    _red_black_tree_deinit(tree, node->children[0]);
    _red_black_tree_deinit(tree, node->children[1]);
    _red_black_tree_node_deinit(node);
  }
}

/* MARK: - Creating and Destroying a RedBlackTree */

/* Creates a new, empty tree. */
static struct RedBlackTree* red_black_tree_init(
  UInt32 width,
  Bool allow_duplicates,
  Int32 (*compare)(const void* lhs, const void* rhs)
) {
  struct RedBlackTree* tree;
  if ((tree = malloc(sizeof(struct RedBlackTree))) == NULL) {
    return NULL;
  }
  
  tree->_width = width;
  tree->count = 0;
  tree->is_empty = true;
  tree->allow_duplicates = allow_duplicates;
  tree->compare = compare;
  
  tree->null = _red_black_tree_node_init(
    NULL,         /* key */
    width,        /* width */
    0,            /* size */
    0,            /* count */
    NULL,         /* left */
    NULL,         /* right */
    NULL,         /* p */
    RBT_BLACK     /* color */
  );
  tree->root = tree->null;
  tree->root->p = tree->null;
  
  return tree;
}

/* Destroys a RedBlackTree. (postorder tree traversal) */
static void red_black_tree_deinit(struct RedBlackTree* tree) {
  _red_black_tree_deinit(tree, tree->root);
  _red_black_tree_node_deinit(tree->null);
  
  free(tree);
}

/* MARK: - Adding Elements */

static void red_black_tree_insert(struct RedBlackTree* tree, const void* key) {
  /*
   * This works by creating a new red node with the key to where it belongs
   * in the tree, using binary search and then fix red black tree property
   * by calling insert_fixup().
   */
  var x = tree->root;
  var y = tree->null;
  var z = _red_black_tree_node_init(
    key,                  /* key */
    tree->_width,         /* width */
    1,                    /* size */
    1,                    /* count */
    tree->null,           /* left */
    tree->null,           /* right */
    tree->null,           /* p */
    RBT_RED               /* color */
  );
  var is_success = true;
  while (x != tree->null) { /* Find the position to insert */
    y = x;
    y->size += 1;
    /* If exists, add `count` by 1. */
    if (tree->compare(x->key, key) == 0) {
      if (tree->allow_duplicates) {
        x->count += 1;
        tree->count += 1;
        return;
      } else {
        is_success = false;
        break;
      }
    }
    x = x->children[(tree->compare(x->key, key) < 0) ? 1 : 0];
  }
  if (!is_success) { /* Insert duplicate when allow_duplicate is false */
    /* Restore substree sizes */
    while (x != tree->null) {
      x->size -= 1;
      x = x->p;
    }
    return;
  }
  z->p = y;
  if (y == tree->null) {
    tree->root = z;
  } else {
    y->children[(tree->compare(y->key, key) < 0) ? 1 : 0] = z;
  }
  _red_black_tree_insert_fixup(tree, z);
  /* Update tree size */
  tree->count += 1;
  tree->is_empty = false;
}

/* MARK: - Removing Elements */

static void red_black_tree_remove(struct RedBlackTree* tree, const void* key) {
  if (tree->is_empty) {
    fprintf(stderr, RBT_FATAL_ERR_REMEM);
    abort();
  }
  var z = tree->root;
  var w = tree->null;
  struct RedBlackTreeNode* y;
  struct RedBlackTreeNode* x;
  struct RedBlackTreeNode* delta;
  enum RedBlackTreeColor old_color;
  while (z != tree->null) { /* Find a node z with the specific key. */
    w = z;
    w->size -= 1;
    if (tree->compare(key, z->key) == 0) {
      break;
    }
    z = z->children[tree->compare(z->key, key) < 0 ? 1 : 0];
  }
  if (z != tree->null) {
    if (z->count > 1) {
      tree->count -= 1;
      z->count -= 1;
      return;
    }
    y = z;
    old_color = y->color;
    if (z->children[0] == tree->null) {
      x = z->children[1];
      _red_black_tree_transplant(tree, z, z->children[1]);
    } else if (z->children[1] == tree->null) {
      x = z->children[0];
      _red_black_tree_transplant(tree, z, z->children[0]);
    } else {
      y = _red_black_tree_minimum(tree, z->children[1]);
      old_color = y->color;
      x = y->children[1];
      if (y->p == z) {
        x->p = y;
      } else {
        delta = y;
        while (delta != z) {
          delta->size -= y->count;
          delta = delta->p;
        }
        _red_black_tree_transplant(tree, y, y->children[1]);
        y->children[1] = z->children[1];
        y->children[1]->p = y;
      }
      _red_black_tree_transplant(tree, z, y);
      y->children[0] = z->children[0];
      y->children[0]->p = y;
      y->color = z->color;
      y->size =
        y->children[0]->size + y->children[1]->size + y->count;
    }
    if (old_color == RBT_BLACK) {
      _red_black_tree_delete_fixup(tree, x);
    }
    _red_black_tree_node_deinit(z);
    tree->count -= 1;
    tree->is_empty = tree->count == 0 ? true : false;
    return;
  } else { /* No such keys, restore subtree sizes */
    while (w != tree->null) {
      w->size += 1;
      w = w->p;
    }
    return;
  }
}

/* MARK: - Finding Elements */

/* Returns the i-th smallest key in a tree. (Zero-based numbering) */
static
void red_black_tree_select(struct RedBlackTree* tree, Int64 i, void* result) {
  if (i < 1 - 1 || i > tree->count - 1) {
    fprintf(stderr, RBT_FATAL_ERR_INDOB);
    abort();
  }
  
  i += 1;
  var x = tree->root;
  while (x != tree->null) {
    if (x->children[0]->size + 1 <= i &&
        x->children[0]->size + x->count >= i) {
      memcpy(result, x->key, tree->_width);
      return;
    } else {
      if (x->children[0]->size + x->count < i) {
        i -= x->children[0]->size + x->count;
        x = x->children[1];
      } else {
        x = x->children[0];
      }
    }
  }
}

/*
 * Returns a Boolean value indicating whether the tree contains the given
 * element.
 */
static Bool red_black_tree_contains(struct RedBlackTree* tree, void* key) {
  var x = tree->root;
  while (x != tree->null) { /* Find the node with key */
    if (tree->compare(x->key, key) == 0) {
      return true;
    }
    x = x->children[(tree->compare(x->key, key) < 0) ? 1 : 0];
  }
  return false;
}

static
void red_black_tree_get(struct RedBlackTree* tree, void* key, void* result) {
  var x = tree->root;
  while (x != tree->null) { /* Find the node with key */
    if (tree->compare(x->key, key) == 0) {
      memcpy(result, x->key, tree->_width);
      return;
    }
    x = x->children[(tree->compare(x->key, key) < 0) ? 1 : 0];
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

struct Entry {
  struct String* key;
  struct String* value;
};

static Int32 compare(const void* a, const void* b) {
  var _a = *(struct Entry*)a;
  var _b = *(struct Entry*)b;
  
  return string_compare_ascii(&_a.key, &_b.key);
}

static struct RedBlackTree* parse(char* buf) {
  var dict = red_black_tree_init(sizeof(struct Entry), false, compare);
  
  /* Remove '{' and '}' */
  var str = buf;
  var len = (int)strlen(str);
  str[len - 1] = '\0';
  str += 1;
  var string = string_init(str);
  var separator = string_init(",");
  var separator2 = string_init(":");
  
  var pairs = array_init(sizeof(struct String*));
  var kv = array_init(sizeof(struct String*));
  string_components(string, separator, pairs);
  var i = 0;
  for (i = 0; i < pairs->count; i += 1) {
    struct String* pair;
    array_get(pairs, i, &pair);
    if (pair->is_empty) {
      continue;
    }
    
    array_remove_all(kv);
    string_components(pair, separator2, kv);
    struct Entry e;
    array_get(kv, 0, &e.key);
    array_get(kv, 1, &e.value);
    
    red_black_tree_insert(dict, &e);
    
    string_deinit(pair);
  }
  
  /* Clean up */
  array_deinit(kv);
  array_deinit(pairs);
  string_deinit(separator);
  string_deinit(separator2);
  string_deinit(string);
  
  return dict;
}

void main_12504(void) {
  var star = array_init(sizeof(struct String*));
  var plus = array_init(sizeof(struct String*));
  var minus = array_init(sizeof(struct String*));
  
  char buf[128];
  var t = 0;
  scanf("%d", &t);
  while (t--) {
    /* init */
    array_remove_all(star);
    array_remove_all(plus);
    array_remove_all(minus);
    
    scanf("%s", buf);
    var old = parse(buf);
    scanf("%s", buf);
    var new = parse(buf);
    
    var i = 0;
    for (i = 0; i < old->count; i += 1) {
      struct Entry e;
      red_black_tree_select(old, i, &e);
      if (red_black_tree_contains(new, &e)) { /* Key not changed, check value */
        struct Entry e2;
        red_black_tree_get(new, &e, &e2);
        if (string_compare_ascii(&e.value, &e2.value) == 0) {
          /* value not changed */
        } else { /* keys with changed value */
          array_append(star, &e.key);
        }
      } else { /* removed keys */
        array_append(minus, &e.key);
      }
    }
    
    for (i = 0; i < new->count; i += 1) {
      struct Entry e;
      red_black_tree_select(new, i, &e);
      if (red_black_tree_contains(old, &e)) {
        /* Handled in previous for-loop */
      } else { /* new keys */
        array_append(plus, &e.key);
      }
    }
  
    if (star->is_empty && plus->is_empty && minus->is_empty) {
      printf("No changes\n");
    } else {
      if (!plus->is_empty) {
        printf("+");
        for (i = 0; i < plus->count; i += 1) {
          struct String* string;
          array_get(plus, i, &string);
          string_c_string(string, buf);
          printf("%s", buf);
          if (i == plus->count - 1) {
            printf("\n");
          } else {
            printf(",");
          }
        }
      }
      if (!minus->is_empty) {
        printf("-");
        for (i = 0; i < minus->count; i += 1) {
          struct String* string;
          array_get(minus, i, &string);
          string_c_string(string, buf);
          printf("%s", buf);
          if (i == minus->count - 1) {
            printf("\n");
          } else {
            printf(",");
          }
        }
      }
      if (!star->is_empty) {
        printf("*");
        for (i = 0; i < star->count; i += 1) {
          struct String* string;
          array_get(star, i, &string);
          string_c_string(string, buf);
          printf("%s", buf);
          if (i == star->count - 1) {
            printf("\n");
          } else {
            printf(",");
          }
        }
      }
    }
    printf("\n");
    
    /* Clean up RBT and its strings */
    for (i = 0; i < old->count; i += 1) {
      struct Entry e;
      red_black_tree_select(old, i, &e);
      red_black_tree_remove(old, &e);
      string_deinit(e.key);
      string_deinit(e.value);
    }
    for (i = 0; i < new->count; i += 1) {
      struct Entry e;
      red_black_tree_select(new, i, &e);
      red_black_tree_remove(new, &e);
      string_deinit(e.key);
      string_deinit(e.value);
    }
    /* Memory leak will happen */
    red_black_tree_deinit(old);
    red_black_tree_deinit(new);
  }
  /* Clean up */
  array_deinit(star);
  array_deinit(plus);
  array_deinit(minus);
}
