/*===----------------------------------------------------------------------===*/
/*                                                        ___   ___           */
/* p11679.c                                             /'___\ /\_ \          */
/*                                                     /\ \__/ \//\ \         */
/* Author: Fang Ling (fangling@fangl.ing)              \ \ ,__\  \ \ \        */
/* Date: November 6, 2024                               \ \ \_/__ \_\ \_  __  */
/*                                                       \ \_\/\_\/\____\/\_\ */
/*                                                        \/_/\/_/\/____/\/_/ */
/*===----------------------------------------------------------------------===*/

/*
 * This source file is part of the hxy open source project.
 *
 * Copyright (c) 2024 Fang Ling All Rights Reserved.
 *
 * Use of this source code is governed by the Apache License, Version 2.0
 * that can be found in the LICENSE file in the root of the source tree.
 * This source code may include problem descriptions from some online judges,
 * which have their own licensing terms.
 */
 
/*
 * 11679 Sub-prime
 *
 * The most recent economic crisis was partly caused by the manner in which
 * banks made loans to people unable to repay them and resold such loans to
 * other banks as debentures. Obviously, when people failed to repay their
 * loans, the whole system collapsed.
 *
 * The crisis was so deep that it affected countries all over the world,
 * including Nlogonia, where the honored prime minister Man Dashuva ordered the
 * Central Bank chairman to come up with a solution. He came up with a brilliant
 * idea: if all banks could liquidate its debentures only with its own monetary
 * reserves, all banks would survive and the crisis would be averted.
 *
 * However, with the elevated number of debentures and banks involved, this was
 * an extremely complicated task, so he asked for your help in writing a program
 * that, given the banks and the debentures printed by them, determines if it is
 * possible that all banks pay back their debts using only their monetary
 * reserves and credits.
 *
 * Input:
 * The input consists of several test cases. The first line of each test case
 * contains two integers B and N, indicating the number of banks (1 ≤ B ≤ 20)
 * and the number of debentures printed by the banks (1 ≤ N ≤ 20). The banks are
 * identified by integers between 1 and B. The second line contains B integers
 * R_i separated by spaces, indicating the monetary reserves of each one of the
 * B banks (0 ≤ Ri ≤ 10**4, for 1 ≤ i ≤ B). The N following lines contain each
 * one three integers separated by spaces: an integer D, indicating the debtor
 * bank (1 ≤ D ≤ B), an integer C , indicating the creditor bank (1 ≤ C ≤ B and
 * D != C) and an integer V , indicating the debenture value (1 ≤ V ≤ 10**4).
 * The end of input is indicated by a line containing only two zeros, separated
 * by spaces.
 *
 * Output:
 * For each test case, your program should print a single line, containing a
 * single character: 'S', if it is possible to liquidate all debentures without
 * a bailout from the Central Bank of Nlogonia, or 'N' if a bailout is
 * necessary.
 *
 * Solution:
 * Simulate; see if all banks have >= 0 reserve
 */

#include "Volume116/p11679.h"

Void p11679_main() {
  Int64 banks[20];
  
  var b = 0;
  var n = 0;
  while (scanf("%d %d", &b, &n) == 2 && b != 0) {
    var i = 0;
    for (i = 0; i < b; i += 1) {
      scanf("%lld", &banks[i]);
    }
    
    var src = 0;
    var dst = 0;
    var amount = 0;
    while (n--) {
      scanf("%d %d %d", &src, &dst, &amount);
      banks[src - 1] -= amount;
      banks[dst - 1] += amount;
    }
    
    var min = banks[0];
    for (i = 0; i < b; i += 1) {
      min = min(min, banks[i]);
    }
    printf("%s\n", min < 0 ? "N" : "S");
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
