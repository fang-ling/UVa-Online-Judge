//
//  814.c
//  hxy
//
//  Created by Fang Ling on 2024/4/13.
//

#include <stdio.h>

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

/* MARK: - Finding Elements */

/*
 * Returns a Boolean value indicating whether the sequence contains the given
 * element.
 */
static bool array_contains(
  struct Array* array,
  void* key,
  bool (*equal)(const void*, const void*)
) {
  var buf = malloc((*array).element_size);
  var i = 0;
  for (i = 0; i < (*array).count; i += 1) {
    array_get(array, i, buf);
    if (equal(buf, key)) {
      free(buf);
      return true;
    }
  }
  free(buf);
  return false;
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

/* The strsep() function first appeared in 4.4BSD. */
/*
 * Copyright (c) 1999 Apple Computer, Inc. All rights reserved.
 *
 * @APPLE_LICENSE_HEADER_START@
 *
 * The contents of this file constitute Original Code as defined in and
 * are subject to the Apple Public Source License Version 1.1 (the
 * "License").  You may not use this file except in compliance with the
 * License.  Please obtain a copy of the License at
 * http://www.apple.com/publicsource and read it before using this file.
 *
 * This Original Code and all software distributed under the License are
 * distributed on an "AS IS" basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE OR NON-INFRINGEMENT.  Please see the
 * License for the specific language governing rights and limitations
 * under the License.
 *
 * @APPLE_LICENSE_HEADER_END@
 */
/*
 * Copyright (c) 1990, 1993
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
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *  This product includes software developed by the University of
 *  California, Berkeley and its contributors.
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

/*
 * Get next token from string *stringp, where tokens are possibly-empty
 * strings separated by characters from delim.
 *
 * Writes NULs into the string at *stringp to end tokens.
 * delim need not remain constant from call to call.
 * On return, *stringp points past the last NUL written (if there might
 * be further tokens), or is NULL (if there are definitely no more tokens).
 *
 * If *stringp is NULL, strsep returns NULL.
 */
static char* hxy_strsep(char** stringp, const char* delim) {
  char *s;
  const char *spanp;
  int c, sc;
  char *tok;
  
  if ((s = *stringp) == NULL)
    return (NULL);
  for (tok = s;;) {
    c = *s++;
    spanp = delim;
    do {
      if ((sc = *spanp++) == c) {
        if (c == 0)
          s = NULL;
        else
          s[-1] = 0;
        *stringp = s;
        return (tok);
      }
    } while (sc != 0);
  }
  /* NOTREACHED */
}

#define LEN 2048

struct MTA {
  char location[LEN];
  char names[LEN][LEN];
  int n;
};

struct User {
  char name[LEN];
  char MTA[LEN];
};

static bool user_equals(const void* a, const void* b) {
  var _a = *(struct User*)a;
  var _b = *(struct User*)b;
  
  return strcmp(_a.name, _b.name) == 0 && strcmp(_a.MTA, _b.MTA) == 0;
}

void main_814(void) {
  struct Array mtas;
  struct Array recpts[LEN];
  array_init(&mtas, sizeof(struct MTA));
  var i = 0;
  
  
  struct MTA mta;
  struct User u;
  struct User sender;
  char* token = NULL;
  var buf = (char*)malloc(sizeof(char) * LEN);
  
  /* Read MTAs */
  while (scanf("%s", buf) == 1 && buf[0] != '*') {
    if (buf[0] == 'M' && buf[1] == 'T' && buf[2] == 'A') {
      scanf("%s", buf);
      strcpy(mta.location, buf);
      array_append(&mtas, &mta);
      var n = 0;
      scanf("%d", &n);
      for (i = 0; i < n; i += 1) {
        scanf("%s", buf);
        strcpy(((struct MTA*)mtas._storage)[mtas.count - 1].names[i], buf);
      }
      ((struct MTA*)mtas._storage)[mtas.count - 1].n = n;
    }
  }
  var rcpts_cnt = 0;
  /* Handle addrs and messages */
  while (scanf("%s", buf) == 1 && buf[0] != '*') {
    for (i = 0; i < LEN; i += 1) {
      array_init(&recpts[i], sizeof(struct User));
    }
    rcpts_cnt = 0;
    
    /* Read RCPTs */
    var tofree = strdup(buf);
    var is_first = true;
    while ((token = hxy_strsep(&tofree, "@")) != NULL) {
      if (is_first) {
        is_first = false;
        strcpy(sender.name, token);
      } else {
        strcpy(sender.MTA, token);
      }
    }
    free(tofree);
    while (scanf("%s", buf) == 1 && buf[0] != '*') {
      tofree = strdup(buf);
      is_first = true;
      while ((token = hxy_strsep(&tofree, "@")) != NULL) {
        if (is_first) {
          is_first = false;
          strcpy(u.name, token);
        } else {
          strcpy(u.MTA, token);
        }
      }
      free(tofree);
      
      var contains = false;
      var j = 0;
      for (j = 0; j < rcpts_cnt; j += 1) {
        if (array_contains(&recpts[j], &u, user_equals)) {
          contains = true;
          continue;
        }
        var k = 0;
        for (k = 0; k < recpts[j].count; k += 1) {
          if (strcmp(((struct User*)(recpts[j]._storage))[k].MTA, u.MTA) == 0) {
            contains = true;
            array_append(&recpts[j], &u);
            break;
          }
        }
      }
      if (!contains) {
        array_append(&recpts[rcpts_cnt], &u);
        rcpts_cnt += 1;
      }
    }
    
    var msg = (char*)malloc(sizeof(char) * LEN * LEN * LEN);
    msg[0] = '\0';
    char* buf2 = NULL;
    var linecap = (unsigned long)0;
    var llen = 0;
    while ((llen = (int)getline(&buf2, &linecap, stdin)) > 0 && buf2[0] != '*') {
      if (buf2[0] == '\r' || buf2[0] == '\n') { /* last char */
        continue;
      }
      strcat(msg, "     ");
      strcat(msg, buf2); /* already has \n */
    }
    
    for (i = 0; i < rcpts_cnt; i += 1) {
      printf(
        "Connection between %s and %s\n",
        sender.MTA,
        ((struct User*)recpts[i]._storage)[0].MTA
      );
      printf("     HELO %s\n", sender.MTA);
      printf("     250\n");
      printf("     MAIL FROM:<%s@%s>\n", sender.name, sender.MTA);
      printf("     250\n");
      var is_send_data = false;
      var k = 0;
      for (k = 0; k < recpts[i].count; k += 1) {
        var is_valid_user = false;
        var m = 0;
        for (m = 0; m < mtas.count; m += 1) {
          var is_contains = false;
          var ll = 0;
          for (ll = 0; ll < ((struct MTA*)mtas._storage)[m].n; ll += 1) {
            if (
              strcmp(((struct MTA*)mtas._storage)[m].names[ll],
                     ((struct User*)recpts[i]._storage)[k].name) == 0
            ) {
              is_contains = true;
              break;
            }
          }
          if (
            strcmp(((struct MTA*)mtas._storage)[m].location,
                   ((struct User*)recpts[i]._storage)[k].MTA) == 0 &&
            is_contains
          ) {
            is_valid_user = true;
            break;
          }
        }
        printf(
          "     RCPT TO:<%s@%s>\n",
          ((struct User*)recpts[i]._storage)[k].name,
          ((struct User*)recpts[i]._storage)[k].MTA
        );
        if (is_valid_user) {
          is_send_data = true;
          printf("     250\n");
        } else {
          printf("     550\n");
        }
      }
      if (is_send_data) {
        printf("     DATA\n");
        printf("     354\n");
        printf("%s", msg);
        printf("     .\n");
        printf("     250\n");
      }
      printf("     QUIT\n");
      printf("     221\n");
      
    }
    
    for (i = 0; i < LEN; i += 1) {
      array_deinit(&recpts[i]);
    }
    free(msg);
  }
  
  array_deinit(&mtas);
  free(buf);
}
