//
//  207.c
//  hxy
//
//  Created by Fang Ling on 2024/4/12.
//

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

/* MARK: - Removing Elements */

/* Removes the last element of the collection. */
static int array_remove_last(struct Array* array) {
  var q1 = 4;
  var q2 = 2;

  if ((*array).is_empty) {
    return 6;
  }
  (*array).count -= 1;
  if ((*array).count == 0) {
    (*array).is_empty = true;
  }
  if ((*array).count * q1 <= (*array).capacity) {
    (*array).capacity /= q2;
    var new_size = (*array).capacity * (*array).element_size;
    (*array)._storage = realloc((*array)._storage, new_size);
    if ((*array)._storage == NULL) {
      /* FIXME: memory leak will happen if realloc failed */
      return 5;
    }
  }

  return 0;
}

/* Removes all the elements. */
static int array_remove_all(struct Array* array) {
  free((*array)._storage);
  (*array)._storage = NULL;
  (*array).count = 0;
  (*array).capacity = 0;
  (*array).is_empty = true;
  
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

#include <stdio.h>
#include <stdbool.h>

#define var __auto_type

struct Player {
  char name[32];
  int round[4];
  bool is_amateur;
  bool is_dq;
  
  /* Only meaningful when player is not dq */
  int tot72;
  int tot36;
  int rounds;
};

static int find_tie_rank_count(struct Array* players) {
  var unsafe = (struct Player*)(*players)._storage;
  var res = (*players).count;
  var i = 0;
  for (i = 69; i < res; i += 1) {
    if (i == res - 1 || unsafe[i].tot36 != unsafe[i + 1].tot36) {
      res = i + 1;
      break;
    }
  }
  return res;
}

static int cmp1(const void* a, const void* b) {
  var _a = *(struct Player*)a;
  var _b = *(struct Player*)b;
  if (_a.tot36 < 0 && _b.tot36 < 0) {
    return 0;
  }
  if (_a.tot36 < 0) {
    return 1;
  }
  if (_b.tot36 < 0) {
    return -1;
  }
  if (_a.tot36 < _b.tot36) {
    return -1;
  } else if (_a.tot36 > _b.tot36) {
    return 1;
  }
  return 0;
}

static int cmp2(const void* a, const void* b) {
  var _a = *(struct Player*)a;
  var _b = *(struct Player*)b;
  
  if (_a.is_dq && _b.is_dq) {
    if (_a.rounds != _b.rounds) {
      return _b.rounds - _a.rounds; /* unsafe */
    }
    if (_a.tot72 != _b.tot72) {
      return _a.tot72 - _b.tot72; /* unsafe */
    }
    return strcmp(_a.name, _b.name);
  }
  if (_a.is_dq) {
    return 1;
  }
  if (_b.is_dq) {
    return -1;
  }
  if (_a.tot72 != _b.tot72) {
    return _a.tot72 - _b.tot72; /* unsafe */
  }
  return strcmp(_a.name, _b.name);
}

void main_207(void) {
  struct Array players;
  array_init(&players, sizeof(struct Player));
  double percents[70];
  struct Player p;
  char alpha[32][32];
  
  char* buf = NULL;
  char buf2[512];
  var linecap = (unsigned long)0;
  var linelen = 0;
  char* token = NULL;
  
  var cases = 0;
  linelen = (int)getline(&buf, &linecap, stdin);
  sscanf(buf, "%d", &cases);
  while (cases--) {
    array_remove_all(&players);
    
    /* Input part 1, money */
    var purse = 0.0;
    linelen = (int)getline(&buf, &linecap, stdin);
    linelen = (int)getline(&buf, &linecap, stdin);
    sscanf(buf, "%lf", &purse);
    var i = 0;
    for (i = 0; i < 70; i += 1) {
      linelen = (int)getline(&buf, &linecap, stdin);
      sscanf(buf, "%lf", &percents[i]);
    }
    
    /* Players */
    var n = 0;
    linelen = (int)getline(&buf, &linecap, stdin);
    sscanf(buf, "%d", &n);
    for (i = 0; i < n; i += 1) {
      /* init player */
      p.is_amateur = false;
      p.is_dq = false;
      p.tot36 = 0;
      p.tot72 = 0;
      p.round[0] = 0;
      p.round[1] = 0;
      p.round[2] = 0;
      p.round[3] = 0;
      
      linelen = (int)getline(&buf, &linecap, stdin);
      buf[linelen - 1] = '\0'; /* Remove extra \n */
      var j = 0;
      for (j = 0; j < 20; j += 1) { /* Copy name */
        p.name[j] = buf[j];
      }
      /* trim */
      for (j = 19; j >= 0; j -= 1) {
        if (p.name[j] == ' ') {
          p.name[j] = '\0';
        } else {
          break;
        }
      }
      if (p.name[strlen(p.name) - 1] == '*') {
        p.is_amateur = true;
      }
      /* Scores */
      memmove(buf, buf + 20, linelen - 20);
      for (j = linelen - 1; j >= linelen - 20; j -= 1) {
        buf[j] = '\0';
      }
      var alpha_count = 0;
      while ((token = hxy_strsep(&buf, " ")) != NULL) {
        if (token[0] == '\0') { /* Empty strings */
          continue;
        }
        strcpy(alpha[alpha_count], token);
        alpha_count += 1;
      }
      for (j = 0; j < alpha_count; j += 1) {
        if (alpha[j][0] == 'D') {
          p.rounds = j;
          p.is_dq = true;
          if (j < 2) {
            p.tot36 = -1;
          }
          break;
        } else {
          sscanf(alpha[j], "%d", &p.round[j]);
          p.tot72 += p.round[j];
          if (j < 2) {
            p.tot36 += p.round[j];
          }
        }
      }
      array_append(&players, &p);
    }
    /* Sort: make the cut */
    array_sort(&players, cmp1);
    n = find_tie_rank_count(&players);
    while (players.count > n) {
      array_remove_last(&players);
    }
    /* Sort: ranklist */
    array_sort(&players, cmp2);
    /* Print result */
    printf(
      "Player Name          Place     RD1  RD2  RD3  RD4  TOTAL     Money Won\n"
    );
    printf(
      "-----------------------------------------------------------------------"
    );
    printf("\n");
    
    i = 0;
    var pos = 0;
    var ps = (struct Player*)players._storage;
    while (i < n) {
      if (ps[i].is_dq) {
        printf("%-30s ", ps[i].name);
        var j = 0;
        for (j = 0; j < ps[i].rounds; j += 1) {
          printf("%-5d", ps[i].round[j]);
        }
        for (j = 0; j < 4 - ps[i].rounds; j += 1) {
          printf("     ");
        }
        printf("DQ\n");
        i += 1;
        continue;
      }
      var j = i;
      var tie_cnt = 0;
      var has_money = false;
      var tot = 0.0;
      while (j < n && ps[i].tot72 == ps[j].tot72) {
        if (!ps[j].is_amateur) {
          tie_cnt += 1;
          if (pos < 70) {
            has_money = true;
            tot += percents[pos];
            pos += 1;
          }
        }
        j += 1;
      }
      var rank = i + 1;
      var award = 0.0;
      if (tie_cnt == 0) {
        award = 0.0;
      } else {
        award = purse * tot / (double)tie_cnt;
      }
      while (i < j) {
        printf("%-20s ", ps[i].name);
        sprintf(buf2, "%d", rank);
        var xxx = (int)strlen(buf2);
        buf2[xxx] = tie_cnt > 1 && has_money && !ps[i].is_amateur ? 'T' : ' ';
        xxx += 1;
        buf2[xxx] = '\0';
        printf("%-10s", buf2);
        var k = 0;
        for (k = 0; k < 4; k += 1) {
          printf("%-5d", ps[i].round[k]);
        }
        if (!ps[i].is_amateur && has_money) {
          printf("%-10d", ps[i].tot72);
          printf("$%9.2f\n", award / 100.00);
        } else {
          printf("%d\n", ps[i].tot72);
        }
        i += 1;
      }
    }
    if (cases > 0) {
      printf("\n");
    }
  }
  
  array_deinit(&players);
}
