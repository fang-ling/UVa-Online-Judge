//
//  1596.c
//  hxy
//
//  Created by Fang Ling on 2024/4/28.
//

#pragma GCC optimize ("O0")
/*
 * We have to disable optimization on GCC for this problem, only gods know why.
 */

#include <stdio.h>

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

/* Replaces the element at the specified position. */
static void array_set(struct Array* array, Int64 index, void* element) {
  _array_check_index(array, index);

  memcpy(
    array->_storage + array->_width * index,
    element,
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

static
struct String* _string_init(UInt32* _utf8, Int32* _utf8_length, Int64 count) {
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

/*-
 * Copyright (c) 1992, 1993
 *  The Regents of the University of California.  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 4. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */
static Int32 _wkq_strtoll(
  const char* __restrict nptr,
  char** __restrict endptr,
  int base,
  Int64* result
) {
  const char *s;
  UInt64 acc;
  char c;
  UInt64 cutoff;
  Int32 neg, any, cutlim;

  /*
   * Skip white space and pick up leading +/- sign if any.
   * If base is 0, allow 0x for hex and 0 for octal, else
   * assume decimal; if base is already 16, allow 0x.
   */
  s = nptr;
  do {
    c = *s++;
  } while (isspace((unsigned char)c));
  if (c == '-') {
    neg = 1;
    c = *s++;
  } else {
    neg = 0;
    if (c == '+')
      c = *s++;
  }
  if ((base == 0 || base == 16) &&
      c == '0' && (*s == 'x' || *s == 'X') &&
      ((s[1] >= '0' && s[1] <= '9') ||
      (s[1] >= 'A' && s[1] <= 'F') ||
      (s[1] >= 'a' && s[1] <= 'f'))) {
    c = s[1];
    s += 2;
    base = 16;
  }
  if (base == 0)
    base = c == '0' ? 8 : 10;
  acc = any = 0;
  if (base < 2 || base > 36)
    goto noconv;

  /*
   * Compute the cutoff value between legal numbers and illegal
   * numbers.  That is the largest legal value, divided by the
   * base.  An input number that is greater than this value, if
   * followed by a legal input character, is too big.  One that
   * is equal to this value may be valid or not; the limit
   * between valid and invalid numbers is then based on the last
   * digit.  For instance, if the range for quads is
   * [-9223372036854775808..9223372036854775807] and the input base
   * is 10, cutoff will be set to 922337203685477580 and cutlim to
   * either 7 (neg==0) or 8 (neg==1), meaning that if we have
   * accumulated a value > 922337203685477580, or equal but the
   * next digit is > 7 (or 8), the number is too big, and we will
   * return a range error.
   *
   * Set 'any' if any `digits' consumed; make it negative to indicate
   * overflow.
   */
  cutoff = neg ? (UInt64) - (WKQ_INT64_MIN + WKQ_INT64_MAX) + WKQ_INT64_MAX
      : WKQ_INT64_MAX;
  cutlim = cutoff % base;
  cutoff /= base;
  for ( ; ; c = *s++) {
    if (c >= '0' && c <= '9')
      c -= '0';
    else if (c >= 'A' && c <= 'Z')
      c -= 'A' - 10;
    else if (c >= 'a' && c <= 'z')
      c -= 'a' - 10;
    else
      break;
    if (c >= base)
      break;
    if (any < 0 || acc > cutoff || (acc == cutoff && c > cutlim))
      any = -1;
    else {
      any = 1;
      acc *= base;
      acc += c;
    }
  }
  if (any < 0) {
    acc = neg ? WKQ_INT64_MIN : WKQ_INT64_MAX;
    return 1; /*errno = ERANGE;*/
  } else if (!any) {
noconv:
    return -1; /*errno = EINVAL;*/
  } else if (neg)
    acc = -acc;
  if (endptr != NULL)
    *endptr = (char *)(any ? s - 1 : nptr);
  *result = acc;
  return 0;
}

/* MARK: - Creating and Destroying a String */

static struct String* string_init(const char* s) {
  struct String* string;
  if ((string = malloc(sizeof(struct String))) == NULL) {
    return NULL;
  }
  
  /* Calculate capacity & is_empty */
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

/* MARK: - Converting Strings */

static Int32 string_to_int64(struct String* string, Int32 base, Int64* result) {
  /* Optimization needed */
  var buf = malloc((string->count + 1) * sizeof(char));
  
  string_c_string(string, buf);
  var ret = _wkq_strtoll(buf, NULL, base, result);
  /*
   * 0: OK
   * 1: The given string was out of range; the value converted has been clamped.
   * 2: The value of base is not supported or no conversion could be performed
   *    (the last feature is not portable across all platforms).
   */
  free(buf);
  
  return ret;
}

/* MARK: - Finding Characters */

/* Returns the first index where the specified value appears in the string. */
static
Int64 string_first_index_of(struct String* string, struct String* value) {
  if (value->is_empty) { /* Special case for empty value */
    return -1;
  }
  
  var i = 0;
  var length = string->count - value->count + 1;
  for (i = 0; i < length; i += 1) {
    var j = 0;
    while (j < value->count && string->_utf8[i + j] == value->_utf8[j]) {
      j += 1;
    }
    if (j == value->count) { /* Find a match at i */
      return i;
    }
  }
  return -1;
}

/* Returns the last index where the specified value appears in the string. */
static
Int64 string_last_index_of(struct String* string, struct String* value) {
  /* Special case for empty value & string */
  if (value->is_empty || string->is_empty) {
    return -1;
  }
  
  var i = 0ll;
  var length = string->count - value->count + 1;
  for (i = length - 1; i >= 0; i -= 1) {
    var j = 0;
    while (j < value->count && string->_utf8[i + j] == value->_utf8[j]) {
      j += 1;
    }
    if (j == value->count) { /* Find a match at i */
      return i;
    }
  }
  return -1;
}

/*
 * Returns a Boolean value indicating whether the sequence contains the given
 * string.
 */
static Bool string_contains(struct String* string, struct String* another) {
  return !(string_first_index_of(string, another) == -1);
}

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

struct Entry {
  Int32 key;
  Int32 value;
};

struct Array_1596 {
  char name;
  Int32 count;
  
  struct Array* storage;
};

static struct Array_1596* array_1596_init(char name, Int32 count) {
  struct Array_1596* array;
  if ((array = malloc(sizeof(struct Array_1596))) == NULL) {
    return NULL;
  }
  
  array->name = name;
  array->count = count;
  array->storage = array_init(sizeof(struct Entry));
  
  return array;
}

static void array_1596_deinit(struct Array_1596* array) {
  array_deinit(array->storage);
  free(array);
  array = NULL;
}

static struct String* get_between(struct String* expr) {
  var lb = string_init("[");
  var ub = string_init("]");
  
  var val = string_substring(
    expr,
    string_first_index_of(expr, lb) + 1,
    string_last_index_of(expr, ub)
  );
  
  string_deinit(lb);
  string_deinit(ub);
  
  return val;
}

static Int32 evaluate(struct Array* arrays, struct String* expr) {
  var result = 0LL;
  if (string_to_int64(expr, 10, &result) == 0) {
    return (Int32)result;
  }
  
  var tofree = get_between(expr);
  result = evaluate(arrays, tofree);
  string_deinit(tofree);
  
  if (result < 0) {
    return (Int32)result;
  }
  
  struct Array_1596* array = NULL;
  struct Array_1596* j;
  var i = 0;
  for (i = 0; i < arrays->count; i += 1) {
    array_get(arrays, i, &j);
    if (j->name == (expr->_utf8[0] & 0xFF)) {
      array = j;
      break;
    }
  }
  if (array == NULL || array->count == 0 || result >= array->count) {
    return -1;
  }
  var contains = false;
  struct Entry e;
  for (i = 0; i < array->storage->count; i += 1) {
    array_get(array->storage, i, &e);
    if (e.key == result) {
      contains = true;
      break;
    }
  }
  if (!contains) {
    return -1;
  }
  return e.value;
}

static Int32 evaluate_left(struct Array* arrays, struct String* expr) {
  var tofree = get_between(expr);
  var result = evaluate(arrays, tofree);
  string_deinit(tofree);
  return result;
}

void main_1596(void) {
  char buf[128];
  struct String* string;
  struct Array_1596* array;
  
  var codes = array_init(sizeof(struct String*));
  var arrays = array_init(sizeof(struct Array_1596*));
  var equal_sign_string = string_init("=");
  
  while (scanf("%s", buf) == 1 && buf[0] != '.') {
    /* Initialization */
    var i = 0;
    for (i = 0; i < codes->count; i += 1) {;
      array_get(codes, i, &string);
      string_deinit(string);
    }
    for (i = 0; i < arrays->count; i += 1) {
      array_get(arrays, i, &array);
      array_1596_deinit(array);
    }
    array_remove_all(codes);
    array_remove_all(arrays);
    var line_num = 0;
    var is_printed = false;
    
    /* Read input */
    string = string_init(buf);
    array_append(codes, &string);
    while (scanf("%s", buf) == 1 && buf[0] != '.') {
      string = string_init(buf);
      array_append(codes, &string);
    }
    
    /* Parse codes */
    for (i = 0; i < codes->count; i += 1) {
      array_get(codes, i, &string);
      line_num += 1;
      if (!string_contains(string, equal_sign_string)) { /* declaration */
        char name = string->_utf8[0] & 0xFF;
        var count_string = get_between(string);
        var count = 0LL;
        string_to_int64(count_string, 10, &count);
        array = array_1596_init(name, (Int32)count);
        array_append(arrays, &array);
        string_deinit(count_string);
      } else { /* assignment */
        var stmt = array_init(sizeof(struct String*));
        string_components(string, equal_sign_string, stmt);
        struct String* left_string;
        struct String* right_string;
        array_get(stmt, 0, &left_string);
        array_get(stmt, 1, &right_string);
        
        var left_index = evaluate_left(arrays, left_string);
        var right = evaluate(arrays, right_string);
        if (left_index < 0 || right < 0) {
          if (!is_printed) {
            printf("%d\n", line_num);
            is_printed = true;
          }
          string_deinit(left_string);
          string_deinit(right_string);
          array_deinit(stmt);
          continue;
        }
        var is_founded = false;
        var j = 0;
        for (j = 0; j < arrays->count; j += 1) {
          array_get(arrays, j, &array);
          if (array->name == (left_string->_utf8[0] & 0xFF)) {
            is_founded = true;
            if (
              !is_printed &&
              (array->count == 0 || array->count <= left_index)
            ) {
              printf("%d\n", line_num);
              is_printed = true;
              break;
            }
            struct Entry e;
            struct Entry e2;
            e.key = left_index;
            e.value = evaluate(arrays, right_string);
            var is_replace = false;
            var k = 0;
            for (k = 0; k < array->storage->count; k += 1) {
              array_get(array->storage, k, &e2);
              if (e2.key == e.key) {
                is_replace = true;
                break;
              }
            }
            if (is_replace) {
              array_set(array->storage, k, &e);
            } else {
              array_append(array->storage, &e);
            }
            
            /* Update arrays, maybe not needed. */
            array_set(arrays, j, &array);
            
            break;
          }
        }
        if (!is_founded) {
          printf("%d\n", line_num);
          is_printed = true;
        }
        
        string_deinit(left_string);
        string_deinit(right_string);
        array_deinit(stmt);
      }
    }
    if (!is_printed) {
      printf("0\n");
    }
  }
  
  string_deinit(equal_sign_string);
  array_deinit(codes);
}
