//
//  594.c
//  hxy
//
//  Created by Fang Ling on 2023/11/27.
//

/*
 * This program converts the given integer to the opposite endian by first
 * breaking it into four individual bytes. It then reconstructs the int by
 * putting the four bytes in reversed order.
 */

#include <stdio.h>

#define var __auto_type

void main_594(void) {
  var delta = 0;
  while (scanf("%d", &delta) == 1) {
    /*
     * MSB                                   LSB
     *    00000000 00000000 00000000 00000000
     */
    var mask = 0x000000FF;
    var byte0 = delta & mask;         /* LSB */
    var byte1 = (delta >> 8) & mask;
    var byte2 = (delta >> 16) & mask;
    var byte3 = (delta >> 24) & mask; /* MSB */
    /* Put it back in reverse order */
    var result = byte3 | (byte2 << 8) | (byte1 << 16) | (byte0 << 24);
    printf("%d converts to %d\n", delta, result);
  }
}
