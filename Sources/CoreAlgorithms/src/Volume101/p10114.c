/*===----------------------------------------------------------------------===*/
/*                                                        ___   ___           */
/* p10114.c                                             /'___\ /\_ \          */
/*                                                     /\ \__/ \//\ \         */
/* Author: Fang Ling (fangling@fangl.ing)              \ \ ,__\  \ \ \        */
/* Date: October 2, 2024                                \ \ \_/__ \_\ \_  __  */
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
 * 10114 Loansome Car Buyer
 * 
 * Kara Van and Lee Sabre are lonesome. A few months ago they took out a loan to
 * buy a new car, but now they’re stuck at home on Saturday night without wheels
 * and without money. You see, there was a wreck and the car was totaled. Their
 * insurance paid $10,000, the current value of the car. The only problem is
 * that they owed the bank $15,000, and the bank wanted payment immediately,
 * since there was no longer a car for collateral. In just a few moments, this
 * unfortunate couple not only lost their car, but lost an additional $5,000 in
 * cash too.
 *
 * What Kara and Lee failed to account for was depreciation, the loss in value
 * as the car ages. Each month the buyer’s loan payment reduces the amount owed
 * on the car. However, each month, the car also depreciates as it gets older.
 * Your task is to write a program that calculates the first time, measured in
 * months, that a car buyer owes less money than a car is worth. For this
 * problem, depreciation is specified as a percentage of the previous month’s
 * value.
 *
 * Input:
 * Input consists of information for several loans. Each loan consists of one
 * line containing the duration in months of the loan, the down payment, the
 * amount of the loan, and the number of depreciation records that follow. All
 * values are nonnegative, with loans being at most 100 months long and car
 * values at most $75,000. Since depreciation is not constant, the varying rates
 * are specified in a series of depreciation records. Each depreciation record
 * consists of one line with a month number and depreciation percentage, which
 * is more than 0 and less than 1. These are in strictly increasing order by
 * month, starting at month 0. Month 0 is the depreciation that applies
 * immediately after driving the car off the lot and is always present in the
 * data. All the other percentages are the amount of depreciation at the end of
 * the corresponding month. Not all months may be listed in the data. If a month
 * is not listed, then the previous depreciation percentage applies. The end of
 * the input is signalled by a negative loan duration - the other three values
 * will be present but indeterminate.
 *
 * For simplicity, we will assume a 0% interest loan, thus the car’s initial
 * value will be the loan amount plus the down payment. It is possible for a
 * car’s value and amount owed to be positive numbers less than $1.00. Do not
 * round values to a whole number of cents ($7,347.635 should not be rounded to
 * $7,347.64).
 *
 * Consider the first example below of borrowing $15,000 for 30 months. As the
 * buyer drives off the lot, he still owes $15,000, but the car has dropped in
 * value by 10% to $13,950. After 4 months, the buyer has made 4 payments, each
 * of $500, and the car has further depreciated 3% in months 1 and 2 and 0.2% in
 * months 3 and 4. At this time, the car is worth $13,073.10528 and the borrower
 * only owes $13,000.
 *
 * Output:
 * For each loan, the output is the number of complete months before the
 * borrower owes less than the car is worth. Note that English requires plurals
 * (5 months) on all values other than one (1 month).
 *
 * Solution:
 * This is a very simple question; you just need to follow the instructions.
 */

#include "Volume101/p10114.h"

struct p10114_Depreciation {
  Int64 month;
  Double rate;
};

Void p10114_main() {
  var depreciations = array_init(sizeof(struct p10114_Depreciation));
  
  var months = 0;
  var down_payment = 0.0;
  var loan = 0.0;
  var count = 0;
  while (
    scanf("%d %lf %lf %d", &months, &down_payment, &loan, &count) == 4 &&
    months >= 0
  ) {
    array_remove_all(depreciations, true);
    
    
    struct p10114_Depreciation depreciation;
    while (count--) {
      scanf("%lld %lf",&depreciation.month, &depreciation.rate);
      array_append(depreciations, &depreciation);
    }
    
    /* The car’s initial value will be the loan amount plus the down payment! */
    var car_value = loan + down_payment;
    
    var repayment = loan / months;
    var i = 0; /* months */
    var j = 0; /* depreciations */
    for (i = 0; i < months; i += 1) {
      if (j + 1 < depreciations->count) {
        array_read(depreciations, j + 1, &depreciation);
        if (depreciation.month <= i) {
          j += 1;
        }
      }
      array_read(depreciations, j, &depreciation);
      
      car_value -= car_value * depreciation.rate;
      
      if (loan <= car_value) {
        break;
      }
      
      loan -= repayment;
    }
    printf("%d month%s\n", i, i == 1 ? "" : "s");
  }
  
  array_deinit(depreciations);
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
