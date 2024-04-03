//
//  113.c
//  hxy
//
//  Created by Fang Ling on 2024/4/3.
//

#include <stdio.h>
#include <math.h>

#define var __auto_type

void main_113(void) {
  var n = 0.0;
  var p = 0.0;
  while (scanf("%lf %lf", &n, &p) == 2) {
    printf("%.0lf\n", pow(p, 1 / n));
  }
}
