//
//  11809.c
//  hxy
//
//  Created by Fang Ling on 2023/12/13.
//

/*
 * log10(A * 10^B) = log10(A) + log10(10^B)
 *                 = log10(A) + B
 *
 * log10(M * 2^E) = log10(M) + log10(2^E)
 *                = log10(M) + log2(2^E)/log2(10)
 *                = log10(M) + E/log2(10)
 *
 * Since A * 10^B == M * 2^E, we can calculate all possible combinations of M
 * and E and then compare them with the values of A and B.
 */

#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>

#define var __auto_type
#define epsilon 1e-6

void main_11809(void) {
  /* mantissa has an implicit leading one. */
  double man2dec[] = {
    0.5,         /* 0.(1)          M: 0 */
    0.75,        /* 0.(1)1         M: 1 */
    0.875,       /* 0.(1)11        M: 2 */
    0.9375,      /* 0.(1)111       M: 3 */
    0.96875,     /* 0.(1)1111      M: 4 */
    0.984375,    /* 0.(1)11111     M: 5 */
    0.9921875,   /* 0.(1)111111    M: 6 */
    0.99609375,  /* 0.(1)1111111   M: 7 */
    0.998046875, /* 0.(1)11111111  M: 8 */
    0.9990234375 /* 0.(1)111111111 M: 9 */
  };
  /* Answer in log scale. (log10 of the actual value) */
  double ans[10][31]; /* 0≤M≤9, 1≤E≤30 */
  /* Pre-compute all possible answers */
  var M = 0;
  for (M = 0; M <= 9; M += 1) {
    var E = 0;
    for (E = 1; E <= 30; E += 1) {
      /* log10(M * 2^E) = log10(M) + E/log2(10) */
      ans[M][E] = log10(man2dec[M]);
      var exp = (1 << E) - 1;
      ans[M][E] += (double)exp / log2(10);
    }
  }

  var A = 0.0;
  var B = 0.0;
  char delta[100];
  while (true) {
    scanf("%s", delta);
    *strchr(delta, 'e') = ' '; /* Change 'e' to ' ' */
    sscanf(delta, "%lf %lf", &A, &B);

    if (A == 0 && B == 0) {
      break;
    }
    /* log10(A * 10^B) = log10(A) + B */
    var value = log10(A) + B;
    for (M = 0; M <= 9; M += 1) {
      var E = 0;
      for (E = 1; E <= 30; E += 1) {
        if (fabs(value - ans[M][E]) <= epsilon) {
          printf("%d %d\n", M, E);
          goto eol;
        }
      }
    }
  eol:;
  }
}
