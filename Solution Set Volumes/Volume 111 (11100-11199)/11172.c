//
//  11172.c
//  hxy
//
//  Created by Fang Ling on 2023/12/7.
//

/*
 * 1. a > b, prints '>'
 * 2. a < b, prints '<'
 * 3. otherwise, prints '='
 */

#include <stdio.h>

#define var __auto_type

void main_11172(void) {
  var t = 0;
  scanf("%d", &t);
  while (t--) {
    var a = 0;
    var b = 0;
    scanf("%d %d", &a, &b);

    if (a > b) {
      printf(">\n");
    } else if (a < b) {
      printf("<\n");
    } else {
      printf("=\n");
    }
  }
}
