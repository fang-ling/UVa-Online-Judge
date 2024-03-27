//
//  11498.c
//  hxy
//
//  Created by Fang Ling on 2024/3/27.
//

#include <stdio.h>

#define var __auto_type

void main_11498(void) {
  var k = 0;
  while (scanf("%d", &k) == 1 && k != 0) {
    var ox = 0;
    var oy = 0;
    scanf("%d %d", &ox, &oy);
    while (k--) {
      var x = 0;
      var y = 0;
      scanf("%d %d", &x, &y);
      
      var dx = x - ox;
      var dy = y - oy;
      if (dx > 0 && dy > 0) {
        printf("NE\n");
      } else if (dx > 0 && dy < 0) {
        printf("SE\n");
      } else if (dx < 0 && dy > 0) {
        printf("NO\n");
      } else if (dx < 0 && dy < 0) {
        printf("SO\n");
      } else {
        printf("divisa\n");
      }
    }
  }
}
