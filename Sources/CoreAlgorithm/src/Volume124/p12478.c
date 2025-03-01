/*===----------------------------------------------------------------------===*/
/*                                                        ___   ___           */
/* p12478.c                                             /'___\ /\_ \          */
/*                                                     /\ \__/ \//\ \         */
/* Author: Fang Ling (fangling@fangl.ing)              \ \ ,__\  \ \ \        */
/* Date: November 24, 2024                              \ \ \_/__ \_\ \_  __  */
/*                                                       \ \_\/\_\/\____\/\_\ */
/*                                                        \/_/\/_/\/____/\/_/ */
/*===----------------------------------------------------------------------===*/

/*
 * This source file is part of the CoreAlgorithm open source project.
 *
 * Copyright (c) 2024 Fang Ling All Rights Reserved.
 *
 * Use of this source code is governed by the Apache License, Version 2.0
 * that can be found in the LICENSE file in the root of the source tree.
 * This source code may include problem descriptions from some online judges,
 * which have their own licensing terms.
 */

/*
 * 12478 Hardest Problem Ever (Easy)
 *
 * IUT once asked a group of people to prepare a number of problems for their
 * yearly national contest. That group of people (let's call them the setters)
 * is really enthusiastic problem solvers, they gratefully accepted the job.
 * They spent day and night, finding interesting ideas, writing solutions,
 * preparing test-data and problem descriptions. The job was almost done. I said
 * almost because for some reason they could not agree on one matter — what kind
 * of problem should be chosen as the easiest problem for this contest. One of
 * the setters proposed a problem related to something what he is currently
 * doing at office. But the coordinator of setters wasn’t really interested.
 *
 * He thought this might be too hard for the newbies. This easiest problem
 * should make everyone happy. No one should return home from the contest
 * without solving anything. So another guy suggested a + b problem, which was
 * also rejected. Reason? Some of the contestants may be really new to
 * programming and may not even know how to take input, they may come to the
 * contest only knowing how to print "Hello world!". Suddenly an idea came to
 * one of the setter's mind. He said, "If we make a task to be solved with
 * printing only, our problem is solved!" Voila! They just solved the hardest
 * problem ever — that is to make a problem that every team can solve.
 *
 * You are given a 9 × 9 grid (in the next page). The names of the setters are
 * hidden in the grid. Names are given below (in no particular order):
 *
 * RAKIBUL
 * ANINDYA
 * MOSHIUR
 * SHIPLU
 * KABIR
 * SUNNY
 * OBAIDA
 * WASI
 *
 * They are hidden in the following ways:
 *   1. The names are present in the grid either vertically or horizontally.
 *      (Letters of a particular name will be adjacent either only horizontally
 *      or only vertically).
 *   2. Each person’s name may not be in its original form, letters may be
 *      permuted. For example "wasi" can be present as "iaws".
 *   3. Exactly the names mentioned above are given. Knowing any other name of
 *      them will not give you any advantage.
 *
 * Now, the task: It is guaranteed that only one name is hidden exactly twice in
 * this grid. All the other names are hidden exactly once. You have to print the
 * name which is hidden just twice.
 *
 * The grid:
 * O B I D A I B K R
 * R K A U L H I S P
 * S A D I Y A N N O
 * H E I S A W H I A
 * I R A K I B U L S
 * M F B I N T R N O
 * U T O Y Z I F A H
 * L E B S Y N U N E
 * E M O T I O N A L
 *
 * Input:
 * There is no input for this problem.
 *
 * Output:
 * Output just one string which is the name hidden twice in the grid.
 *
 * Solution:
 * Brute force.
 */

#include "Volume124/p12478.h"

static Int32 p12478_char_compare(AnyConstantObject lhs, AnyConstantObject rhs) {
  let _lhs = *(Char*)lhs;
  let _rhs = *(Char*)rhs;

  if (_lhs < _rhs) {
    return -1;
  } else if (_lhs > _rhs) {
    return 1;
  }
  return 0;
}

static Void p12478_sort_char_array(Char* string) {
  let count = strlen(string);
  qsort(string, count, sizeof(Char), p12478_char_compare);
}

static Int32 p12478_count_name(Char** grid, Char* name) {
  var count = 0;

  let name_count = (Int32)strlen(name);
  var name_copy = ansi_strdup(name);
  p12478_sort_char_array(name_copy);

  var r = 0;
  for (; r < 9; r += 1) {
    var c = 0;
    for (; c < 9; c += 1) {
      var new_name = (Char*)malloc(sizeof(Char) * (name_count + 1));

      /* Construct and compare the new name (in row direction) */
      var i = 0;
      for (; i < name_count && i + r < 9; i += 1) {
        new_name[i] = grid[i + r][c];
      }
      new_name[i] = '\0';
      p12478_sort_char_array(new_name);
      if (strcmp(name_copy, new_name) == 0) {
        count += 1;
      }

      /* Construct and compare the new name (in column direction) */
      for (i = 0; i < name_count && i + c < 9; i += 1) {
        new_name[i] = grid[r][i + c];
      }
      new_name[i] = '\0';
      p12478_sort_char_array(new_name);
      if (strcmp(name_copy, new_name) == 0) {
        count += 1;
      }

      free(new_name);
    }
  }
  
  free(name_copy);

  return count;
}

Void p12478_main() {
  Char* grid[16];
  grid[0] = "OBIDAIBKR";
  grid[1] = "RKAULHISP";
  grid[2] = "SADIYANNO";
  grid[3] = "HEISAWHIA";
  grid[4] = "IRAKIBULS";
  grid[5] = "MFBINTRNO";
  grid[6] = "UTOYZIFAH";
  grid[7] = "LEBSYNUNE";
  grid[8] = "EMOTIONAL";

  Char* names[8];
  names[0] = "RAKIBUL";
  names[1] = "ANINDYA";
  names[2] = "MOSHIUR";
  names[3] = "SHIPLU";
  names[4] = "KABIR";
  names[5] = "SUNNY";
  names[6] = "OBAIDA";
  names[7] = "WASI";

  var i = 0;
  for (; i < 8; i += 1) {
    if (p12478_count_name(grid, names[i]) == 2) {
      printf("%s\n", names[i]);
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
