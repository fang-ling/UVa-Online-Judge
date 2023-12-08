//
//  458.c
//  hxy
//
//  Created by Fang Ling on 2023/12/8.
//

/*
 * 'J' = 'C' + 7
 */

#include <stdio.h>

#define var __auto_type

void main_458(void) {
  var c = (char)'0';
  while (scanf("%c", &c) == 1) {
    if (c != '\n') {
      c -= 7;
    }
    printf("%c", c);
  }
}
