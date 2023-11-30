//
//  1583.c
//  hxy
//
//  Created by Fang Ling on 2023/11/30.
//

/*
 * For every integer n, calculate its digit sum and use that sum to maintain the
 * smallest generator table.
 */

#include <stdio.h>
#include <stdlib.h>

#define var __auto_type

static int digit_sum_1583(int n) {
  var sum = n;
  while (n != 0) {
    sum += n % 10;
    n /= 10;
  }
  return sum;
}

void main_1583(void) {
  var TBL = (int*)malloc(sizeof(int) * (100000 + 1));
  var i = 0;
  for (i = 0; i <= 100000; i += 1) {
    TBL[i] = 0x7fffffff;
  }
  for (i = 1; i <= 100000; i += 1) {
    var sum = digit_sum_1583(i);
    if (TBL[sum] > i) {
      TBL[sum] = i;
    }
  }

  var T = 0;
  scanf("%d", &T);
  while (T--) {
    var delta = 0;
    scanf("%d", &delta);
    printf("%d\n", TBL[delta] == 0x7fffffff ? 0 : TBL[delta]);
  }
  free(TBL);
}
