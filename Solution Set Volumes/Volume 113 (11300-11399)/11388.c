//
//  11388.c
//  hxy
//
//  Created by Fang Ling on 2024/3/31.
//

#include <stdio.h>

#define var __auto_type

void main_11388(void) {
  var t = 0;
  scanf("%d", &t);
  while (t--) {
    var a = 0;
    var b = 0;
    scanf("%d %d", &a, &b);
    
    if (b % a == 0) {
      printf("%d %d\n", a, b);
    } else {
      printf("-1\n");
    }
  }
}
