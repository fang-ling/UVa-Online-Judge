//
//  10035.c
//  hxy
//
//  Created by Fang Ling on 2024/3/23.
//

#include <stdio.h>
#include <string.h>

#define var __auto_type

void main_10035(void) {
  char lhs[16];
  char rhs[16];
  char buf[16];
  while (scanf("%s %s", lhs, rhs) == 2) {
    var count_l = (int)strlen(lhs);
    var count_r = (int)strlen(rhs);
    if (count_l == 1 && count_r == 1 && lhs[0] == '0' && rhs[0] == '0') {
      break;
    }
    
    /* Addition */
    var carry = 0;
    var carry_count = 0;
    
    var i = 0;
    if (count_l != count_r) { /* Dont have the same length */
      var zero_count_l = 16 - 1 - count_l;
      for (i = 0; i < zero_count_l; i += 1) {
        buf[i] = '0';
      }
      count_l += zero_count_l;
      for (; i < count_l; i += 1) {
        buf[i] = lhs[i - zero_count_l];
      }
      buf[i] = '\0';
      strcpy(lhs, buf);
      
      var zero_count_r = 16 - 1 - count_r;
      for (i = 0; i < zero_count_r; i += 1) {
        buf[i] = '0';
      }
      count_r += zero_count_r;
      for (; i < count_r; i += 1) {
        buf[i] = rhs[i - zero_count_r];
      }
      buf[i] = '\0';
      strcpy(rhs, buf);
    }
    for (i = count_l - 1; i >= 0; i -= 1) {
      var sum = carry + lhs[i] - '0' + rhs[i] - '0';
      if (sum >= 10) {
        carry = 1;
        carry_count += 1;
      } else {
        carry = 0;
      }
    }
    if (carry_count == 0) {
      printf("No ");
    } else {
      printf("%d ", carry_count);
    }
    printf("carry operation");
    if (carry_count <= 1) {
      printf(".\n");
    } else {
      printf("s.\n");
    }
  }
}
