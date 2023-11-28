//
//  12720.c
//  hxy
//
//  Created by Fang Ling on 2023/11/28.
//

/*
 * Break `A` into two logical halves: the first half is bounded by [0 ... mid1],
 * and the second half is bounded by [mid2 ..< count] in reversed order.
 * This ensures that mid1 and mid2 keep track of the middle value of 'A'.
 * As for updating the value of s, it can be observed that every time we append
 * a new bit `b`, we multiply s by 2 and add `b`.
 */

#include <stdio.h>
#include <string.h>

#define var __auto_type
#define P 1000000007

int s_12720;

void foo(const char* buf, int count, int mid1, int mid2) {
  var count1 = mid1 + 1 - 0;
  var count2 = count - mid2;
  if (count1 == 0 && count2 == 0) {
    return;
  }
  if (mid1 == mid2) { /* Special initial case */
    s_12720 = ((s_12720 % P << 1) + (buf[mid1] - '0')) % P;
    mid1 -= 1;
    mid2 += 1;
  } else if (count1 == count2) { /* Even case */
    /*
     * Both middle bits of A are compared. The bigger one (anyone in case of a
     * tie) is added to the end of S and removed from A.
     */
    if (buf[mid1] == '1') {
      s_12720 = ((s_12720 % P << 1) + (buf[mid1] - '0')) % P;
      mid1 -= 1;
    } else {
      s_12720 = ((s_12720 % P << 1) + (buf[mid2] - '0')) % P;
      mid2 += 1;
    }
  } else if (count1 > count2) { /* Odd case 1 */
    s_12720 = ((s_12720 % P << 1) + (buf[mid1] - '0')) % P;
    mid1 -= 1;
  } else { /* Odd case 2 */
    s_12720 = ((s_12720 % P << 1) + (buf[mid2] - '0')) % P;
    mid2 += 1;
  }
  foo(buf, count, mid1, mid2);
}

void main_12720(void) {
  char buf[100000 + 1];
  
  var T = 0;
  scanf("%d", &T);
  var CASE = 1;
  for (; CASE <= T; CASE += 1) {
    scanf("%s", buf);
    
    s_12720 = 0;
    var count = (int)strlen(buf);
    var mid1 = 0;
    var mid2 = 0;
    if (count % 2 == 1) { /* Odd case: mid1 == mid2 */
      mid1 = count / 2;
      mid2 = mid1;
    } else { /* Even case */
      mid2 = count / 2;
      mid1 = mid2 - 1;
    }
    foo(buf, count, mid1, mid2);
    printf("Case #%d: %d\n", CASE, s_12720);
  }
}
