//
//  10071.c
//  hxy
//
//  Created by Fang Ling on 2023/12/6.
//

/*
 * displacement = 2 * velocity * time
 */

#include <stdio.h>

#define var __auto_type

void main_10071(void) {
  var v = 0;
  var t = 0;
  while (scanf("%d %d", &v, &t) == 2) {
    printf("%d\n", 2 * v * t);
  }
}
