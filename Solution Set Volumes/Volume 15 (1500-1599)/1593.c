//
//  1593.c
//  hxy
//
//  Created by Fang Ling on 2024/4/16.
//

#include <stdio.h>

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

#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

/*===----------------------------------------------------------------------===*/
/*                                                        ___   ___           */
/* Array START                                          /'___\ /\_ \          */
/*                                                     /\ \__/ \//\ \         */
/* Author: Fang Ling (fangling@fangl.ing)              \ \ ,__\  \ \ \        */
/* Version: 1.7                                         \ \ \_/__ \_\ \_  __  */
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

#define var __auto_type

#define ARRAY_MULTIPLE_FACTOR 2
#define ARRAY_RESIZE_FACTOR   4

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
  if ((*array).capacity == 0) {
    (*array)._storage = realloc((*array)._storage, 1 * (*array).element_size);
    (*array).capacity = 1;
  }
  if ((*array).count == (*array).capacity) {
    (*array).capacity *= ARRAY_MULTIPLE_FACTOR;
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

/* MARK: - Removing Elements */

/* Removes all the elements. */
static int array_remove_all(struct Array* array) {
  free((*array)._storage);
  (*array)._storage = NULL;
  (*array).count = 0;
  (*array).capacity = 0;
  (*array).is_empty = true;
  
  return 0;
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


#define var __auto_type

static char const WKQ_UTF8_LEN[] = {
/* 0  1  2  3  4  5  6  7  8  9  A  B  C  D  E  F */
   1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 2, 2, 3, 4
};
#define WKQUTF8LEN(c) WKQ_UTF8_LEN[((c) & 0xFF) >> 4]

struct String {
  /* A buffer of a string’s contents as a collection of UTF-8 code units. */
  struct Array utf8;
  /* The number of characters in a string. */
  int count;
  /* A Boolean value indicating whether a string has no characters. */
  bool is_empty;
};

/*-
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * Copyright (c) 2001 Mike Barcroft <mike@FreeBSD.org>
 * Copyright (c) 1990, 1993
 *  The Regents of the University of California.  All rights reserved.
 *
 * This code is derived from software contributed to Berkeley by
 * Chris Torek.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the University nor the names of its contributors
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

/*
 * Find the first occurrence of find in s, where the search is limited to the
 * first slen characters of s.
 */
static char* wkq_strnstr(const char* s, const char* find, int slen) {
  char c, sc;
  int len;
  
  if ((c = *find++) != '\0') {
    len = (int)strlen(find);
    do {
      do {
        if (slen-- < 1 || (sc = *s++) == '\0')
          return (NULL);
      } while (sc != c);
      if (len > slen)
        return (NULL);
    } while (strncmp(s, find, len) != 0);
    s--;
  }
  return ((char *)s);
}

/* MARK: - Creating and Destroying a String */

/* Creates an empty string. */
static void string_init(struct String* str) {
  (*str).count = 0;
  (*str).is_empty = true;
  array_init(&(*str).utf8, sizeof(char));
}

/*
 * Creates a string from the null-terminated character sequence (C-string)
 * pointed by s.
 */
static void string_init_c_string(struct String* str, const char* s) {
  string_init(str);
  
  var _s = s;
  while (*_s != '\0') {
    var code_len = WKQUTF8LEN(*_s);
    (*str).count += 1;
    while (code_len--) {
      array_append(&(*str).utf8, (void*)_s);
      _s += 1;
    }
  }
  if ((*str).count > 0) {
    (*str).is_empty = false;
  }
}

/* Destroys a string. */
static void string_deinit(struct String* str) {
  array_deinit(&(*str).utf8);
  (*str).count = 0;
  (*str).is_empty = true;
}

/* MARK: - Splitting a String */

/*
 * Returns an array containing substrings from the string that have been divided
 * by the given separator.
 * It's caller's responsibility to free the strings stored in the result.
 */
/*
 *                    1                 2    3             4
 * Assuming: str = "#zyy#jasdjq2n3oasd#zyy##zyy#adn972929#zyy#"
 *           separator = "#zyy#"
 *      will return 5 substrings.
 */
static void string_components_c_string(
  struct String* str,
  const char* separator,
  struct Array* result
) {
  var separator_len = (int)strlen(separator);
  
  char* tofree;
  var s = (char*)malloc(sizeof(char) * ((*str).utf8.count + 1 + separator_len));
  tofree = s;
  memcpy(s, (*str).utf8._storage, sizeof(char) * (*str).utf8.count);
  /* Append the dummy separator */
  memcpy(s + (*str).utf8.count, separator, separator_len);
  s[(*str).utf8.count + separator_len] = '\0';
  
  var substr_end = 0;
  var last_len = 0;
  var remaining_len = (*str).utf8.count + separator_len;
  
  char* i_p;
  while ((i_p = wkq_strnstr(s, separator, remaining_len)) != NULL) {
    remaining_len -= last_len;
    
    substr_end = (int)(i_p - s);
    s[substr_end] = '\0';
    last_len = (int)strlen(s);
    
    struct String new_str;
    string_init_c_string(&new_str, s);
    array_append(result, &new_str);
    /* Let the caller to call string_deinit(&new_str); */
    s += last_len;
    s += separator_len;
    remaining_len -= separator_len;
  }
  
  free(tofree);
}

/*void string_components(
  struct String* str,
  struct String* separator,
  struct Array* result
) {
  
}*/


/* MARK: - Getting C Strings */

/* Returns a representation of the string as a C string using utf-8 encoding. */
static void string_c_string(struct String* str, char* result) {
  memcpy(result, (*str).utf8._storage, (*str).utf8.count);
  result[(*str).utf8.count] = '\0';
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

#define LEN 1024

#define MAX(a, b) (a) > (b) ? (a) : (b)

void main_1593(void) {
  struct Array words[LEN];
  struct Array delta;
  array_init(&delta, sizeof(struct String));
  
  struct String str;
  struct String str2;
  
  char* buf = NULL;
  var linecap = (unsigned long)0;
  var linelen = 0;
  
  var cols = 0;
  var line_count = 0;
  while ((linelen = (int)getline(&buf, &linecap, stdin)) > 0) {
    array_init(&words[line_count], sizeof(struct String));
    array_remove_all(&delta); /* Maybe unsafe? */
    buf[linelen - 1] = '\0'; /* Remove \n */
    string_init_c_string(&str, buf);
    string_components_c_string(&str, " ", &delta);
    
    var i = 0;
    for (i = 0; i < delta.count; i += 1) {
      array_get(&delta, i, &str2);
      if (!str2.is_empty) {
        array_append(&words[line_count], &str2);
      } else {
        string_deinit(&str2); /* Empty strings are not copied to words */
      }
    }
    cols = MAX(cols, words[line_count].count);
    
    string_deinit(&str);
    line_count += 1;
  }
  var lengths = (int*)calloc(cols, sizeof(int));
  
  var i = 0;
  for (i = 0; i < cols; i += 1) {
    var j = 0;
    for (j = 0; j < line_count; j += 1) {
      if (i < words[j].count) {
        lengths[i] = MAX(lengths[i], ((struct String*)words[j]._storage)[i].count);
      }
    }
  }
  char buf2[512];
  var row = 0;
  for (row = 0; row < line_count; row += 1) {
    for (i = 0; i < words[row].count; i += 1) {
      array_get(&words[row], i, &str2);
      string_c_string(&str2, buf2);
      printf("%s", buf2);
      if (i != words[row].count - 1) { /* not the last one */
        printf(" ");
        var j = 0;
        var len = lengths[i] - str2.utf8.count;
        for (; j < len; j += 1) {
          printf(" ");
        }
      }
    }
    printf("\n");
  }

  for (i = 0; i < line_count; i += 1) {
    var j = 0;
    for (j = 0; j < words[i].count; j += 1) {
      array_get(&words[i], j, &str);
      string_deinit(&str);
    }
    array_deinit(&words[i]);
  }
  
  free(lengths);
  array_deinit(&delta);
}
