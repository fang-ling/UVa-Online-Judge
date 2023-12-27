//
//  133.c
//  hxy
//
//  Created by Fang Ling on 2023/12/27.
//

/*
 * This problem is straightforward, simply utilize an array to simulate the
 * dole queue.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define var __auto_type

void main_133(void) {
  bool queue[20 + 2];

  var n = 0;
  var k = 0;
  var m = 0;
  while (scanf("%d %d %d", &n, &k, &m) == 3 && n != 0) {
    var current_size = n;
    var i = 0;
    for (i = 0; i <= n + 1; i += 1) {
      queue[i] = true;
    }

    var cw = 0;
    var ccw = n + 1;
    while (current_size > 0) {
      /* Clockwise */
      for (i = 0; i < k; i += 1) {
        cw += 1;
        while (true) {
          if (cw > n) {
            cw -= n;
          }
          if (queue[cw] != false) {
            break;
          }
          cw += 1;
        }
      }
      /* Counterclockwise */
      for (i = 0; i < m; i += 1) {
        ccw -= 1;
        while (true) {
          if (ccw < 1) {
            ccw += n;
          }
          if (queue[ccw] != false) {
            break;
          }
          ccw -= 1;
        }
      }
      queue[cw] = false;
      queue[ccw] = false;
      if (cw == ccw) {
        printf("%3d", cw);
        current_size -= 1;
      } else {
        printf("%3d%3d", cw, ccw);
        current_size -= 2;
      }
      if (current_size > 0) {
        printf(",");
      }
    }
    printf("\n");
  }
}
