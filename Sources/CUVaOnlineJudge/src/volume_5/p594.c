/*===----------------------------------------------------------------------===*/
/*                                                        ___   ___           */
/* p594.c                                               /'___\ /\_ \          */
/*                                                     /\ \__/ \//\ \         */
/* Author: Fang Ling (fangling@fangl.ing)              \ \ ,__\  \ \ \        */
/* Date: September 15, 2024                             \ \ \_/__ \_\ \_  __  */
/*                                                       \ \_\/\_\/\____\/\_\ */
/*                                                        \/_/\/_/\/____/\/_/ */
/*===----------------------------------------------------------------------===*/

/*
 * This source file is part of the hxy open source project
 *
 * Copyright (c) 2024 Fang Ling All Rights Reserved.
 *
 * Use of this source code is governed by the Apache License, Version 2.0
 * that can be found in the LICENSE file in the root of the source tree.
 * This source code may include problem descriptions from some online judges,
 * which have their own licensing terms.
 */

/*
 * 594 One Little, Two Little, Three Little Endians
 *
 * Writing programs that are completely portable across different operating 
 * systems, operating system versions and hardware platforms is a challenging
 * task. One of the difficulties encountered is a result of decisions made by
 * hardware manufacturers about how they will store integer data in memory.
 * Because these representations can differ from machine to machine, sharing
 * binary data often cannot be done without modifying the way in which the data
 * is stored or the way in which it is handled by one or more of the platforms.
 *
 * Fortunately there is near-universal agreement among hardware manufacturers
 * that addressable memory be ordered into 8-bit bytes. For integer data values
 * that require more than 8-bits, such as the typical 2- byte, 4-byte, and
 * 8-byte integer types available on most modern hardware, there is no such
 * agreement and two incompatible storage schemes exist. The first stores
 * integers as groups of consecutive 8-bit bytes with the least significant byte
 * occupying the lowest memory location within the group and the most
 * significant byte occupying the highest memory location. The second is just
 * the reverse; the least significant byte is stored in the highest memory
 * location within the group, and the most significant byte is stored in the
 * lowest memory location. The computing industry has dubbed these schemes
 * Little Endian and Big Endian, respectively. There is also near-universal
 * agreement that signed integers are stored using "two's complement"
 * representation, and you may assume that this is the case.
 *
 * When binary integer data is shared between a Little Endian and Big Endian
 * machine, a data conversion must be performed which involves reversing the
 * bytes of the data. Once the bytes have been reversed the integer is then
 * correctly interpreted by the hardware as the original value from the 
 * opposite-endian machine. The object of this problem is to write a program
 * that will read a list of integers and report the integers that the binary
 * representations of the input integers would represent on an opposite-endian
 * machine.
 *
 * Input:
 * The input will consist of a list integers. The end of the input file marks
 * the end of the list. All input integers can be represented as a 32-bit signed
 * integer value. That is, the input integers will be in the range -2147483648
 * to 2147483647.
 *
 * Output:
 * For each input integer a single line should be printed to the output file.
 * The line should contain the input integer followed by the phrase
 * 'converts to' followed by one space followed the other-endian value.
 *
 * Solution:
 * This program converts the given integer to the opposite endian by first
 * breaking it into four individual bytes. It then reconstructs the integer by
 * putting the four bytes in reversed order.
 */

#include "volume_5/p594.h"

Void main_p594() {
  var input = 0;
  while (scanf("%d", &input) == 1) {
    let mask = 0x000000FF;
    let byte0 = input & mask;         /* LSB */
    let byte1 = (input >> 8) & mask;
    let byte2 = (input >> 16) & mask;
    let byte3 = (input >> 24) & mask; /* MSB */
    /* Put it back in reverse order */
    let output = byte3 | (byte2 << 8) | (byte1 << 16) | (byte0 << 24);
    
    printf("%d converts to %d\n", input, output);
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
