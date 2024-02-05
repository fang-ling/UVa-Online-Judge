//
//  1591.c
//  hxy
//
//  Created by Fang Ling on 2024/2/5.
//

#include <stdio.h>
#include <stdint.h>

#define var __auto_type

void main_1591(void) {
  var n = 0;
  var s_p = 0;
  var s_q = 0;
  while (scanf("%d %d %d", &n, &s_p, &s_q) == 3) {
    var alpha = (long long)(n - 1) * s_p;
    var K = INT64_MAX;
    
    var A = 0;
    var B = 0;
    var i = 0;
    for (i = 0; i < 32; i += 1) {
      var j = 0;
      for (j = 0; j < 32; j += 1) {
        /* 
         * Q'(n-1) = (P(n-1) + P(n-1) << A) >> B
         * Q'(n-1) = ((n-1)*s_p + n-1*s_p << A) >> B
         * Q'(n) = Q'(n-1) + s_q
         */
        var delta = ((alpha + (alpha << i)) >> j) + s_q;
        if (delta >= n * s_q && delta < K) {
          K = delta;
          A = i;
          B = j;
        }
      }
    }
    printf("%lld %d %d\n", K, A, B);
  }
}
