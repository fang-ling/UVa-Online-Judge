//
//  100.c
//  hxy
//
//  Created by Fang Ling on 2023/12/2.
//

/*
 * Use a helper function to calcualte the cycle length of given number. Then 
 * pre-calculate all the cycle lengths for numbers in the range of
 * 0 < n < 10,000. Lastly, we can find the maximum cycle length within the given
 * range [i, j] and consider it as the answer.
 */

#include <stdio.h>
#include <stdbool.h>

#define var __auto_type

int three_n_plus_one_length_100(int n) {
  if (n == 0) {
    return 0;
  }
  var count = 1; /* including the 1 */
  while (n != 1) {
    count += 1;
    if (n % 2 == 1) {
      n = 3 * n + 1;
    } else {
      n /= 2;
    }
  }
  return count;
}

void main_100(void) {
  var i = 0;
  var j = 0;
  while (scanf("%d %d", &i, &j) == 2) {
    var is_swapped = false;
    if (i > j) {
      i = i ^ j;
      j = i ^ j;
      i = i ^ j;
      is_swapped = true;
    }
    var max = 0;
    var delta = 0;
    var k = 0;
    for (k = i; k <= j; k += 1) {
      delta = three_n_plus_one_length_100(k);
      max = max < delta ? delta : max;
    }
    if (is_swapped) {
      i = i ^ j;
      j = i ^ j;
      i = i ^ j;
    }
    printf("%d %d %d\n", i, j, max);
  }
}
