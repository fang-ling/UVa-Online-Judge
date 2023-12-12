//
//  1588.c
//  hxy
//
//  Created by Fang Ling on 2023/12/12.
//

/*
 * =====>
 *
 * +----------+
 * |1      111|   A
 * +-+2222+---+
 *   +----+
 *
 * +-+    +---+
 * |2+----+222|   B
 * |2 1111 222|
 * +----------+
 *
 * Worst case: length = A.length + B.length
 */

#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define var __auto_type
#define N 200 + 1

void main_1588(void) {
  char input_A[100 + 1];
  char input_B[100 + 1];
  char A[N];
  char B[N];
  while (scanf("%s\n%s", input_A, input_B) == 2) {
    var i = 0;
    for (i = 0; i < N; i += 1) {
      A[i] = '0';
      B[i] = '0';
    }
    /*
     * A
     * B
     */
    var count_a = (int)strlen(input_A);
    var count_b = (int)strlen(input_B);
    for (i = 0; i < count_a; i += 1) {
      A[i] = input_A[i];
    }
    for (i = 0; i < count_b; i += 1) {
      B[i] = input_B[i];
    }
    /* Try every possible starting position. */
    var is_ok = true;
    var ans1 = 0;
    var j = 0;
    for (j = 0; j <= count_b; j += 1) {
      is_ok = true;
      for (i = 0; i < count_a; i += 1) {
        if (A[i] - '0' + B[i + j] - '0' > 3) {
          is_ok = false;
          break;
        }
      }
      if (is_ok) {
        ans1 = j + count_a < count_b ? count_b : j + count_a;
        break;
      }
    }

    /*
     * B
     * A
     */
    for (i = 0; i < N; i += 1) {
      A[i] = '0';
      B[i] = '0';
    }
    count_b = (int)strlen(input_A);
    count_a = (int)strlen(input_B);
    for (i = 0; i < count_a; i += 1) {
      A[i] = input_B[i];
    }
    for (i = 0; i < count_b; i += 1) {
      B[i] = input_A[i];
    }
    /* Try every possible starting position. */
    var ans2 = 0;
    for (j = 0; j <= count_b; j += 1) {
      is_ok = true;
      for (i = 0; i < count_a; i += 1) {
        if (A[i] - '0' + B[i + j] - '0' > 3) {
          is_ok = false;
          break;
        }
      }
      if (is_ok) {
        ans2 = j + count_a < count_b ? count_b : j + count_a;
        break;
      }
    }

    printf("%d\n", ans1 > ans2 ? ans2 : ans1);
  }
}
