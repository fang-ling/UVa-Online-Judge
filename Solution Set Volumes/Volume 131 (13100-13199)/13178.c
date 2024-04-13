//
//  13178.c
//  hxy
//
//  Created by Fang Ling on 2024/4/13.
//

#include <stdio.h>

#define var __auto_type
typedef long long int64;

void main_13178(void) {
  var n = 0;
  scanf("%d", &n);
  while (n--) {
    var x = 0ll;
    scanf("%lld", &x);
    printf("%s\n", (((1 + x) * x) / 2) % 3 == 0 ? "YES" : "NO");
  }
}
