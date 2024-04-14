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
    /*var tofree = strdup(buf);
    var is_first = true;
    while ((token = hxy_strsep(&tofree, "@")) != NULL) {
      if (is_first) {
        is_first = false;*/
    var at_i = 0;
    var at_count = (int)strlen(buf);
    for (at_i = 0; at_i < at_count; at_i += 1) {
      if (buf[at_i] == '@') {
        break;
      }
    }
    memset(sender.name, 0, LEN);
    memset(sender.MTA, 0, LEN);
    var ii = 0;
    for (ii = 0; ii < at_i; ii += 1) {
      sender.name[ii] = buf[ii];
    }
    sender.name[ii] = '\0';
    /*strcpy(sender.name, "test");*/
      /*} else {*/
    
    for (ii = at_i + 1; ii < at_count; ii += 1) {
      sender.MTA[ii - at_i - 1] = buf[ii];
    }
    sender.MTA[ii] = '\0';
        /*strcpy(sender.MTA, "test");*/
      /*}
    }
    free(tofree);*/
    while (scanf("%s", buf) == 1 && buf[0] != '*') {
      
      at_i = 0;
      at_count = (int)strlen(buf);
      for (at_i = 0; at_i < at_count; at_i += 1) {
        if (buf[at_i] == '@') {
          break;
        }
      }
      memset(u.name, 0, LEN);
      memset(u.MTA, 0, LEN);
      var ii = 0;
      for (ii = 0; ii < at_i; ii += 1) {
        u.name[ii] = buf[ii];
      }
      u.name[ii] = '\0';
      /*strcpy(sender.name, "test");*/
        /*} else {*/
      for (ii = at_i + 1; ii < at_count; ii += 1) {
        u.MTA[ii - at_i - 1] = buf[ii];
      }
      u.MTA[ii] = '\0';
      /*tofree = strdup(buf);
      is_first = true;
      while ((token = hxy_strsep(&tofree, "@")) != NULL) {
        if (is_first) {
          is_first = false;*/
          
        /*} else {*/
          
        /*}
      }
      free(tofree);*/
      
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
