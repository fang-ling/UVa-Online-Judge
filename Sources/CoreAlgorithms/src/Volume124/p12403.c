/*===----------------------------------------------------------------------===*/
/*                                                        ___   ___           */
/* p12403.c                                             /'___\ /\_ \          */
/*                                                     /\ \__/ \//\ \         */
/* Author: Fang Ling (fangling@fangl.ing)              \ \ ,__\  \ \ \        */
/* Date: May 4, 2025                                    \ \ \_/__ \_\ \_  __  */
/*                                                       \ \_\/\_\/\____\/\_\ */
/*                                                        \/_/\/_/\/____/\/_/ */
/*===----------------------------------------------------------------------===*/

/*
 * This source file is part of the CoreAlgorithm open source project.
 *
 * Copyright (c) 2024-2025 Fang Ling All Rights Reserved.
 *
 * Use of this source code is governed by the Apache License, Version 2.0
 * that can be found in the LICENSE file in the root of the source tree.
 * This source code may include problem descriptions from some online judges,
 * which have their own licensing terms.
 */

/*
 * 12403 Save Shetu
 *
 * Rahaduzzaman Setu, (Roll - 12) of 13th batch, CSE, University of Dhaka is
 * tremendously ill. He has been suffering from Multi Drug Resistant TB for a
 * long time. Now, his left lung is damaged and beyond repair. No medicine is
 * working on his body to ease his pain. It is urgent to operate on his left
 * lung so that the disease doesn’t spread to his right lung. It can either be
 * removed through surgery or transplanted. He comes from a modest family and it
 * is difficult and impossible for them to bare his medical expenses anymore.
 * Because of the money needed (12 million BDT) to transplant, it is his
 * family's decision to go with the surgery (3 million BDT). We must help them
 * financially by raising money. But we must not be confined with that amount
 * only to do the surgery. We must go for the Transplant. Our target will be to
 * collect as much as possible to help our friend.
 *
 * If anyone wants to contribute now, please send me your contribution or
 * contact me. Please contribute as much as you can to save a life that you saw
 * every week for the first two years of your University life. Please contribute
 * as per your abilities. Our combined effort may save a life.
 *
 * For more information, consult the link below.
 *
 *   http://supportsetu.com/
 *
 * However, in this problem, you have to build a software that can calculate the
 * donations. Initially the total amount of money is 0 and in each time, two
 * types of operations will be there.
 *
 *   1) 'donate K' (100 ≤ K ≤ 105), then you have to add K to the account.
 *   2) 'report', report all the money currently in the account.
 *
 * Input:
 * The first line of input will contain T (1 ≤ T ≤ 100) denoting the number of
 * operations. Then there will be T lines each containing two types of
 * operations as given. You may assume that the input follows the restrictions
 * above.
 *
 * Output:
 * For each 'report' operation, print the total amount of money in the account.
 */

#include "Volume124/p12403.h"

Void p12403_main() {
  var balance = 0;

  var operation_count = 0;
  scanf("%d", &operation_count);

  Int8 operation[8];
  while (operation_count--) {
    scanf("%s", operation);

    if (operation[0] == 'd') {
      var k = 0;
      scanf("%d", &k);
      balance += k;
    } else {
      printf("%d\n", balance);
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
