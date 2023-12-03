//
//  10055.c
//  hxy
//
//  Created by Fang Ling on 2023/12/3.
//

/*
 * A - B Problem.
 */

#include <stdio.h>

#define var __auto_type

void main_10055(void) {
  var a = 0ll;
  var b = 0ll;
  while (scanf("%lld %lld", &a, &b) == 2) {
    printf("%lld\n", a - b > 0 ? a - b : b - a);
  }
}
