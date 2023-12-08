//
//  10783.c
//  hxy
//
//  Created by Fang Ling on 2023/12/8.
//

/* A simple for-loop will solve the problem. */

#include <stdio.h>

#define var __auto_type

void main_10783(void) {
  var T = 0;
  scanf("%d", &T);
  var i = 0;
  for (i = 1; i <= T; i += 1) {
    var a = 0;
    var b = 0;
    scanf("%d\n%d", &a, &b);

    var sum = 0;
    var j = 0;
    for (j = a; j <= b; j += 1) {
      if (j % 2 == 1) {
        sum += j;
      }
    }

    printf("Case %d: %d\n", i, sum);
  }
}
