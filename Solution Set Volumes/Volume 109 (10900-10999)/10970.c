//
//  10970.c
//  hxy
//
//  Created by Fang Ling on 2024/4/3.
//

#include <stdio.h>

#define var __auto_type

void main_10970(void) {
  var m = 0;
  var n = 0;
  while (scanf("%d %d", &m, &n) == 2) {
    printf("%d\n", m * (n - 1) + (m - 1));
  }
}
