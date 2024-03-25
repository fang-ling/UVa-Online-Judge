//
//  299.c
//  hxy
//
//  Created by Fang Ling on 2024/3/25.
//

#include <stdio.h>

#define var __auto_type

void main_299(void) {
  int A[64];
  
  var n = 0;
  scanf("%d", &n);
  while (n--) {
    var l = 0;
    scanf("%d", &l);
    var i = 0;
    for (i = 0; i < l; i += 1) {
      scanf("%d", &A[i]);
    }
    
    var count = 0;
    for (i = 0; i < l; i += 1) {
      var j = 0;
      for (j = i + 1; j < l; j += 1) {
        count += A[i] > A[j] ? 1 : 0;
      }
    }
    printf("Optimal train swapping takes %d swaps.\n", count);
  }
}
