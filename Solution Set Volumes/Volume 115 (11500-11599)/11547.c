//
//  11547.c
//  hxy
//
//  Created by Fang Ling on 2024/3/27.
//

#include <stdio.h>

#define var __auto_type

void main_11547(void) {
  var t = 0;
  scanf("%d", &t);
  while (t--) {
    var n = 0;
    scanf("%d", &n);
    n = (n * 63 + 7492) * 5 - 498;
    n /= 10;
    printf("%d\n", n % 10 > 0 ? n % 10 : -(n % 10));
  }
}
