//
//  1597.c
//  hxy
//
//  Created by Fang Ling on 2024/5/1.
//

#include <stdio.h>

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
  var a = (struct String*)lhs;
  var b = (struct String*)rhs;
  
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

/* MARK: - Finding Characters */

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
  struct RedBlackTreeNode* nil;
  
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

static void _red_black_tree_rotate(
  struct RedBlackTree* tree,
  struct RedBlackTreeNode* x,
  Int32 is_right
) {
  var y = x->children[is_right ^ 1];
  x->children[is_right ^ 1] = y->children[is_right];
  if (y->children[is_right] != tree->nil) {
    y->children[is_right]->p = x;
  }
  y->p = x->p;
  if (x->p == tree->nil) {
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

static void _red_black_tree_transplant(
  struct RedBlackTree* tree,
  struct RedBlackTreeNode* u,
  struct RedBlackTreeNode* v
) {
  if (u->p == tree->nil){
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
  while (x->children[0] != tree->nil) {
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
  if (node != tree->nil) {
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
  
  tree->nil = _red_black_tree_node_init(
    NULL,         /* key */
    width,        /* width */
    0,            /* size */
    0,            /* count */
    NULL,         /* left */
    NULL,         /* right */
    NULL,         /* p */
    RBT_BLACK     /* color */
  );
  tree->root = tree->nil;
  tree->root->p = tree->nil;
  
  return tree;
}

/* Destroys a RedBlackTree. (postorder tree traversal) */
static void red_black_tree_deinit(struct RedBlackTree* tree) {
  _red_black_tree_deinit(tree, tree->root);
  _red_black_tree_node_deinit(tree->nil);
  
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
  var y = tree->nil;
  var z = _red_black_tree_node_init(
    key,                  /* key */
    tree->_width,         /* width */
    1,                    /* size */
    1,                    /* count */
    tree->nil,            /* left */
    tree->nil,            /* right */
    tree->nil,            /* p */
    RBT_RED /* color */
  );
  while (x != tree->nil) { /* Find the position to insert */
    y = x;
    y->size += 1;
    /* If exists, add `count` by 1. */
    if (tree->compare(x->key, key) == 0) {
      if (tree->allow_duplicates) {
        x->count += 1;
        tree->count += 1;
      }
      return;
    }
    x = x->children[(tree->compare(x->key, key) < 0) ? 1 : 0];
  }
  z->p = y;
  if (y == tree->nil) {
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
  var w = tree->nil;
  struct RedBlackTreeNode* y;
  struct RedBlackTreeNode* x;
  struct RedBlackTreeNode* delta;
  enum RedBlackTreeColor old_color;
  while (z != tree->nil) { /* Find a node z with the specific key. */
    w = z;
    w->size -= 1;
    if (tree->compare(key, z->key) == 0) {
      break;
    }
    z = z->children[tree->compare(z->key, key) < 0 ? 1 : 0];
  }
  if (z != tree->nil) {
    if (z->count > 1) {
      tree->count -= 1;
      z->count -= 1;
      return;
    }
    y = z;
    old_color = y->color;
    if (z->children[0] == tree->nil) {
      x = z->children[1];
      _red_black_tree_transplant(tree, z, z->children[1]);
    } else if (z->children[1] == tree->nil) {
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
    while (w != tree->nil) {
      w->size += 1;
      w = w->p;
    }
    return;
  }
}

/* MARK: - Finding Elements */

/* Returns the i-th smallest key in a tree */
static
void red_black_tree_select(struct RedBlackTree* tree, Int64 i, void* result) {
  if (i < 1 || i > tree->count) {
    fprintf(stderr, RBT_FATAL_ERR_INDOB);
    abort();
  }
  
  var x = tree->root;
  while (x != tree->nil) {
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

static Bool red_black_tree_contains(struct RedBlackTree* tree, void* key) {
  var x = tree->root;
  while (x != tree->nil) { /* Find the node with key */
    if (tree->compare(x->key, key) == 0) {
      return true;
    }
    x = x->children[(tree->compare(x->key, key) < 0) ? 1 : 0];
  }
  return false;
}

static void red_black_tree_get(struct RedBlackTree* tree, void* key) {
  var x = tree -> root;
  while (x != tree -> nil) { /* Find the node with key */
    if (tree -> compare(x -> key, key) == 0) {
      memcpy(key, x -> key, tree -> _width);
      break;
    }
    x = x -> children[(tree -> compare(x -> key, key) < 0) ? 1 : 0];
  }
}

struct Document {
  struct Array* lines;
};

static struct Document* document_init(void) {
  struct Document* document = malloc(sizeof(struct Document));
  document->lines = array_init(sizeof(struct String*));
  return document;
}

static void document_deinit(struct Document* document) {
  struct String* string;
  var i = 0;
  for (i = 0; i < document->lines->count; i += 1) {
    array_get(document->lines, i, &string);
    string_deinit(string);
  }
  array_deinit(document->lines);
  free(document);
}

struct DocumentIdentifier {
  Int32 document_number;
  Int32 line_number;
};

struct Entry {
  struct String* term;
  struct Array* dids;
};

static Int32 compare2(const void* a, const void* b) {
  var l = *(struct DocumentIdentifier*)a;
  var r = *(struct DocumentIdentifier*)b;
  
  if (l.document_number == r.document_number && l.line_number == r.line_number) {
    return 0;
  }
  
  /* Unsafe */
  return l.document_number == r.document_number ?
         l.line_number - r.line_number :
         l.document_number - r.document_number;
}

static Int32 compare(const void* a, const void* b) {
  var l = (struct Entry*)a;
  var r = (struct Entry*)b;
  return string_compare_ascii(l->term, r->term);
}

static Int32 compare3(const void* a, const void* b) {
  var l = *(Int32*)a;
  var r = *(Int32*)b;
  return l - r; /* Unsafe */
}

void main_1597(void) {
  char output_buf[512];
  var documents = array_init(sizeof(struct Document*));
  var inv_index = red_black_tree_init(sizeof(struct Entry), false, compare);
  var separator = string_init(" ");
  
  var document_number = 0;
  var n = 0;
  scanf("%d\n", &n);
  while (n--) {
    char* buf = NULL;
    var linecap = (unsigned long)0;
    var linelen = 0;

    var line_number = 0;
    var document = document_init();
    /* Read the document */
    while ((linelen = (int)getline(&buf, &linecap, stdin)) > 0) {
      buf[linelen - 1] = '\0'; /* Remove \n char */
      linelen -= 1;
      if (buf[0] == '*') { /* End of the document */
        break;
      }
      
      var line = string_init(buf);
      array_append(document->lines, &line);
      
      /* Tokenlize */
      var i = 0;
      for (i = 0; i < linelen; i += 1) {
        if (!isalpha(buf[i])) { /* Replace non-alphabetic character with ' ' */
          buf[i] = ' ';
        }
        if (isupper(buf[i])) {
          buf[i] = tolower(buf[i]);
        }
      }
      var terms = array_init(sizeof(struct String*));
      var terms_empty = array_init(sizeof(struct String*));
      var token_string = string_init(buf);
      string_components(token_string, separator, terms_empty);
      for (i = 0; i < terms_empty->count; i += 1) {
        struct String* string;
        array_get(terms_empty, i, &string);
        if (string->is_empty || string->count == 0) { /* Bug in is_empty */
          string_deinit(string);
        } else {
          array_append(terms, &string);
        }
      }
      string_deinit(token_string);
      array_deinit(terms_empty);
      /* Construct DID */
      struct DocumentIdentifier did;
      did.document_number = document_number;
      did.line_number = line_number;
      
      for (i = 0; i < terms->count; i += 1) {
        struct String* term;
        array_get(terms, i, &term);
        struct Entry entry;
        entry.term = term;
        
        if (red_black_tree_contains(inv_index, &entry)) {
          entry.dids = NULL;
          red_black_tree_get(inv_index, &entry);
          string_deinit(term); /* Deinit duplicate terms */
          red_black_tree_remove(inv_index, &entry);
        } else {
          entry.dids = array_init(sizeof(struct DocumentIdentifier));
        }
        array_append(entry.dids, &did);
        red_black_tree_insert(inv_index, &entry);
      }
      line_number += 1;
    }
    array_append(documents, &document);
    document_number += 1;
  }
  
  /* Query */
  var m = 0;
  scanf("%d\n", &m);
  while (m--) {
    char* buf = NULL;
    var linecap = (unsigned long)0;
    var linelen = (int)getline(&buf, &linecap, stdin);
    
    buf[linelen - 1] = '\0';
    linelen -= 1;
    
    var query = string_init(buf);
    var query_tokens = array_init(sizeof(struct String*));
    
    string_components(query, separator, query_tokens);
    
    var result = red_black_tree_init(
      sizeof(struct DocumentIdentifier),
      false,
      compare2
    );
    
    if (query_tokens->count == 1) {
      struct String* term;
      array_get(query_tokens, 0, &term);
      struct Entry e;
      e.term = term;
      red_black_tree_get(inv_index, &e);
      if (red_black_tree_contains(inv_index, &e)) {
        var i = 0;
        for (i = 0; i < e.dids->count; i += 1) {
          struct DocumentIdentifier did;
          array_get(e.dids, i, &did);
          if (!red_black_tree_contains(result, &did)) {
            red_black_tree_insert(result, &did);
          }
        }
      }
    } else if (query_tokens->count == 2) {
      struct String* term;
      array_get(query_tokens, 1, &term);
      struct Entry e;
      e.term = term;
      e.dids = NULL;
      red_black_tree_get(inv_index, &e);
      
      var not_output = red_black_tree_init(sizeof(Int32), false, compare3);
      
      if (e.dids != NULL) { /* Found something */
        var i = 0;
        for (i = 0; i < e.dids->count; i += 1) {
          struct DocumentIdentifier did;
          array_get(e.dids, i, &did);
          if (!red_black_tree_contains(not_output, &did.document_number)) {
            red_black_tree_insert(not_output, &did.document_number);
          }
        }
      }
      
      var array = array_init(sizeof(Int32));
      
      var i = 0;
      for (i = 0; i < documents->count; i += 1) {
        if (red_black_tree_contains(not_output, &i)) {
          continue;
        }
        array_append(array, &i);
      }
      for (i = 0; i < array->count; i += 1) {
        var j = 0;
        array_get(array, i, &j);
        struct Document* document;
        array_get(documents, j, &document);
        var k = 0;
        for (k = 0; k < document->lines->count; k += 1) {
          struct String* line;
          array_get(document->lines, k, &line);
          string_c_string(line, output_buf);
          printf("%s\n", output_buf);
        }
        if (i != array->count - 1) {
          printf("----------\n");
        }
      }
      if (array->count == 0) {
        printf("Sorry, I found nothing.\n");
      }
      
      array_deinit(array);
      red_black_tree_deinit(not_output);
      goto end;
    } else if (query_tokens->count == 3) {
      struct String* op;
      struct String* left;
      struct String* right;
      array_get(query_tokens, 0, &left);
      array_get(query_tokens, 1, &op);
      array_get(query_tokens, 2, &right);
      
      if ((op->_utf8[0] & 0xFF) == 'O') { /* OR */
        struct Entry e;
        e.term = left;
        e.dids = NULL;
        red_black_tree_get(inv_index, &e);
        if (red_black_tree_contains(inv_index, &e)) {
          var i = 0;
          for (i = 0; i < e.dids->count; i += 1) {
            struct DocumentIdentifier did;
            array_get(e.dids, i, &did);
            if (!red_black_tree_contains(result, &did)) {
              red_black_tree_insert(result, &did);
            }
          }
        }
        e.term = right;
        e.dids = NULL;
        red_black_tree_get(inv_index, &e);
        if (red_black_tree_contains(inv_index, &e)) {
          var i = 0;
          for (i = 0; i < e.dids->count; i += 1) {
            struct DocumentIdentifier did;
            array_get(e.dids, i, &did);
            if (!red_black_tree_contains(result, &did)) {
              red_black_tree_insert(result, &did);
            }
          }
        }
      } else { /* AND */
        struct Entry e1;
        e1.term = left;
        e1.dids = NULL;
        struct Entry e2;
        e2.term = right;
        e2.dids = NULL;
        red_black_tree_get(inv_index, &e1);
        red_black_tree_get(inv_index, &e2);
        if (e1.dids != NULL && e2.dids != NULL) {
          var i = 0;
          for (i = 0; i < e1.dids->count; i += 1) {
            struct DocumentIdentifier did1;
            array_get(e1.dids, i, &did1);
            var j = 0;
            for (j = 0; j < e2.dids->count; j += 1) {
              struct DocumentIdentifier did2;
              array_get(e2.dids, j, &did2);
              
              if (did1.document_number == did2.document_number) {
                if (!red_black_tree_contains(result, &did1)) {
                  red_black_tree_insert(result, &did1);
                }
                if (!red_black_tree_contains(result, &did2)) {
                  red_black_tree_insert(result, &did2);
                }
              }
            }
          }
        }
      }
    }
    /* Output */
    var last_document = -1;
    var i = 0;
    for (i = 1; i <= result->count; i += 1) {
      struct DocumentIdentifier did;
      red_black_tree_select(result, i, &did);
      
      struct Document* document;
      struct String* line;
      array_get(documents, did.document_number, &document);
      array_get(document->lines, did.line_number, &line);
      string_c_string(line, output_buf);
      
      if (last_document != did.document_number && last_document != -1) {
        printf("----------\n");
      }
      printf("%s\n", output_buf);
      last_document = did.document_number;
    }
    if (result->is_empty) {
      printf("Sorry, I found nothing.\n");
    }
    
  end:
    printf("==========\n");
    
    string_deinit(query);
    red_black_tree_deinit(result);
  }
  
  /* Clean up */
  var i = 0;
  for (i = 0; i < documents->count; i += 1) {
    struct Document* document;
    array_get(documents, i, &document);
    document_deinit(document);
  }
  string_deinit(separator);
  red_black_tree_deinit(inv_index); /* Memory leak */
}
