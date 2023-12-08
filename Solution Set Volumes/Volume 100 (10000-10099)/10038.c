//
//  10038.c
//  hxy
//
//  Created by Fang Ling on 2023/12/8.
//

/*
 * Use a boolean table to keep track of the unique occurence of the number.
 */

#include <stdio.h>
#include <stdbool.h>

#define var __auto_type

static int abs_10038(int x) {
  return x > 0 ? x : -x;
}

void main_10038(void) {
  int nums[3000];
  bool jolly_tbl[3000];

  var n = 0;
  while (scanf("%d", &n) == 1) {
    var i = 0;
    for (i = 0; i < n; i += 1) {
      scanf("%d", &nums[i]);
      jolly_tbl[i] = false;
    }
    
    var is_jolly = true;
    for (i = 1; i < n; i += 1) {
      var delta = abs_10038(nums[i] - nums[i - 1]);
      if (delta >= 1 && delta < n && jolly_tbl[delta] == false) {
        jolly_tbl[delta] = true;
      } else {
        is_jolly = false;
        break;
      }
    }

    printf(is_jolly ? "Jolly\n" : "Not jolly\n");
  }
}
