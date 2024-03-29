//
//  11332.c
//  hxy
//
//  Created by Fang Ling on 2024/3/29.
//

#include <stdio.h>

#define var __auto_type

static int f(int n) {
  var sum = 0;
  while (n != 0) {
    sum += n % 10;
    n /= 10;
  }
  return sum;
}

void main_11332(void) {
  var n = 0;
  while (scanf("%d", &n) == 1 && n != 0) {
    while ((n = f(n)) >= 10);
    printf("%d\n", n);
  }
}
